#ifndef MEDIA_DEFINE_H
#define MEDIA_DEFINE_H

typedef struct
{
	unsigned int	nChannel;			// 混合流通道
	unsigned int	nDataSize;			// data数据长度
	char			reserve[16];
}frame_mix_head;

typedef struct
{
	unsigned int	nFrameNo;			// 帧号
	unsigned int	nFrameType;			// 帧类型	gos_frame_type_t
	unsigned int	nCodeType;			// 编码类型 gos_codec_type_t
	unsigned int	nFrameRate;			// 视频帧率，音频采样率
	unsigned int	nTimestamp;			// 时间戳
	unsigned short	sWidth;				// 视频宽
	unsigned short	sHeight;			// 视频高
	unsigned int	nUtcTime;			// Unix时间戳
	unsigned int	nDataSize;			// data数据长度
	char			data[0];
}frame_head;

typedef struct
{
	unsigned int	nFrameNo;			// 帧号
	unsigned int	nFrameType;			// 帧类型	gos_frame_type_t
	unsigned int	nCodeType;			// 编码类型 gos_codec_type_t
	unsigned int	nFrameRate;			// 视频帧率，音频采样率
	unsigned int	nTimestamp;			// 时间戳
	unsigned int	nUtcTime;			// 绝对时间s			备注：一拖多实时流时，此属性被赋值为流下标
	unsigned int	nChannel;			// 设备通道，用于多路录像区分
	unsigned int	nDataSize;			// data数据长度
	unsigned short	sWidth;				// 视频宽
	unsigned short	sHeight;			// 视频高
}rec_frame_head;

typedef enum
{
	gos_codec_unknown = 0,

	gos_video_codec_start = 10,
	gos_video_H264_AAC,
	gos_video_H264_G711,
	gos_video_H265,
	gos_video_MPEG4,
	gos_video_MJPEG,
	gos_video_codec_end,

	gos_audio_codec_start = 50,
	gos_audio_AAC,
	gos_audio_G711A,
	gos_audio_G711U,
	gos_audio_pcm,
	gos_audio_codec_end,

} gos_codec_type_t;

typedef enum
{
	gos_unknown_frame = 0,				// 未知帧
	gos_video_i_frame = 1,				// I 帧
	gos_video_p_frame = 2,				// P 帧
	gos_video_b_frame = 3,				// B 帧
	gos_video_rec_i_frame = 4,			//录像I帧
	gos_video_rec_p_frame = 5,			//录像P帧
	gos_video_rec_b_frame = 6,			//录像B帧
	gos_video_rec_end_frame = 7,		//录像完成接收完成(不带数据)
	gos_video_cut_i_frame = 8,			//剪接录像I帧
	gos_video_cut_p_frame = 9,			//剪接录像P帧
	gos_video_cut_b_frame = 10,			//剪接录像B帧
	gos_video_cut_end_frame =11,		//剪接录像完成(不带数据)
	gos_video_preview_i_frame = 12,		//预览图
	gos_video_rec_start_frame = 13,		//录像开始播放(不需要解码)
    gos_video_encryption_i_frame = 15,

	gos_audio_frame   	= 50,			// 音频帧
	gos_rec_audio_frame   = 51, 		// 音频帧
	gos_cut_audio_frame   = 52, 		// 音频帧

	gos_special_frame 	= 100,			// 特殊帧	 gos_special_data 比如门灯灯状态主动上传app
	gos_ai_frame 			= 101,		// AI信息帧SAiInfo
	gos_rec_picture_frame 	= 102,		// 卡录像缩略图
} gos_frame_type_t;

typedef struct
{
	unsigned short codec_id;	// Media codec type defined in sys_mmdef.h,
								// MEDIA_CODEC_AUDIO_PCMLE16 for audio,
								// MEDIA_CODEC_VIDEO_H264 for video.
	unsigned char flags;		// Combined with IPC_FRAME_xxx.
	unsigned char cam_index;	// 0 - n

	unsigned char onlineNum;	// number of client connected this device
	unsigned char reserve1[3];

	unsigned int reserve2;	//
	unsigned int timestamp;	// Timestamp of the frame, in milliseconds

    // unsigned int videoWidth;
    // unsigned int videoHeight;

}FRAMEINFO_t;

/* CODEC ID */
typedef enum
{
	MEDIA_CODEC_UNKNOWN			= 0x00,
	MEDIA_CODEC_VIDEO_MPEG4		= 0x4C,
	MEDIA_CODEC_VIDEO_H263		= 0x4D,
	MEDIA_CODEC_VIDEO_H264		= 0x4E,
	MEDIA_CODEC_VIDEO_MJPEG		= 0x4F,
	MEDIA_CODEC_VIDEO_HEVC      = 0x50,

    MEDIA_CODEC_AUDIO_AAC_RAW   = 0x86,   // 2017-05-04 add AAC Raw data audio codec definition
    MEDIA_CODEC_AUDIO_AAC_ADTS  = 0x87,   // 2017-05-04 add AAC ADTS audio codec definition
    MEDIA_CODEC_AUDIO_AAC_LATM  = 0x88,   // 2017-05-04 add AAC LATM audio codec definition
    MEDIA_CODEC_AUDIO_AAC       = 0x88,   // 2014-07-02 add AAC LATM audio codec definition
    MEDIA_CODEC_AUDIO_G711U     = 0x89,   //g711 u-law
    MEDIA_CODEC_AUDIO_G711A     = 0x8A,   //g711 a-law
    MEDIA_CODEC_AUDIO_ADPCM     = 0X8B,
	MEDIA_CODEC_AUDIO_PCM		= 0x8C,
	MEDIA_CODEC_AUDIO_SPEEX		= 0x8D,
	MEDIA_CODEC_AUDIO_MP3		= 0x8E,
    MEDIA_CODEC_AUDIO_G726      = 0x8F,

}ENUM_CODECID;

/* FRAME Flag */
typedef enum
{
	IPC_FRAME_FLAG_PBFRAME	= 0x00,	// A/V P/B frame..
	IPC_FRAME_FLAG_IFRAME	= 0x01,	// A/V I frame.
	IPC_FRAME_FLAG_MD		= 0x02,	// For motion detection.
	IPC_FRAME_FLAG_IO		= 0x03,	// For Alarm IO detection.
}ENUM_FRAMEFLAG;

typedef enum
{
	AUDIO_SAMPLE_8K			= 0x00,
	AUDIO_SAMPLE_11K		= 0x01,
	AUDIO_SAMPLE_12K		= 0x02,
	AUDIO_SAMPLE_16K		= 0x03,
	AUDIO_SAMPLE_22K		= 0x04,
	AUDIO_SAMPLE_24K		= 0x05,
	AUDIO_SAMPLE_32K		= 0x06,
	AUDIO_SAMPLE_44K		= 0x07,
	AUDIO_SAMPLE_48K		= 0x08,
}ENUM_AUDIO_SAMPLERATE;

typedef enum
{
	AUDIO_DATABITS_8		= 0,
	AUDIO_DATABITS_16		= 1,
}ENUM_AUDIO_DATABITS;

typedef enum
{
	AUDIO_CHANNEL_MONO		= 0,
	AUDIO_CHANNEL_STERO		= 1,
}ENUM_AUDIO_CHANNEL;

#endif
