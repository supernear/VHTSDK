#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

int get_domain_ip(char* domain, char* ip, int socktype);
int ulife_exec_cmd(const char *cmd);
int32_t get_tick(void);
int32_t ulife_tick_ms(void);
void  get_file_name(char* full_name,char * dest);
int ulife_str_splite(char* str, char* split, char* des, int rows, int row_size);
unsigned long long ulife_get_tf_freeKb(char* dir);
int ulife_is_file_exist(const char* file_path);
int ulife_is_dir_exist(const char* dir_path);
long ulife_file_size(char* file);

#ifdef __cplusplus
}
#endif

#endif
