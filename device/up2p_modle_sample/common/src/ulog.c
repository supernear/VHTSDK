#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <sys/file.h>

#include "ulog.h"

//打印字体颜色
#define U_NONE         "\033[m"
#define U_RED          "\033[0;32;31m"
#define U_LIGHT_RED    "\033[1;31m"
#define U_GREEN        "\033[0;32;32m"
#define U_LIGHT_GREEN  "\033[1;32m"
#define U_BLUE         "\033[0;32;34m"
#define U_LIGHT_BLUE   "\033[1;34m"
#define U_DARY_GRAY    "\033[1;30m"
#define U_CYAN         "\033[0;36m"
#define U_LIGHT_CYAN   "\033[1;36m"
#define U_PURPLE       "\033[0;35m"
#define U_LIGHT_PURPLE "\033[1;35m"
#define U_BROWN        "\033[0;33m"
#define U_YELLOW       "\033[1;33m"
#define U_LIGHT_GRAY   "\033[0;37m"
#define U_WHITE        "\033[1;37m"

//宏定义
#define MAX_LOG_BUFSIZE		2048
#define MAX_LOG_FILESIZE	25*1024

static ulog_ctrl s_ulog_ctrl;
static FILE* s_log_fd = NULL;
static char s_log_file[256] = {0};
static char s_log_buffer[MAX_LOG_BUFSIZE] = {0};
static pthread_mutex_t s_buffer_mtx = PTHREAD_MUTEX_INITIALIZER;

int ulog_ctrl_param_get(ulog_ctrl *param)
{
	pthread_mutex_lock(&s_buffer_mtx);
	memcpy(param, &s_ulog_ctrl, sizeof(ulog_ctrl));
	pthread_mutex_unlock(&s_buffer_mtx);

	return 0;
}

int ulog_ctrl_param_set(ulog_ctrl *param)
{
	pthread_mutex_lock(&s_buffer_mtx);
	memcpy(&s_ulog_ctrl, param, sizeof(ulog_ctrl));
	sprintf(s_log_file, "%s/ulifeSDK.log", s_ulog_ctrl.path);

	pthread_mutex_unlock(&s_buffer_mtx);

	return 0;
}

void* ulog_ctrl_file_cb_proxy(void* lparam)
{
	pthread_detach(pthread_self());

	ulog_file_info* info = (ulog_file_info*)lparam;
	if(s_ulog_ctrl.file_cb != NULL)
	{
		s_ulog_ctrl.file_cb(info->file, info->size);
	}

	free(info);

	return NULL;
}

int ulog_ctrl_file_callback()
{
	FILE* fd = fopen(s_log_file, "rb");
	if(fd != NULL)
	{
		unsigned long filesize = 0;
		struct stat statbuff;
		if(fstat(fileno(fd), &statbuff) >= 0)
		{
			filesize = statbuff.st_size;
		}

		if(s_ulog_ctrl.file_cb != NULL)
		{
			ulog_file_info* info = (ulog_file_info*)malloc(sizeof(ulog_file_info));
			info->size = (unsigned int)filesize;
			strcpy(info->file, s_log_file);

			pthread_t tid;
			if(pthread_create(&tid, NULL, ulog_ctrl_file_cb_proxy, info) != 0)
			{
				printf("create thread ulog_ctrl_file_cb_proxy failure\n");
				free(info);
			}
		}

		fclose(fd);
	}

	return 0;
}

int ulog_ctrl_file_copy()
{
	char buff[1024];
	int len;
    FILE *in,*out;
	char bak[512] = {0};
	unsigned int total_bytes = 0;

  	snprintf(bak,512,"%s.bak", s_log_file);
    in = fopen(s_log_file,"r+");
	if(in == NULL)
		return -1;

    out = fopen(bak,"w+");
  	if(out == NULL)
  	{
  		fclose(in);
		return -1;
	}

    while((len = fread(buff,1,sizeof(buff),in)) != 0)
    {
        fwrite(buff,1,len,out);
		total_bytes += len;
    }

	fclose(out);
	fclose(in);

	if(s_ulog_ctrl.file_cb != NULL)
	{
		ulog_file_info* info = (ulog_file_info*)malloc(sizeof(ulog_file_info));
		info->size = total_bytes;
		strcpy(info->file, bak);

		pthread_t tid;
		if(pthread_create(&tid, NULL, ulog_ctrl_file_cb_proxy, info) != 0)
		{
			printf("create thread ulog_ctrl_file_cb_proxy failure\n");
			free(info);
		}
	}

    return 0;
}

int ulog_ctrl_file_write(char* data, int len)
{
	if(s_log_fd == NULL)
	{
		s_log_fd = fopen(s_log_file, "a+");
		if(s_log_fd == NULL)
		{
			printf("open log file %s error\n", s_log_file);
		}
	}

	fwrite(data, 1, len, s_log_fd);
	fflush(s_log_fd);

	//检测文件大小 是否备份刷新
	int fd = fileno(s_log_fd);
	unsigned long filesize = 0;
    struct stat statbuff;
    if(fstat(fd, &statbuff) >= 0)
	{
        filesize = statbuff.st_size;
    }

	if(filesize > s_ulog_ctrl.max_size)
	{
		printf("tigger log file backup\n");
		fclose(s_log_fd);
		int ret = ulog_ctrl_file_copy();
		if(ret == 0)
			s_log_fd = fopen(s_log_file, "w+");
		else
			s_log_fd = fopen(s_log_file, "a+");
	}

	return 0;
}

int ulog_ctrl_print(int level, const char* t, ...)
{
	if(level > s_ulog_ctrl.level)
	{
		return 0;
	}

	struct timeval v;
	gettimeofday(&v, 0);
	struct tm *p = localtime(&v.tv_sec);
	char fmt[1024] = {0};
	snprintf(fmt, 1024, "%s%04d/%02d/%02d %02d:%02d:%02d.%03d [SDK]%s %s\n"U_NONE,level==ULOG_TRACE? "":(level==ULOG_DEBUG? U_LIGHT_GREEN:(level==ULOG_INFO? U_LIGHT_CYAN:(level==ULOG_WARN?U_YELLOW:U_LIGHT_RED)))
			, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, (int)(v.tv_usec/1000)
			, level==ULOG_TRACE? "TRACE":(level==ULOG_DEBUG? "DEBUG":(level==ULOG_INFO? "!INFO":(level==ULOG_WARN? "!WARN":"ERROR"))), t);

	va_list params;
	va_start(params, t);
	vfprintf(stdout, fmt, params);
	va_end(params);
	fflush(stdout);

	if(s_ulog_ctrl.wt == 1)
	{
		snprintf(fmt, 1024,"%04d/%02d/%02d %02d:%02d:%02d.%03d [SDK]%s %s\n"
				, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, (int)(v.tv_usec/1000)
				, level==ULOG_TRACE? "TRACE":(level==ULOG_DEBUG? "DEBUG":(level==ULOG_INFO? "!INFO":(level==ULOG_WARN? "!WARN":(level==ULOG_ERR? "ERROR":"EMERG")))), t);

		//这里需要上锁
		va_list params;
		va_start(params, t);
		pthread_mutex_lock(&s_buffer_mtx);
		memset(s_log_buffer, 0, MAX_LOG_BUFSIZE);
		vsnprintf(s_log_buffer, MAX_LOG_BUFSIZE, fmt, params);
		ulog_ctrl_file_write(s_log_buffer, strlen(s_log_buffer));
		pthread_mutex_unlock(&s_buffer_mtx);
		va_end(params);
	}

	return 0;
}

