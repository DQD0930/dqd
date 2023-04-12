// EventLock.h: interface for the CEventLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTLOCK_H__25354D1F_7A0D_4BAD_AF70_1DC04AAF0E36__INCLUDED_)
#define AFX_EVENTLOCK_H__25354D1F_7A0D_4BAD_AF70_1DC04AAF0E36__INCLUDED_

class CEventLock  
{
public:
    CEventLock();
    virtual ~CEventLock();
    virtual int GetEvent(int passMicroSeconds=TIME_WAIT_FOR_EVER)=0;
    virtual int SetEvent()=0;
};

#endif // !defined(AFX_EVENTLOCK_H__25354D1F_7A0D_4BAD_AF70_1DC04AAF0E36__INCLUDED_)
