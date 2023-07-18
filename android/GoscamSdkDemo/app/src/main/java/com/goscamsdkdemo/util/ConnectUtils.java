package com.goscamsdkdemo.util;

import com.gos.platform.device.base.Connection;
import com.gos.platform.device.contact.ConnType;
import com.gos.platform.device.ulife.UlifeConnection;

public class ConnectUtils {

    public static String mDeviceId;
    public static Connection connection;

    public static Connection createConnection(String deviceId){
        if (null == connection){
            connection =  new UlifeConnection(deviceId, "", "",
                    ConnType.TYPE_P2P, true);
            mDeviceId = deviceId;
        }else {
            if (!deviceId.equals(mDeviceId)){
                mDeviceId = deviceId;
                connection.release();
                connection = new UlifeConnection(deviceId, "", "",
                        ConnType.TYPE_P2P, true);
            }
        }
        return connection;
    }

}
