package com.goscamsdkdemo;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import com.goscamsdkdemo.util.LoadingDialog;

public class BaseActivity extends AppCompatActivity {
    public static final String EXTRA_DEVICE_ID = "EXTRA_DEVICE_ID";

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSupportActionBar().hide();
        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
    }

    protected void showToast(CharSequence msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    protected void showLToast(CharSequence msg) {
        Toast.makeText(this, msg, Toast.LENGTH_LONG).show();
    }

    public void showLoading() {
        LoadingDialog.disDialog();
        LoadingDialog.showLoading(this);
    }

    public void backClick(View v){
        finish();
    }

    public void dismissLoading() {
        LoadingDialog.disDialog();
    }
}
