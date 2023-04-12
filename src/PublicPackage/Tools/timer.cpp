#include "timer.h"
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

 CTimer *CTimer::m_pCTimer = NULL;

CTimer::CTimer()
{
    
}

CTimer::~CTimer()
{

}

CTimer* CTimer::GetTimer()
{
    if(m_pCTimer == NULL)
    {
        m_pCTimer = new CTimer();
        if(NULL == m_pCTimer)
        {
            printf("new m_pCTimer faild\r\n");
        }
    }
    return m_pCTimer;
}

int CTimer::CreateTime(int s , int us , void (*fun)(int))
{
   
}

