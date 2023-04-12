/*
 * Empty C++ Application
 */
#include "DataToCp.h"
#include "CGlobalVal.h"
#include "inifile.h"

#define VERSION   "2.0.0-2023.4.4"
int main()
{
   char serverip[20] = {0};
   char serveriplen = 0;
   short serverport = 0;
   short localport = 0;
   char protocoltype = 0;
   char sendProtocoltype = 0;
   char printloglevel = 0;
   char PIMtype = 0;

   CGlobalVal *pGlobalVal = CGlobalVal::GetpGlobalVal();

	printf("\n******  IP-Data-Transfer Version: [%s] Is Running ****** \n",VERSION);
   pGlobalVal->SetPrintFlag(0);

   printloglevel = read_profile_int("DEBUG" , "loglevel" , NULL , "config.ini");
   pGlobalVal->SetPrintLogLevel(printloglevel);
   printf("log level = %d\r\n" , printloglevel);
   printf("-----------------------------\n\n");

   printf("***********************************GOGOGO***********************************\n\n");
   

   //pGlobalVal->SetRawEthName(RX_RAW_MAC_DEV);

	CMutexSignalFactory *pMutexLockFactory;
    pMutexLockFactory = CLinuxMutexSignalFactory::GetMutexSignalFactory();
    if (NULL == pMutexLockFactory)
    {
       abort();
    }

    CDataTransferInterfaceFactory *pDataTransferInterfaceFactory;
    pDataTransferInterfaceFactory = CLinuxNetDataTransferInterfaceFactory::GetDataTransferInterfaceFactory();
    if (NULL == pDataTransferInterfaceFactory)
    {
       abort();
    }

	CThread *pThread;
    pThread = CLinuxThread::GetThread();
    if (NULL == pThread)
    {
       abort();
    }

    DataToCp* pDataToCp = DataToCp::GetpDataToCp(pMutexLockFactory,pDataTransferInterfaceFactory,pThread);
	if(NULL == pDataToCp)
   {
	   abort();
   }

   if(pDataToCp->Init() < 0)
   {
	   abort();
   }
   pDataToCp->Run();


	while (1)
	{
		sleep(1000);
	}
	return 0;
}
