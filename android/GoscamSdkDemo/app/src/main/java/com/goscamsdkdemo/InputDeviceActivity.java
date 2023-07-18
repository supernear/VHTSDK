package com.goscamsdkdemo;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.gos.platform.api.GosSession;
import com.goscamsdkdemo.tf.NewTfFilePlayActivity;
import com.goscamsdkdemo.util.PermissionUtil;
import com.goscamsdkdemo.util.Util;

public class InputDeviceActivity extends BaseActivity{
    private Button btnNext,btnPlayBack;
    private EditText etDevId;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_input);
        etDevId = findViewById(R.id.et_dev_id);
        btnNext = findViewById(R.id.btn_next);
        btnPlayBack = findViewById(R.id.btn_tf);
        etDevId.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void afterTextChanged(Editable editable) {
                if (editable.length() < 15){
                    btnNext.setEnabled(false);
                    btnPlayBack.setEnabled(false);
                }else {
                    btnNext.setEnabled(true);
                    btnPlayBack.setEnabled(true);
                }
            }
        });
        PermissionUtil.verifyAppPermissions(this);
        btnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                GosSession.getSession().appGetBSAddress(Util.getPhoneUUID(InputDeviceActivity.this),"");

                PlayWithIdActivity.startActivity(InputDeviceActivity.this,etDevId.getText().toString());
            }
        });

        btnPlayBack.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                NewTfFilePlayActivity.startActivity(InputDeviceActivity.this, etDevId.getText().toString());
            }
        });
    }
}
