// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__B356D3C4_B72E_4BA9_BECB_29C8E5F27F6C__INCLUDED_)
#define AFX_THREAD_H__B356D3C4_B72E_4BA9_BECB_29C8E5F27F6C__INCLUDED_

#include <stdio.h>
class CThread
{
protected:
    static CThread * m_pThread;
protected:
    CThread();
    virtual ~CThread();
public:
    virtual void CreateThread(void (pFun)(void *),void *arg=NULL)=0;
    virtual void CreateThread(int priority,void (pFun)(void *),void *arg=NULL)=0;
};

#endif // !defined(AFX_THREAD_H__B356D3C4_B72E_4BA9_BECB_29C8E5F27F6C__INCLUDED_)
