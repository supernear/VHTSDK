package com.goscamsdkdemo.ws;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.NonNull;
import android.text.TextUtils;

import com.google.gson.Gson;
import com.gos.platform.api.PlatformApiParser;
import com.gos.platform.api.UlifeResultParser;
import com.gos.platform.api.contact.PushType;
import com.gos.platform.api.request.AppHeartRequest;
import com.gos.platform.api.request.GetDevPushStatusRequest;
import com.gos.platform.api.request.QueryMsgInfoRequest;
import com.gos.platform.api.request.RegistPushRequest;
import com.gos.platform.api.request.Request;
import com.gos.platform.api.request.SetDevPushStatusRequest;
import com.gos.platform.api.request.UnRegistPushRequest;
import com.gos.platform.api.result.AppHeartResult;
import com.gos.platform.api.result.PlatResult;
import com.gos.platform.api.result.PlatResult.PlatCmd;
import com.gos.platform.api.result.PushMsgResult;
import com.gos.platform.device.domain.DevAlarmInfo;
import com.gos.platform.device.receiver.PushMessageBroadReceiver;
import com.gos.platform.device.result.DevResult;
import com.gos.platform.device.result.DevResult.DevCmd;
import com.gos.platform.device.ulife.request.FormatDevSdCardRequest;
import com.gos.platform.device.ulife.request.GetAllAlarmListRequest;
import com.gos.platform.device.ulife.request.GetAllRecordListRequest;
import com.gos.platform.device.ulife.request.UlifeDevRequest;
import com.gos.platform.device.ulife.response.DevResponse;
import com.goscamsdkdemo.GApplication;
import com.goscamsdkdemo.util.dbg;

import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import okhttp3.Response;
import okhttp3.WebSocket;
import okhttp3.WebSocketListener;
import okio.ByteString;

import static com.gos.platform.api.BaseParser.NETSDK_EVENT_CONN_SUCCESS;
import static com.gos.platform.api.BaseParser.NETSDK_EVENT_GOS_RECV;

public class WsManager extends WebSocketListener {
    private final static String TAG = "WsManager";
    private static WsManager mInstance;
    private WsStatus mStatus;
    private WebSocket mWebSocket;
    private OkHttpClient mOkHttpClient;
    private int reconnectCount = 0;//重连次数
    private final long minInterval = 3000;//重连最小时间间隔
    private final long maxInterval = 60000;//重连最大时间间隔
    private final String mWsUrl = "ws://119.23.124.137:8000";
    private NetStatusReceiver mNetStatusReceiver;
    public static final String DEFAULT_SESSION = "DEFAULT_SESSION";//用于用户没有登录情况下心跳包的发送
    private String mSessionEx = DEFAULT_SESSION;
    private String mSessionId = "-10000";
    private boolean isInit;
    private Context mContext;

    private ScheduledExecutorService mExecutor = Executors.newSingleThreadScheduledExecutor();
    private static final int CODE_TIMEOUT = -101;
    private static final int PLAT_HANDLER = 101;
    private static final int DEV_HANDLER = 102;
    private Handler mHandler = new Handler(Looper.getMainLooper()){
        @Override
        public void handleMessage(@NonNull Message msg) {
            dbg.D(TAG, "handleMessage="+msg.obj);
            int what = msg.what;
            //心跳
            if(PLAT_HANDLER == what && ((PlatResult)msg.obj).getPlatCmd() == PlatCmd.appHeart){
                AppHeartResult result = (AppHeartResult) msg.obj;
                int code = result.getResponseCode();
                if(code == CODE_TIMEOUT){
                    heartbeatFailCount++;
                    if (heartbeatFailCount >= 3) {
                        reconnect();
                    }
                }else {
                    heartbeatFailCount = 0;
                }
                //避免重复
                mHandler.removeCallbacks(heartbeatTask);
                mHandler.postDelayed(heartbeatTask, HEARTBEAT_INTERVAL);
            }

            for(WeakReference<ICallback> w : eventCallbacks){
                ICallback callback = w.get();
                if(callback != null){
                    if(PLAT_HANDLER == what){
                        callback.OnEvent((PlatResult) msg.obj,null);
                    }else if(DEV_HANDLER == what){
                        callback.OnEvent(null, (DevResult) msg.obj);
                    }
                }
            }
        }
    };

    public static WsManager getInstance(){
        if(mInstance == null){
            synchronized (WsManager.class){
                if(mInstance == null){
                    mInstance = new WsManager();
                }
            }
        }
        return mInstance;
    }

    private WsManager(){

    }

    public void init(Context context){
        dbg.D(TAG, "init,isInit="+isInit);
        if(!isInit){
            mContext = context;
            isInit = true;
            mOkHttpClient = new OkHttpClient.Builder()
                    .readTimeout(3, TimeUnit.SECONDS)//设置读取超时时间
                    .writeTimeout(3, TimeUnit.SECONDS)//设置写的超时时间
                    .connectTimeout(3, TimeUnit.SECONDS)//设置连接超时时间
                    .build();
            okhttp3.Request request = new okhttp3.Request.Builder().url(mWsUrl).build();
            setStatus(WsStatus.CONNECTING);
            mWebSocket = mOkHttpClient.newWebSocket(request, this);
            dbg.D(TAG, "init, mWsUrl = " + mWsUrl);
            //注册网络监听
            mNetStatusReceiver = new NetStatusReceiver();
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
            mContext.registerReceiver(mNetStatusReceiver, intentFilter);
        }
    }

    public void unInit(){
        dbg.D(TAG, "unInit,isInit="+isInit);
        if(isInit){
            isInit = false;
            cancelHeartbeat();
            cancelReconnect();
            mWebSocket.cancel();
            mContext.unregisterReceiver(mNetStatusReceiver);
        }
    }

    private void cancelReconnect() {
        dbg.D(TAG, "cancelReconnect");
        reconnectCount = 0;
        mHandler.removeCallbacks(mReconnectTask);
    }

    public void reconnect(){
        dbg.D(TAG, "reconnect,isInit="+isInit+",mStatus="+mStatus+",mWebSocket="+mWebSocket);
        if (!isNetConnect()) {
            reconnectCount = 0;
            return;
        }

        if (mWebSocket != null && isInit &&
                getStatus() != WsStatus.CONNECT_SUCCESS &&
                getStatus() != WsStatus.CONNECTING) {//不是正在重连状态
            reconnectCount++;
            setStatus(WsStatus.CONNECTING);
            //取消心跳
            cancelHeartbeat();

            long reconnectTime = minInterval;
            if (reconnectCount > 3) {
                long temp = minInterval * (reconnectCount - 2);
                reconnectTime = temp > maxInterval ? maxInterval : temp;
            }
            dbg.D(TAG, "reconnect, reconnectCount="+reconnectCount+",reconnectTime="+reconnectTime);
            mHandler.postDelayed(mReconnectTask, reconnectTime);
        }
    }

    private Runnable mReconnectTask = new Runnable() {

        @Override
        public void run() {
            try {
                dbg.D(TAG, "mReconnectTask, run,mWsUrl="+mWsUrl);
                okhttp3.Request request = new okhttp3.Request.Builder().url(mWsUrl).build();
                mWebSocket = mOkHttpClient.newWebSocket(request, WsManager.this);
            } catch (Exception e) {
                e.printStackTrace();
                dbg.D(TAG, "mReconnectTask, run,ex="+e.getLocalizedMessage());
            }
        }
    };

    public void updateSession(String sessionEx, String sessionId){
        this.mSessionId = sessionId;
        this.mSessionEx = sessionEx;
        cancelHeartbeat();
        startHeartbeat(0);
    }

    private void startHeartbeat(long delay){
        dbg.D(TAG, "startHeartbeat");
        mHandler.postDelayed(heartbeatTask, delay);
    }

    private void cancelHeartbeat(){
        dbg.D(TAG, "cancelHeartbeat");
        heartbeatFailCount = 0;
        mHandler.removeCallbacks(heartbeatTask);
    }

    private static final long HEARTBEAT_INTERVAL = 30000;//心跳间隔
    private static final int REQUEST_TIMEOUT = 10000;//请求超时时间
    private int heartbeatFailCount = 0;
    private Runnable heartbeatTask = new Runnable() {
        @Override
        public void run() {
            String sessionIdEx = mSessionEx;
            String sessionId = mSessionId;
            AppHeartRequest request = new AppHeartRequest(sessionIdEx,sessionId);
            dbg.D(TAG, "heartbeatTask run, data=" + request.toJSON());
            sendPlat(PlatCmd.appHeart, request, REQUEST_TIMEOUT, 1);
        }
    };

    private void setStatus(WsStatus status){
        dbg.D(TAG, "setStatus, status=" + status);
        mStatus = status;
    }


    private WsStatus getStatus() {
        dbg.D(TAG, "getStatus, status=" + mStatus);
        return mStatus;
    }


    @Override
    public void onOpen(WebSocket webSocket, Response response) {
        dbg.D(TAG, "onOpen, code="+response.code());
        setStatus(WsStatus.CONNECT_SUCCESS);
        cancelReconnect();
        PlatResult platResult = PlatformApiParser.parser(null, NETSDK_EVENT_CONN_SUCCESS, 0, null, 0, null);
        mHandler.obtainMessage(PLAT_HANDLER, platResult).sendToTarget();
        startHeartbeat(HEARTBEAT_INTERVAL);
    }

    @Override
    public void onClosed(WebSocket webSocket, int code, String reason) {
        dbg.D(TAG, "onClosed, code="+code+",reason="+reason);
        setStatus(WsStatus.CONNECT_FAIL);
        reconnect();
    }

    @Override
    public void onClosing(WebSocket webSocket, int code, String reason) {
        dbg.D(TAG, "onClosing, code="+code+",reason="+reason);
        setStatus(WsStatus.CONNECT_FAIL);
    }

    @Override
    public void onFailure(WebSocket webSocket, Throwable t, Response response) {
        dbg.D(TAG, "onFailure, code="+(response!=null?response.code():20000));
        setStatus(WsStatus.CONNECT_FAIL);
        reconnect();
    }

    @Override
    public void onMessage(WebSocket webSocket, String text) {
        dbg.D(TAG, "onMessage, text="+text);
        Gson gson = new Gson();
        DevResponse baseResponse = gson.fromJson(text, DevResponse.class);
        if(baseResponse != null){
            if(TextUtils.equals(baseResponse.MessageType, Request.MsgType.PushMsgRequest)){
                //长连接设备推送
                PushMsgResult res = new PushMsgResult(NETSDK_EVENT_GOS_RECV, 0, text);
                DevAlarmInfo alarmInfo = res.getAlarmInfo();
                alarmInfo.pushType = PushType.MPS;
                Intent intent = new Intent();
                intent.setAction(PushMessageBroadReceiver.EXTRA_PUSHMSG_ACTION);
                intent.putExtra(PushMessageBroadReceiver.EXTRA_PUSH_MSG, alarmInfo);
                intent.setComponent( new ComponentName(mContext.getPackageName() ,
                        "com.goscam.ulifeplus.receiver.UlifePushMsgBroadReceiver"));
                mContext.sendBroadcast(intent);


            } else if(TextUtils.equals(baseResponse.MessageType, Request.MsgType.NotifyDeviceStatus)){
                //设备在线状态场链接设备告知
                PlatResult platResult = PlatformApiParser.parser(null, NETSDK_EVENT_GOS_RECV, 0, text, 0, null);
                mHandler.obtainMessage(PLAT_HANDLER, platResult).sendToTarget();


            } else if(TextUtils.equals(baseResponse.MessageType, Request.MsgType.BypassParamResponse)){
                //设备平台数据
                DevResult devResult = UlifeResultParser.parser(NETSDK_EVENT_GOS_RECV, 0, text, 0, null);
                if(devResult != null){
                    devResult.setDeviceId(baseResponse.Body.DeviceId);
                    DevCmdI cmdI = DevCmdI.create(devResult.getDevCmd(), baseResponse.Body.DeviceId);
                    CallbackWrapper callbackWrapper = devCallbacks.remove(cmdI);
                    if(callbackWrapper != null){
                        callbackWrapper.getTimeoutTask().cancel(true);
                        callbackWrapper.getTempCallback().onSuccess(devResult);
                    }else{
                        if(devResult.getDevCmd() == DevCmd.getAllAlarmList
                                || devResult.getDevCmd() == DevCmd.getAllRecordList){
                            mHandler.obtainMessage(DEV_HANDLER, devResult).sendToTarget();
                        }
                    }
                }

            } else {
                //平台数据
                PlatResult platResult = PlatformApiParser.parser(null, NETSDK_EVENT_GOS_RECV, 0, text, 0, null);
                if(platResult != null){
                    CallbackWrapper callbackWrapper = platCallbacks.remove(platResult.getPlatCmd());
                    if(callbackWrapper != null){
                        callbackWrapper.getTimeoutTask().cancel(true);
                        callbackWrapper.getTempCallback().onSuccess(platResult);
                    }
                }
            }
        }
    }

    @Override
    public void onMessage(WebSocket webSocket, ByteString bytes) {
        dbg.D(TAG, "onMessage, bytes="+bytes);
    }

    public enum WsStatus {
        CONNECT_SUCCESS,//连接成功
        CONNECT_FAIL,//连接失败
        CONNECTING;//正在连接
    }

    private boolean isNetConnect() {
        ConnectivityManager connectivity = (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (connectivity != null) {
            NetworkInfo info = connectivity.getActiveNetworkInfo();
            if (info != null && info.isConnected()) {
                if (info.getState() == NetworkInfo.State.CONNECTED) {
                    return true;
                }
            }
        }
        return false;
    }

    protected ConcurrentLinkedQueue<WeakReference<ICallback>> eventCallbacks = new ConcurrentLinkedQueue<>();
    public void addICallback(ICallback listener) {
        for(WeakReference<ICallback> w : eventCallbacks){
            ICallback callback = w.get();
            if(callback == listener){
                return;
            }
        }
        if(listener != null)
            eventCallbacks.add(new WeakReference<>(listener));
    }

    public void removeICallback(ICallback listener) {
        for(WeakReference<ICallback> w : eventCallbacks){
            ICallback callback = w.get();
            if(callback == listener || callback == null){
                eventCallbacks.remove(w);
            }
        }
    }

    public interface ICallback{
        void OnEvent(PlatResult platResult, DevResult devResult);
    }


    private Map<PlatCmd, CallbackWrapper<PlatCmd>> platCallbacks = new HashMap<>();
    //平台命令发送
    public int sendPlat(final PlatCmd cmd, Request request, final long timeOut, int reqCount){
        dbg.D(TAG, "sendPlat, cmd="+cmd+",request="+request.toJSON()+",timeOut="+timeOut+",reqCount="+reqCount);
        if(!isNetConnect()){
            PlatResult platResult = PlatformApiParser.parser(null, NETSDK_EVENT_GOS_RECV, CODE_TIMEOUT, request.toJSON(), 0, null);
            mHandler.obtainMessage(PLAT_HANDLER, platResult).sendToTarget();
            return -1;
        }

        //同一个请求只设置一个超时
        CallbackWrapper callbackWrapper = platCallbacks.get(cmd);
        dbg.D(TAG, "sendPlat, callbackWrapper=" + callbackWrapper);
        if(callbackWrapper != null){
            //取消超时任务
            callbackWrapper.timeoutTask.cancel(true);
            platCallbacks.remove(cmd);
        }

        //设置超时回调
        ScheduledFuture scheduledFuture = mExecutor.schedule(new Runnable() {
            @Override
            public void run() {
                CallbackWrapper wrapper = platCallbacks.remove(cmd);
                dbg.D(TAG, "scheduledFuture run, wrapper=" + wrapper);
                if (wrapper != null) {
                    dbg.D(TAG, "scheduledFuture run, data=" + wrapper.getRequest().toJSON());
                    wrapper.getTempCallback().onTimeout(wrapper.getRequest(), wrapper.getCmd());
                }
            }
        }, timeOut, TimeUnit.MILLISECONDS);

        IWsCallback temp = new IWsCallback<PlatResult, PlatCmd>() {
            @Override
            public void onSuccess(PlatResult data) {
                mHandler.obtainMessage(PLAT_HANDLER, data).sendToTarget();
            }

            @Override
            public void onTimeout(Request request, PlatCmd cmd) {
                dbg.D(TAG, "IWsCallback onTimeout, request=" + request.toJSON() + ",requestCount="+request.requestCount);
                if (request.requestCount > 3) {
                    //-101请求超时
                    PlatResult platResult = PlatformApiParser.parser(null, NETSDK_EVENT_GOS_RECV, CODE_TIMEOUT, request.toJSON(), 0, null);
                    onSuccess(platResult);
                } else {
                    sendPlat(cmd, request, timeOut, request.requestCount + 1);
                }
            }
        };

        dbg.D(TAG, "sendPlat send, cmd="+cmd);
        request.requestCount = reqCount;
        platCallbacks.put(cmd, new CallbackWrapper<>(cmd, temp, scheduledFuture, request));
        mWebSocket.send(request.toJSON());
        return 0;
    }

    public interface IWsCallback<T, A>{
        void onSuccess(T data);
        void onTimeout(Request request, A cmd);
    }

    public class CallbackWrapper<T> {

        private T cmd;
        private final IWsCallback tempCallback;
        private final ScheduledFuture timeoutTask;
        private final Request request;

        public CallbackWrapper(T cmd, IWsCallback tempCallback, ScheduledFuture timeoutTask, Request request) {
            this.cmd = cmd;
            this.tempCallback = tempCallback;
            this.timeoutTask = timeoutTask;
            this.request = request;
        }

        public IWsCallback getTempCallback() {
            return tempCallback;
        }

        public ScheduledFuture getTimeoutTask() {
            return timeoutTask;
        }

        public Request getRequest() {
            return request;
        }

        public T getCmd(){
            return cmd;
        }
    }

    private static class DevCmdI{
        public DevCmd cmd;
        public String deviceID;

        public static DevCmdI create(DevCmd cmd, String deviceID){
            DevCmdI cmdI = new DevCmdI();
            cmdI.cmd = cmd;
            cmdI.deviceID = deviceID;
            return cmdI;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            DevCmdI devCmdI = (DevCmdI) o;
            return cmd == devCmdI.cmd &&
                    deviceID.equals(devCmdI.deviceID);
        }

        @Override
        public int hashCode() {
            return Objects.hash(cmd, deviceID);
        }
    }

    private Map<DevCmdI, CallbackWrapper> devCallbacks = new HashMap<>();
    //平台命令发送
    public int sendDev(DevCmd cmd, String deviceID, Request request, final long timeOut, int reqCount){
        dbg.D(TAG, "sendDev, cmd="+cmd+",request="+request.toJSON()+",timeOut="+timeOut+",reqCount="+reqCount);
        if(!isNetConnect()){
            DevResult devResult = UlifeResultParser.parser(NETSDK_EVENT_GOS_RECV, CODE_TIMEOUT, request.toJSON(), 0, null);
            devResult.setDeviceId(deviceID);
            mHandler.obtainMessage(DEV_HANDLER, devResult).sendToTarget();
            return -1;
        }

        final DevCmdI cmdI = DevCmdI.create(cmd, deviceID);
        //同一个请求只设置一个超时
        CallbackWrapper callbackWrapper = devCallbacks.get(cmdI);
        if(callbackWrapper != null){
            //取消超时任务
            callbackWrapper.timeoutTask.cancel(true);
            devCallbacks.remove(cmdI);
        }

        //设置超时回调
        ScheduledFuture scheduledFuture = mExecutor.schedule(new Runnable() {
            @Override
            public void run() {
                CallbackWrapper wrapper = devCallbacks.remove(cmdI);
                if (wrapper != null) {
                    wrapper.getTempCallback().onTimeout(wrapper.getRequest(), wrapper.getCmd());
                }
            }
        }, timeOut, TimeUnit.MILLISECONDS);

        IWsCallback temp = new IWsCallback<DevResult,DevCmdI>() {
            @Override
            public void onSuccess(DevResult data) {
                mHandler.obtainMessage(DEV_HANDLER, data).sendToTarget();
            }

            @Override
            public void onTimeout(Request request, DevCmdI cmd) {
                dbg.D(TAG, "sendDev onTimeout, cmd="+cmd+",requestCount="+request.requestCount+",request="+request.toJSON());
                if (request.requestCount > 3) {
                    //-101请求超时
                    DevResult devResult = UlifeResultParser.parser(NETSDK_EVENT_GOS_RECV, CODE_TIMEOUT, request.toJSON(), 0, null);
                    onSuccess(devResult);
                } else {
                    sendDev(cmd.cmd, cmd.deviceID, request, timeOut, request.requestCount + 1);
                }
            }
        };

        dbg.D(TAG, "sendDev send, cmd="+cmd);
        request.requestCount = reqCount;
        devCallbacks.put(cmdI, new CallbackWrapper<>(cmdI, temp, scheduledFuture, request));
        mWebSocket.send(request.toJSON());
        return 0;
    }

    public class NetStatusReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ConnectivityManager.CONNECTIVITY_ACTION.equals(action)) {
                ConnectivityManager connectivityManager
                        = (ConnectivityManager) mContext
                        .getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo info = connectivityManager.getActiveNetworkInfo();
                if (info != null && info.isAvailable()) {
                    dbg.D(TAG, "NetStatusReceiver onReceive, NET CHANGE");
                    WsManager.getInstance().reconnect();//wify 4g切换重连websocket
                }
            }
        }
    }
}
