// WinSemaphoreLock.cpp: implementation of the CWinSemaphoreLock class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>
#include "stdef.h"
#include "SemaphoreLock.h"
#include "LinuxSemaphoreLock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxSemaphoreLock::CLinuxSemaphoreLock(int lInitialCount, int lMaxCount )
{
	m_nMaxCount = lMaxCount;
    sem_init(&m_nSem,0,lInitialCount);
}

CLinuxSemaphoreLock::~CLinuxSemaphoreLock()
{
    sem_destroy(&m_nSem);
}

int CLinuxSemaphoreLock::Lock(int passMicroSeconds)
{
    int waitResult;
    if(passMicroSeconds==TIME_WAIT_FOR_EVER)
    {
        waitResult = sem_wait(&m_nSem);
    }
    else
    {
        struct timespec abs_timeout;
        if(clock_gettime(CLOCK_REALTIME,&abs_timeout) == -1)
        {
        	printf("!!! clock_gettime Failed! \n\n");
        	return RETURN_FAILED;
        }
        //printf("before sem_timedwait clock_gettime return sec: %u , nsec: %u \n",abs_timeout.tv_sec,abs_timeout.tv_nsec);
        int sec = passMicroSeconds/1000;
        int msec = passMicroSeconds - sec*1000;
        abs_timeout.tv_sec += sec;
        abs_timeout.tv_nsec += msec*1000;
#define NSECTOSEC 1000000000
        abs_timeout.tv_sec += abs_timeout.tv_nsec/NSECTOSEC;
        abs_timeout.tv_nsec = abs_timeout.tv_nsec % NSECTOSEC;
        waitResult = sem_timedwait(&m_nSem,&abs_timeout);
    }

    if(0 == waitResult)
    	return RETURN_OK;
    else
    {
    	switch(errno)
    	{
    	   case ETIMEDOUT:
    		   return RETURN_TIMEOUT;
    	   default:
    		   return RETURN_FAILED;
    	}
    }
}

int CLinuxSemaphoreLock::Unlock()
{
	int curVal = 100;
	GetSemVal(&curVal);
	if(curVal < m_nMaxCount)
      return sem_post(&m_nSem);
	else
	  return -1;
}

int CLinuxSemaphoreLock::GetSemVal(int *val)
{
    return sem_getvalue(&m_nSem,val);
}
