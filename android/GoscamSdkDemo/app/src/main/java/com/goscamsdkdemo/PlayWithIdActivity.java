package com.goscamsdkdemo;


import android.content.Context;
import android.content.Intent;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.gos.avplayer.GosMediaPlayer;
import com.gos.avplayer.contact.BufferCacheType;
import com.gos.avplayer.contact.DecType;
import com.gos.avplayer.contact.RecEventType;
import com.gos.avplayer.jni.AvPlayerCodec;
import com.gos.avplayer.surface.GLFrameSurface;
import com.gos.avplayer.surface.GlRenderer;
import com.gos.platform.api.contact.ResultCode;
import com.gos.platform.device.GosConnection;
import com.gos.platform.device.base.Connection;
import com.gos.platform.device.contact.ConnectStatus;
import com.gos.platform.device.contact.StreamType;
import com.gos.platform.device.contact.VideoQuality;
import com.gos.platform.device.domain.AvFrame;
import com.gos.platform.device.inter.IVideoPlay;
import com.gos.platform.device.inter.OnDevEventCallback;
import com.gos.platform.device.result.ConnectResult;
import com.gos.platform.device.result.DevResult;
import com.goscamsdkdemo.tf.NewTfFilePlayActivity;
import com.goscamsdkdemo.util.ConnectUtils;
import com.goscamsdkdemo.util.Packet;
import com.goscamsdkdemo.util.dbg;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Date;
import java.util.TimeZone;

public class PlayWithIdActivity extends BaseActivity implements OnDevEventCallback, AvPlayerCodec.OnDecCallBack, AvPlayerCodec.OnRecCallBack, IVideoPlay {
    TextView mTvTitle;
    GLFrameSurface mGlFrameSurface;
    Button mBtnStartVideo;
    Button mBtnStopVideo;
    Button mBtnStartTalk;
    Button mBtnStopTalk;
    Button mBtnHD;
    Button mBtnSD;

    final int STREAM_TYPE = 11;


    Connection mConnection;
    GlRenderer mGlRenderer;
    GosMediaPlayer mMediaPlayer;
    HandlerThread recordHandlerThread;
    HandlerThread audioHandlerThread;
    private String deviceId;
    int HD = 720;
    private int videoQuality = -1;

    public static void startActivity(Context context, String deviceId) {
        Intent intent = new Intent(context, PlayWithIdActivity.class);
        intent.putExtra(EXTRA_DEVICE_ID, deviceId);
        context.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play_id);
        deviceId = getIntent().getStringExtra(EXTRA_DEVICE_ID);
        GosConnection.TransportProtype();
        mConnection = ConnectUtils.createConnection(deviceId);
        mConnection.setPlatDevOnline(true);
        mConnection.addOnEventCallbackListener(this);

        mTvTitle = findViewById(R.id.text_title);
        mTvTitle.setText(deviceId);
        mGlFrameSurface = findViewById(R.id.gl_surface);
        mBtnStartVideo = findViewById(R.id.btn_OpenStream);
        mBtnStartVideo.setEnabled(false);
        mBtnStopVideo = findViewById(R.id.btn_CloseStream);
        mBtnStopVideo.setEnabled(false);
        mBtnStartTalk = findViewById(R.id.btn_StartTalk);
        mBtnStartTalk.setEnabled(false);
        mBtnStopTalk = findViewById(R.id.btn_Stop_Talk);
        mBtnStopTalk.setEnabled(false);

        mBtnHD = findViewById(R.id.btn_live_hd);
        mBtnHD.setEnabled(false);
        mBtnSD = findViewById(R.id.btn_live_sd);
        mBtnSD.setEnabled(false);

        mGlFrameSurface.setEGLContextClientVersion(2);
        mGlRenderer = new GlRenderer(mGlFrameSurface);
        mGlFrameSurface.setRenderer(mGlRenderer);
        mGlFrameSurface.setEnableZoom(true);

        mMediaPlayer = new GosMediaPlayer();
        mMediaPlayer.getPort();
        mMediaPlayer.setDecodeType(DecType.YUV420);
        mMediaPlayer.setBufferSize(BufferCacheType.StreamCache, 60, 200 * 1024);//60
        mMediaPlayer.start(100);
        mMediaPlayer.setOnDecCallBack(this);
        mMediaPlayer.setOnRecCallBack(this);

        int sampleRate = 8000;
        int channelConfig = AudioFormat.CHANNEL_OUT_MONO;
        int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        int nMinBufSize = AudioTrack.getMinBufferSize(sampleRate, channelConfig, audioFormat);

        sAudioRecord = new AudioRecord(MediaRecorder.AudioSource.VOICE_COMMUNICATION,
                sampleRate, AudioFormat.CHANNEL_IN_MONO, audioFormat, nMinBufSize);

        sAudioTrack = new AudioTrack(AudioManager.STREAM_VOICE_CALL,//STREAM_VOICE_CALL  STREAM_MUSIC
                sampleRate, AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT,
                nMinBufSize, AudioTrack.MODE_STREAM, sAudioRecord.getAudioSessionId());//,

        sAudioTrack.play();

        recordHandlerThread = new HandlerThread("record");
        recordHandlerThread.start();
        sRecordHandler = new RecordHandler(recordHandlerThread.getLooper());
        audioHandlerThread = new HandlerThread("audio");
        audioHandlerThread.start();
        sAudioHandler = new AudioHandler(audioHandlerThread.getLooper());
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {  //停止拉流
        super.onPause();


    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mConnection.removeOnEventCallbackListener(this);
        mGlRenderer.stopDisplay();
        mGlRenderer.release();

        mMediaPlayer.stop();
        mMediaPlayer.releasePort();
        mMediaPlayer.setOnDecCallBack(this);
        mMediaPlayer.setOnRecCallBack(this);

        recordHandlerThread.quitSafely();
        audioHandlerThread.quitSafely();
        sAudioHandler.removeCallbacksAndMessages(null);
        mConnection.stopTalk(0);
        mConnection.stopVideo(0, this);
        if (sAudioRecord != null && AudioRecord.STATE_UNINITIALIZED != sAudioRecord.getState()) {
            sAudioRecord.stop();
            sAudioRecord.release();
        }

        sAudioTrack.stop();
        sAudioTrack.release();
    }

    AudioTrack sAudioTrack;
    AudioHandler sAudioHandler;

    class AudioHandler extends Handler {
        public AudioHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            byte[] data = (byte[]) msg.obj;
            if (sAudioTrack.getPlayState() != AudioTrack.PLAYSTATE_PLAYING)
                sAudioTrack.play();
            sAudioTrack.write(data, 0, data.length);
        }
    }

    AudioRecord sAudioRecord;
    RecordHandler sRecordHandler;

    class RecordHandler extends Handler {
        public boolean isStartRecord;

        public RecordHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            byte[] audioData = new byte[640];
            if (sAudioRecord.getState() == AudioRecord.STATE_INITIALIZED) {
                sAudioRecord.startRecording();
            }

            while (isStartRecord) {
                int size = sAudioRecord.read(audioData, 0, audioData.length);
                if (size == audioData.length) {
                    byte[] g711Buf = new byte[320];
                    int len = AvPlayerCodec.nativeEncodePCMtoG711A(8000, 1, audioData, audioData.length, g711Buf);
                    if (len > 0) {
                        mConnection.sendTalkData(0, 53, 8000, 0, g711Buf, g711Buf.length);

                    }
                }
            }
            mConnection.stopTalk(0);
        }
    }

    public void connect(View view) {
        if (mConnection.isConnected()) {
            showToast("connect success");
            mBtnStartVideo.setEnabled(true);
            mBtnStartTalk.setEnabled(true);
            mBtnHD.setEnabled(true);
            mBtnSD.setEnabled(true);
        } else {
            mConnection.connect(0);
        }
    }

    public void openStream(View view) {
        int timestamp = (int) (System.currentTimeMillis() / 1000L);
        int timezone = (TimeZone.getDefault().getRawOffset() / 3600000) + 24;// on the IPC side, -24,
        if (TimeZone.getDefault().inDaylightTime(new Date())) {
            timezone++;
        }
        mConnection.startVideo(0, StreamType.VIDEO_AUDIO, "", timestamp, timezone, this);
    }



    public void stopStream(View view) {
        mConnection.stopVideo(0, this);

    }

    public void startTalk(View view) {
        if (mConnection.isConnected()) {
            mConnection.startTalk(0, "");
            mBtnStopTalk.setEnabled(true);
        }
    }

    public void stopTalk(View view) {
        sRecordHandler.isStartRecord = false;
    }


    public void changeHd(View view) {
        if (videoQuality == VideoQuality.STREAM_HD)
            return;
        videoQuality = VideoQuality.STREAM_HD;
        mConnection.setStreamQuality(0, VideoQuality.STREAM_HD);
    }

    public void changeSd(View view) {
        if (videoQuality == VideoQuality.STREAM_SD)
            return;
        videoQuality = VideoQuality.STREAM_SD;
        mConnection.setStreamQuality(0, VideoQuality.STREAM_SD);
    }

    @Override
    public void onDevEvent(String s, DevResult devResult) {
        if (!TextUtils.equals(s, deviceId)) {
            return;
        }

        DevResult.DevCmd devCmd = devResult.getDevCmd();
        int code = devResult.getResponseCode();
        switch (devCmd) {
            case connect:
                ConnectResult connectResult = (ConnectResult) devResult;
                if (connectResult.getConnectStatus() == ConnectStatus.CONNECT_SUCCESS) {
                    mBtnStartVideo.setEnabled(true);
                    mBtnStartTalk.setEnabled(true);
                    showToast("connect success");
                }
                break;
            case startVideo:
                if (ResultCode.SUCCESS == code) {
                    mBtnStopVideo.setEnabled(true);
                    mBtnHD.setEnabled(true);
                    mBtnSD.setEnabled(true);
                    showToast("start video success");
                }
                break;
            case stopVideo:
                break;
            case startTalk:
                if (ResultCode.SUCCESS == code) {
                    sRecordHandler.isStartRecord = true;
                    sRecordHandler.sendEmptyMessage(0);
                    showToast("start talk success");
                } else {
                    mConnection.stopTalk(0);
                }
                break;
            case sendSpeakFile:
                mConnection.stopTalk(0);
                break;
            case stopTalk:
                break;

        }
    }

    @Override
    public void decCallBack(DecType type, byte[] data, int dataSize, int width, int height, int rate, int ch, int flag, int frameNo, String aiInfo) {
        if (DecType.YUV420 == type) {
            ByteBuffer buf = ByteBuffer.wrap(data);
            mGlRenderer.update(buf, width, height);
            checkVideoQualityChanged(width, height);
        } else if (DecType.AUDIO == type) {
            byte[] t = new byte[dataSize];
            System.arraycopy(data, 0, t, 0, dataSize);
            Log.e("Audio", "decCallBack: " + data.length);
            Message obtain = Message.obtain();
            obtain.obj = t;
            sAudioHandler.sendMessage(obtain);
        }
    }


    private void checkVideoQualityChanged(int width, int height) {
        dbg.D("checkVideoQualityChanged", "width=" + width + ",height=" + height + " videoQuality " + videoQuality);
    }


    @Override
    public void recCallBack(RecEventType type, long data, long flag) {

    }

    long retVal;
    @Override
    public void onVideoStream(String s, AvFrame avFrame) {
        byte[] temp = new byte[avFrame.data.length];
        System.arraycopy(avFrame.data, 0, temp, 0, avFrame.data.length);
        retVal = mMediaPlayer.putFrame(avFrame.data, avFrame.dataLen, 1);
        int nFrameType = Packet.byteArrayToInt_Little(avFrame.data, 4);
        Log.d("onStreamCallback", "retVal=" + retVal + " nFrameType " + nFrameType);
        if (retVal == -20) {
            mConnection.pasueRecvStream(0, true);
        }
    }


}