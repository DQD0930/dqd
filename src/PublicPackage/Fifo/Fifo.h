#ifndef CFIFO_H
#define CFIFO_H
#include "stdef.h"
typedef struct FifoBd{
   int len;
   unsigned char *pdata;
   struct FifoBd *next;
}FifoBd;

class CMutexLock;
class CSemaphoreLock;
class CMutexSignalFactory;

class CFifo
{
private:
   int m_nBdsNum;
   int m_nBufLen;
   UC *m_pAllDataBuf;
   FifoBd *m_pAllBds;
   int m_nFreeNum;
   int m_nAlreadyNum;
private:

   CMutexLock *m_pFreeMutex;
   CMutexLock *m_pUsedMutex;
   CSemaphoreLock *m_pFreeSemaphore;
   CSemaphoreLock *m_pUsedSemaphore;
   CMutexSignalFactory *m_pMutexSignalFactory;
private:
   FifoBd *m_pOut;
   FifoBd *m_pIn;
   FifoBd *m_pFree;
public:
  CFifo();
  ~CFifo();

protected:
  FifoBd* GetFree(int timeout,int force);
  FifoBd* GetUsed(int timeout);
  int PutFree(FifoBd* pbd);
  int PutUsed(FifoBd* pbd);
//  int PutUrgent(FifoBd* pbd);

public:
  int Create(CMutexSignalFactory *pMutexSignalFactory,int bdsNum=10,int buflen=512);
  int Put(char *pPutDataBuf,int len,int timeout=TIME_WAIT_FOR_EVER,int force=0);
  int Get(char *pGetDataBuf,const int bufLen,int timeout=TIME_WAIT_FOR_EVER);
  inline int GetBufLen(){return m_nBufLen;};
  inline int IsHaveUsed(){ return m_pOut != NULL; };
  inline int IsHaveFree(){return m_pFree != NULL;};
  inline int GetFreeNum(){return m_nFreeNum;};
  inline int GetUsedNum(){return (m_nBdsNum-m_nFreeNum);};
  int GetLastBufSize();
};

#endif
