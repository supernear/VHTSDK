package com.goscamsdkdemo.util;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;

import java.util.ArrayList;
import java.util.List;

/**
 * 动态权限
 */

public class PermissionUtil {
    private static boolean verifyPermissions(Activity activity, String permmissions, String[] permmis, int requestCode) {
        try {
            //检测是否有写的权限
            int permission = ActivityCompat.checkSelfPermission(activity,
                    permmissions);
            if (permission != PackageManager.PERMISSION_GRANTED) {
                // 没有写的权限，去申请写的权限，会弹出对话框
                ActivityCompat.requestPermissions(activity, permmis, requestCode);
                return false;
            } else {
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static final int REQUEST_WIFI = 6;

    public static boolean verifyWifiPermissions(Activity activity) {
        String[] PERMISSIONS_WIFI = {Manifest.permission.CHANGE_WIFI_STATE};
        return verifyPermissions(activity, Manifest.permission.CHANGE_WIFI_STATE, PERMISSIONS_WIFI, REQUEST_RECORD_AUDIO);
    }

    public static final int REQUEST_EXTERNAL_STORAGE = 1;

    public static boolean verifyStoragePermissions(Activity activity) {
        String[] PERMISSIONS_STORAGE = {Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE};
        return verifyPermissions(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE, PERMISSIONS_STORAGE, REQUEST_EXTERNAL_STORAGE);
    }

    public static final int REQUEST_CAMERA = 2;

    public static boolean verifyCameraPermissions(Activity activity) {
        String[] PERMISSIONS_CAMERA = {Manifest.permission.CAMERA};
        return verifyPermissions(activity, Manifest.permission.CAMERA, PERMISSIONS_CAMERA, REQUEST_CAMERA);
    }

    public static final int REQUEST_RECORD_AUDIO = 3;

    public static boolean verifyRecordPermissions(Activity activity) {
        String[] PERMISSIONS_RECORD_AUDIO = {Manifest.permission.RECORD_AUDIO};
        return verifyPermissions(activity, Manifest.permission.RECORD_AUDIO, PERMISSIONS_RECORD_AUDIO, REQUEST_RECORD_AUDIO);
    }

    public static final int ACCESS_COARSE_LOCATION = 4;

    public static boolean verifyLocationPermissions(Activity activity) {
        //因谷歌政策原因，不再获取位置权限，wifi名称手动填写
        if(true){
            return false;
        }
        List<String> permiss = new ArrayList<>();
        permiss.add(Manifest.permission.ACCESS_FINE_LOCATION);
        permiss.add(Manifest.permission.ACCESS_WIFI_STATE);
        permiss.add(Manifest.permission.ACCESS_BACKGROUND_LOCATION);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            permiss.add(Manifest.permission.ACCESS_COARSE_LOCATION);
        }


//            String[] PERMISSIONS_RECORD_AUDIO = {Manifest.permission.ACCESS_COARSE_LOCATION,Manifest.permission.ACCESS_FINE_LOCATION,
//                    Manifest.permission.ACCESS_WIFI_STATE,Manifest.permission.ACCESS_BACKGROUND_LOCATION};


        String[] permm = new String[permiss.size()];
        for (int i = 0; i < permiss.size(); i++) {
            permm[i] = permiss.get(i);
        }
        return verifyPermissions(activity, Manifest.permission.ACCESS_BACKGROUND_LOCATION, permm, REQUEST_APP_PERMISS);
    }


    public static final int REQUEST_APP_PERMISS = 5;

    public static boolean verifyAppPermissions(Activity activity) {
        try {
            int writeStoragePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE);
            int readStoragePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.READ_EXTERNAL_STORAGE);
            int cameraPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.CAMERA);
            int recordPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.RECORD_AUDIO);
            int readPhonePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.READ_PHONE_STATE);
            int openWifiPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.CHANGE_WIFI_STATE);

            List<String> permiss = new ArrayList<>();
            if (openWifiPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.CHANGE_WIFI_STATE);

            if (writeStoragePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);

            if (readStoragePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.READ_EXTERNAL_STORAGE);

            if (cameraPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.CAMERA);

            if (recordPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.RECORD_AUDIO);

            if (readPhonePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.READ_PHONE_STATE);

            if (permiss.size() > 0) {
                String[] permm = new String[permiss.size()];
                for (int i = 0; i < permiss.size(); i++) {
                    permm[i] = permiss.get(i);
                }
                ActivityCompat.requestPermissions(activity, permm, REQUEST_APP_PERMISS);
                return false;
            } else {
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static final int REQUEST_APP_PERMIS = 6;

    public static boolean verifyAppPermissionss(Activity activity) {
        try {
            int writeStoragePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE);
            int readStoragePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.READ_EXTERNAL_STORAGE);
            int cameraPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.CAMERA);
            int recordPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.RECORD_AUDIO);
            int readPhonePermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.READ_PHONE_STATE);

            int wakeLockPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.WAKE_LOCK);
            int disableKeyguardPermission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.DISABLE_KEYGUARD);

            List<String> permiss = new ArrayList<>();
            if (writeStoragePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);

            if (readStoragePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.READ_EXTERNAL_STORAGE);

            if (cameraPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.CAMERA);

            if (recordPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.RECORD_AUDIO);

            if (readPhonePermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.READ_PHONE_STATE);

            if (disableKeyguardPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.DISABLE_KEYGUARD);

            if (wakeLockPermission != PackageManager.PERMISSION_GRANTED)
                permiss.add(Manifest.permission.WAKE_LOCK);

            dbg.D("permiss", "" + permiss);
            if (permiss.size() > 0) {
                String[] permm = new String[permiss.size()];
                for (int i = 0; i < permiss.size(); i++) {
                    permm[i] = permiss.get(i);
                }
                dbg.D("permiss", "" + permm);
                ActivityCompat.requestPermissions(activity, permm, REQUEST_APP_PERMISS);
                return false;
            } else {
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }


    /**
     * 检测GPS是否打开
     *
     * @return
     */
    public static boolean checkGPSIsOpen(Context context) {
        boolean isOpen;
        LocationManager locationManager = (LocationManager) context
                .getSystemService(Context.LOCATION_SERVICE);
        isOpen = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
        return isOpen;
    }


}
