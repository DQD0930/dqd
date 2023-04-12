#ifndef MSGOBSERVER_H
#define MSGOBSERVER_H
#ifdef WIN32
#pragma warning( disable : 4200)
#endif

class CObserver
{
public:
    CObserver(){};
    virtual ~CObserver(){};
    virtual void Update(void *pMsg) = 0;
};
#endif
