/*
  File name:      cfifo.cpp
  Author:
  Version:        0.0.1
  Date:           2007.8.7
  Description:    FIFO
  History:
    1. Date:      2006.1.18
       Author:
       Modification:
*/
#include <string.h>
#include <stdio.h>
#include "stdef.h"
#include "MutexSignalIncludes.h"
#include "Fifo.h"

CFifo::CFifo()
{
   m_pAllDataBuf = NULL;
   m_pAllBds = NULL;
   m_pOut = NULL;
   m_pIn = NULL;
   m_pFree = NULL;

   m_pFreeMutex = NULL;
   m_pUsedMutex = NULL;
   m_pFreeSemaphore = NULL;
   m_pUsedSemaphore = NULL;

   m_nAlreadyNum = 0;
}

CFifo::~CFifo()
{
   if(m_pAllDataBuf)
   {
      delete [] m_pAllDataBuf;
   }

   if(m_pAllBds)
   {
      delete [] m_pAllBds;
   }

   if(m_pFreeMutex)
   {
       delete m_pFreeMutex;
   }

   if(m_pUsedMutex)
   {
       delete m_pUsedMutex;
   }

   if(m_pFreeSemaphore)
   {
	   delete m_pFreeSemaphore;
   }

   if(m_pUsedSemaphore)
   {
	   delete m_pUsedSemaphore;
   }
}

int CFifo::Create(CMutexSignalFactory *pMutexSignalFactory,int bdsNum,int buflen)
{
   int i;
   m_nBdsNum = bdsNum;
   m_nBufLen = buflen;
   m_pAllBds = new FifoBd[bdsNum];
   if(!m_pAllBds)
       return -1;
   m_pAllDataBuf = new UC [bdsNum*buflen];
   if(!m_pAllDataBuf)
   {
       delete [] m_pAllBds;
       return -1;
   }
   m_nFreeNum = bdsNum;
   memset(m_pAllBds,0,sizeof(FifoBd)*bdsNum);
   memset(m_pAllDataBuf,0,bdsNum*buflen);
   m_pFree = m_pAllBds;

   for(i=0;i<bdsNum;i++)
   {
       (m_pFree+i)->pdata = m_pAllDataBuf+i*buflen;
   }

   for(i=0;i<bdsNum-1;i++)
   {
        (m_pFree+i)->next =(m_pFree+i+1);
   }

   m_pFreeMutex = pMutexSignalFactory->CreateMutexLock();
   m_pUsedMutex = pMutexSignalFactory->CreateMutexLock();
   m_pFreeSemaphore = pMutexSignalFactory->CreateSemaphoreLock(bdsNum,bdsNum);
   m_pUsedSemaphore = pMutexSignalFactory->CreateSemaphoreLock(0,bdsNum);

   return RETURN_OK;
}

FifoBd* CFifo::GetFree(int timeout,int force)
{
    int retcode;
    FifoBd *pRet=NULL;
    if(force)
    {
       if(!m_pFree)
        {
            return GetUsed(TIME_WAIT_FOR_EVER);
        }
    }

	retcode = m_pFreeSemaphore->Lock(timeout);
    if(RETURN_TIMEOUT == retcode)
    {
        pRet=NULL;
    }
    else
    {
        m_pFreeMutex->Lock();
        pRet = m_pFree;
        if(m_pFree)
        {
            m_pFree = m_pFree->next;
            pRet->next = NULL;
        }
        m_pFreeMutex->Unlock();
    }

    return pRet;
}


FifoBd* CFifo::GetUsed(int timeout)
{
   int retcode;
   FifoBd *pRet=NULL;
   retcode = m_pUsedSemaphore->Lock(timeout);
   if(RETURN_TIMEOUT == retcode || RETURN_FAILED == retcode)
   {
      pRet = NULL;
   }
   else
   {
	  m_pUsedMutex->Lock();
      pRet = m_pOut;
      if(m_pOut)
      {
         m_pOut = m_pOut->next;
         if(!m_pOut)
         {
            m_pIn = NULL;
         }
      }
	  m_pUsedMutex->Unlock();
   }
   return pRet;
}


int CFifo::PutFree(FifoBd* pbd)
{
	if(pbd)
	{
	   m_pFreeMutex->Lock();
	  pbd->next = m_pFree;
		if(m_pFree)
		{
			m_pFree = pbd;
		}
		else
		{
			m_pFree = pbd;
		}
	  m_nFreeNum++;
	  m_pFreeMutex->Unlock();
	  m_pFreeSemaphore->Unlock();
	}
   return RETURN_OK;
}


int CFifo::PutUsed(FifoBd* pbd)
{
	if(pbd)
	{
		m_pUsedMutex->Lock();
		pbd->next = NULL;
		if(m_pIn)
		{
			m_pIn->next = pbd;
			m_pIn = pbd;
		}
		else
		{
			m_pIn = m_pOut = pbd;
		}
		m_nFreeNum--;
		m_pUsedMutex->Unlock();
		m_pUsedSemaphore->Unlock();
	}
   return RETURN_OK;
}

//int CFifo::PutUrgent(FifoBd* pbd)
//{
//   if(pbd)
//   {
//	  m_pUsedMutex->Lock();
//      pbd->next = NULL;
//      if(m_pOut)
//      {
//         pbd->next = m_pOut;
//         m_pOut = pbd;
//      }
//      else
//      {
//         m_pIn = m_pOut = pbd;
//      }
//	  m_pUsedMutex->Unlock();
//
//	  m_pUsedSemaphore->Unlock();
//   }
//   return RETURN_OK;
//}
//

int CFifo::Put(char *pPutDataBuf,int len,int timeout, int force)
{
	FifoBd *pBd;
	pBd = GetFree(timeout,force);
	if(!pBd)
	{
		return RETURN_FAILED;
	}
	else
	{
		pBd->len = len;
		memcpy(pBd->pdata,pPutDataBuf,len);
		PutUsed(pBd);
	}
	return RETURN_OK;
}


int CFifo::Get(char *pGetDataBuf,const int bufLen,int timeout)
{
	FifoBd *pBd=NULL;
	//printf("!!!!!!!!!!!!!!!!!!!!!!!!!CFifo Get! timeout=%x\n",timeout);
	pBd = GetUsed(timeout);
	if(pBd)
	{
		//printf("!!!!!!!!!!!!!CFifo GetUsed, in bufLen=%d !!!!!!!!!!!!!!!!!!\n",bufLen);
		int cpLen = (pBd->len)>bufLen?bufLen:pBd->len;
		//printf("!!!!!!!!!!!!!CFifo GetUsed, now bufLen=%d !!!!!!!!!!!!!!!!!!\n",bufLen);
		memcpy(pGetDataBuf,pBd->pdata,cpLen);
		PutFree(pBd);
		return cpLen;
	}
	//printf("!!!!!!!!!!!!!CFifo GetUsed Failed!!!!!!!!!!!!!!!!!!\n");
	return RETURN_FAILED;
}

int CFifo::GetLastBufSize()
{
   //m_pUsedMutex->Lock();
   if(m_pOut)
   {
         return m_pOut->len;
   }
   //m_pUsedMutex->Unlock();
   return 0;
}
