#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ulog.h"
#include "Pthread.h"
#include "turn_api.h"
#include "protocol_struct.h"
#include "protocol_cmd.h"
#include "media_define.h"
#include "aes256.h"
#include "sha256.h"

#define		DEMO_REPLAY_FILE 		"rec_replay.media"
#define		DEMO_LIVE_CHN0_FILE 	"live_stream_ch0.media"
#define		DEMO_LIVE_CHN1_FILE 	"live_stream_ch1.media"


typedef struct
{
	Pthread_t			live_tid;
	int					live_stop;
	Pthread_t			replay_tid;
	int					replay_stop;

	Turn_Replay_t		replay_info;
	int					speaker_state;
	TurnConn 			speaker_conn;
}Turn_Instance_t;

static Turn_Instance_t s_Turn_Instance = {0};
static int s_liveChn = -1;
static FILE* s_spk_fd = NULL;
static FILE* s_live_fd = NULL;

int Turn_On_ForceIDR(int channel)
{
	ULOGI("force idr..");

	return 0;
}

void* Turn_On_Live_Task(void* lparam)
{
	//Turn_Instance_t* handle = (Turn_Instance_t*)lparam;
	ULOGW("Turn Live task start...");

//	int ret;
	unsigned int rbytes;
	frame_head frameHead;
	unsigned char* live_frame = (unsigned char*)malloc(256*1024);
	unsigned char* enc_frame = NULL;
	unsigned int enc_len = 0;

	unsigned char* denc_frame = NULL;
	unsigned int denc_len = 0;
    unsigned char key[32] = {0};

   // FILE* fp1 =  fopen("enc.media", "wb");

	while(s_Turn_Instance.live_stop != 1)
	{
		if(s_liveChn == -1)
		{
			usleep(20*1000);
			continue;
		}

		// 读取帧头信息
		rbytes = fread(&frameHead, 1, sizeof(frameHead), s_live_fd);
		if(rbytes > 0)
		{
			TurnData_Type_E turnData_type;
			if(frameHead.nCodeType != gos_audio_G711A)
			{
				turnData_type = E_TurnData_Type_video;
			}
			else
			{
				turnData_type = E_TurnData_Type_audio;
			}

			ULOGD("nCodeType:%02u nFrameType:%02u nFrameNo:%04u nUtcTime:%u nTimestamp:%u nFrameRate:%04u nDataSize:%u",
			        frameHead.nCodeType,
			        frameHead.nFrameType,
			        frameHead.nFrameNo,
			        frameHead.nUtcTime,
			        frameHead.nTimestamp,
			        frameHead.nFrameRate,
			        frameHead.nDataSize);
			memcpy(live_frame, &frameHead, sizeof(frameHead));
			rbytes = fread(live_frame+sizeof(frameHead), 1, frameHead.nDataSize, s_live_fd);
            if(frameHead.nFrameType == gos_video_i_frame)
            {
                help_sha256_mac((unsigned char *)"40EAA085-5783-48c0-A420-5CC77F32865E",
                                strlen("40EAA085-5783-48c0-A420-5CC77F32865E"), key);
                int ret = aes256_cbc_enc(live_frame+sizeof(frameHead), rbytes, &enc_frame, &enc_len, key);
                if (ret == 0)
                {
                    frameHead.nFrameType = gos_video_encryption_i_frame;
                    frameHead.nDataSize = enc_len;
                    memcpy(live_frame, &frameHead, sizeof(frameHead));
                    memcpy(live_frame+sizeof(frameHead), (char*)(enc_frame), enc_len);
                    rbytes = enc_len;
                    //aes256_cbc_dec(enc_frame, enc_len, &denc_frame, &denc_len, key);
                    //ULOGW("rbye = %d  enc_len = %d  denc_len = %d", rbytes, enc_len, denc_len);
                    //if(denc_frame != NULL)
                    //{
                    //   int ii = 0;
                    //    for(ii = 0; ii < 16; ii ++)
                    //    {
                    //        ULOGW("0x%x  0x%x", *(live_frame+sizeof(frameHead) +ii), *(denc_frame + ii));
                    //    }
                   // }
                   if(enc_frame != NULL)
                   {
                        free(enc_frame);
                        enc_frame = NULL;
                   }
                }
            }

             {
                // fwrite(live_frame, 1, rbytes+sizeof(frameHead), fp1);
             }

            int isKey = 0;
            if( frameHead.nFrameType==gos_video_i_frame || frameHead.nFrameType==gos_video_encryption_i_frame)
            {
                isKey =1;
            }
			Turn_SendAVData(0, (char*)live_frame, rbytes+sizeof(frameHead), turnData_type, 0, isKey);

			if(frameHead.nCodeType != gos_audio_G711A)
			{
				usleep(25*1000);
			}
			else
			{
				usleep(10*1000);
			}
		}
		else
		{
			if(s_live_fd != NULL)
			{
				fclose(s_live_fd);
				s_live_fd = NULL;
			}

			if(s_liveChn == 0)
			{
				s_live_fd = fopen(DEMO_LIVE_CHN0_FILE, "rb");
			}
			else
			{
				s_live_fd = fopen(DEMO_LIVE_CHN1_FILE, "rb");
			}
		}
	}
    if(live_frame != NULL)
    {
        free(live_frame);
        live_frame = NULL;
    }
	return NULL;
}

int Turn_On_LiveStart(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_START clnt id:%d", conn.id);
	SMsgAVIoctrlAVStream *p = (SMsgAVIoctrlAVStream*)data;
	SMsgAVIoctrlAVStreamResp resp;
	memset((void *)&resp, 0, sizeof(SMsgAVIoctrlAVStreamResp));

	// 请求一个I帧 更快显示图像
	Turn_clearCache(conn);
	Turn_MarkLiveState(conn, 1);
	Turn_On_ForceIDR(p->channel);


	if(s_live_fd == NULL)
	{
		s_live_fd = fopen(DEMO_LIVE_CHN0_FILE, "rb");
	}

	s_liveChn = 0;

	if(s_Turn_Instance.live_tid == 0)
	{
		Pthread_Attr attr;
		Pthread_Result rlt;
		memset(&attr, 0, sizeof(Pthread_Attr));
		strcpy(attr.name, "Turn_On_Live_Task");

		s_Turn_Instance.live_stop = 0;
		rlt = Pthread_create(&s_Turn_Instance.live_tid, &attr, Turn_On_Live_Task, &s_Turn_Instance);
		if(rlt != Pthread_SUCCESS)
		{
			s_Turn_Instance.live_tid = 0;
			resp.result = -1;
		}
	}

	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlAVStreamResp), IOTYPE_USER_IPCAM_STARTRESP);

	return 0;
}
int Turn_On_LiveStop(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_STOP");
//	SMsgAVIoctrlAVStream *p = (SMsgAVIoctrlAVStream*)data;

	Turn_MarkLiveState(conn, 0);
	if(s_Turn_Instance.live_tid != 0)
	{
		s_Turn_Instance.live_stop = 1;
		Pthread_join(s_Turn_Instance.live_tid, NULL);
		s_Turn_Instance.live_tid = 0;
	}
	s_liveChn = -1;
	if(s_live_fd != NULL)
	{
		fclose(s_live_fd);
		s_live_fd = NULL;
	}
	return 0;
}


int Turn_On_AudioStart(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_AUDIOSTART");
	Turn_MarkAudioState(conn, 1);

	return 0;
}

int Turn_On_AudioStop(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_AUDIOSTOP");
	Turn_MarkAudioState(conn, 0);

	return 0;
}

int Turn_On_SpeakStart(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_SPEAKERSTART");
	SMsgAVIoctrlSpeakerProcessResp resp;
	memset((void *)&resp, 0, sizeof(SMsgAVIoctrlSpeakerProcessResp));

	if(s_Turn_Instance.speaker_state == 1)
	{
		ULOGW("speaker already start..");
		resp.result = -1;
		Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlSpeakerProcessResp), IOTYPE_USER_IPCAM_SPEAKERPROCESS_RESP);
		return 0;
	}
	else
	{
		memcpy(&s_Turn_Instance.speaker_conn, &conn, sizeof(TurnConn));

		Turn_MarkSpeakState(conn, 1);
		s_Turn_Instance.speaker_state = 1;
		Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlSpeakerProcessResp), IOTYPE_USER_IPCAM_SPEAKERPROCESS_RESP);


		if(s_spk_fd == NULL)
		{
			s_spk_fd = fopen("./speak_data.g711a", "wb");
			if(s_spk_fd == NULL)
			{
				ULOGE("speak_data.g711a open error");
			}
		}

		return 0;
	}
}

int Turn_On_SpeakStop(TurnConn conn, int type, void* data, int length)
{
	ULOGI("IOTYPE_USER_IPCAM_SPEAKERSTOP");
//	SMsgAVIoctrlAVStream *p = (SMsgAVIoctrlAVStream*)data;
	SMsgAVIoctrlSpeakerProcessResp resp;
	Turn_MarkSpeakState(conn, 0);
	resp.result = 0;
	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlSpeakerProcessResp), IOTYPE_USER_IPCAM_SPEAKERPROCESS_RESP);
	// 回调上层
	s_Turn_Instance.speaker_state = 0;

	if(s_spk_fd != NULL)
	{
		fclose(s_spk_fd);
		s_spk_fd = NULL;
	}

	return 0;
}

int Turn_On_VideoQuality_Set(TurnConn conn, int type, void* data, int length)
{
	SMsgAVIoctrlSetStreamCtrlResp resp;
	SMsgAVIoctrlSetStreamCtrlReq *p = (SMsgAVIoctrlSetStreamCtrlReq*)data;

	ULOGI("try Set video channel %d quality = %d", p->channel, p->quality);
	s_liveChn = p->quality;
	if(s_live_fd != NULL)
	{
		fclose(s_live_fd);
		s_live_fd = NULL;
	}

	if(s_liveChn == 0)
	{
		s_live_fd = fopen(DEMO_LIVE_CHN0_FILE, "rb");
	}
	else
	{
		s_live_fd = fopen(DEMO_LIVE_CHN1_FILE, "rb");
	}

	resp.result = 0;
	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlSetStreamCtrlResp),IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP);

	return 0;
}


int Turn_On_SpeakData(TurnConn conn, int type, void* data, int length)
{
	if(s_spk_fd != NULL)
	{
		int wbytes = fwrite((unsigned char*)data+sizeof(frame_head), 1, length-sizeof(frame_head), s_spk_fd);
		ULOGD("recv speak data lenght:%d", length-sizeof(frame_head));
	}

	return 0;
}

int Turn_On_Replay_SpecFrame(TurnConn conn, int play_type, int frame_type)
{
	frame_head frameInfo;
	memset(&frameInfo, 0, sizeof(frameInfo));

	frameInfo.nFrameType = frame_type;
	frameInfo.nDataSize = 0;

	int wbytes = Turn_SendRecData(0, conn, (char*)&frameInfo, sizeof(frameInfo), E_TurnData_Type_video);
	ULOGW("send frame_type:%d wbytes:%d", frame_type, wbytes);

	return 0;
}

int Turn_On_Replay_Packet(int play_type, frame_head* frameHead, TurnData_Type_E* media_type)
{
	if(frameHead->nFrameType >= gos_audio_frame)
	{
		*media_type = E_TurnData_Type_audio;
	}
	else
	{
		*media_type = E_TurnData_Type_video;
	}

	if(play_type == Turn_Replay_type_play)
	{
		if(frameHead->nFrameType == gos_video_i_frame)
			frameHead->nFrameType = gos_video_rec_i_frame;
		else if(frameHead->nFrameType == gos_video_p_frame )
			frameHead->nFrameType = gos_video_rec_p_frame;
		else if(frameHead->nFrameType == gos_audio_frame)
			frameHead->nFrameType = gos_rec_audio_frame;
		else
			ULOGE("error nFrameType");
	}
	else if(play_type == 2)
	{
		if(frameHead->nFrameType == gos_video_i_frame)
			frameHead->nFrameType = gos_video_cut_i_frame;
		else if(frameHead->nFrameType ==gos_video_p_frame )
			frameHead->nFrameType = gos_video_cut_p_frame;
		else if(frameHead->nFrameType == gos_audio_frame)
			frameHead->nFrameType = gos_cut_audio_frame;
		else
			ULOGE("error nFrameType");
	}

	return 0;
}

/*
0	成功
-1	查找失败
1	读取失败
*/
int Turn_On_Replay(Turn_Instance_t* handle, Turn_Replay_t replay_info)
{
	int ret;
	int rbytes;
	FILE* fd = NULL;
	char* filename = DEMO_REPLAY_FILE;
	frame_head frameHead;
	frame_mix_head mixHead = {0};
	char* rec_frame = (char*)malloc(256*1024);

	while(handle->replay_stop != 1)
	{
		if(handle->replay_info.conn.id == -1){
			ULOGW("playback force stop...");
			break;
		}

		if(handle->replay_info.refresh == 1){
			ULOGW("playback info change...");
			break;
		}

		if(fd == NULL){
			fd = fopen(filename, "rb");
			if(fd == NULL){
				ULOGE("file %s open error", filename);
				break;
			}
		}

		// 读取帧头信息
		rbytes = fread(&frameHead, 1, sizeof(frameHead), fd);
		if (rbytes == 0)
		{
			ULOGI("file:%s read end...", filename);
			if(fd != NULL){
				fclose(fd);
				fd = NULL;
			}
			continue;
		}
		else if(rbytes != sizeof(frameHead))
		{// 读数据异常
			ULOGE("read frame head error readLen:%d head:%d", rbytes, sizeof(frameHead));
			break;
		}

		// 打包结构体
		TurnData_Type_E media_type;
		Turn_On_Replay_Packet(replay_info.type, &frameHead, &media_type);
		ULOGD("nChannel:%d nCodeType:%02u nFrameType:%02u nFrameNo:%04u nUtcTime:%u nTimestamp:%u nFrameRate:%04u nDataSize:%u", mixHead.nChannel, frameHead.nCodeType, frameHead.nFrameType, frameHead.nFrameNo, frameHead.nUtcTime, frameHead.nTimestamp, frameHead.nFrameRate, frameHead.nDataSize);
		memcpy(rec_frame, &frameHead, sizeof(frameHead));

		// 读取帧内容
		if(frameHead.nDataSize > 256*1024 - sizeof(frameHead))
		{
			ULOGE("data size %d out of max frame buffer %d", frameHead.nDataSize, 256*1024 - sizeof(frameHead));
			break;
		}

		rbytes = fread(rec_frame+sizeof(frameHead), 1, frameHead.nDataSize, fd);
		if (rbytes != frameHead.nDataSize)
		{
			ULOGE("read frame data error readLen:%d!", fd, rbytes);
			break;
		}

		// 发送 - 当发送太快回触发buffer满，Turn将返回-70027，此时应该尝试重发
		int send_result = 0;
		while(handle->replay_stop != 1)
		{
			if(handle->replay_info.refresh == 1)
			{
				ULOGW("playback info change...");
				break;
			}

			ret = Turn_SendRecData(mixHead.nChannel, replay_info.conn, rec_frame, sizeof(frameHead)+frameHead.nDataSize, media_type);
			if(ret == -70027){// 发送太快
				if(frameHead.nFrameType == gos_video_rec_i_frame || frameHead.nFrameType == gos_video_cut_i_frame){
					ULOGW("p2p send error! ret:%d frame_type:%d", ret, frameHead.nFrameType);
				}
				usleep(20*1000);
				continue;
			}else if(ret == -70023){// 对象不存在
				ULOGE("send record data error[%d], object not exist", ret);
				break;
			}
			else if(ret == -1)
			{// 连接已经不存在
				ULOGE("connection object not exist", ret);
				break;
			}

			send_result = 1;
			break;
		}

		if(send_result != 1)	break;
		if(media_type == E_TurnData_Type_video)	usleep(10*1000);		//适当休眠
	}

	if(fd != NULL){
		fclose(fd);
		fd = NULL;
	}

	free(rec_frame);

	return ret;
}

void* Turn_On_Replay_Task(void* lparam)
{
	Turn_Instance_t* handle = (Turn_Instance_t*)lparam;
	ULOGW("Turn Replay task start...");

	int ret;
	while(handle->replay_stop != 1)
	{
		if(handle->replay_info.refresh == 1)
		{
			handle->replay_info.refresh = 0;
			ULOGW("clnt id:%d playback start type:%d utctime:%u duration:%d", handle->replay_info.conn.id, handle->replay_info.type, handle->replay_info.utctime, handle->replay_info.duration);

			Turn_clearCache(handle->replay_info.conn);

			if(handle->replay_info.type == Turn_Replay_type_play)
			{
				// 发送起始帧
				Turn_On_Replay_SpecFrame(handle->replay_info.conn, Turn_Replay_type_play, gos_video_rec_start_frame);
				// 真正查找文件发送数据
				ret = Turn_On_Replay(handle, handle->replay_info);
				// 发送结束帧
				Turn_On_Replay_SpecFrame(handle->replay_info.conn, Turn_Replay_type_play, gos_video_rec_end_frame);

				if(ret == -1)
				{
					ULOGE("error happen...");
				}
			}
			else
			{
				// 真正查找文件发送数据
				Turn_On_Replay(handle, handle->replay_info);
				// 发送结束帧
				Turn_On_Replay_SpecFrame(handle->replay_info.conn, Turn_Replay_type_cut, gos_video_cut_end_frame);
			}
		}

		usleep(100*1000);
	}

	ULOGW("Turn Replay task end...");

	return NULL;
}

int Turn_On_Replay_Start(TurnConn conn, int type, void* data, int length)
{
	// 直接发送文件
	SMsgAVIoctrlPlayPreviewResp resp;
	SMsgAVIoctrlPlayRecordReq* p = (SMsgAVIoctrlPlayRecordReq*)data;
	memset(&resp,0,sizeof(SMsgAVIoctrlPlayPreviewResp));
	ULOGI("utctime:%u type:%d duration:%d password:%s", p->utctime, p->type, p->duration, p->password);

	// 启动回放线程
	if(s_Turn_Instance.replay_tid == 0)
	{
		memcpy(&s_Turn_Instance.replay_info.conn, &conn, sizeof(TurnConn));
		s_Turn_Instance.replay_info.refresh = 1;
		s_Turn_Instance.replay_info.type = p->type;
		s_Turn_Instance.replay_info.utctime = p->utctime;
		s_Turn_Instance.replay_info.duration = p->duration;

		Pthread_Attr attr;
		Pthread_Result rlt;
		memset(&attr, 0, sizeof(Pthread_Attr));
		strcpy(attr.name, "Turn_On_Replay_Task");

		s_Turn_Instance.replay_stop = 0;
		rlt = Pthread_create(&s_Turn_Instance.replay_tid, &attr, Turn_On_Replay_Task, &s_Turn_Instance);
		if(rlt != Pthread_SUCCESS)
		{
			s_Turn_Instance.replay_tid = 0;
			resp.result = -1;
		}
		else
		{
			resp.result = 0;
		}
	}
	else
	{
		if(s_Turn_Instance.replay_info.conn.id != conn.id && s_Turn_Instance.replay_info.conn.id != -1)
		{
			ULOGW("record play already lock...");
			resp.result = -1;
		}
		else
		{
			resp.result = 0;
			// 刷新定位
			memcpy(&s_Turn_Instance.replay_info.conn, &conn, sizeof(TurnConn));
			s_Turn_Instance.replay_info.refresh = 1;
			s_Turn_Instance.replay_info.type = p->type;
			s_Turn_Instance.replay_info.utctime = p->utctime;
			s_Turn_Instance.replay_info.duration = p->duration;
			ULOGW("record play task already start, refresh...");
		}
	}

	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlPlayPreviewResp), IOTYPE_USER_IPCAM_PLAY_RECORD_RESP);


	return 0;
}

int Turn_On_Replay_Stop(TurnConn conn, int type, void* data, int length)
{
	SMsgAVIoctrlPlayPreviewResp resp;
	memset(&resp,0,sizeof(SMsgAVIoctrlPlayPreviewResp));

	if(s_Turn_Instance.replay_tid != 0)
	{
		s_Turn_Instance.replay_stop = 1;
		Pthread_join(s_Turn_Instance.replay_tid, NULL);
		s_Turn_Instance.replay_tid = 0;
	}

	Turn_clearCache(conn);
	resp.result = 0;
	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlPlayPreviewResp), IOTYPE_USER_IPCAM_STOP_PLAY_RECORD_RESP);

	return 0;
}

int Turn_On_Replay_MediaListGet(TurnConn conn, int type, void* data, int length)
{
//	SMsgAVIoctrlGetRecDayEventListReq* p = (SMsgAVIoctrlGetRecDayEventListReq*)data;
	SMsgAVIoctrlGetRecDayEventListResp resp;
	memset(&resp, 0, sizeof(SMsgAVIoctrlGetRecDayEventListResp));

	return 0;
}

int Turn_On_Replay_MediaListRefresh(TurnConn conn, int type, void* data, int length)
{
	//SMsgAVIoctrlGetRecDayEventRefreshReq* p = (SMsgAVIoctrlGetRecDayEventRefreshReq*)data;
	SMsgAVIoctrlGetRecDayEventRefreshResp resp;
	memset(&resp, 0, sizeof(SMsgAVIoctrlGetRecDayEventRefreshResp));

	resp.total_num = 1;
	resp.day_event_list[0].start_time = 1685664401;
	resp.day_event_list[0].end_time = 1685664411;
	resp.day_event_list[0].type = 0;

	Turn_SendData(conn, (char*)&resp, sizeof(SMsgAVIoctrlGetRecDayEventListResp), IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_RESP);

	return 0;

}

int Turn_On_Replay_ThumbnailGet(TurnConn conn, int type, void* data, int length)
{
	//SMsgAVIoctrlGetRecJpegReq* p = (SMsgAVIoctrlGetRecJpegReq*)data;
	SMsgAVIoctrlGetRecJpegResp resp;
	memset(&resp, 0, sizeof(SMsgAVIoctrlGetRecJpegResp));

	return 0;
}

int Turn_On_UserCmd(TurnConn conn, int type, void* data, int length)
{
	ULOGI("handle clnt id:%d clnt type:%d cmd type:0x%x length:%d", conn.id, conn.type, type, length);
	switch(type)
	{
		case IOTYPE_USER_IPCAM_START:
		{
			ULOGW("IOTYPE_USER_IPCAM_START");
			Turn_On_LiveStart(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_STOP:
		{
			ULOGW("IOTYPE_USER_IPCAM_STOP");
			Turn_On_LiveStop(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_AUDIOSTART:
		{
			ULOGW("IOTYPE_USER_IPCAM_AUDIOSTART");
			Turn_On_AudioStart(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_AUDIOSTOP:
		{
			ULOGW("IOTYPE_USER_IPCAM_AUDIOSTOP");
			Turn_On_AudioStop(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_SPEAKERSTART:
		{
			ULOGW("IOTYPE_USER_IPCAM_SPEAKERSTART");
			Turn_On_SpeakStart(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_SPEAKERSTOP:
		{
			ULOGW("IOTYPE_USER_IPCAM_SPEAKERSTOP");
			Turn_On_SpeakStop(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ:
		{
			ULOGW("IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ");
			Turn_On_VideoQuality_Set(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_PLAY_RECORD_REQ:
		{
			ULOGI("IOTYPE_USER_IPCAM_PLAY_RECORD_REQ");
			Turn_On_Replay_Start(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_STOP_PLAY_RECORD_REQ:
		{
			ULOGI("IOTYPE_USER_IPCAM_STOP_PLAY_RECORD_REQ");
			Turn_On_Replay_Stop(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_REQ:
		{
			ULOGI("IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_LIST_REQ");
			Turn_On_Replay_MediaListGet(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_REQ:
		{
			ULOGI("IOTYPE_USER_IPCAM_GET_REC_DAY_EVENT_REFRESH_REQ");
			Turn_On_Replay_MediaListRefresh(conn, type, data, length);
			break;
		}
		case IOTYPE_USER_IPCAM_GET_REC_JPEG_REQ:
		{
			ULOGI("IOTYPE_USER_IPCAM_GET_REC_JPEG_REQ");
			Turn_On_Replay_ThumbnailGet(conn, type, data, length);
			break;
		}
		default:
		{
			ULOGE("unsupport cmd:0x%x", type);
			break;
		}
	}

	return 0;
}

int Turn_On_ServerState(Turn_state_e state, TurnConn* conn, void* data, int length)
{
	// 可以这里来根据句柄关闭回放线程
	int replay_stop = 0;
	int speaker_stop = 0;
	if(data != NULL)
	{
		ULOGW("on turn state:%d %s", state, data);
	}

	// 某个链路断开
	if(state == P2pTurn_state_conn_disconnect || state == TcpTurn_state_conn_disconnect)
	{
		if(conn != NULL)
		{
			if(s_Turn_Instance.replay_info.conn.id == conn->id && s_Turn_Instance.replay_info.conn.type == conn->type)
			{
				ULOGW("conn type:%d id:%d, replay force stop..", conn->type, conn->id);
				replay_stop = 1;
			}

			if(s_Turn_Instance.speaker_state == 1 && s_Turn_Instance.speaker_conn.id == conn->id && s_Turn_Instance.speaker_conn.type == conn->type)
			{
				ULOGW("conn type:%d id:%d, speaker force stop..", conn->type, conn->id);
				speaker_stop = 1;
			}
		}
	}
	else if(state == TcpTurn_state_disconnect)
	{
		if(s_Turn_Instance.replay_info.conn.type == E_Turn_Conn_TCP_Av)
		{
			ULOGW("TCP_Av disconnect replay force stop..");
			replay_stop = 1;
		}
		if(s_Turn_Instance.speaker_state == 1 && s_Turn_Instance.speaker_conn.type == E_Turn_Conn_TCP_Av)
		{
			ULOGW("TCP_Av disconnect speaker force stop..");
			speaker_stop = 1;
		}
	}
	else if(state == P2pTurn_state_disconnect)
	{
		if(s_Turn_Instance.replay_info.conn.type == E_Turn_Conn_P2P)
		{
			ULOGW("P2P disconnect, replay force stop..");
			replay_stop = 1;
		}
		if(s_Turn_Instance.speaker_state == 1 && s_Turn_Instance.speaker_conn.type == E_Turn_Conn_P2P)
		{
			ULOGW("TCP_Av disconnect speaker force stop..");
			speaker_stop = 1;
		}
	}

	if(replay_stop == 1)
	{
		s_Turn_Instance.replay_info.conn.id = -1;
	}
	if(speaker_stop == 1)
	{
		if(s_Turn_Instance.speaker_state == 1)
		{
			s_Turn_Instance.speaker_state = 0;
		}
	}
	return 0;
}

