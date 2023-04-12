// SemaphoreLock.h: interface for the CSemaphoreLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEMAPHORELOCK_H__B36300F6_93DC_4B36_B999_7FD3E15FBBD8__INCLUDED_)
#define AFX_SEMAPHORELOCK_H__B36300F6_93DC_4B36_B999_7FD3E15FBBD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSemaphoreLock  
{
public:
	CSemaphoreLock();
	virtual ~CSemaphoreLock();
    virtual int Lock(int passMicroSeconds=TIME_WAIT_FOR_EVER)=0;
    virtual int Unlock()=0;
    virtual int GetSemVal(int *val) = 0;
};

#endif // !defined(AFX_SEMAPHORELOCK_H__B36300F6_93DC_4B36_B999_7FD3E15FBBD8__INCLUDED_)
