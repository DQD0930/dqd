// WinEventLock.cpp: implementation of the CWinEventLock class.
//
//////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include "stdef.h"
#include "EventLock.h"
#include "LinuxEventLock.h"
#include <pthread.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxEventLock::CLinuxEventLock()
{
    pthread_mutex_init(&m_nMutex,NULL);
    pthread_mutex_lock(&m_nMutex);
}

CLinuxEventLock::~CLinuxEventLock()
{
    pthread_mutex_destroy(&m_nMutex);
}

int CLinuxEventLock::GetEvent(int passMicroSeconds)
{
    int waitResult;
    if(passMicroSeconds==TIME_WAIT_FOR_EVER)
    {
        waitResult = pthread_mutex_lock(&m_nMutex);
    }
    else
    {
        struct timespec abs_timeout;
        abs_timeout.tv_sec = time(NULL)+(passMicroSeconds/1000);
        //abs_timeout.tv_sec = time(NULL)+ 5;
        abs_timeout.tv_nsec = 0;
        //printf(">>>>>>>>>>Be4 pthread_mutex_timedlock: time=%d \n",passMicroSeconds);
        waitResult = pthread_mutex_timedlock(&m_nMutex,&abs_timeout);
    }
    //printf("CLinuxEventLock::waitResult =%d \n",waitResult);
    switch(waitResult)
    {
    case 0:
         return RETURN_OK;
    case ETIMEDOUT:
         return RETURN_TIMEOUT;
    default:
         return RETURN_FAILED;
    }
}

int CLinuxEventLock::SetEvent()
{
    return pthread_mutex_unlock(&m_nMutex);
}
