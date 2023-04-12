// MutexSignalFactory.h: interface for the CMutexSignalFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTEXSIGNALFACTORY_H__7E3AB0CA_8DF4_492E_AEB8_2A7F49986B72__INCLUDED_)
#define AFX_MUTEXSIGNALFACTORY_H__7E3AB0CA_8DF4_492E_AEB8_2A7F49986B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MutexLock.h"
#include "SemaphoreLock.h"
#include "EventLock.h"
class CMutexSignalFactory  
{
protected:
    static CMutexSignalFactory *m_pMutexSignalFactory;
protected:
	CMutexSignalFactory();
	virtual ~CMutexSignalFactory();
public:
    virtual CMutexLock *CreateMutexLock() = 0;
    virtual CSemaphoreLock *CreateSemaphoreLock(int lInitialCount = 1, int lMaxCount = 1) = 0;
    virtual CEventLock *CreateEventLock() = 0;    
};

#endif // !defined(AFX_MUTEXSIGNALFACTORY_H__7E3AB0CA_8DF4_492E_AEB8_2A7F49986B72__INCLUDED_)
