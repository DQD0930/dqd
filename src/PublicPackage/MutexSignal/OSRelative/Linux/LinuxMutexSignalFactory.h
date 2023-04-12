// WinMutexSignalFactory.h: interface for the CWinMutexSignalFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINMUTEXSIGNALFACTORY_H__CCB53FD3_0141_4B80_896C_AB9302A8D838__INCLUDED_)
#define AFX_WINMUTEXSIGNALFACTORY_H__CCB53FD3_0141_4B80_896C_AB9302A8D838__INCLUDED_

#include "MutexSignalFactory.h"

class CLinuxMutexSignalFactory : public CMutexSignalFactory  
{
protected:
	CLinuxMutexSignalFactory();
	virtual ~CLinuxMutexSignalFactory();
public:
    static CMutexSignalFactory * GetMutexSignalFactory();
    virtual CMutexLock *CreateMutexLock();
    virtual CSemaphoreLock *CreateSemaphoreLock(int lInitialCount = 1, int lMaxCount = 1);
    virtual CEventLock *CreateEventLock();    
};

#endif // !defined(AFX_WINMUTEXSIGNALFACTORY_H__CCB53FD3_0141_4B80_896C_AB9302A8D838__INCLUDED_)
