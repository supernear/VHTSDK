#ifndef __U_LOG_H__
#define __U_LOG_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum{
	ULOG_EMERG,
    ULOG_ERR,
    ULOG_WARN,
    ULOG_INFO,
    ULOG_DEBUG,
    ULOG_TRACE,
}ulog_level_e;

typedef int (*f_log_file_cb)(char *file, int size);

typedef struct ulog_file_info_s
{
	char			file[128];
	unsigned int 	size;
}ulog_file_info; 

typedef struct ulog_ctrl_s
{
	char			path[128];
	int				level;
	int				wt;
	unsigned int 	max_size;
	f_log_file_cb	file_cb;
}ulog_ctrl; 

int ulog_ctrl_param_get(ulog_ctrl *param);
int ulog_ctrl_param_set(ulog_ctrl *param);
int ulog_ctrl_file_callback();
int ulog_ctrl_print(int level, const char* t, ...);

#define ULOGT(t, ...)	ulog_ctrl_print(ULOG_TRACE, "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ULOGD(t, ...) 	ulog_ctrl_print(ULOG_DEBUG, "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ULOGI(t, ...) 	ulog_ctrl_print(ULOG_INFO,  "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ULOGW(t, ...)	ulog_ctrl_print(ULOG_WARN,  "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ULOGE(t, ...) 	ulog_ctrl_print(ULOG_ERR,   "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define ULOGM(t, ...) 	ulog_ctrl_print(ULOG_EMERG, "[%s][%04d]"t"", __FUNCTION__, __LINE__, ##__VA_ARGS__)


#endif
