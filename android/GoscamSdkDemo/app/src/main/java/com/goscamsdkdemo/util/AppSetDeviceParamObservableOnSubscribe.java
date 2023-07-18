package com.goscamsdkdemo.util;

import com.gos.platform.api.GosSession;
import com.gos.platform.api.devparam.DevParam;
import com.gos.platform.api.devparam.DevParamResult;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;

public class AppSetDeviceParamObservableOnSubscribe implements ObservableOnSubscribe<DevParamResult> {
    String deviceId;
    List<DevParam> devParams;

    public AppSetDeviceParamObservableOnSubscribe(String deviceId){
        this.deviceId = deviceId;
        devParams = new ArrayList<>();
    }

    public AppSetDeviceParamObservableOnSubscribe(String deviceId, DevParam...params){
        this(deviceId);
        if(params != null && params.length > 0){
            devParams.addAll(Arrays.asList(params));
        }
    }

    public AppSetDeviceParamObservableOnSubscribe add(DevParam param){
        devParams.add(param);
        return this;
    }

    @Override
    public void subscribe(ObservableEmitter<DevParamResult> e) throws Exception {
        DevParam[] params = devParams.toArray(new DevParam[0]);
        DevParamResult devParamResult = GosSession.getSession().AppSetDeviceParam(deviceId, params);
        e.onNext(devParamResult);
        e.onComplete();
    }
}
