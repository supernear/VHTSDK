#ifndef PROTOCOL_STRUCT_H
#define PROTOCOL_STRUCT_H

/*
* SD卡录像文件传输结构体
* 
*/

typedef struct 
{
	unsigned int 	total_packet_num;			//文件分包的总包数
	unsigned int	curr_packet_no;				//当前数据包序号
	unsigned int	total_file_length;			//文件总长度
	unsigned int 	curr_packet_length;			//当前数据包长度
	unsigned int	curr_packet_offset;			//当前数据包相对于文件头部位置的偏移量
	//unsigned int 	end_packet_flag;			//文件最后一个数据包标志位
	unsigned int 	reserved[2];				//保留位
}FILE_PACKET_HEAD;


typedef struct 
{
	FILE_PACKET_HEAD file_head;					//数据包头部信息
	char	file_data[9*1024];					//文件数据		
}LAN_FILE_PACKET_BUFFER;

typedef struct 
{
	FILE_PACKET_HEAD file_head;					//数据包头部信息
	char	file_data[3*1024];						//文件数据		
}P2P_FILE_PACKET_BUFFER;

typedef struct
{
	char ssid[32]; 				// WiFi ssid
	char mode;	   				// refer to ENUM_AP_MODE
	char enctype;  				// refer to ENUM_AP_ENCTYPE
	char signal;   				// signal intensity 0--100%
	char status;   				// 0 : invalid ssid or disconnected
								// 1 : connected with default gateway
								// 2 : unmatched password
								// 3 : weak signal and connected
								// 4 : selected:
								//		- password matched and
								//		- disconnected or connected but not default gateway
}SWifiAp;

typedef struct
{
	unsigned short year;	// The number of year.
	unsigned char month;	// The number of months since January, in the range 1 to 12.
	unsigned char day;		// The day of the month, in the range 1 to 31.
	unsigned char wday;		// The number of days since Sunday, in the range 0 to 6. (Sunday = 0, Monday = 1, ...)
	unsigned char hour;     // The number of hours past midnight, in the range 0 to 23.
	unsigned char minute;   // The number of minutes after the hour, in the range 0 to 59.
	unsigned char second;   // The number of seconds after the minute, in the range 0 to 59.
}STimeDay;

typedef struct
{
	STimeDay stTime;
	unsigned char event;
	unsigned char status;	// 0x00: Recording file exists, Event unreaded
							// 0x01: Recording file exists, Event readed
							// 0x02: No Recording file in the event
	unsigned char reserved[2];
}SAvEvent;

typedef struct
{
	unsigned short index;		// the stream index of camera
	unsigned short channel;		// the channel index used in AVAPIs, that is ChID in avServStart2(...,ChID)
	char reserved[4];
}SStreamDef;

typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned int reserved[4];	//
	unsigned char password[64];
} SMsgAVIoctrlAVStream;

typedef struct
{
	int result;					// 0 success -1 password error
	unsigned int reserved[4];	//
} SMsgAVIoctrlAVStreamResp;


/*
IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ		= 0x0322,
** @struct SMsgAVIoctrlGetStreamCtrlReq
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetStreamCtrlReq;

/*
IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ		= 0x0320,
IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP	= 0x0323,
** @struct SMsgAVIoctrlSetStreamCtrlReq, SMsgAVIoctrlGetStreamCtrlResq
*/
typedef struct
{
	unsigned int  channel;	// Camera Index
	unsigned char quality;	//refer to ENUM_QUALITY_LEVEL
	unsigned char reserved[3];
} SMsgAVIoctrlSetStreamCtrlReq, SMsgAVIoctrlGetStreamCtrlResq;

/*
IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP	= 0x0321,
** @struct SMsgAVIoctrlSetStreamCtrlResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetStreamCtrlResp;


/*
 * IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ	= 0x0326,
 * @struct SMsgAVIoctrlGetMotionDetectReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetMotionDetectReq;


/*
 * IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ		= 0x0324,
 * IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP		= 0x0327,
 * @struct SMsgAVIoctrlSetMotionDetectReq, SMsgAVIoctrlGetMotionDetectResp
*/
typedef struct
{
	unsigned int channel; 		//  Camera Index
	unsigned int sensitivity; 	//  移动侦测等级阀值,值越小,灵敏度越高。1(max) ~ 100(min):  (关: 100,  低: 90  中: 60  高: 30)
	unsigned int reserved[4];	//  
}SMsgAVIoctrlSetMotionDetectReq, SMsgAVIoctrlGetMotionDetectResp;


/*
 * IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP	= 0x0325,
 * @struct SMsgAVIoctrlSetMotionDetectResp
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlSetMotionDetectResp;


/*
 * IOTYPE_USER_IPCAM_SPEAKERPROCESS_RESP	= 0x0352,
 * @struct SMsgAVIoctrlSpeakerProcessResp
*/
typedef struct
{
	int result;			// 0:对讲开启成功
						//-1:对讲忙，设备当前正处于对讲状态
						//-2:password erro
	unsigned int reserved[4];	//reserved[0] 用于区分对讲操作应答类型，1表示开启对讲的应答，0表示关闭对讲的应答
}SMsgAVIoctrlSpeakerProcessResp;

/*
IOTYPE_USER_IPCAM_DEVINFO_REQ			= 0x0330,
** @struct SMsgAVIoctrlDeviceInfoReq
*/
typedef struct
{
	unsigned char reserved[4];
}SMsgAVIoctrlDeviceInfoReq;


/*
IOTYPE_USER_IPCAM_DEVINFO_RESP			= 0x0331,
** @struct SMsgAVIoctrlDeviceInfo
*/
#if 1
typedef struct
{
	unsigned char model[16];	// IPCam mode
	unsigned char vendor[16];	// IPCam manufacturer
	unsigned int version;		// IPCam firmware version	ex. v1.2.3.4 => 0x01020304;  v1.0.0.2 => 0x01000002
	unsigned int channel;		// Camera index
	unsigned int total;			// 0: No cards been detected or an unrecognizeable sdcard that could not be re-formatted.
								// -1: if camera detect an unrecognizable sdcard, and could be re-formatted
								// otherwise: return total space size of sdcard (MBytes)								
								
	unsigned int free;			// Free space size of sdcard (MBytes)
	unsigned char reserved[8];	// reserved
}SMsgAVIoctrlDeviceInfofortutkResp;
#endif
#if 1
typedef struct
{
	char device_id[32];					//TUTK_UID号
	char macaddr[32];					//MAC地址
	char soft_ver[32];					//软件版本号
	char firm_ver[16];					//硬件版本号
	char model_num[16];					//设备型号
	char reserved[64];					// reserved
}SMsgAVIoctrlDeviceInfoResp;

#endif

/*
IOTYPE_USER_IPCAM_SETPASSWORD_REQ		= 0x0332,
** @struct SMsgAVIoctrlSetPasswdReq
*/
typedef struct
{
	char oldpasswd[32];			// The old security code
	char newpasswd[32];			// The new security code
}SMsgAVIoctrlSetPasswdReq;


/*
IOTYPE_USER_IPCAM_SETPASSWORD_RESP		= 0x0333,
** @struct SMsgAVIoctrlSetPasswdResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetPasswdResp;


/*
IOTYPE_USER_IPCAM_LISTWIFIAP_REQ		= 0x0340,
** @struct SMsgAVIoctrlListWifiApReq
*/
typedef struct
{
	unsigned char reserved[4];
}SMsgAVIoctrlListWifiApReq;

/*
IOTYPE_USER_IPCAM_LISTWIFIAP_RESP		= 0x0341,
** @struct SMsgAVIoctrlListWifiApResp
*/
typedef struct
{
	unsigned int number; // MAX number: 1024(IOCtrl packet size) / 36(bytes) = 28
	SWifiAp stWifiAp[1];
}SMsgAVIoctrlListWifiApResp;

/*
 * IOTYPE_USER_IPCAM_SETWIFI_REQ			= 0x0342,
 * @struct SMsgAVIoctrlSetWifiReq
*/
typedef struct
{
	unsigned char ssid[32];			//WiFi ssid
	unsigned char password[64];		//if exist, WiFi password
	unsigned char mode;				//refer to ENUM_AP_MODE
	unsigned char enctype;			//refer to ENUM_AP_ENCTYPE
	unsigned char reserved[10];
}SMsgAVIoctrlSetWifiReq;

/*
IOTYPE_USER_IPCAM_SETWIFI_RESP			= 0x0343,
** @struct SMsgAVIoctrlSetWifiResp
*/
typedef struct
{
	int result; 				//0:设置成功，-1: 设置失败
	unsigned char reserved[4];
}SMsgAVIoctrlSetWifiResp;

/*
 * IOTYPE_USER_IPCAM_GETWIFI_REQ			= 0x0344,
 * @struct SMsgAVIoctrlGetWifiReq
*/
typedef struct
{
	unsigned char reserved[4];
}SMsgAVIoctrlGetWifiReq;

/*
 * IOTYPE_USER_IPCAM_GETWIFI_RESP			= 0x0345,
 * @struct SMsgAVIoctrlGetWifiResp //if no wifi connected, members of SMsgAVIoctrlGetWifiResp are all 0
*/
typedef struct
{
	unsigned char ssid[32];		// WiFi ssid
	unsigned char password[64]; // WiFi password if not empty
	unsigned char mode;			// refer to ENUM_AP_MODE
	unsigned char enctype;		// refer to ENUM_AP_ENCTYPE
	unsigned char signal;		// signal intensity 0--100%
	unsigned char status;		// refer to "status" of SWifiAp
}SMsgAVIoctrlGetWifiResp;

/*
IOTYPE_USER_IPCAM_GETRECORD_REQ			= 0x0312,
** @struct SMsgAVIoctrlGetRecordReq
*/
typedef struct
{
	unsigned int channel; // Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetRecordReq;

/*
IOTYPE_USER_IPCAM_SETRECORD_REQ			= 0x0310,
IOTYPE_USER_IPCAM_GETRECORD_RESP		= 0x0313,
** @struct SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq
*/
typedef struct
{
	unsigned int channel;		// Camera Index
	unsigned int recordType;	// Refer to ENUM_RECORD_TYPE
	unsigned char reserved[4];
}SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq;

/*
IOTYPE_USER_IPCAM_SETRECORD_RESP		= 0x0311,
** @struct SMsgAVIoctrlSetRecordResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetRecordResp;


/*
IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ	= 0x0316,
** @struct SMsgAVIoctrlGetRcdDurationReq
*/
typedef struct
{
	unsigned int channel; // Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetRcdDurationReq;

/*
IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ	= 0x0314,
IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP  = 0x0317,
** @struct SMsgAVIoctrlSetRcdDurationReq, SMsgAVIoctrlGetRcdDurationResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned int presecond; 	// pre-recording (sec)
	unsigned int durasecond;	// recording (sec)
}SMsgAVIoctrlSetRcdDurationReq, SMsgAVIoctrlGetRcdDurationResp;


/*
IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP  = 0x0315,
** @struct SMsgAVIoctrlSetRcdDurationResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetRcdDurationResp;

/*
IOTYPE_USER_IPCAM_LISTEVENT_REQ			= 0x0318,
** @struct SMsgAVIoctrlListEventReq
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	STimeDay stStartTime; 		// Search event from ...
	STimeDay stEndTime;	  		// ... to (search event)
	unsigned char event;  		// event type, refer to ENUM_EVENTTYPE
	unsigned char status; 		// 0x00: Recording file exists, Event unreaded
								// 0x01: Recording file exists, Event readed
								// 0x02: No Recording file in the event
	unsigned char reserved[2];
}SMsgAVIoctrlListEventReq;
	
/*
IOTYPE_USER_IPCAM_LISTEVENT_RESP		= 0x0319,
** @struct SMsgAVIoctrlListEventResp
*/
typedef struct
{
	unsigned int  channel;		// Camera Index
	unsigned int  total;		// Total event amount in this search session
	unsigned char index;		// package index, 0,1,2...; 
								// because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
	unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
	unsigned char count;		// how much events in this package
	unsigned char reserved[1];
	SAvEvent stEvent[1];		// The first memory address of the events in this package
}SMsgAVIoctrlListEventResp;

	
/*
IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 	= 0x031A,
** @struct SMsgAVIoctrlPlayRecord
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned int command;	// play record command. refer to ENUM_PLAYCONTROL
	unsigned int Param;		// command param, that the user defined
	STimeDay stTimeDay;		// Event time from ListEvent
	unsigned char reserved[4];
} SMsgAVIoctrlPlayRecord;

/*
IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
** @struct SMsgAVIoctrlPlayRecordResp
*/
typedef struct
{
	unsigned int command;	// Play record command. refer to ENUM_PLAYCONTROL
	unsigned int result; 	// Depends on command
							// when is AVIOCTRL_RECORD_PLAY_START:
							//	result>=0   real channel no used by device for playback
							//	result <0	error
							//			-1	playback error
							//			-2	exceed max allow client amount
	unsigned char reserved[4];
} SMsgAVIoctrlPlayRecordResp; // only for play record start command


/*
IOTYPE_USER_IPCAM_PTZ_COMMAND	= 0x1001,	// P2P Ptz Command Msg 
** @struct SMsgAVIoctrlPtzCmd
*/
typedef struct
{
	unsigned char control;	// PTZ control command, refer to ENUM_PTZCMD
	unsigned char speed;	// PTZ control speed
	unsigned char point;	// no use in APP so far. preset position, for RS485 PT
	unsigned char limit;	// no use in APP so far. 
	unsigned char aux;		// no use in APP so far. auxiliary switch, for RS485 PT
	unsigned char channel;	// camera index
	unsigned char reserve[2];
} SMsgAVIoctrlPtzCmd;

/*
IOTYPE_USER_IPCAM_EVENT_REPORT	= 0x1FFF,	// Device Event Report Msg 
*/
/** @struct SMsgAVIoctrlEvent
 */
typedef struct
{
	STimeDay stTime;
	unsigned long time; 	// UTC Time
	unsigned int  channel; 	// Camera Index
	unsigned int  event; 	// Event Type
	unsigned char reserved[4];
} SMsgAVIoctrlEvent;



#if 0

/* 	IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ	= 0x0400,	// Get Event Config Msg Request 
 */
/** @struct SMsgAVIoctrlGetEventConfig
 */
typedef struct
{
	unsigned int	channel; 		  //Camera Index
	unsigned char   externIoOutIndex; //extern out index: bit0->io0 bit1->io1 ... bit7->io7;=1: get this io value or not get
    unsigned char   externIoInIndex;  //extern in index: bit0->io0 bit1->io1 ... bit7->io7; =1: get this io value or not get
	char reserved[2];
} SMsgAVIoctrlGetEventConfig;
 
/*
	IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP	= 0x0401,	// Get Event Config Msg Response 
	IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ	= 0x0402,	// Set Event Config Msg req 
*/
/* @struct SMsgAVIoctrlSetEventConfig
 * @struct SMsgAVIoctrlGetEventCfgResp
 */
typedef struct
{
	unsigned int    channel;        // Camera Index
	unsigned char   mail;           // enable send email
	unsigned char   ftp;            // enable ftp upload photo
	unsigned char   externIoOutStatus;   // enable extern io output //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
	unsigned char   p2pPushMsg;			 // enable p2p push msg
	unsigned char   externIoInStatus;    // enable extern io input  //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
	char            reserved[3];
}SMsgAVIoctrlSetEventConfig, SMsgAVIoctrlGetEventCfgResp;

/*
	IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP	= 0x0403,	// Set Event Config Msg resp 
*/
/** @struct SMsgAVIoctrlSetEventCfgResp
 */
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int result;	// 0: success; otherwise: failed.
}SMsgAVIoctrlSetEventCfgResp;

#endif


/*
IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ		= 0x0360,
** @struct SMsgAVIoctrlSetEnvironmentReq
*/
typedef struct
{
	unsigned int channel;		// Camera Index
	unsigned char mode;			// refer to ENUM_ENVIRONMENT_MODE
	unsigned char reserved[3];
}SMsgAVIoctrlSetEnvironmentReq;


/*
IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP		= 0x0361,
** @struct SMsgAVIoctrlSetEnvironmentResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned char result;		// 0: success; otherwise: failed.
	unsigned char reserved[3];
}SMsgAVIoctrlSetEnvironmentResp;


/*
IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ		= 0x0362,
** @struct SMsgAVIoctrlGetEnvironmentReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetEnvironmentReq;

/*
IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP		= 0x0363,
** @struct SMsgAVIoctrlGetEnvironmentResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned char mode;			// refer to ENUM_ENVIRONMENT_MODE
	unsigned char reserved[3];
}SMsgAVIoctrlGetEnvironmentResp;


/*
IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ			= 0x0370,
** @struct SMsgAVIoctrlSetVideoModeReq
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned char mode;		// refer to ENUM_VIDEO_MODE
	unsigned char reserved[3];
}SMsgAVIoctrlSetVideoModeReq;


/*
IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP		= 0x0371,
** @struct SMsgAVIoctrlSetVideoModeResp
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char result;	// 0: success; otherwise: failed.
	unsigned char reserved[3];
}SMsgAVIoctrlSetVideoModeResp;


/*
IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ			= 0x0372,
** @struct SMsgAVIoctrlGetVideoModeReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetVideoModeReq;


/*
IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP		= 0x0373,
** @struct SMsgAVIoctrlGetVideoModeResp
*/
typedef struct
{
	unsigned int  channel; 	// Camera Index
	unsigned char mode;		// refer to ENUM_VIDEO_MODE
	unsigned char reserved[3];
}SMsgAVIoctrlGetVideoModeResp;


/*
/IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ			= 0x0380,
** @struct SMsgAVIoctrlFormatExtStorageReq
*/
typedef struct
{
	unsigned int storage; 	// Storage index (ex. sdcard slot = 0, internal flash = 1, ...)
	unsigned char reserved[4];
}SMsgAVIoctrlFormatExtStorageReq;


/*
IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ		= 0x0381,
** @struct SMsgAVIoctrlFormatExtStorageResp
*/
typedef struct
{
	unsigned int  storage; 	// Storage index
	unsigned char result;	// 0: success;
							// -1: format command is not supported.
							// otherwise: failed.
	unsigned char reserved[3];
}SMsgAVIoctrlFormatExtStorageResp;

/*	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ			= 0x0328,
 */
typedef struct
{
	unsigned char reserved[4];
}SMsgAVIoctrlGetSupportStreamReq;


/*	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP			= 0x0329,
 */
typedef struct
{
	unsigned int number; 		// the quanity of supported audio&video stream or video stream
	SStreamDef streams[1];
}SMsgAVIoctrlGetSupportStreamResp;


/* IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ			= 0x032A, //used to speak. but once camera is connected by App, send this at once.
 */
typedef struct
{
	unsigned int channel;		// camera index
	char reserved[4];
}SMsgAVIoctrlGetAudioOutFormatReq;

/* IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP			= 0x032B,
 */
typedef struct
{
	unsigned int channel;		// camera index
	int format;					// refer to ENUM_CODECID in AVFRAMEINFO.h
	char reserved[4];
}SMsgAVIoctrlGetAudioOutFormatResp;

/* IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME			= 0x1002,
 */
typedef struct
{
	unsigned int channel;		// camera index
	char reserved[4];
}SMsgAVIoctrlReceiveFirstIFrame;

/* IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ              = 0x390
 */
typedef struct
{
	unsigned int channel;			// camera index
	unsigned int collect_interval;	// seconds of interval to collect flow information
									// send 0 indicates stop collecting.
}SMsgAVIoctrlGetFlowInfoReq;

/* IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP            = 0x391
 */
typedef struct
{
	unsigned int channel;			// camera index
	unsigned int collect_interval;	// seconds of interval client will collect flow information
}SMsgAVIoctrlGetFlowInfoResp;

/* IOTYPE_USER_IPCAM_CURRENT_FLOWINFO              = 0x392
 */
typedef struct
{
	unsigned int channel;						// camera index
	unsigned int total_frame_count;				// Total frame count in the specified interval
	unsigned int lost_incomplete_frame_count;	// Total lost and incomplete frame count in the specified interval
	unsigned int total_expected_frame_size;		// Total expected frame size from avRecvFrameData2()
	unsigned int total_actual_frame_size;		// Total actual frame size from avRecvFrameData2()
	unsigned int timestamp_ms;					// Timestamp in millisecond of this report.
	char reserved[8];
}SMsgAVIoctrlCurrentFlowInfo;

/* IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ               = 0x3A0
 * IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP              = 0x3A1
 * IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ               = 0x3B0
 * IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP              = 0x3B1
 */
typedef struct
{
	int cbSize;							// the following package size in bytes, should be sizeof(SMsgAVIoctrlTimeZone)
	int nIsSupportTimeZone;
	int nGMTDiff;						// the difference between GMT in hours
	char szTimeZoneString[256];			// the timezone description string in multi-bytes char format
}SMsgAVIoctrlTimeZone;

/*
// dropbox support
IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_REQ      = 0x500,
IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_RESP     = 0x501,
*/
typedef struct
{
    unsigned short nSupportDropbox;     // 0:no support/ 1: support dropbox
    unsigned short nLinked;             // 0:no link/ 1:linked
    char szLinkUDID[64];                // Link UDID for App
}SMsgAVIoctrlGetDropbox;


/*
 // dropbox support
 IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_REQ      = 0x502,
 IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_RESP     = 0x503,
 */
typedef struct
{
    unsigned short nLinked;             // 0:no link/ 1:linked
    char szLinkUDID[64];                // UDID for App
    char szAccessToken[128];             // Oauth token
    char szAccessTokenSecret[128];       // Oauth token secret
	char szAppKey[128];                  // App Key (reserved)
	char szSecret[128];                  // Secret  (reserved)
}SMsgAVIoctrlSetDropbox;



/******************* 自定义结构体 *********************/

/*
* IOTYPE_USER_IPCAM_GET_ALARM_CONTROL_REQ	= 0x03B4
* 获取一键布防请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetAlarmControlReq;


/*
* IOTYPE_USER_IPCAM_SET_ALARM_CONTROL_REQ	= 0x03B2
* IOTYPE_USER_IPCAM_GET_ALARM_CONTROL_RESP	= 0x03B5
* 设置一键布防请求结构体 / 获取一键布防请求应答结构体
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned int enable; 		// 一键布防开关
}SMsgAVIoctrlSetAlarmControlReq, SMsgAVIoctrlGetAlarmControlResp;


/*
* IOTYPE_USER_IPCAM_SET_ALARM_CONTROL_RESP	= 0x03B3
* 设置一键布防请求应答结构体
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetAlarmControlResp;


/*
* IOTYPE_USER_IPCAM_GET_ALARM_RING_REQ  = 0x03B8
* 获取报警铃声状态请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetAlarmRingReq;


/*
* IOTYPE_USER_IPCAM_SET_ALARM_RING_REQ  = 0x03B6
* IOTYPE_USER_IPCAM_GET_ALARM_RING_RESP = 0x03B9
* 设置报警铃声请求结构体 / 获取报警铃声状态请求应答结构体
*/
typedef struct
{
	unsigned int alarm_ring_no;	//报警铃声编号
	unsigned int reserved[4];	//reserved[0] 表示当前铃声播放状态，0表示铃声处于关闭状态，1表示铃声处于播放状态	
}SMsgAVIoctrlSetAlarmRingReq, SMsgAVIoctrlGetAlarmRingResp;


/*
* IOTYPE_USER_IPCAM_SET_ALARM_RING_RESP = 0x03B7
* 设置报警铃声请求应答结构体
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetAlarmRingResp;


/*
* IOTYPE_USER_IPCAM_PLAY_ALARM_RING_RESP = 0x03BE
* 开始播放报警铃声请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlPlayAlarmRingReq;


/*
* IOTYPE_USER_IPCAM_PLAY_ALARM_RING_START = 0x03BD
* 开始播放报警铃声请求应答结构体
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned int reserved[4]; //reserved[0] 用于区分播放铃声操作应答类型，1表示开启播放铃声的应答，0表示关闭播放铃声的应答
}SMsgAVIoctrlPlayAlarmRingResp;


/*
* IOTYPE_USER_IPCAM_GET_ALARM_RING_DATA_RESP = 0x03BB
* 上传自定义报警铃声应答结构体
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlGetAlarmRingDataResp;


/*
* IOTYPE_USER_IPCAM_GET_ALL_PARAM_REQ = 0x03C0
* 获取所有配置项参数请求结构体
*/
typedef struct
{
	unsigned int channel; 					// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetAllParamReq;


/*
* IOTYPE_USER_IPCAM_GET_ALL_PARAM_RESP = 0x03C1
* 获取所有配置项参数请求应答结构体
*/
typedef struct
{
	char device_id[32];							//TUTK_UID号
	char macaddr[32];							//MAC地址
	char soft_ver[32];							//软件版本号
	char firm_ver[16];							//硬件版本号
	char model_num[16];							//设备型号
	char wifi_ssid[32];							//WIFI SSID 号
	unsigned int  video_mirror_mode;			//镜像 & 翻转模式 (0:none,1:horizontal,2:vertical,3:horizonta+vertical) 
	unsigned int  manual_record_switch;			//手动录像开关   (关: 0,  开: 1)
	unsigned int  motion_detect_sensitivity;	//移动侦测等级   (关: 100,  低: 90  中: 60  高: 30)
	unsigned int  pir_detect_switch;			//红外侦测开关   (关: 0,  开: 1)	
	unsigned int  video_quality;				//码流质量       (高清: 0, 流畅: 1)
	unsigned int  audio_alarm_sensitivity;		//音频侦测等级 0 关 1 低 2 中 3高
	unsigned char battery_status;				//电池电量
	unsigned char reserved1[3];					//保留
	unsigned int  reserved[2];					//保留	
}SMsgAVIoctrlGetAllParamResq;


/*
* IOTYPE_USER_IPCAM_SET_MOBILE_CLENT_TYPE_REQ = 0x03C2
* 安卓手机客户端置位请求结构体
*/
typedef struct
{
	unsigned int alarm_msg_req; 		// 
	unsigned int reserve[4];			//
}SMsgAVIoctrlSetAndriodAlarmMsgReq;


/*
* IOTYPE_USER_IPCAM_SET_MOBILE_CLENT_TYPE_RESP = 0x03C3
* 安卓手机客户端置位请求应答结构体
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[4];   //reserved[0] 为当前sid对应的置位状态
}SMsgAVIoctrlSetAndriodAlarmMsgResp;


/*
* IOTYPE_USER_IPCAM_SEND_ANDROID_MOTION_ALARM = 0x03C4
* 安卓手机客户端专用推送命令结构体
*/
typedef struct
{
	unsigned int alarm_type;	//ALARM_TYPE
	char pic_url[256];			//图片URL
	unsigned int reserved[4];
	double humiture_value;
}SMsgAVIoctrlSendAndriodAlarmMsg;


/*
* IOTYPE_USER_IPCAM_GET_AUTHENTICATION_REQ	 = 0x03C7
* 获取设备鉴权信息请求结构体
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned char reserved[4];
}SMsgAVIoctrlGetDeviceAuthenticationInfoReq;


/*
* IOTYPE_USER_IPCAM_SET_AUTHENTICATION_REQ	 = 0x03C5
* IOTYPE_USER_IPCAM_GET_AUTHENTICATION_RESP  = 0x03C8
* 设置设备鉴权信息请求结构体 / 获取设备鉴权信息请求应答结构体
*/
typedef struct
{
	char user_name[64];
	char passwd[64];
	unsigned char reserved[4];
}SMsgAVIoctrlSetDeviceAuthenticationInfoReq, SMsgAVIoctrlGetDeviceAuthenticationInfoResp;


/*
* IOTYPE_USER_IPCAM_SET_AUTHENTICATION_RESP = 0x03C6
* 设置设备鉴权信息请求应答结构体
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned char reserved[4];
}SMsgAVIoctrlSetDeviceAuthenticationInfoResp;


/*
* IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY_REQ = 0x03C9
* 获取设备能力集请求结构体
*/
typedef struct
{
	unsigned int channel; 				// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetDeviceAbilityReq;


/*
* IOTYPE_USER_IPCAM_GET_DEVICE_ABILITY_RESP = 0x03CA
* 获取设备能力集请求应答结构体
*/
typedef struct
{
	unsigned int  pir_flag;				//是否有PIR传感器，0:无，1:有，下同
	unsigned int  ptz_flag;				//是否有云台
	unsigned int  mic_flag;				//是否有咪头
	unsigned int  speaker_flag;			//是否有喇叭
	unsigned int  temperature_flag;		//是否有温感探头
	unsigned int  resolution_0_flag;	//主码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int  resolution_1_flag;	//子码流分辨率大小 Width:高16位 Height:低16位  Ming@2016.06.14
	unsigned int  reserver[6];			
}SMsgAVIoctrlGetDeviceAbilityResp;


/*
* IOTYPE_USER_IPCAM_GET_MONTH_EVENT_LIST_REQ = 0x03CB
* 获取某月录像事件列表请求结构体
*/
typedef struct
{
	//char monthevent_date[7];	        //指定的年月份，某年某月，格式如: "201603" (2016 means year,03 means month)
	unsigned int  channel; 				// Camera Index
	unsigned int  reserved[2];
}SMsgAVIoctrlGetMonthEventListReq;

/*
* IOTYPE_USER_IPCAM_GET_MONTH_EVENT_LIST_RESP = 0x03CC
* 获取某月录像事件列表请求应答结构体
*/
typedef struct
{
	unsigned int  result;					//获取录像列表返回值(0:获取录像列表成功, 1:获取录像列表失败 , 2:录像列表为空，即为无录像, 3:无卡)
	unsigned int  total_num;				//分片总数
	unsigned int  curr_no;					//当前分片序号
	char 		  monthevent_list[911];		//搜索到有录像的日期列表, example:"201603010003|201603020001|201603100022|" (2016 means year, 03 means month, 01 means day , 0003 means how many files exist) 	
	unsigned int  reserved[2];				//
}SMsgAVIoctrlGetMonthEventListResp;

/*
* IOTYPE_USER_IPCAM_GET_DAY_EVENT_LIST_REQ = 0x03CD
* 获取某天录像事件列表请求结构体
*/
typedef struct
{
	char dayevent_date[9];			//指定的某一天，某年某月某日，格式如: "20160316" (2016 means year, 03 means month, 16 means the day)
	unsigned int  file_type;		//请求文件类型 (视频: 0 , 图片: 1)
	unsigned int  reserved[2];		//
}SMsgAVIoctrlGetDayEventListReq;

/*
* IOTYPE_USER_IPCAM_GET_DAY_EVENT_LIST_RESP = 0x03CE
* 获取某天录像事件列表请求应答结构体
*/
typedef struct
{
	unsigned int  result;				//获取天录像列表返回值(0:获取录像列表成功, 1:获取录像列表失败 , 2:录像列表为空，即为无录像, 3:无卡)
	unsigned int  total_num;			//分片总数
	unsigned int  curr_no;				//当前分片序号
	char day_file_list[961];			//搜索到的录像和图片列表, example:"201603121132231bc0120.mp4@xxxxxx|201603121133231bc0120.mp4@xxxxxx|*.jpg"	201606211719320ca0000.jpg
										/* 
										  各条目(如201603121132231bc0120.mp4@xxxxxx)长度为32位
										  (2016 means year, 03 means month, 12 means day, 11 means hour, 32 means minute, 23 means second, 
										  1    means the file can not remove when auto circulate record is open,
										  b    means record type (value frome enum RECORD_TYPE + 'a')
										  c    means alarm type (value frome enum E_SDK_ALARM_TYPE + 'a')) 
									 	  012  means time 
										  .mp4 means file type
										  xxxxxx means the size of file 
										*/
	unsigned int  reserved[2];
}SMsgAVIoctrlGetDayEventListResp;


/*
* IOTYPE_USER_IPCAM_GET_RECORDFILE_START_REQ = 0x03CF
* 开始下载指定录像文件请求结构体
*/
typedef struct
{
	unsigned int  channel; 	// Camera Index
	char filename[32];	//录像或图片文件名
	unsigned int  reserved[4];
}SMsgAVIoctrlGetRecordFileStartReq;


/*
* IOTYPE_USER_IPCAM_GET_RECORDFILE_START_RESP = 0x03D0
* 开始下载指定录像文件请求应答结构体
*/
typedef struct
{
	int result;  //下载录像时，客户端需要根据 result的值给出相应的提示信息
				/*result的值解释：
				 2: UDP重传方式开始下载
				 1: TCP方式开始下载录像成功
				 0：UDP方式开始下载录像成功
				-1: 指定录像文件不存在
				-2: 其他录像文件下载中
				*/
	unsigned int reserved[4];
}SMsgAVIoctrlGetRecordFileStartResp;


/*
* IOTYPE_USER_IPCAM_GET_RECORDFILE_STOP_REQ = 0x03D1
* 结束下载指定录像文件请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetRecordFileStopReq;


/*
* IOTYPE_USER_IPCAM_GET_RECORDFILE_STOP_RESP = 0x03D2
* 结束下载指定录像文件请求应答结构体
*/
typedef struct
{
	int result;		// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlGetRecordFileStopResp;


/*
* IOTYPE_USER_IPCAM_LOCK_RECORDFILE_REQ = 0x03D3
* 对指定录像文件进行上锁或解锁请求结构体
*/
typedef struct
{
	unsigned char file_name[32];	//录像或图片文件名
	unsigned int  lock_value;		// 1:上锁， 0:解锁
	unsigned int  reserved[4];
}SMsgAVIoctrlLockRecordFileReq;


/*
* IOTYPE_USER_IPCAM_LOCK_RECORDFILE_RESP = 0x03D4
* 对指定录像文件进行上锁或解锁请求应答结构体
*/
typedef struct
{
	int result;		// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlLockRecordFileResp;


/*
* IOTYPE_USER_IPCAM_DEL_RECORDFILE_REQ = 0x03D5
* 删除指定录像文件请求结构体
*/
typedef struct
{
	char filename[32];	//录像或图片文件名
	unsigned int  reserved[4];
}SMsgAVIoctrlDelRecordFileReq;


/*
* IOTYPE_USER_IPCAM_DEL_RECORDFILE_RESP = 0x03D6
* 删除指定录像文件请求应答结构体
*/
typedef struct
{
	int result;		// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlDelRecordFileResp;


/*
* IOTYPE_USER_IPCAM_MANUAL_RECORD_REQ = 0x03D7
* 手动录像开启或结束请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int operate_value;  // 1: 开启手动录像， 0: 关闭手动录像
	unsigned int reserved[4];
}SMsgAVIoctrlManualRecordReq;


/*
* IOTYPE_USER_IPCAM_MANUAL_RECORD_RESP = 0x03D8
* 手动录像开启或结束请求应答结构体
*/
typedef struct
{
	//unsigned int operate_value;  // 1: 开启手动录像， 0: 关闭手动录像
	unsigned int result;  //针对开启手动录像时，客户端需要根据 result的值给出相应的提示信息
						  /*result的值解释：
			                0：开启或关闭录像成功
			                1: 开启或关闭录像失败
			                2：无卡，不允许录像
			                3: 卡出错，不允许录像
			                4: 卡剩余容量不足，不允许录像			                
							5: 正在录像中，不允许录像
			                6: 操作太频繁
		                  */
	unsigned int reserved[4];
}SMsgAVIoctrlManualRecordResp;


/*
* IOTYPE_USER_IPCAM_GET_STORAGE_INFO_REQ = 0x03D9
* 获取 SD卡当前容量信息请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetStorageInfoReq;


/*
* IOTYPE_USER_IPCAM_GET_STORAGE_INFO_RESP = 0x03DA
* 获取 SD卡当前容量信息请求应答结构体
*/
typedef struct
{
	int 		 result;		// (0: 成功获取SD卡容量， -1: 失败，一般为无卡)
	unsigned int total_size;	//总容量
	unsigned int used_size;		//已用容量
	unsigned int free_size;		//未用容量
	unsigned int reserved[4];
}SMsgAVIoctrlGetStorageInfoResp;


/*
* IOTYPE_USER_IPCAM_FORMAT_STORAGE_REQ = 0x03DB
* 格式化 SD卡请求结构体
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlFormatStorageReq;

   
/*
* IOTYPE_USER_IPCAM_FORMAT_STORAGE_RESP = 0x03DC
* 格式化 SD卡请求应答结构体
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlFormatStorageResp;


/*
* IOTYPE_USER_IPCAM_FILE_RESEND_REQ = 0x03DD
* SD卡录像下载丢包重传请求结构体
*/
typedef struct
{
	unsigned int   channel; 					// Camera Index
	unsigned char  loss_flag;					//丢包标志位: (0: 没丢包，不需重传， 1:有丢包，需重传)
	unsigned int   total_num;					//
	unsigned short loss_packet_no[256];			//丢失包的序号
	unsigned char  reserved[2];
}SMsgAVIoctrlFileRetransportReq;

   
/*
* IOTYPE_USER_IPCAM_FILE_RESEND_RESP = 0x03DE
* SD卡录像下载丢包重传请求应答
*/
typedef struct
{
	int result;								// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlFileRetransportResp;


/* 
 * IOTYPE_USER_IPCAM_SET_PIRDETECT_REQ		 = 0x03DF
 * IOTYPE_USER_IPCAM_GET_PIRDETECT_RESP		 = 0x03E2
 * 设置PIR红外侦测参数请求 | 获取PIR红外侦测参数请求应答
*/
typedef struct
{
	unsigned int channel; 		//  Camera Index
	unsigned int pir_switch; 	//  PIR侦测等级(1-10, 其中 0 为关闭 )，值越小，灵敏度越高  (关: 0,  低: 8, 中: 5, 高: 2), 暂时默认下发 5
	unsigned int reserved[4];	//  
}SMsgAVIoctrlSetPirDetectReq, SMsgAVIoctrlGetPirDetectResp;

/* 
 * IOTYPE_USER_IPCAM_SET_PIRDETECT_RESP		 = 0x03E0
 * 设置PIR红外侦测参数请求应答
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[4];
}SMsgAVIoctrlSetPirDetectResp;

/* 
 * IOTYPE_USER_IPCAM_GET_PIRDETECT_REQ		 = 0x03E1
 * 获取PIR红外侦测参数请求
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[4];
}SMsgAVIoctrlGetPirDetectReq;


/* 
 * IOTYPE_USER_IPCAM_SET_TIME_PARAM_REQ		 = 0x03E3
 * IOTYPE_USER_IPCAM_GET_TIME_PARAM_RESP	 = 0x03E6
 * 设置时间校验参数请求 | 获取时间校验参数请求应答
*/
typedef struct
{
	unsigned int 	AppTimeSec;			//App端的时间 (以秒数下发)
	unsigned int	NtpOpen;			//ntp校时开关 (1:开启， 0:关闭， 默认为开启)
	unsigned int	EuroTime;			//夏令时开关  (1:开启,  0:关闭， 默认为关闭)
	unsigned int	NtpRefTime;			//ntp校时间隔 (单位秒, 默认为300s)
	int				TimeZone;			//时区 (-12~11， 默认为 8)
	char     		NtpServer[64];		//ntp校时服务器地址
	unsigned int	NtpPort; 			//ntp校时服务器端口
	unsigned int	reserved[2];
}SMsgAVIoctrlSetTimeParamReq, SMsgAVIoctrlGetTimeParamResp;

/* 
 * IOTYPE_USER_IPCAM_SET_TIME_PARAM_RESP		 = 0x03E4
 * 设置时间校验参数请求应答
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetTimeParamResp;

/* 
 * IOTYPE_USER_IPCAM_GET_TIME_PARAM_REQ		 = 0x03E5
 * 获取时间校验参数请求
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[2];
}SMsgAVIoctrlGetTimeParamReq;



/* 
 * IOTYPE_USER_IPCAM_SET_TEMPERATURE_REQ	 = 0x03E7
 * IOTYPE_USER_IPCAM_GET_TEMPERATURE_RESP	 = 0x03EA
 * 设置温度报警参数请求 | 获取温度报警参数请求应答
*/
typedef struct
{
	unsigned int alarm_enale;			//上下限温度报警开关， 0:上下限全部关闭， 1:上限开启，下限关闭，2:上限关闭，下限开启，3:上下限全部开启
	unsigned int temperature_type;		//温度表示类型， 0:表示摄氏温度.C， 1；表示华氏温度.F
	double curr_temperature_value;		//当前温度
	double max_alarm_value;				//上限报警温度
	double min_alarm_value;				//下限报警温度
	unsigned char reserved[16];			//
}SMsgAVIoctrlSetTemperatureAlarmParamReq, SMsgAVIoctrlGetTemperatureAlarmParamResp;


/* 
 * IOTYPE_USER_IPCAM_SET_TEMPERATURE_RESP		 = 0x03E8
 * 设置温度报警参数请求应答
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetTemperatureAlarmParamResp;

/* 
 * IOTYPE_USER_IPCAM_GET_TEMPERATURE_REQ		 = 0x03E9
 * 获取温度报警参数请求
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int reserved[2];
}SMsgAVIoctrlGetTemperatureAlarmParamReq;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_REQ	 = 0x03EB
 * IOTYPE_USER_IPCAM_GET_LIGHT_RESP	        = 0x03EE
 * 设置灯开关 | 获取灯开关应答*/
typedef struct
{
	unsigned int un_switch;			//0:关闭， 1:开启
	unsigned char reserved[16];	
}SMsgAVIoctrlSetLightReq, SMsgAVIoctrlGetLightResp;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_RESP		 = 0x03EC
 * 设置灯开关应答*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetLightResp;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_TIME_REQ	 = 0x03F3
 * IOTYPE_USER_IPCAM_GET_LIGHT_TIME_RESP	 = 0x03F6
 * 设置灯打开时间 | 获取灯打开时间应答*/
typedef struct
{
	unsigned int un_pir_time;			//pir触发开灯时间
	unsigned int un_man_time;			//手动开灯时间
	unsigned char reserved[16];	
}SMsgAVIoctrlSetLightTimeReq, SMsgAVIoctrlGetLightTimeResp;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_TIME_RESP		 = 0x03F4
 * 设置灯开关应答*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetLightTimeResp;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_AUTO_TIME_REQ	 = 0x03FA
 * IOTYPE_USER_IPCAM_GET_LIGHT_AUTO_TIME_RESP	 = 0x03FD
 * 设置灯打开时间 | 获取灯打开时间应答*/
typedef struct
{
	unsigned int un_time_on_hour;		//定时开灯  小时
	unsigned int un_time_on_min;		//定时开灯  分钟
	unsigned int un_time_off_hour;		//定时关灯  小时
	unsigned int un_time_off_min;		//手动关灯   分钟
	unsigned int un_time_wday_switch;	/*开关设置  按位表示 
										* 第0位表示星期一，第六位表示星期天
										* 0->开启 1->关闭
										*/
	unsigned char reserved[16];	
}SMsgAVIoctrlSetLightAutoTimeReq, SMsgAVIoctrlGetLighAutotTimeResp;

/* * IOTYPE_USER_IPCAM_SET_LIGHT_AUTO_TIME_RESP		 = 0x03FB
 * 设置灯开关应答*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetLightAutoTimeResp;

/* * IOTYPE_USER_IPCAM_SET_AUDIO_ALARM_REQ 	    = 0x03EF
 *IOTYPE_USER_IPCAM_GET_AUDIO_ALARM_RESP		= 0x03F2
 * 设置声音报警开关 | 获取音报警开关应答*/
typedef struct
{
	unsigned int un_switch;			//0:关闭， 1:低2:中3:高
	unsigned char reserved[16];	
}SMsgAVIoctrlSetAudioAlarmReq, SMsgAVIoctrlGetAudioAlarmResp;

/* * IOTYPE_USER_IPCAM_SET_AUDIO_ALARM_RESP		= 0x03F0
 * 设置声音报警开关应答*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetAudioAlarmResp;

/* 
 * IOTYPE_USER_IPCAM_RESET_RESP		 = 0x03F8
 * 恢复出厂设置应答
*/
typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlResetResp;

/*
//升级
IOTYPE_USER_IPCAM_SET_UPDATE_REQ			= 0x0450,	//获取升级参数
IOTYPE_USER_IPCAM_SET_UPDATE_RESP			= 0x0451,	//获取升级参数应答

*/
typedef struct
{
	int port;	//端口
	char ip_addr[128];

}SMsgAVIoctrlSetUpdateReq;

typedef struct
{
	int result;					// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetUpdateResp;


/*
*
//amba 电池状态
IOTYPE_USER_IPCAM_GET_BATTERY_REQ			= 0x0470,	//获取电池状态	
IOTYPE_USER_IPCAM_GET_BATTERY_RESP			= 0x0471,	//获取电池状态应答
*/
typedef struct
{
	unsigned int un_battery_level;	//
	unsigned int un_charge_state;	//0:off 1:on
	unsigned int un_battery_state;  //0:full 1:middle 2:low 3.deep low

}SMsgAVIoctrlGetbatteryReq,SMsgAVIoctrlGetbatteryResp;

/*
*
IOTYPE_USER_IPCAM_SET_BATTERY_ALARM_REQ 		= 0x0472,	//设置电量报警参数请求
IOTYPE_USER_IPCAM_GET_BATTERY_ALARM_RESP	= 0x0475,	//获取电量报警参数请求应答

*/
typedef struct
{
	unsigned char alarm_switch[4];			//电量告警类型开关,(0:关闭推送，1:开启推送) alarm_type[0]:电量消息推送总开关, alarm_type[1]:满电, alarm_type[2]:低电剩余%25的电，alarm_type[3]:电量过低剩余%5的电
	unsigned char reserved[16]; 
}SMsgAVIoctrlSetbatteryAlarmReq,SMsgAVIoctrlGetbatteryAlarmResp;
/*
IOTYPE_USER_IPCAM_SET_BATTERY_ALARM_RESP	= 0x0473,	//设置电量报警参数请求应答
*/
typedef struct
{
	int result; 				// 0: success; otherwise: failed.
	unsigned int reserved[2];
}SMsgAVIoctrlSetbatteryAlarmResp;

/*
类TCP方式下载录像文件请求重传结构体
*/
typedef struct 
{
	unsigned int   channel; 					// Camera Index
	unsigned int   nextNum_flag;				// 请求下一包标志
	unsigned int   curr_num;					// 当前包号
	unsigned char  reserved[4];			
}SMsgAVIoctrlRetransmissionReq;

typedef struct 
{
	int result;						// 0: success; otherwise: failed.
	unsigned int reserved[2];				
}SMsgAVIoctrlRetransmissionResp;

typedef struct 
{
  unsigned int  utctime;        // 请求时间
  int        type;          // 0 是获取预览图 1是开始回放视频2剪接视频
  int        duration;        // 剪接时长
  int        nChannel;        // 通道号
  char      childID[16];      // 子设备ID
  unsigned char  password[64];      // 密码
}SMsgAVIoctrlPlayRecordReq;

typedef struct 
{
	int result;				// 0 success -1 password error
	unsigned int type;
	unsigned int utctime;	//预览图请求返回文件实际位置时间
	unsigned char  reserved[4];	
}SMsgAVIoctrlPlayPreviewResp;

///////////////////////////////////////////////////////////////////////
/*	add by donyj 20190415*/
#define REC_DAY_EVENT_NODE_MAX_SIZE	256
typedef struct
{
	unsigned int 	start_time;
	unsigned int 	end_time;
	unsigned int 	type;
	unsigned int  	reserved[2];
}SMsgAVIoctrl_DAY_EVENT_NODE;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_LIST_REQ = 0x0948
* 获取某月录像事件列表请求结构体
*/
typedef struct
{
	unsigned int  type;
	unsigned int  reserved[2];
}SMsgAVIoctrlGetRecDaytListReq;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_LIST_RESP = 0x0949
* 获取某月录像事件列表请求应答结构体
*/
typedef struct
{
	unsigned int  result;					//获取录像列表返回值(0:获取录像列表成功, 1:获取录像列表失败 , 2:录像列表为空，即为无录像, 3:无卡)
	char 		  monthevent_list[1024];	//搜索到有录像的日期列表, example:"201603013|201603021|2016031022|" (2016 means year, 03 means month, 01 means day , 3 means how many files exist) 	
	unsigned int  reserved[2];				//
}SMsgAVIoctrlGetRecDaytListResp;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_REQ = 0x094A
* 获取某天录像事件列表请求结构体
*/
typedef struct
{
	unsigned int  time;				//指定的某一天，某年某月某日，格式如: unix时间戳
	unsigned int  type;				//请求文件类型 (全天: 0 , 报警: 1)
	unsigned int  reserved[2];		//
}SMsgAVIoctrlGetRecDayEventListReq;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_RESP = 0x094B
* 获取某天录像事件列表请求应答结构体
*/
typedef struct
{
	unsigned int  result;				//获取天录像列表返回值(0:获取录像列表成功, 1:获取录像列表失败 , 2:录像列表为空，即为无录像, 3:无卡)
	unsigned int  total_num;			//分片总数
	unsigned int  page_num;				//当前分片录像数
	SMsgAVIoctrl_DAY_EVENT_NODE day_event_list[REC_DAY_EVENT_NODE_MAX_SIZE];
	unsigned int  reserved[2];
}SMsgAVIoctrlGetRecDayEventListResp;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_REQ = 0x094C
* 获取某天录像事件列表请求结构体
*/
typedef struct
{
	unsigned int  time;				//指定的某一天，某年某月某日，格式如: unix时间戳
	unsigned int  type;				//请求文件类型 (全天: 0 , 报警: 1)
	unsigned int  reserved[2];		//reserved[0]:分页大小(不分页,默认大小256:0 , 分页大小:非0) reserved[1]:预留
}SMsgAVIoctrlGetRecDayEventRefreshReq;

/*
* IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_RESP = 0x094D
* 获取某天录像事件列表请求应答结构体
*/
typedef struct
{
	unsigned int  result;				//获取天录像列表返回值(0:获取录像列表成功, 1:获取录像列表失败 , 2:录像列表为空，即为无录像, 3:无卡)
	unsigned int  total_num;			//分片总数
	SMsgAVIoctrl_DAY_EVENT_NODE day_event_list[REC_DAY_EVENT_NODE_MAX_SIZE];
	unsigned int  reserved[2];
}SMsgAVIoctrlGetRecDayEventRefreshResp;

typedef struct 
{
 unsigned int utctime[10];   	// 请求时间, 一次最大支持获取10个缩略图
 int    nCount;     			// 请求数量
 int    nChannel;    			// 通道号
 char   reserved[16];   		// 预留
}SMsgAVIoctrlGetRecJpegReq;


typedef struct 
{
 int    nResult;    			// 请求结果
 char   reserved[16];   		// 预留
}SMsgAVIoctrlGetRecJpegResp;


#endif
