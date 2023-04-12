// MutexLock.h: interface for the CMutexLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTEXLOCK_H__F4BF5D33_512B_4D72_A142_9238A42268B1__INCLUDED_)
#define AFX_MUTEXLOCK_H__F4BF5D33_512B_4D72_A142_9238A42268B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMutexLock  
{
public:
	CMutexLock();
	virtual ~CMutexLock();
    virtual int Lock(int passMicroSeconds=TIME_WAIT_FOR_EVER)=0;
    virtual int Unlock()=0;
};

#endif // !defined(AFX_MUTEXLOCK_H__F4BF5D33_512B_4D72_A142_9238A42268B1__INCLUDED_)
