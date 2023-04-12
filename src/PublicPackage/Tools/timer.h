#ifndef _TOOL_TIMER_H
#define _TOOL_TIMER_H

#include <sys/time.h>
#include <vector>
using namespace std;


class CTimer {
private:
        static CTimer *m_pCTimer; 
protected:
        CTimer();
        ~CTimer();
public:
        CTimer* GetTimer();
        int CreateTime(int s , int us , void (*fun)(int));
};



#endif