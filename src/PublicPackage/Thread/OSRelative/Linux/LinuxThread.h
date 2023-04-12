// WindowsThread.h: interface for the CWindowsThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSTHREAD_H__F149F408_C445_4587_96F1_674A99CEEAC7__INCLUDED_)
#define AFX_WINDOWSTHREAD_H__F149F408_C445_4587_96F1_674A99CEEAC7__INCLUDED_

#include "Thread.h"

class CLinuxThread : public CThread
{
protected:
    CLinuxThread();
    virtual ~CLinuxThread();
public:
    static CThread * GetThread();
    virtual void CreateThread(void (pFun)(void *),void *arg=NULL);
     virtual void CreateThread(int priority,void (pFun)(void *),void *arg=NULL);
};

#endif // !defined(AFX_WINDOWSTHREAD_H__F149F408_C445_4587_96F1_674A99CEEAC7__INCLUDED_)
