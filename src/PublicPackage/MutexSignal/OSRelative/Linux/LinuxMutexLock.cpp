// WinMutexLock.cpp: implementation of the CWinMutexLock class.
//
//////////////////////////////////////////////////////////////////////
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include "stdef.h"
#include "MutexLock.h"
#include "LinuxMutexLock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxMutexLock::CLinuxMutexLock()
{
    pthread_mutex_init(&m_nMutex,NULL);
}

CLinuxMutexLock::~CLinuxMutexLock()
{
    pthread_mutex_destroy(&m_nMutex);
}

int CLinuxMutexLock::Lock(int passMicroSeconds)
{
    int waitResult;
    if(passMicroSeconds==TIME_WAIT_FOR_EVER)
    {
        waitResult = pthread_mutex_lock(&m_nMutex);
    }
    else
    {
        struct timespec abs_timeout;
        abs_timeout.tv_sec = passMicroSeconds;
        abs_timeout.tv_nsec = 0;
        waitResult = pthread_mutex_timedlock(&m_nMutex,&abs_timeout);
    }
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

int CLinuxMutexLock::Unlock()
{
    return pthread_mutex_unlock(&m_nMutex);
}
