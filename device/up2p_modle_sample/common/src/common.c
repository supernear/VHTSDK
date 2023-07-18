#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/vfs.h>
#include <sys/time.h>

#include <dirent.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/ether.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#include <libgen.h>

#include "common.h"


int get_domain_ip(char* domain, char* ip, int socktype)
{
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    struct sockaddr_in *addr;
	int ret;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_socktype = socktype;//SOCK_DGRAM;
	ret = getaddrinfo(domain, NULL,&hints,&res);
    if (ret < 0) {
//		printf("getaddrinfo error\n");
        return -1;
    }

	ret = -1;
    for (cur = res; cur != NULL; cur = cur->ai_next) {
        addr = (struct sockaddr_in *)cur->ai_addr;
		if(cur->ai_family == AF_INET && cur->ai_socktype == socktype)
		{
			inet_ntop(AF_INET, &addr->sin_addr, ip, 16);
			ret = 0;
		}
    }
    freeaddrinfo(res);
    return ret;
}

int ulife_exec_cmd(const char *cmd)   
{   
    FILE *fp = NULL;
    if((fp = popen(cmd, "r")) == NULL)
    {
        printf("Fail to popen\n");
        return -1;
    }
    pclose(fp);
	
	return 0;
} 

int32_t get_tick(void)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return (int32_t)now.tv_sec;
}

int32_t ulife_tick_ms(void)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return (int32_t)now.tv_sec*1000 + now.tv_nsec/1000000;
}

void  get_file_name(char* full_name,char * dest)
{
	char*  mn_first = full_name;
	char*  mn_last  = full_name + strlen( full_name );
	if ( strrchr( full_name, '\\' ) != NULL )
		mn_first = strrchr( full_name, '\\' ) + 1;
	else if ( strrchr( full_name, '/' ) != NULL )
		mn_first = strrchr( full_name, '/' ) + 1;
//	if ( strrchr( full_name, '.' ) != NULL )
//		mn_last = strrchr( full_name, '.' );
	if ( mn_last < mn_first )
		mn_last = full_name + strlen( full_name );
	
	memmove(dest ,mn_first,(mn_last-mn_first));
}

/*
//不适用与两个;;合并在一起，如果合并在一起，中间的空降被忽略
char dest[15][100];
int size = ulife_str_splite("84;57;43;47;58;57;57;45;65;75;57;", ";", (char*)dest, 15, 100);
*/
int ulife_str_splite(char* str, char* split, char* des, int rows, int row_size)
{
	if(str == NULL || split == NULL)
		return -1;

	char *outer_ptr = NULL;
	char* buf = (char*)malloc(strlen(str)+1);
	memset(buf, 0, strlen(str)+1);
	strcpy(buf, str);

	int count = 0;
	char*p = strtok_r(buf, split, &outer_ptr); 
	while(p!=NULL) 
	{ 
		snprintf(des+row_size*count, row_size, "%s", p);
		p = strtok_r(NULL, split, &outer_ptr); 
		
		count++;
		if(count >= rows)
			break;
	}
	free(buf);
	
	return count;
}

unsigned long long ulife_get_tf_freeKb(char* dir)
{
	int ret;
	if(dir == NULL) return 0;
	
	struct statfs diskInfo;
	ret = statfs(dir, &diskInfo);
	if(ret == 0)
	{
		unsigned long long totalBlocks = diskInfo.f_bsize;
		unsigned long long freeDisk = diskInfo.f_bfree*totalBlocks;
		return freeDisk/1024LL;
	}
	
	return 0;
}

int ulife_is_file_exist(const char* file_path)
{
	if(file_path == NULL)
		return -1;
	if(access(file_path, F_OK) == 0)
		return 0;

	return -1;
}

int ulife_is_dir_exist(const char* dir_path)
{
	char* _dir = dirname((char*)dir_path);
	struct stat _stat;
	
	if((stat(_dir, &_stat) == 0) && (((_stat.st_mode) & S_IFMT) == S_IFDIR)) 
	{
		return 0;	
	}
	else
	{
		return -1;
	}
}

long ulife_file_size(char* file)
{
	FILE* fd = fopen(file, "rb");
	if(fd == NULL)
	{
		return -1;
	}

	do
	{
		long cur_offset = ftell(fd);	// 获取当前偏移位置
		if (cur_offset == -1) 
		{
			printf("ftell failed :%s\n", strerror(errno));
			break;
		}
		
		if (fseek(fd, 0, SEEK_END) != 0) 	// 移动文件指针到文件末尾
		{
			printf("fseek failed: %s\n", strerror(errno));
			break;
		}
		
		long file_size = ftell(fd);	// 获取此时偏移值，即文件大小
		if (file_size == -1) 
		{
			printf("ftell failed :%s\n", strerror(errno));
			break;
		}

		fclose(fd);
		return file_size;
	}while(0);

	fclose(fd);
	return -1;
}

