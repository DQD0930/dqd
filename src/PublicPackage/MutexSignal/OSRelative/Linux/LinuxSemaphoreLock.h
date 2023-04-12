// WinSemaphoreLock.h: interface for the CWinSemaphoreLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINSEMAPHORELOCK_H__42A09A89_A411_4713_9455_28EE544910B3__INCLUDED_)
#define AFX_WINSEMAPHORELOCK_H__42A09A89_A411_4713_9455_28EE544910B3__INCLUDED_

#include "SemaphoreLock.h"

class CLinuxSemaphoreLock : public CSemaphoreLock  
{
	int   m_nMaxCount;
    sem_t m_nSem;
public:
    CLinuxSemaphoreLock(int lInitialCount = 1, int lMaxCount = 1);
    virtual ~CLinuxSemaphoreLock();
    virtual int Lock(int passMicroSeconds=TIME_WAIT_FOR_EVER);
    virtual int Unlock();
    virtual int GetSemVal(int *val);
};

#endif // !defined(AFX_WINSEMAPHORELOCK_H__42A09A89_A411_4713_9455_28EE544910B3__INCLUDED_)
