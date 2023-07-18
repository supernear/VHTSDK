package com.goscamsdkdemo;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.os.Process;

import com.gos.avplayer.GosMediaPlayer;
import com.gos.platform.api.ConfigManager;
import com.gos.platform.api.GosSession;
import com.gos.platform.api.Goscam;
import com.gos.platform.api.contact.PlatCode;
import com.gos.platform.api.contact.ServerType;
import com.gos.platform.api.domain.DeviceEntity;
import com.gos.platform.api.inter.OnPlatformEventCallback;
import com.gos.platform.api.jni.PlatformSession;
import com.gos.platform.api.result.GetDeviceListResult;
import com.gos.platform.api.result.LoginResult;
import com.gos.platform.api.result.PlatResult;
import com.gos.platform.device.PlatformType;
import com.gos.platform.device.base.Connection;
import com.gos.platform.device.contact.TransportProType;
import com.goscamsdkdemo.entitiy.Device;
import com.goscamsdkdemo.entitiy.DeviceManager;
import com.goscamsdkdemo.entitiy.User;
import com.goscamsdkdemo.util.dbg;

import java.util.ArrayList;
import java.util.List;

public class GApplication extends Application implements OnPlatformEventCallback {
    static {
        System.loadLibrary("AVAPIs");
        System.loadLibrary("IOTCAPIs");
        System.loadLibrary("NetProSDK");
        System.loadLibrary("GosNetSDK");
        System.loadLibrary("DevPlatform");

        System.loadLibrary("AVPlayer");
        System.loadLibrary("avplayercodec");

        System.loadLibrary("voiceRecog");
    }

    public static GApplication app;
    public User user;
    @Override
    public void onCreate() {
        super.onCreate();
        if(!shouldInit(this)){
            return;
        }

        app = this;
        GosMediaPlayer.init();
        Goscam.setDebugenble(true);
        int transportProType = TransportProType.NETPRO_ENABLE_ALL;
        int userType = getResources().getInteger(R.integer.user_type);//APP定制类型
//         userType = 30;//APP定制类型
        Goscam.init(this, PlatformType.ULIFE, transportProType, 0, userType, true, 2, null);
        ConfigManager.IS_ENCRYPT = true;//采用加密
//        ConfigManager.serverType = ConfigManager.TEST_SERVER_NET_CN;
        ConfigManager.serverType = ConfigManager.CN_SERVER;

        GosSession.getSession().addOnPlatformEventCallback(this);

        //示例
        //String crtyKey = "PujvjKu/7Nzl1ojM+3ARg6ZgdDFiDKIapOYX1KEXE7R8ESB1Bc/uHCQfwYqbNasFv6rgQ02PtSKJCGJeeoi4PanQTtnKA+FG/FVbhb3EddUwtyu/R/5cuELorv23jtjS";
        //String pws = "qwer2222";
        //传入秘钥
        //PlatformSession.getSession().NativeGetDecCryptKey(crtyKey, crtyKey.length());
        //传入密码
        //PlatformSession.getSession().NativeGetEncCryptKey(pws, pws.length());

    }

    @Override
    public void OnPlatformEvent(PlatResult platResult) {
        PlatResult.PlatCmd platCmd = platResult.getPlatCmd();
        int code = platResult.getResponseCode();
        switch (platCmd){
            case login:
                if(code == PlatCode.SUCCESS){
                    LoginResult loginResult = (LoginResult) platResult;
                    user = new User();
                    user.userName = loginResult.userName;
                    user.token = loginResult.token;
                    user.sessionId = loginResult.getSessionId();
                    user.sessionIdEx = loginResult.sessionIdEx;

//                    GosSession.getSession().stopHeartBeat();
//                    GosSession.getSession().netClosse(ServerType.CGSA);
//                    GosSession.getSession().netConnect(ServerType.CGSA);//sdk中会调用开启心跳
                }
                break;
            case getDeviceList:
            case getDeviceListEx:
                if(code == PlatCode.SUCCESS){
                    GetDeviceListResult getDeviceListResult = (GetDeviceListResult) platResult;
                    List<DeviceEntity> deviceEntityList = getDeviceListResult.getDeviceEntityList();
                    List<Device> list = new ArrayList<>();
                    for(int i = 0; deviceEntityList != null && i < deviceEntityList.size(); i++){
                        DeviceEntity deviceEntity = deviceEntityList.get(i);
                        Device device = new Device(deviceEntity.deviceName, deviceEntity.deviceId, deviceEntity.devStatus == 1, deviceEntity.deviceType,deviceEntity.streamUser,deviceEntity.streamPassword
                        ,deviceEntity.cap,deviceEntity.deviceHdType,deviceEntity.deviceSfwVer,deviceEntity.deviceHdwVer);
                        list.add(device);
                    }
                    List<Device> deviceList = DeviceManager.getInstance().saveDevice(list);
                    for(int i = 0; deviceList != null && i < deviceList.size(); i++){
                        Device device = deviceList.get(i);
                        Connection connection = device.getConnection();
                        connection.setPlatDevOnline(device.isOnline);
//                        if(device.isOnline){
//                            connection.connect(0);
//                        }
                    }
                }
                break;
        }
    }

    public static boolean shouldInit(Context context) {
        ActivityManager am = ((ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE));
        List<ActivityManager.RunningAppProcessInfo> processInfos = am.getRunningAppProcesses();
        String mainProcessName = context.getPackageName();
        int myPid = Process.myPid();
        for (ActivityManager.RunningAppProcessInfo info : processInfos) {
            dbg.D("GApplication","APPLICATION:myPid="+":"+info.pid+
                    ","+mainProcessName+"::"+info.processName);
            if (info.pid == myPid && mainProcessName.equals(info.processName)) {
                return true;
            }
        }
        return false;
    }
}
