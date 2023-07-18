#ifndef PTHREAD_HH
#define PTHREAD_HH
#include <pthread.h>

#define Pthread_SUCCESS	0
#define Pthread_FAILURE	1

typedef int	Pthread_Result;
typedef pthread_t Pthread_t;
typedef void* (*Pthread_Task)(void*);

typedef enum
{
	Pthread_Policy_NONE,
	Pthread_Policy_FIFO,
	Pthread_Policy_RR
}Pthread_Policy_E;

// 要求Pthread_Attr必现memset
typedef struct
{
	unsigned int		stack_size;
	Pthread_Policy_E    policy;			// 调度机制
	char				priority;		
	char				detached;
	char				name[64];
	void*				lparam;			// 外部携带的参数
	Pthread_Task		task;
}Pthread_Attr;

#ifdef __cplusplus
extern "C"{
#endif

Pthread_Result Pthread_create(Pthread_t* tid, Pthread_Attr* attr, Pthread_Task start_routine, void *arg);
Pthread_Result Pthread_join(Pthread_t tid, void **retval);

#ifdef __cplusplus
}
#endif
#endif