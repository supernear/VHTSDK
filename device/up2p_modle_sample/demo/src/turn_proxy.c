#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ulog.h"
#include "turn_proxy.h"
#include "turn_proxy_cb.h"

int Turn_Devability_Set(int limit_guess, Turn_devability* turn_capbility)
{
	turn_capbility->p2p_tcp = 1;
	if(limit_guess == 0)
	{
		turn_capbility->p2p_port_guess = 1;
		ULOGW("enable p2p port guess!");
	}
	else
	{
		turn_capbility->p2p_port_guess = 0;
		ULOGW("disable p2p port guess!");
	}
	
	return 0;
}

int Turn_Params_Set(char* serial_number, char* dispatch_addr, Turn_params* turn_params)
{
	memset(turn_params, 0, sizeof(Turn_params));

	turn_params->retry_ms = 3000;
	strcpy(turn_params->uid, serial_number);
	strcpy(turn_params->dispatch_addr, dispatch_addr);
	
	return 0;
}

int Turn_Cb_Set(Turn_cb* turn_cb)
{
	memset(turn_cb, 0, sizeof(Turn_cb));
	turn_cb->on_turn_recv_speak_data = Turn_On_SpeakData;
	turn_cb->on_turn_service_state = Turn_On_ServerState;
	turn_cb->on_turn_recv_user_cmd = Turn_On_UserCmd;
	
	return 0;
}

