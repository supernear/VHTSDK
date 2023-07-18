#ifndef TURN_API_H
#define TURN_API_H
#include "turn_types.h"

void Turn_SetLogLevel(int loglv);
int Turn_Initialize(Turn_Mode_E mode, int maxbuff, int maxclnt, int port_guss);
int Turn_DeInitialize(void);
int Turn_InitDeviceCapability(Turn_devability* capbility, Turn_params* params, Turn_cb* cb); 
int Turn_SetLoginStatus(int state);

int Turn_StartService(void);
int Turn_StopService(void);

int Turn_clearCache(TurnConn conn);
int Turn_MarkLiveState(TurnConn conn, int state);
int Turn_MarkAudioState(TurnConn conn, int state);
int Turn_MarkSpeakState(TurnConn conn, int state);
int Turn_MarkChannel(TurnConn conn, int channel);
int Turn_CheckChannel(TurnConn conn, int channel);

int Turn_SendData(TurnConn conn, char* data, unsigned int length, int type);
int Turn_SendRecData(int channel, TurnConn conn, char* data, unsigned int length, TurnData_Type_E type);
int Turn_SendAVData(int channel, char* data, unsigned int length, TurnData_Type_E type, unsigned long long pts_ms, int iskey);

int Turn_StartLive(Turn_Live_Mode_E mode, char* rtmp_url);
int Turn_StopLive();
int Turn_SendLiveData(char* data, unsigned int length, TurnData_Type_E type, unsigned long long pts_ms, int iskey);

#endif
