// WindowsThread.cpp: implementation of the CWindowsThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdef.h"
#include "pthread.h"
#include "Thread.h"
#include "MutexSignalIncludes.h"
#include "LinuxThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxThread::CLinuxThread()
{
}

CLinuxThread::~CLinuxThread()
{
}

CThread * CLinuxThread::GetThread()
{
    if(!m_pThread)
    {
        m_pThread = new CLinuxThread();
    }
    return m_pThread;
}

void CLinuxThread::CreateThread(void (pFun)(void *),void *arg)
{
    pthread_t thread_tid;
    void *(*pLinuxFun)(void *);
    pLinuxFun = (void* (*)(void*))pFun;
    pthread_create(&thread_tid,NULL,pLinuxFun,arg);
    //printf("Thread Create! thread_id is %u \n",(int)thread_tid);
}

//1-99 big number has higer priority
void CLinuxThread::CreateThread(int priority,void (pFun)(void *),void *arg)
{
	int inher;
	pthread_t thread_tid;
	pthread_attr_t prior;
	struct sched_param param;
	void *(*pLinuxFun)(void *);		//指针函数的函数指针
	pLinuxFun = (void* (*)(void*))pFun;
    if(priority==0)
       pthread_create(&thread_tid,NULL,pLinuxFun,arg);
    else
    {

    	pthread_attr_init(&prior);
  		pthread_attr_getinheritsched(&prior, &inher);

		if(inher == PTHREAD_EXPLICIT_SCHED)
		{
		}

		if(inher == PTHREAD_INHERIT_SCHED)
		{
			inher = PTHREAD_EXPLICIT_SCHED;
		}
		/*设置继承的调度策略*/
		/*必须设置为PTHREAD_EXPLICIT_SCHED，否则设置优先级不起效*/
		pthread_attr_setinheritsched(&prior, inher);
		pthread_attr_getschedparam(&prior,&param);
		param.sched_priority = priority;
		pthread_attr_setschedpolicy(&prior,SCHED_RR);
		pthread_attr_setschedparam(&prior,&param);
		pthread_create(&thread_tid,&prior,pLinuxFun,arg);
    }
}


