#ifndef TURN_PROXY_H
#define TURN_PROXY_H

#include "turn_types.h"

int Turn_Devability_Set(int limit_guess, Turn_devability* turn_capbility);
int Turn_Params_Set(char* serial_number, char* dispatch_addr, Turn_params* turn_params);
int Turn_Cb_Set(Turn_cb* turn_cb);
	
#endif
