#ifndef TURN_TYPES_H
#define TURN_TYPES_H

#define TURN_DATABUFF_SIZE			(128*1024)
#define TURN_MAX_ERROR_STRING_LEN 	(256)
#define TURN_MAX_RECV_DATA_SIZE		(5*1024)
#define TURN_MAX_RECV_CMD_SIZE		(20)
#define TURN_MAX_TALK_SIZE			(5*1024)

typedef enum
{
	P2pTurn_state_idle,
	P2pTurn_state_running,
	P2pTurn_state_disconnect,		// 整个服务断开
	P2pTurn_state_conn_disconnect,	// 单个链接断开
	TcpTurn_state_idle,
	TcpTurn_state_running,
	TcpTurn_state_disconnect,		// 整个服务断开
	TcpTurn_state_conn_disconnect,	// 单个链接断开
	
	TcpPush_state_idle,
	TcpPush_state_running,
	TcpPush_state_disconnect,		// 整个服务断开
	TcpPush_state_conn_disconnect,	// 单个链接断开
}Turn_state_e;

typedef enum
{
	E_Turn_Mode_P2P 	= 1,
	E_Turn_Mode_TCP		= 2,
	E_Turn_Mode_PUSH	= 4,
}Turn_Mode_E;

typedef enum
{
	E_TURN_LIVE_MODE_RTMP,
	E_TURN_LIVE_MODE_TURN,
}Turn_Live_Mode_E;

typedef enum
{
	E_TurnData_Type_video 	= 0x00F2,
	E_TurnData_Type_audio 	= 0x00F3,
	E_TurnData_Type_notic	= 0x00F4,
	E_TurnData_Type_file	= 0x00F5,
	E_TurnData_Type_cmd		= 0x00F6,
}TurnData_Type_E;

typedef enum
{
	E_TurnDs_state_idle,
	E_TurnDs_state_running,
	E_TurnDs_state_success,
	E_TurnDs_state_failure,	E_TurnDs_state_unauthorized,}TurnDs_State_E;

typedef enum
{
	E_Turn_Conn_P2P,
	E_Turn_Conn_TCP_Signal,
	E_Turn_Conn_TCP_Av,
}Turn_Conn_E;

typedef struct
{
	int 			id;
	Turn_Conn_E 	type;
}TurnConn;

typedef struct
{
	Turn_Mode_E 	mode;
	int 			live;		// 是否开启直播
	int 			audio;		// 是否开启音频
	int 			speak;		// 是否开启音频
	void*			transport;
	int 			conn_id;
	Turn_Conn_E 	conn_type;
	int 			iwait;
	int				channel;
}TurnClnt;

typedef enum
{
	Turn_Replay_type_play = 1,
	Turn_Replay_type_cut,
}Turn_Replay_type_e;

typedef struct
{
	TurnConn conn;			// 回放的客户
	int type;				// 0 是获取历史数据预览图1是实时播放历史数据
	int	refresh;			// 刷新
	int duration;			//剪接时长
	unsigned int utctime;	//app 定位时间
}Turn_Replay_t;

typedef struct{
	TurnConn conn;
	int type;
	int len;
	unsigned char* body;
}Turn_Cmd;

typedef struct
{
	int				retry_ms;			//	重新发起连接的时间，这将影响反应速度, 最少 20ms
	char			dispatch_addr[128];	// 调度服务器地址 组合结构是  IP:PORT;IP:PORT

	char			service_addr[128];	// 服务服务器地址
	unsigned short	service_port;		// 服务服务器地址

	char			uid[32];
	char			passwd[64];
}Turn_params;

typedef struct
{
	char		p2p_tcp;			// 使用tcp连接与服务器通信
	char		p2p_port_guess; 	// 使用端口猜测穿透
}Turn_devability;

typedef struct
{
	int (*on_turn_recv_user_cmd)(TurnConn conn, int type, void* data, int length);
	int (*on_turn_recv_speak_data)(TurnConn conn, int type, void* data, int length);
	int (*on_turn_service_state)(Turn_state_e state, TurnConn* conn, void* data, int length);
}Turn_cb;

#endif

