#ifndef TURN_PROXY_CB_H
#define TURN_PROXY_CB_H

int Turn_On_SpeakData(TurnConn conn, int type, void* data, int length);
int Turn_On_UserCmd(TurnConn conn, int type, void* data, int length);
int Turn_On_ServerState(Turn_state_e state, TurnConn* conn, void* data, int length);

#endif