// WinEventLock.h: interface for the CWinEventLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINEVENTLOCK_H__0A6C66DD_7A1E_4325_BD91_18CA1CF31937__INCLUDED_)
#define AFX_WINEVENTLOCK_H__0A6C66DD_7A1E_4325_BD91_18CA1CF31937__INCLUDED_

#include "EventLock.h"

class CLinuxEventLock : public CEventLock
{
    pthread_mutex_t m_nMutex;
public:
    CLinuxEventLock();
    virtual ~CLinuxEventLock();
    virtual int GetEvent(int passMicroSeconds=TIME_WAIT_FOR_EVER);
    virtual int SetEvent();

};

#endif // !defined(AFX_WINEVENTLOCK_H__0A6C66DD_7A1E_4325_BD91_18CA1CF31937__INCLUDED_)
