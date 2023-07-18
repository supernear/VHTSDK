package com.goscamsdkdemo.util;

import com.gos.platform.api.GosSession;
import com.gos.platform.api.devparam.DevParamResult;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;

public class AppGetDeviceParamObservableOnSubscribe implements ObservableOnSubscribe<DevParamResult> {
    String deviceId;
    List<String> CMDTypes;

    public AppGetDeviceParamObservableOnSubscribe(String deviceId){
        this.deviceId = deviceId;
        CMDTypes = new ArrayList<>();
    }

    public AppGetDeviceParamObservableOnSubscribe(String deviceId, String...types){
        this(deviceId);
        if(types != null && types.length > 0)
            CMDTypes.addAll(Arrays.asList(types));
    }

    public AppGetDeviceParamObservableOnSubscribe add(String type){
        CMDTypes.add(type);
        return this;
    }

    public List<String> getCMDTypes(){
        return CMDTypes;
    }

    @Override
    public void subscribe(ObservableEmitter<DevParamResult> e) throws Exception {
        String[] cmdTypes = CMDTypes.toArray(new String[0]);
        DevParamResult devParamResult = GosSession.getSession().AppGetDeviceParam(deviceId, cmdTypes);
        e.onNext(devParamResult);
        e.onComplete();
    }
}
