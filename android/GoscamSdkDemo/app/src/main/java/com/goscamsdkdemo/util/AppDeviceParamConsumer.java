package com.goscamsdkdemo.util;

import com.gos.platform.api.devparam.DevParamResult;

import java.lang.ref.WeakReference;

import io.reactivex.functions.Consumer;

public abstract class AppDeviceParamConsumer<T> implements Consumer<DevParamResult> {
    WeakReference<T> w;

    public AppDeviceParamConsumer(T t){
        w = new WeakReference<>(t);
    }

    @Override
    public void accept(DevParamResult result) throws Exception {
        accept(w.get(), result);
    }

    public abstract void accept(T t, DevParamResult result);
}
