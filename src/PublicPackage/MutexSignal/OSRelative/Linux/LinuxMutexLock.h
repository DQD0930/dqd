// WinMutexLock.h: interface for the CWinMutexLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINMUTEXLOCK_H__0B447E03_80A3_413D_AFAC_D790886EFB78__INCLUDED_)
#define AFX_WINMUTEXLOCK_H__0B447E03_80A3_413D_AFAC_D790886EFB78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MutexLock.h"

class CLinuxMutexLock : public CMutexLock
{
    pthread_mutex_t m_nMutex;
public:
    CLinuxMutexLock();
    virtual ~CLinuxMutexLock();
    virtual int Lock(int passMicroSeconds=TIME_WAIT_FOR_EVER);
    virtual int Unlock();
};

#endif // !defined(AFX_WINMUTEXLOCK_H__0B447E03_80A3_413D_AFAC_D790886EFB78__INCLUDED_)
