package com.goscamsdkdemo.util;

import android.text.TextUtils;

import com.goscamsdkdemo.GApplication;
import com.goscamsdkdemo.R;


public class ErrorCodeUtil {

    //设置手动录像
    public final static int CODE_2 = 2;
    public final static int CODE_3 = 3;
    public final static int CODE_4 = 4;
    public final static int CODE_5 = 5;
    public final static int CODE_6 = 6;

    public final static int CODE_101 = -101;
    public final static int CODE_103 = -103;
    public final static int CODE_105 = -105;
    public final static int CODE_106 = -106;
    public final static int CODE_10000 = -10000;
    public final static int CODE_10030 = -10030;
    public final static int CODE_10085 = -10085;
    public final static int CODE_10086 = -10086;
    public final static int CODE_10087 = -10087;
    public final static int CODE_10088 = -10088;
    public final static int CODE_10089 = -10089;
    public final static int CODE_10090 = -10090;
    public final static int CODE_10091 = -10091;
    public final static int CODE_10092 = -10092;
    public final static int CODE_10093 = -10093;
    public final static int CODE_10094 = -10094;
    public final static int CODE_10095 = -10095;
    public final static int CODE_10096 = -10096;
    public final static int CODE_10097 = -10097;
    public final static int CODE_10098 = -10098;
    public final static int CODE_10099 = -10099;
    public final static int CODE_10100 = -10100;
    public final static int CODE_10101 = -10101;
    public final static int CODE_10102 = -10102;
    public final static int CODE_10103 = -10103;
    public final static int CODE_10104 = -10104;
    public final static int CODE_10105 = -10105;
    public final static int CODE_10106 = -10106;
    public final static int CODE_10107 = -10107;
    public final static int CODE_10108 = -10108;
    public final static int CODE_10109 = -10109;
    public final static int CODE_10110 = -10110;


    public final static int CODE_20000 = -20000;
    public final static int CODE_20001 = -20001;
    public final static int CODE_20002 = -20002;
    public final static int CODE_20003 = -20003;
    public final static int CODE_20004 = -20004;
    public final static int CODE_20005 = -20005;
    public final static int CODE_20006 = -20006;
    public final static int CODE_20007 = -20007;
    public final static int CODE_20008 = -20008;

    public final static int CODE_70000 = -70000;
    public final static int CODE_70001 = -70001;
    public final static int CODE_70002 = -70002;
    public final static int CODE_70003 = -70003;
    public final static int CODE_70004 = -70004;
    public final static int CODE_70005 = -70005;


    public final static int CODE_80000 = -80000;
    public final static int CODE_80001 = -80001;
    public final static int CODE_80002 = -80002;
    public final static int CODE_80003 = -80003;
    public final static int CODE_80004 = -80004;
    public final static int CODE_80005 = -80005;
    public final static int CODE_80006 = -80006;
    public final static int CODE_80007 = -80007;
    public final static int CODE_80009 = -80009;
    public final static int CODE_80010 = -80010;
    public final static int CODE_80012 = -80012;
    public final static int CODE_80013 = -80013;
    public final static int CODE_80014 = -80014;
    public final static int CODE_80015 = -80015;
    public final static int CODE_80016 = -80016;
    public final static int CODE_80017 = -80017;
    public final static int CODE_80018 = -80018;
    public final static int CODE_80019 = -80019;
    public final static int CODE_80020 = -80020;
    public final static int CODE_80021 = -80021;
    public final static int CODE_80022 = -80022;

    public static String handlePlatResultCode(int code) {
        return getErrorMsgByCode(code);
    }

    private static String getErrorMsgByCode(int code) {
//        String errorMsg = getString(R.string.unknown_error)+":"+code;
        String errorMsg = getString(R.string.request_failed);
        switch (code) {
            case CODE_101:
                errorMsg = getString(R.string.error_code_101);
                break;
            case CODE_103:
                errorMsg = getString(R.string.error_code_103);
                break;
            case CODE_105:
                errorMsg = getString(R.string.error_code_105);
                break;
            case CODE_106:
                break;
            case CODE_10000:
                break;
            case CODE_10030:
                errorMsg = getString(R.string.error_code_10030);
                break;
            case CODE_10085:
                errorMsg = getString(R.string.error_code_10085);
                break;
            case CODE_10086:
                errorMsg = getString(R.string.error_code_10086);
                break;
            case CODE_10087:
                errorMsg = getString(R.string.error_code_10087);
                break;
            case CODE_10088:
                errorMsg = getString(R.string.error_code_10088);
                break;
            case CODE_10089:
                errorMsg = getString(R.string.error_code_10089);
                break;
            case CODE_10090:
                errorMsg = getString(R.string.error_code_10090);
                break;
            case CODE_10091:
                errorMsg = getString(R.string.error_code_10091);
                break;
            case CODE_10092:
                errorMsg = getString(R.string.error_code_10092);
                break;
            case CODE_10093:
                errorMsg = getString(R.string.error_code_10093);
                break;
            case CODE_10094:
                errorMsg = getString(R.string.error_code_10094);
                break;
            case CODE_10095:
                errorMsg = getString(R.string.error_code_10095);
                break;
            case CODE_10096:
                errorMsg = getString(R.string.error_code_10096);
                break;
            case CODE_10097:
                errorMsg = getString(R.string.error_code_10097);
                break;
            case CODE_10098:
                errorMsg = getString(R.string.error_code_10098);
                break;
            case CODE_10099:
                errorMsg = getString(R.string.error_code_10099);
                break;
            case CODE_10100:
                errorMsg = getString(R.string.error_code_10100);
                break;
            case CODE_10101:
                errorMsg = getString(R.string.error_code_10101);
                break;
            case CODE_10102:
                errorMsg = getString(R.string.error_code_10102);
                break;
            case CODE_10103:
                errorMsg = getString(R.string.error_code_10103);
                break;
            case CODE_10104:
                break;
            case CODE_10105:
                errorMsg = getString(R.string.error_code_10105);
                break;
            case CODE_10106:
                errorMsg = getString(R.string.error_code_10106);
                break;
            case CODE_10107:
                errorMsg = getString(R.string.error_code_10106);
                break;
            case CODE_10108:
                errorMsg = getString(R.string.error_code_10108);
                break;
            case CODE_10109:
                errorMsg = getString(R.string.error_code_10109);
                break;
            case CODE_10110:
                errorMsg = getString(R.string.error_code_10110);
                break;
            case CODE_20000:
                break;
            case CODE_20001:
                errorMsg = getString(R.string.error_code_20001);
                break;
            case CODE_20002:
                errorMsg = getString(R.string.error_code_20002);
                break;
            case CODE_20004:
                errorMsg = getString(R.string.error_code_20004);
                break;
            case CODE_20005:
                errorMsg = getString(R.string.error_code_20005);
                break;
            case CODE_20006:
                break;
            case CODE_20007:
                break;
            case CODE_20008:
                break;
            case CODE_70000:
                break;
            case CODE_70001:
                break;
            case CODE_70002:
                errorMsg = getString(R.string.error_code_70002);
                break;
            case CODE_70003:
                errorMsg = getString(R.string.error_code_70003);
                break;
            case CODE_70004:
                errorMsg = getString(R.string.error_code_70004);
                break;
            case CODE_70005:
                break;
            case CODE_80000:
                break;
            case CODE_80001:
                break;
            case CODE_80002:
                errorMsg = getString(R.string.error_code_70002);
                break;
            case CODE_80003:
                break;
            case CODE_80004:
                errorMsg = getString(R.string.error_code_80004);
                break;
            case CODE_80005:
                errorMsg = getString(R.string.error_code_80005);
                break;
            case CODE_80006:
                errorMsg = getString(R.string.error_code_80006);
                break;
            case CODE_80007:
                break;
            case CODE_80009:
                errorMsg = getString(R.string.error_code_80009);
                break;
            case CODE_80010:
                errorMsg = getString(R.string.error_code_80010);
                break;
            case CODE_80012:
                errorMsg = getString(R.string.error_code_80012);
                break;
            case CODE_80013:
                errorMsg = getString(R.string.error_code_80013);
                break;
            case CODE_80014:
                errorMsg = getString(R.string.error_code_80014);
                break;
            case CODE_80015:
                errorMsg = getString(R.string.error_code_80015);
                break;
            case CODE_80016:
                break;
            case CODE_80017:
                break;
            case CODE_80018:
                errorMsg = getString(R.string.error_code_80018);
                break;
            case CODE_80019:
                break;
            case CODE_80020:
                break;
            case CODE_80021:
                break;
            case CODE_80022:
                break;
            default:
                break;
        }

//        return errorMsg + ",code=" + code;
        return errorMsg;
    }

    public static String getSetRecordErrorMsgByCode(int code){
        String mess = null;
        switch (code) {
            case 2:
                mess = getString(R.string.manual_record_not_card);
                break;
            case 3:
                mess = getString(R.string.manual_record_card_error);
                break;
            case 4:
                mess = getString(R.string.manual_record_not_space);
                break;
            case 5:
                mess = getString(R.string.manual_record_recording);
                break;
            case 6:
                mess = getString(R.string.manual_record_frequently_opr);
                break;
            default:
                break;
        }
        return !TextUtils.isEmpty(mess)?mess:getErrorMsgByCode(code);
    }

    private static String getString(int stringRes) {
        return GApplication.app.getString(stringRes);
    }
}
