#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/prctl.h>

#include "Pthread.h"
#include "ulog.h"

void* Pthread_task_proxy(void* lparam)
{
	Pthread_Attr* attr = (Pthread_Attr*)lparam;
	if(strlen(attr->name) != 0)
	{
		prctl(PR_SET_NAME, (unsigned long)(attr->name), 0, 0, 0);
	}

	if(attr->task != NULL)
	{
		attr->task(attr->lparam);
	}	
	
	free(attr);
	
	return NULL;
}

Pthread_Result Pthread_create(Pthread_t* tid, Pthread_Attr* attr, Pthread_Task start_routine, void *arg)
{
	if(tid == NULL || start_routine == NULL)
	{
		ULOGE("error params");
		return Pthread_FAILURE;
	}

	int rlt;
	if(attr != NULL)
	{
		Pthread_Attr* _attr = (Pthread_Attr*)malloc(sizeof(Pthread_Attr));
		memcpy(_attr, attr, sizeof(Pthread_Attr));
		_attr->task = start_routine;
		_attr->lparam = arg;
		
		pthread_attr_t tid_attr;
		pthread_attr_init(&tid_attr);
		if(attr->stack_size != 0)
		{
			pthread_attr_setstacksize(&tid_attr, attr->stack_size);
		}
		if(attr->detached == 1)
		{
			pthread_attr_setdetachstate(&tid_attr, PTHREAD_CREATE_DETACHED);
		}
		if(attr->policy != Pthread_Policy_NONE)
		{
			struct sched_param param;
			param.sched_priority = attr->priority;
			if(attr->policy == Pthread_Policy_RR){
				pthread_attr_setschedpolicy(&tid_attr,SCHED_RR);
			}else if(attr->policy == Pthread_Policy_FIFO){
				pthread_attr_setschedpolicy(&tid_attr,SCHED_FIFO);
			}
		    pthread_attr_setschedparam(&tid_attr,&param);
		    pthread_attr_setinheritsched(&tid_attr,PTHREAD_EXPLICIT_SCHED);//要使优先级其作用必须要有这句话
		}
		
		rlt = pthread_create(tid, &tid_attr, Pthread_task_proxy, _attr);
		if(rlt != 0)
		{
			ULOGE("pthread %s create error[%d]", _attr->name, errno);
			pthread_attr_destroy(&tid_attr);
			return Pthread_FAILURE;
		}
		ULOGT("pthread %s create success", _attr->name);
		
		pthread_attr_destroy(&tid_attr);
	}
	else
	{
		rlt = pthread_create(tid, NULL, start_routine, arg);
		if(rlt != 0)
		{
			ULOGE("pthread create error[%d]", errno);
			return Pthread_FAILURE;
		}
	}
	
	return Pthread_SUCCESS;
}

Pthread_Result Pthread_join(Pthread_t tid, void **retval)
{
	int rlt = pthread_join(tid, retval);
	if(rlt != 0)
	{
		ULOGE("pthread tid(%d) join error[%d]", tid, errno);
		return Pthread_FAILURE;
	}

	return Pthread_SUCCESS;
}
