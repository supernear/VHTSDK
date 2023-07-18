#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ulog.h"
#include "turn_proxy.h"
#include "turn_proxy_cb.h"
#include "turn_api.h"

int main(int argc, char* argv[])
{
	Turn_devability turn_capbility;
	Turn_params turn_params;
	Turn_cb turn_cb;

	ulog_ctrl ulog_param;
	memset(&ulog_param, 0, sizeof(ulog_ctrl));
	ulog_param.level = ULOG_DEBUG;
	ulog_param.wt = 0;
	ulog_param.max_size = 20*1024;
	ulog_param.file_cb = NULL;
	strncpy(ulog_param.path, "./", 128);

	ulog_ctrl_param_set(&ulog_param);
	Turn_SetLogLevel(4);

//	Turn_Devability_Set(1, &turn_capbility);
	Turn_Devability_Set(0, &turn_capbility);
//	Turn_Params_Set("Z99LD210JJUBAOH", "engos-cms.ulifecam.com:6002", &turn_params);
	Turn_Params_Set("A99ZC210NLC8ZTX", "cnp2p.ulifecam.com:6001", &turn_params);
	Turn_Cb_Set(&turn_cb);
    Turn_Initialize(E_Turn_Mode_P2P, 500*1024, 10, turn_capbility.p2p_port_guess);
    Turn_InitDeviceCapability(&turn_capbility, &turn_params, &turn_cb);
    Turn_StartService();



	printf("Usage: input \n");
	printf("q: Quit\n");

	while(1)
	{
		char c = getchar();

		if(c == 'q')
		{
		    Turn_StopService();
		    Turn_DeInitialize();
			break;
		}
	}

	return 0;
}
