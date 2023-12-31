#ifndef PROTOCOL_CMD_H
#define PROTOCOL_CMD_H
typedef enum 
{
	IOTYPE_USER_IPCAM_START 					= 0x01FF,	//开启流
	IOTYPE_USER_IPCAM_STARTRESP 				= 0x0200,	//开启流应答
	IOTYPE_USER_IPCAM_STOP	 					= 0x02FF,	//关闭流
	IOTYPE_USER_IPCAM_AUDIOSTART 				= 0x0300,	//开启音频	
	IOTYPE_USER_IPCAM_AUDIOSTOP 				= 0x0301,	//关闭音频
	IOTYPE_USER_IPCAM_SPEAKERSTART 				= 0x0350,	//开启对讲
	IOTYPE_USER_IPCAM_SPEAKERSTOP 				= 0x0351,	//关闭对讲
	IOTYPE_USER_IPCAM_SPEAKERPROCESS_RESP 		= 0x0352,	//对讲操作应答
	IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ			= 0x0320,	//码流切换
	IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP		= 0x0321,	//码流切换应答
	IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ			= 0x0322,	//获取当前码流参数
	IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP		= 0x0323,	//获取当前码流参数应答
	IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ		= 0x0324,	//设置移动侦测开关
	IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP		= 0x0325,	//设置移动侦测开关应答
	IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ		= 0x0326,	//获取移动侦测参数
	IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP		= 0x0327,	//获取移动侦测参数应答
	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ		= 0x0328,
	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP		= 0x0329,
	IOTYPE_USER_IPCAM_DEVINFO_REQ				= 0x0330,	//获取设备信息请求
	IOTYPE_USER_IPCAM_DEVINFO_RESP				= 0x0331,	//获取设备信息请求应答	
	IOTYPE_USER_IPCAM_SETPASSWORD_REQ			= 0x0332,
	IOTYPE_USER_IPCAM_SETPASSWORD_RESP			= 0x0333,
	IOTYPE_USER_IPCAM_LISTWIFIAP_REQ			= 0x0340,
	IOTYPE_USER_IPCAM_LISTWIFIAP_RESP			= 0x0341,
	IOTYPE_USER_IPCAM_SETWIFI_REQ				= 0x0342,	//设置WIFI参数请求
	IOTYPE_USER_IPCAM_SETWIFI_RESP				= 0x0343,	//设置WIFI参数请求应答
	IOTYPE_USER_IPCAM_GETWIFI_REQ				= 0x0344,	//获取WIFI参数请求
	IOTYPE_USER_IPCAM_GETWIFI_RESP				= 0x0345,	//获取WIFI参数请求应答
	IOTYPE_USER_IPCAM_SETRECORD_REQ				= 0x0310,
	IOTYPE_USER_IPCAM_SETRECORD_RESP			= 0x0311,
	IOTYPE_USER_IPCAM_GETRECORD_REQ				= 0x0312,
	IOTYPE_USER_IPCAM_GETRECORD_RESP			= 0x0313,
	IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ		= 0x0314,	//设置录像时长
	IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP  	= 0x0315,	//设置录像时长应答
	IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ		= 0x0316,	//获取录像时长
	IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP  	= 0x0317,	//获取录像时长应答
	IOTYPE_USER_IPCAM_LISTEVENT_REQ				= 0x0318,
	IOTYPE_USER_IPCAM_LISTEVENT_RESP			= 0x0319,
	IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 		= 0x031A,
	IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
	
	IOTYPE_USER_IPCAM_PLAY_RECORD_REQ			= 0x031C, 	//历史回放和缩略图剪接
	IOTYPE_USER_IPCAM_PLAY_RECORD_RESP			= 0x031D,
	IOTYPE_USER_IPCAM_STOP_PLAY_RECORD_REQ		= 0x031E,	//停止预览历史流播放
	IOTYPE_USER_IPCAM_STOP_PLAY_RECORD_RESP		= 0x031F,
	
	IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ		= 0x0360,
	IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP		= 0x0361,
	IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ		= 0x0362,
	IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP		= 0x0363,
	IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ 		= 0x0370,	//设置翻转/镜像请求
	IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP		= 0x0371,	//设置翻转/镜像请求应答
	IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ 		= 0x0372,	//获取翻转/镜像设置参数请求
	IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP		= 0x0373,	//获取翻转/镜像设置参数请求应答
	IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ		= 0x0380,
	IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_RESP		= 0x0381,
	IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ		= 0x0400,
	IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP		= 0x0401,
	IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ		= 0x0402,
	IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP		= 0x0403,
	IOTYPE_USER_IPCAM_PTZ_COMMAND				= 0x1001,	//云台控制命令
	IOTYPE_USER_IPCAM_EVENT_REPORT				= 0x1FFF,
	IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ		= 0x032A,	//获取音频输出格式请求
	IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP	= 0x032B,	//获取音频输出格式请求应答
	IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME		= 0x1002,	//强制获取I帧请求
	IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ			= 0x0390,
	IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP			= 0x0391,
	IOTYPE_USER_IPCAM_CURRENT_FLOWINFO			= 0x0392,
	IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ          = 0x03A0,	//获取设备系统时区请求
	IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP         = 0x03A1,	//获取设备系统时区请求应答
	IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ          = 0x03B0,	//设置设备系统时区请求
	IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP         = 0x03B1,	//设置设备系统时区请求应答


	/**************自定义命令****************/
	IOTYPE_USER_IPCAM_SET_ALARM_CONTROL_REQ		= 0x03B2,	//设置一键布防请求
	IOTYPE_USER_IPCAM_SET_ALARM_CONTROL_RESP	= 0x03B3,	//设置一键布防请求应答
	IOTYPE_USER_IPCAM_GET_ALARM_CONTROL_REQ		= 0x03B4,	//获取一键布防参数请求
	IOTYPE_USER_IPCAM_GET_ALARM_CONTROL_RESP	= 0x03B5,	//获取一键布防参数请求应答

	IOTYPE_USER_IPCAM_SET_ALARM_RING_REQ		= 0x03B6,	//设置报警铃声请求
	IOTYPE_USER_IPCAM_SET_ALARM_RING_RESP		= 0x03B7,	//设置报警铃声请求应答
	IOTYPE_USER_IPCAM_GET_ALARM_RING_REQ		= 0x03B8,	//获取报警铃声状态请求
	IOTYPE_USER_IPCAM_GET_ALARM_RING_RESP		= 0x03B9,	//获取报警铃声状态请求应答
	IOTYPE_USER_IPCAM_GET_ALARM_RING_DATA_START	= 0x03BA,	//开始获取自定义报警铃声请求
	IOTYPE_USER_IPCAM_GET_ALARM_RING_DATA_RESP	= 0x03BB,	//获取自定义报警铃声请求应答
	IOTYPE_USER_IPCAM_GET_ALARM_RING_DATA_STOP	= 0x03BC,	//停止获取自定义报警铃声请求
	IOTYPE_USER_IPCAM_PLAY_ALARM_RING_START		= 0x03BD,	//开始播放报警铃声请求
	IOTYPE_USER_IPCAM_PLAY_ALARM_RING_RESP		= 0x03BE,	//播放报警铃声请求应答
	IOTYPE_USER_IPCAM_PLAY_ALARM_RING_STOP		= 0x03BF,	//结束播放报警铃声请求

	IOTYPE_USER_IPCAM_GET_ALL_PARAM_REQ			= 0x03C0,	//获取所有配置项参数请求
	IOTYPE_USER_IPCAM_GET_ALL_PARAM_RESP		= 0x03C1,	//获取所有配置项参数请求应答

	IOTYPE_USER_IPCAM_SET_MOBILE_CLENT_TYPE_REQ = 0x03C2,	//安卓手机客户端置位请求
	IOTYPE_USER_IPCAM_SET_MOBILE_CLENT_TYPE_RESP= 0x03C3,	//安卓手机客户端置位请求应答
	IOTYPE_USER_IPCAM_SEND_ANDROID_MOTION_ALARM	= 0x03C4,	//安卓手机客户端专用推送命令请求 

	IOTYPE_USER_IPCAM_SET_AUTHENTICATION_REQ	= 0x03C5,	//设置设备鉴权信息(用户名，密码)请求
	IOTYPE_USER_IPCAM_SET_AUTHENTICATION_RESP	= 0x03C6,	//设置设备鉴权信息(用户名，密码)请求应答
	IOTYPE_USER_IPCAM_GET_AUTHENTICATION_REQ 	= 0x03C7,	//获取设备鉴权信息(用户名，密码)请求
	IOTYPE_USER_IPCAM_GET_AUTHENTICATION_RESP	= 0x03C8,	//获取设备鉴权信息(用户名，密码)请求应答
	IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY_REQ	= 0x03C9,	//获取设备能力集请求
	IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY_RESP	= 0x03CA,	//获取设备能力集请求应答

	IOTYPE_USER_IPCAM_GET_MONTH_EVENT_LIST_REQ	= 0x03CB,	//获取某月录像事件列表请求 (即获取SD卡中该月有哪些天是有录像的)
	IOTYPE_USER_IPCAM_GET_MONTH_EVENT_LIST_RESP	= 0x03CC,	//获取某月录像事件列表请求应答
	IOTYPE_USER_IPCAM_GET_DAY_EVENT_LIST_REQ	= 0x03CD,	//获取某天录像事件列表请求 (即获取SD卡中该天中有哪些录像)
	IOTYPE_USER_IPCAM_GET_DAY_EVENT_LIST_RESP	= 0x03CE,	//获取某天录像事件列表请求应答
	IOTYPE_USER_IPCAM_GET_RECORDFILE_START_REQ	= 0x03CF,	//开始下载指定录像文件请求
	IOTYPE_USER_IPCAM_GET_RECORDFILE_START_RESP	= 0x03D0,	//开始下载指定录像文件请求应答
	IOTYPE_USER_IPCAM_GET_RECORDFILE_STOP_REQ	= 0x03D1,	//结束下载指定录像文件请求
	IOTYPE_USER_IPCAM_GET_RECORDFILE_STOP_RESP 	= 0x03D2,	//结束下载指定录像文件请求应答
	IOTYPE_USER_IPCAM_LOCK_RECORDFILE_REQ		= 0x03D3,	//对指定录像文件进行上锁或解锁请求
	IOTYPE_USER_IPCAM_LOCK_RECORDFILE_RESP		= 0x03D4,	//对指定录像文件进行上锁或解锁请求应答
	IOTYPE_USER_IPCAM_DEL_RECORDFILE_REQ		= 0x03D5,	//删除指定录像文件请求
	IOTYPE_USER_IPCAM_DEL_RECORDFILE_RESP		= 0x03D6,	//删除指定录像文件请求应答
	IOTYPE_USER_IPCAM_MANUAL_RECORD_REQ 		= 0x03D7,	//手动录像开启或结束请求
	IOTYPE_USER_IPCAM_MANUAL_RECORD_RESP		= 0x03D8,	//手动录像开启或结束请求应答
	IOTYPE_USER_IPCAM_GET_STORAGE_INFO_REQ 		= 0x03D9,	//获取 SD卡当前容量信息请求 (已用容量/可用容量)
	IOTYPE_USER_IPCAM_GET_STORAGE_INFO_RESP		= 0x03DA,	//获取 SD卡当前容量信息请求应答
	IOTYPE_USER_IPCAM_FORMAT_STORAGE_REQ 		= 0x03DB,	//格式化 SD卡请求
	IOTYPE_USER_IPCAM_FORMAT_STORAGE_RESP		= 0x03DC,	//格式化 SD卡请求应答
	IOTYPE_USER_IPCAM_FILE_RESEND_REQ			= 0x03DD,	//SD卡录像下载丢包重传请求
	IOTYPE_USER_IPCAM_FILE_RESEND_RESP			= 0x03DE,	//SD卡录像下载丢包重传请求应答

	IOTYPE_USER_IPCAM_SET_PIRDETECT_REQ			= 0x03DF,	//设置PIR红外侦测参数请求
	IOTYPE_USER_IPCAM_SET_PIRDETECT_RESP		= 0x03E0,	//设置PIR红外侦测参数请求应答
	IOTYPE_USER_IPCAM_GET_PIRDETECT_REQ			= 0x03E1,	//获取PIR红外侦测参数请求
	IOTYPE_USER_IPCAM_GET_PIRDETECT_RESP		= 0x03E2,	//获取PIR红外侦测参数请求应答
	IOTYPE_USER_IPCAM_SET_TIME_PARAM_REQ 		= 0x03E3,	//设置时间校验参数请求
	IOTYPE_USER_IPCAM_SET_TIME_PARAM_RESP		= 0x03E4,	//设置时间校验参数请求应答
	IOTYPE_USER_IPCAM_GET_TIME_PARAM_REQ 		= 0x03E5,	//获取时间校验参数请求
	IOTYPE_USER_IPCAM_GET_TIME_PARAM_RESP		= 0x03E6,	//获取时间校验参数请求应答
	IOTYPE_USER_IPCAM_SET_TEMPERATURE_REQ		= 0x03E7,	//设置温度报警参数请求
	IOTYPE_USER_IPCAM_SET_TEMPERATURE_RESP		= 0x03E8,	//设置温度报警参数请求应答
	IOTYPE_USER_IPCAM_GET_TEMPERATURE_REQ		= 0x03E9,	//获取温度报警参数请求
	IOTYPE_USER_IPCAM_GET_TEMPERATURE_RESP		= 0x03EA,	//获取温度报警参数请求应答

	/********************阳光照明相关命令*******************/
	IOTYPE_USER_IPCAM_SET_LIGHT_REQ				= 0x03EB,	//设置灯开关
	IOTYPE_USER_IPCAM_SET_LIGHT_RESP			= 0x03EC,	//设置灯开关应答
	IOTYPE_USER_IPCAM_GET_LIGHT_REQ 			= 0x03ED,	//获取灯开关
	IOTYPE_USER_IPCAM_GET_LIGHT_RESP			= 0x03EE,	//获取灯开关应答
	/******************************************************/
	
	IOTYPE_USER_IPCAM_SET_AUDIO_ALARM_REQ 	    = 0x03EF,	//设置声音报警开关
	IOTYPE_USER_IPCAM_SET_AUDIO_ALARM_RESP		= 0x03F0,	//设置声音报警开关应答
	IOTYPE_USER_IPCAM_GET_AUDIO_ALARM_REQ 		= 0x03F1,	//获取声音报警开关
	IOTYPE_USER_IPCAM_GET_AUDIO_ALARM_RESP		= 0x03F2,	//获取声音报警开关应答
	
	/********************阳光照明相关命令*******************/
	IOTYPE_USER_IPCAM_SET_LIGHT_TIME_REQ 		= 0x03F3,	//设置灯亮时间
	IOTYPE_USER_IPCAM_SET_LIGHT_TIME_RESP		= 0x03F4,	//设置灯亮时间应答
	IOTYPE_USER_IPCAM_GET_LIGHT_TIME_REQ 		= 0x03F5,	//获取灯亮时间
	IOTYPE_USER_IPCAM_GET_LIGHT_TIME_RESP		= 0x03F6,	//获取灯亮时间应答
	IOTYPE_USER_IPCAM_RESET_REQ					= 0x03F7,	//恢复出厂设置
	IOTYPE_USER_IPCAM_RESET_RESP				= 0x03F8,	//恢复出厂设置应答
	/*******************************************************/
	
	IOTYPE_USER_IPCAM_GET_REC_JPEG_REQ   		= 0x03F9,  	//获取SD卡录像缩略图请求
 	IOTYPE_USER_IPCAM_GET_REC_JPEG_RESP   		= 0x03FA, 	//获取SD卡录像缩略图应答	SMsgAVIoctrlGetRecJpegResp
 	
//	IOTYPE_USER_IPCAM_SET_LIGHT_TIMING_INFO_REQ 	= 0x03FA,	//设置定时自动亮灯、灭灯时间
//	IOTYPE_USER_IPCAM_SET_LIGHT_TIMING_INFO_RESP	= 0x03FB,	//设置自动亮灯、灭灯时间应答
//	IOTYPE_USER_IPCAM_GET_LIGHT_TIMING_INFO_REQ 	= 0x03FC,	//获取自动亮灯、灭灯时间
//	IOTYPE_USER_IPCAM_GET_LIGHT_TIMING_INFO_RESP	= 0x03FD,	//获取自动亮灯、灭灯时间
	
	//升级
	
	IOTYPE_USER_IPCAM_SET_UPDATE_REQ			= 0x0450,	//获取升级参数
	IOTYPE_USER_IPCAM_SET_UPDATE_RESP			= 0x0451,	//获取升级参数应答
	IOTYPE_USER_IPCAM_SET_CANCEL_UPDATE_REQ		= 0x0452,	//设置取消升级参数
	IOTYPE_USER_IPCAM_SET_CANCEL_UPDATE_RESP	= 0x0453,	//设置取消升级应答

	//amba 电池状态
	IOTYPE_USER_IPCAM_GET_BATTERY_REQ			= 0x0470,	//获取电池状态	
	IOTYPE_USER_IPCAM_GET_BATTERY_RESP			= 0x0471,	//获取电池状态应答
	IOTYPE_USER_IPCAM_SET_BATTERY_ALARM_REQ 	= 0x0472,	//设置电量报警参数请求
	IOTYPE_USER_IPCAM_SET_BATTERY_ALARM_RESP	= 0x0473,	//设置电量报警参数请求应答
	IOTYPE_USER_IPCAM_GET_BATTERY_ALARM_REQ 	= 0x0474,	//获取电量报警参数请求
	IOTYPE_USER_IPCAM_GET_BATTERY_ALARM_RESP	= 0x0475,	//获取电量报警参数请求应答
	
	// dropbox support
    IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_REQ      = 0x0500,
    IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_RESP     = 0x0501,
    IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_REQ      = 0x0502,
    IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_RESP     = 0x0503,
    
	IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY1_REQ   = 0x0504,
    IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY1_RESP	= 0x0505,	//获取设备能力集1请求应答version 1

    IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY2_RESP	= 0x0507,	//获取设备能力集2请求应答version 2	
    
	IOTYPE_USER_IPCAM_RETRANSMISSION_REQ      	= 0x0508,   //类TCP方式下载录像文件重传请求
	IOTYPE_USER_IPCAM_RETRANSMISSION_RESP     	= 0x0509, 	//类TCP方式下载录像文件重传请求应答

	//Uife add 20170603
	IOTYPE_USER_IPCAM_DEVICE_SWITCH_REQ			= 0X0600,//设备摄像头开关
	IOTYPE_USER_IPCAM_DEVICE_SWITCH_RESP 		= 0X0601,	
	IOTYPE_USER_IPCAM_DEVICE_MIC_SWITCH_REQ 	= 0X0602,//设备摄像头麦克风开关
	IOTYPE_USER_IPCAM_DEVICE_MIC_SWITCH_RESP	= 0X0603,
	IOTYPE_USER_IPCAM_DEVICE_LED_SWITCH_REQ 	= 0X0604,//设备状态灯开关
	IOTYPE_USER_IPCAM_DEVICE_LED_SWITCH_RESP	= 0X0605,
	IOTYPE_USER_IPCAM_DEVICE_SET_NIGHT_SWITCH_REQ	= 0X0606,//设备夜视开关
	IOTYPE_USER_IPCAM_DEVICE_SET_NIGHT_SWITCH_RESP	= 0X0607,
	IOTYPE_USER_IPCAM_DEVICE_GET_NIGHT_SWITCH_REQ	= 0X0608,//设备夜视开关
	IOTYPE_USER_IPCAM_DEVICE_GET_NIGHT_SWITCH_RESP	= 0X0609,
	IOTYPE_USER_IPCAM_DEVICE_NTSC_PAL_REQ			= 0X0610,//设备抗闪烁设置
	IOTYPE_USER_IPCAM_DEVICE_NTSC_PAL_RESP			= 0X0611,
	IOTYPE_USER_IPCAM_DEVICE_SEARCH_SSID_REQ		= 0X0612,//搜索设备附近WiFi列表
	IOTYPE_USER_IPCAM_DEVICE_SEARCH_SSID_RESP		= 0X0613,
	IOTYPE_USER_IPCAM_GET_DEVICE_SWITCH_REQ			= 0X0614,//获取设备摄像头开关
	IOTYPE_USER_IPCAM_GET_DEVICE_SWITCH_RESP 		= 0X0615,
	//结束播放铃声应答
	IOTYPE_USER_IPCAM_PLAY_ALARM_RING_STOP_RESP		= 0x0616,//结束播放报警铃声请求应答

	//Amazon Alexa Skills
	IOTYPE_USER_IPCAM_DEVICE_GET_SNAPSHOT_REQ		= 0x0700,//设备拍照
	IOTYPE_USER_IPCAM_DEVICE_GET_SNAPSHOT_RESP		= 0x0701,

	IOTYPE_USER_IPCAM_DEVICE_PLAY_LULLABY_REQ		= 0x0706,//播放摇篮曲
	IOTYPE_USER_IPCAM_DEVICE_PLAY_LULLABY_RESP		= 0x0707,
	
	IOTYPE_USER_IPCAM_LAST_VIDEO_MOTION_REQ			= 0x0708,//最后一条移动侦测的时间
	IOTYPE_USER_IPCAM_LAST_VIDEO_MOTION_RESP		= 0x0709,

	IOTYPE_USER_IPCAM_LAST_SOUND_MOTION_REQ			= 0x070A,//最后一条声音侦测的时间
	IOTYPE_USER_IPCAM_LAST_SOUND_MOTION_RESP		= 0x070B,

	IOTYPE_USER_IPCAM_DEVICE_GET_TEMPERATURE_REQ	= 0x070C,//摄像头周围温度
	IOTYPE_USER_IPCAM_DEVICE_GET_TEMPERATURE_RESP	= 0x070D,

	IOTYPE_USER_IPCAM_DEVICE_GET_STATUS_REQ			= 0x070E,//Check Status (MOTION, SOUND, TEMPERATURE) 
	IOTYPE_USER_IPCAM_DEVICE_GET_STATUS_RESP		= 0x070F,

	IOTYPE_USER_IPCAM_DEVICE_GET_RTSP_URL_REQ		= 0x0710,//RTSP地址请求
	IOTYPE_USER_IPCAM_DEVICE_GET_RTSP_URL_RESP		= 0x0711,
	//Amazon Alexa Skills End
	
	IOTYPE_USER_IPCAM_DEVICE_GET_ALLRECORDLIST_REQ		= 0x0780,//查询摄像头录像列表
	IOTYPE_USER_IPCAM_DEVICE_GET_ALLRECORDLIST_RESP		= 0x0781,
	IOTYPE_USER_IPCAM_DEVICE_GET_ALLALARMLIST_REQ		= 0x0782,//查询摄像头报警列表
	IOTYPE_USER_IPCAM_DEVICE_GET_ALLALARMLIST_RESP		= 0x0783,
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_RECORDLIST_REQ 	= 0x0784,//刷新最新的列表
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_RECORDLIST_RESP	= 0x0785,
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_ALARM_RECORDLIST_REQ 	= 0x0786,//刷新最新的告警列表
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_ALARM_RECORDLIST_RESP	= 0x0787,
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_OLDEST_TIME_REQ	= 0x0788,//刷新最旧的文件时间
	IOTYPE_USER_IPCAM_DEVICE_GET_REFRESH_OLDEST_TIME_RESP	= 0x0789,
		

	IOTYPE_USER_IPCAM_SET_HUMIDITY_REQ				= 0x0804,	//设置湿度报警参数请求
	IOTYPE_USER_IPCAM_SET_HUMIDITY_RESP				= 0x0805,	//设置湿度报警参数请求应答
	IOTYPE_USER_IPCAM_GET_HUMIDITY_REQ				= 0x0806,	//获取湿度报警参数请求
	IOTYPE_USER_IPCAM_GET_HUMIDITY_RESP				= 0x0807,	//获取湿度报警参数请求应答
	IOTYPE_USER_IPCAM_SET_WBGT_REQ					= 0x0808,	//设置WBGT   报警参数请求
	IOTYPE_USER_IPCAM_SET_WBGT_RESP					= 0x0809,	//设置WBGT   报警参数请求应答
	IOTYPE_USER_IPCAM_GET_WBGT_REQ					= 0x080A,	//获取WBGT   报警参数请求
	IOTYPE_USER_IPCAM_GET_WBGT_RESP					= 0x080B,	//获取WBGT   报警参数请求应答
	IOTYPE_USER_IPCAM_SET_TEMP_HUM_WBGT_REQ			= 0x080C,	//设置温湿度加wbgt报警参数请求
	IOTYPE_USER_IPCAM_SET_TEMP_HUM_WBGT_RESP		= 0x080D,	//设置温湿度加wbgt报警参数请求应答
	IOTYPE_USER_IPCAM_GET_TEMP_HUM_WBGT_REQ			= 0x080E,	//获取温湿度加wbgt报警参数请求
	IOTYPE_USER_IPCAM_GET_TEMP_HUM_WBGT_RESP		= 0x080F,	//获取温湿度加wbgt 报警参数请求应答

//==================宠物喂食器相关的命令fuxf add 20180301=========================
	IOTYPE_USER_IPCAM_SET_MANUAL_FEED_REQ			= 0x0810,	//设置手动喂食参数请求
	IOTYPE_USER_IPCAM_SET_MANUAL_FEED_RESP			= 0x0811,	//设置手动喂食参数请求应答
	IOTYPE_USER_IPCAM_GET_MANUAL_FEED_REQ			= 0x0812,	//获取喂食器状态参数请求
	IOTYPE_USER_IPCAM_GET_MANUAL_FEED_RESP			= 0x0813,	//获取喂食器状态参数请求应答
	
	IOTYPE_USER_IPCAM_SET_AUTO_FEED_REQ				= 0x0814,	//设置自动喂食参数请求
	IOTYPE_USER_IPCAM_SET_AUTO_FEED_RESP			= 0x0815,	//设置自动喂食参数请求应答
	IOTYPE_USER_IPCAM_GET_AUTO_FEED_REQ				= 0x0816,	//获取自动喂食参数请求
	IOTYPE_USER_IPCAM_GET_AUTO_FEED_RESP			= 0x0817,	//获取自动喂食参数请求应答	
	
	IOTYPE_USER_IPCAM_SET_BOWL_SETTING_REQ			= 0x0818,	//设置食盆返仓设定参数请求
	IOTYPE_USER_IPCAM_SET_BOWL_SETTING_RESP			= 0x0819,	//设置食盆返仓设定参数请求应答
	IOTYPE_USER_IPCAM_GET_BOWL_SETTING_REQ			= 0x081A,	//获取食盆返仓设定参数请求
	IOTYPE_USER_IPCAM_GET_BOWL_SETTING_RESP			= 0x081B,	//获取食盆返仓设定参数请求应答
	
	IOTYPE_USER_IPCAM_SET_DEDUCT_WEIGHT_REQ			= 0x081C,	//设置设备扣重参数请求
	IOTYPE_USER_IPCAM_SET_DEDUCT_WEIGHT_RESP		= 0x081D,	//设置设备扣重参数请求应答
	//IOTYPE_USER_IPCAM_GET_DEDUCT_WEIGHT_REQ		= 0x081E,	//获取设备扣重参数请求
	//IOTYPE_USER_IPCAM_GET_DEDUCT_WEIGHT_RESP		= 0x081F,	//获取设备扣重参数请求应答
	
	IOTYPE_USER_IPCAM_SET_FEED_CALIBRATION_REQ		= 0x0820,	//设置出粮校准参数请求
	IOTYPE_USER_IPCAM_SET_FEED_CALIBRATION_RESP		= 0x0821,	//设置出粮校准参数请求应答
	//IOTYPE_USER_IPCAM_GET_FEED_CALIBRATION_REQ	= 0x0822,	//获取出粮校准参数请求
	//IOTYPE_USER_IPCAM_GET_FEED_CALIBRATION_RESP	= 0x0823,	//获取出粮校准参数请求应答

	IOTYPE_USER_IPCAM_SET_FEED_RECORD_REQ			= 0x0824,	//设置喂食记录参数请求
	IOTYPE_USER_IPCAM_SET_FEED_RECORD_RESP			= 0x0825,	//设置喂食记录参数请求应答
	IOTYPE_USER_IPCAM_GET_FEED_RECORD_REQ			= 0x0826,	//获取喂食记录参数请求
	IOTYPE_USER_IPCAM_GET_FEED_RECORD_RESP			= 0x0827,	//获取喂食记录参数请求应答

	//IOTYPE_USER_IPCAM_GET_FEED_REMAIN_REQ			= 0x0828,	//获取设备余粮参数请求
	//IOTYPE_USER_IPCAM_GET_FEED_REMAIN_RESP		= 0x0829,	//获取设备余粮参数请求应答

	IOTYPE_USER_IPCAM_SET_BOWL_SWITCH_REQ			= 0x082A,	//设置食盆开关按钮参数请求
	IOTYPE_USER_IPCAM_SET_BOWL_SWITCH_RESP			= 0x082B,	//设置食盆开关按钮参数请求应答

//==========================GD6509 相关命令 guotf add 20180528=========================
	IOTYPE_USER_IPCAM_SET_TLIGHT_REQ					= 0x082C,	//设置三状态灯开关
	IOTYPE_USER_IPCAM_SET_TLIGHT_RESP					= 0x082D,	//设置三状态灯开关应答
	IOTYPE_USER_IPCAM_GET_TLIGHT_REQ 					= 0x082E,	//获取三状态灯开关
	IOTYPE_USER_IPCAM_GET_TLIGHT_RESP					= 0x082F,	//获取三状态灯开关应答

	IOTYPE_USER_IPCAM_SET_VOICE_OPERATED_SWITCH_REQ		= 0x0830,	//设置声控开关
	IOTYPE_USER_IPCAM_SET_VOICE_OPERATED_SWITCH_RESP	= 0x0831,	//设置声控开关应答
	IOTYPE_USER_IPCAM_GET_VOICE_OPERATED_SWITCH_REQ 	= 0x0832,	//获取声控开关
	IOTYPE_USER_IPCAM_GET_VOICE_OPERATED_SWITCH_RESP	= 0x0833,	//获取声控开关应答

	IOTYPE_USER_IPCAM_SET_TLIGHT_TIME_REQ				= 0x0834,	//设置三状态灯开灯时间
	IOTYPE_USER_IPCAM_SET_TLIGHT_TIME_RESP				= 0x0835,	//设置三状态灯开灯时间应答
	IOTYPE_USER_IPCAM_GET_TLIGHT_TIME_REQ 				= 0x0836,	//获取三状态灯开灯时间
	IOTYPE_USER_IPCAM_GET_TLIGHT_TIME_RESP				= 0x0837,	//获取三状态灯开灯时间应答

	IOTYPE_USER_IPCAM_GET_TLIGHT_STATUS_REQ 			= 0x0838,	//获取三状态灯照明灯状态
	IOTYPE_USER_IPCAM_GET_TLIGHT_STATUS_RESP			= 0x0839,	//获取三状态灯照明灯状态应答
//=====================================================================================
//==========================T5886HAJ 相关命令 guotf add 20180614=========================
	IOTYPE_USER_IPCAM_SET_PROJECTION_LIGHT_REQ 			= 0x0840,	//设置投影灯 0: 红灯 1:绿灯 2:蓝灯 3:夜灯 4:旋转
	IOTYPE_USER_IPCAM_SET_PROJECTION_LIGHT_RESP			= 0x0841,	//设置投影灯应答
//=====================================================================================
	//IOT Skills
	IOTYPE_USER_IPCAM_SET_PREPARE_NEW_IOT_SENSOR_REQ	= 0x0910,	//添加新
	IOTYPE_USER_IPCAM_SET_PREPARE_NEW_IOT_SENSOR_RESP	= 0x0911,
	IOTYPE_USER_IPCAM_SET_CHECK_NEW_IOT_SENSOR_REQ		= 0x0912,	//添加新
	IOTYPE_USER_IPCAM_SET_CHECK_NEW_IOT_SENSOR_RESP		= 0x0913,
	IOTYPE_USER_IPCAM_SET_ADD_NEW_IOT_SENSOR_REQ		= 0x0900,	//添加新
	IOTYPE_USER_IPCAM_SET_ADD_NEW_IOT_SENSOR_RESP		= 0x0901,
	IOTYPE_USER_IPCAM_SET_DELETE_IOT_SENSOR_REQ			= 0x0902,	//删除
	IOTYPE_USER_IPCAM_SET_DELETE_IOT_SENSOR_RESP		= 0x0903,
	IOTYPE_USER_IPCAM_SET_IOT_SENSOR_STATE_REQ			= 0x0904,	//设置参数
	IOTYPE_USER_IPCAM_SET_IOT_SENSOR_STATE_RESP			= 0x0905,
	IOTYPE_USER_IPCAM_GET_IOT_SENSOR_STATE_REQ			= 0x0906,	//获取参数
	IOTYPE_USER_IPCAM_GET_IOT_SENSOR_STATE_RESP			= 0x0907,
	IOTYPE_USER_IPCAM_STOP_IOT_SENSOR_ALARM_REQ			= 0x0914,
	IOTYPE_USER_IPCAM_STOP_IOT_SENSOR_ALARM_RESP		= 0x0915,
	
	IOTYPE_USER_IPCAM_PAIR_IOT_STROBE_SIREN_REQ			= 0x0908,
	IOTYPE_USER_IPCAM_PAIR_IOT_STROBE_SIREN_RESP		= 0x0909,
	IOTYPE_USER_IPCAM_STOP_IOT_STROBE_SIREN_REQ			= 0x090a,
	IOTYPE_USER_IPCAM_STOP_IOT_STROBE_SIREN_RESP		= 0x090b,
	IOTYPE_USER_IPCAM_SET_IOT_STROBE_SIREN_STATE_REQ	= 0x090c,
	IOTYPE_USER_IPCAM_SET_IOT_STROBE_SIREN_STATE_RESP	= 0x090d,
	IOTYPE_USER_IPCAM_GET_IOT_STROBE_SIREN_STATE_REQ	= 0x090e,
	IOTYPE_USER_IPCAM_GET_IOT_STROBE_SIREN_STATE_RESP	= 0x090f,

	IOTYPE_USER_IPCAM_SET_DELETE_ALL_SENSOR_REQ			= 0x0916,	//删除所有
	IOTYPE_USER_IPCAM_SET_DELETE_ALL_SENSOR_RESP		= 0x0917,
	//IOT Skills End

	IOTYPE_USER_IPCAM_DEVICE_40TCP_START_REQ			= 0x0918,
	IOTYPE_USER_IPCAM_DEVICE_40TCP_START_RESP			= 0x0919,
	IOTYPE_USER_IPCAM_DEVICE_40TCP_STOP_REQ				= 0x091A,
	IOTYPE_USER_IPCAM_DEVICE_40TCP_STOP_RESP			= 0x091B,
	
	IOTYPE_USER_RTMPPUSH_STOP_REQ						= 0x091C,
	IOTYPE_USER_RTMPPUSH_STOP_RESP						= 0x091D,

/////////////////////////////////////////////////////////////////////////////
	IOTYPE_USER_IPCAM_WEB_GET_IMAGE_SETUP_REQ			= 0x091C,
	IOTYPE_USER_IPCAM_WEB_GET_IMAGE_SETUP_RESP			= 0x091D,
	IOTYPE_USER_IPCAM_WEB_SET_IMAGE_SETUP_REQ			= 0x091E,
	IOTYPE_USER_IPCAM_WEB_SET_IMAGE_SETUP_RESP			= 0x091F,
	
	IOTYPE_USER_IPCAM_WEB_GET_STREAM_SETUP_REQ			= 0x0920,
	IOTYPE_USER_IPCAM_WEB_GET_STREAM_SETUP_RESP			= 0x0921,
	IOTYPE_USER_IPCAM_WEB_SET_STREAM_SETUP_REQ			= 0x0922,
	IOTYPE_USER_IPCAM_WEB_SET_STREAM_SETUP_RESP			= 0x0923,

	IOTYPE_USER_IPCAM_WEB_GET_OSD_SETUP_REQ				= 0x0924,
	IOTYPE_USER_IPCAM_WEB_GET_OSD_SETUP_RESP			= 0x0925,
	IOTYPE_USER_IPCAM_WEB_SET_OSD_SETUP_REQ				= 0x0926,
	IOTYPE_USER_IPCAM_WEB_SET_OSD_SETUP_RESP			= 0x0927,

	IOTYPE_USER_IPCAM_WEB_GET_NIGHTVISION_SETUP_REQ		= 0x0928,
	IOTYPE_USER_IPCAM_WEB_GET_NIGHTVISION_SETUP_RESP	= 0x0929,
	IOTYPE_USER_IPCAM_WEB_SET_NIGHTVISION_SETUP_REQ		= 0x092A,
	IOTYPE_USER_IPCAM_WEB_SET_NIGHTVISION_SETUP_RESP	= 0x092B,

	IOTYPE_USER_IPCAM_WEB_GET_WIRELESS_SETUP_REQ		= 0x092C,
	IOTYPE_USER_IPCAM_WEB_GET_WIRELESS_SETUP_RESP		= 0x092D,
	IOTYPE_USER_IPCAM_WEB_SET_WIRELESS_SETUP_REQ		= 0x092E,
	IOTYPE_USER_IPCAM_WEB_SET_WIRELESS_SETUP_RESP		= 0x092F,

	IOTYPE_USER_IPCAM_WEB_GET_TCPIP_SETUP_REQ			= 0x0930,
	IOTYPE_USER_IPCAM_WEB_GET_TCPIP_SETUP_RESP			= 0x0931,
	IOTYPE_USER_IPCAM_WEB_SET_TCPIP_SETUP_REQ			= 0x0932,
	IOTYPE_USER_IPCAM_WEB_SET_TCPIP_SETUP_RESP			= 0x0933,

	IOTYPE_USER_IPCAM_WEB_GET_DDNS_SETUP_REQ			= 0x0934,
	IOTYPE_USER_IPCAM_WEB_GET_DDNS_SETUP_RESP			= 0x0935,
	IOTYPE_USER_IPCAM_WEB_SET_DDNS_SETUP_REQ			= 0x0936,
	IOTYPE_USER_IPCAM_WEB_SET_DDNS_SETUP_RESP			= 0x0937,

	IOTYPE_USER_IPCAM_WEB_GET_UPNP_SETUP_REQ			= 0x0938,
	IOTYPE_USER_IPCAM_WEB_GET_UPNP_SETUP_RESP			= 0x0939,
	IOTYPE_USER_IPCAM_WEB_SET_UPNP_SETUP_REQ			= 0x093A,
	IOTYPE_USER_IPCAM_WEB_SET_UPNP_SETUP_RESP			= 0x093B,

	IOTYPE_USER_IPCAM_SET_PERSON_DETECT_REQ				= 0x0930,
	IOTYPE_USER_IPCAM_SET_PERSON_DETECT_RESP			= 0x0931,
	IOTYPE_USER_IPCAM_GET_PERSON_DETECT_REQ				= 0x0932,
	IOTYPE_USER_IPCAM_GET_PERSON_DETECT_RESP			= 0x0933,

	IOTYPE_USER_IPCAM_SET_MOTION_TRACKER_REQ			= 0x0934,
	IOTYPE_USER_IPCAM_SET_MOTION_TRACKER_RESP			= 0x0935,
	IOTYPE_USER_IPCAM_GET_MOTION_TRACKER_REQ			= 0x0936,
	IOTYPE_USER_IPCAM_GET_MOTION_TRACKER_RESP			= 0x0937,

	IOTYPE_USER_IPCAM_GET_PERSON_TRACKER_REQ			= 0x0938,
	IOTYPE_USER_IPCAM_GET_PERSON_TRACKER_RESP			= 0x0939,
	IOTYPE_USER_IPCAM_SET_PERSON_TRACKER_REQ			= 0x093A,
	IOTYPE_USER_IPCAM_SET_PERSON_TRACKER_RESP			= 0x093B,
	
	IOTYPE_USER_IPCAM_WEB_GET_P2P_SETUP_REQ				= 0x093C,
	IOTYPE_USER_IPCAM_WEB_GET_P2P_SETUP_RESP			= 0x093D,
	IOTYPE_USER_IPCAM_WEB_SET_P2P_SETUP_REQ				= 0x093E,
	IOTYPE_USER_IPCAM_WEB_SET_P2P_SETUP_RESP			= 0x093F,

	IOTYPE_USER_IPCAM_WEB_GET_STORAGE_SETUP_REQ			= 0x0940,
	IOTYPE_USER_IPCAM_WEB_GET_STORAGE_SETUP_RESP		= 0x0941,
	IOTYPE_USER_IPCAM_WEB_SET_STORAGE_SETUP_REQ			= 0x0942,
	IOTYPE_USER_IPCAM_WEB_SET_STORAGE_SETUP_RESP		= 0x0943,

	IOTYPE_USER_IPCAM_WEB_GET_CAMERA_SETUP_REQ			= 0x0944,
	IOTYPE_USER_IPCAM_WEB_GET_CAMERA_SETUP_RESP			= 0x0945,
	IOTYPE_USER_IPCAM_WEB_SET_CAMERA_SETUP_REQ			= 0x0946,
	IOTYPE_USER_IPCAM_WEB_SET_CAMERA_SETUP_RESP			= 0x0947,

	/*	add by donyj 20190415*/
	IOTYPE_USER_IPCAM_GET_REC_DAY_LIST_REQ				= 0x0948,
	IOTYPE_USER_IPCAM_GET_REC_DAY_LIST_RESP				= 0x0949,
	IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_REQ		= 0x094A,
	IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_RESP		= 0x094B,
	IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_REQ		= 0x094C,
	IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_RESP	= 0x094D,

	IOTYPE_USER_IPCAM_WEB_GET_TASK_SETUP_REQ			= 0x094E,
	IOTYPE_USER_IPCAM_WEB_GET_TASK_SETUP_RESP 			= 0x094F,
	IOTYPE_USER_IPCAM_WEB_SET_TASK_SETUP_REQ			= 0x0950,
	IOTYPE_USER_IPCAM_WEB_SET_TASK_SETUP_RESP 			= 0x0951,
	
	IOTYPE_USER_IPCAM_WEB_START_LIVE_REQ				= 0x0952,
	IOTYPE_USER_IPCAM_WEB_START_LIVE_RESP				= 0x0953,
	IOTYPE_USER_IPCAM_WEB_STOP_LIVE_REQ					= 0x0954,
	IOTYPE_USER_IPCAM_WEB_STOP_LIVE_RESP				= 0x0955,

	IOTYPE_USER_IPCAM_WEB_GET_STREAMCTRL_REQ			= 0x0956,
	IOTYPE_USER_IPCAM_WEB_GET_STREAMCTRL_RESP			= 0x0957,
	IOTYPE_USER_IPCAM_WEB_SET_STREAMCTRL_REQ			= 0x0958,
	IOTYPE_USER_IPCAM_WEB_SET_STREAMCTRL_RESP			= 0x0959,

	////////////////////////////////////AI/////////////////////////////////////////
	IOTYPE_USER_IPCAM_AI_SET_FACE_BACK_REQ              = 0x0960,
	IOTYPE_USER_IPCAM_AI_SET_FACE_BACK_RESP             = 0x0961,
	IOTYPE_USER_IPCAM_AI_STORE_FACE_IMAGE_REQ           = 0x0962,
	IOTYPE_USER_IPCAM_AI_STORE_FACE_IMAGE_RESP          = 0x0963,
	IOTYPE_USER_IPCAM_AI_GET_RELATIONLIST_REQ           = 0x0964,
	IOTYPE_USER_IPCAM_AI_GET_RELATIONLIST_RESP          = 0x0965,
	IOTYPE_USER_IPCAM_AI_GET_EVERYBODY_REQ              = 0x0966,
	IOTYPE_USER_IPCAM_AI_GET_EVERYBODY_RESP             = 0x0967,
	IOTYPE_USER_IPCAM_AI_DELETE_FACE_REQ                = 0x0968,
	IOTYPE_USER_IPCAM_AI_DELETE_FACE_RESP               = 0x0969,
	
	IOTYPE_USER_IPCAM_GET_UPGRADE_INFO_REQ 				= 0x1114,			//app请求设备升级
	IOTYPE_USER_IPCAM_GET_UPGRADE_INFO_RESP				= 0x1115,			//app请求设备升级回复
	IOTYPE_USER_IPCAM_GET_UPGRADE_STATUS_REQ 			= 0x1116,			//app请求设备升级状态
	IOTYPE_USER_IPCAM_GET_UPGRADE_STATUS_RESP			= 0x1117,			//app请求设备升级状态回复

	IOTYPE_USER_IPCAM_GET_SPEAKER_VOLUME_REQ			= 0x1120,
	IOTYPE_USER_IPCAM_GET_SPEAKER_VOLUME_RESP			= 0x1121,
	IOTYPE_USER_IPCAM_SET_SPEAKER_VOLUME_REQ 			= 0x1122,
	IOTYPE_USER_IPCAM_SET_SPEAKER_VOLUME_RESP			= 0x1123,
	
	IOTYPE_USER_IPCAM_SET_LOG_PARAM_REQ					= 0x1124,			//设置设备日志上报参数
	IOTYPE_USER_IPCAM_SET_LOG_PARAM_RESP				= 0x1125,

	IOTYPE_USER_IPCAM_GET_PUSH_MESSAGES_PARAMS_REQ 		= 0x1126,			//获取推送时间间隔
	IOTYPE_USER_IPCAM_GET_PUSH_MESSAGES_PARAMS_RESP 	= 0x1127,
	IOTYPE_USER_IPCAM_SET_PUSH_MESSAGES_PARAMS_REQ  	= 0x1128,
	IOTYPE_USER_IPCAM_SET_PUSH_MESSAGES_PARAMS_RESP 	= 0x1129,

	IOTYPE_USER_IPCAM_REBOOT_REQ						= 0x1130,			//设置设备重启
	IOTYPE_USER_IPCAM_REBOOT_RESP						= 0x1131,

    IOTYPE_USER_CMD_MAX									= 0xFFFF
}ENUM_AVIOCTRL_MSGTYPE;

// module params enum

// end

// transprot cmd enum

// end

#endif
