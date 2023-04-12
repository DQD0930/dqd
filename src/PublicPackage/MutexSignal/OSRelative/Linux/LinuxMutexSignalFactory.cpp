// WinMutexSignalFactory.cpp: implementation of the CWinMutexSignalFactory class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "stdef.h"
#include "EventLock.h"
#include "MutexLock.h"
#include "SemaphoreLock.h"
#include "LinuxMutexLock.h"
#include "LinuxEventLock.h"
#include "LinuxSemaphoreLock.h"
#include "LinuxMutexSignalFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxMutexSignalFactory::CLinuxMutexSignalFactory()
{

}

CLinuxMutexSignalFactory::~CLinuxMutexSignalFactory()
{

}

CMutexSignalFactory * CLinuxMutexSignalFactory::GetMutexSignalFactory()
{
    if(!m_pMutexSignalFactory)
    {
        m_pMutexSignalFactory = new CLinuxMutexSignalFactory();
    }
    return m_pMutexSignalFactory;
}

CMutexLock *CLinuxMutexSignalFactory::CreateMutexLock()
{
    return new CLinuxMutexLock();
}

CSemaphoreLock *CLinuxMutexSignalFactory::CreateSemaphoreLock(int lInitialCount, int lMaxCount)
{
    return new CLinuxSemaphoreLock(lInitialCount, lMaxCount);
}

CEventLock *CLinuxMutexSignalFactory::CreateEventLock()
{
    return new CLinuxEventLock();
}
