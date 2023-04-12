// DataTransferInterface.cpp: implementation of the CDataTransferInterface class.
//
//////////////////////////////////////////////////////////////////////
#include <Thread.h>

#include "DataTransferInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataTransferInterface::CDataTransferInterface(CThread *pThread)
{
    m_pThread = pThread;
}

CDataTransferInterface::~CDataTransferInterface()
{

}

void CDataTransferInterface::OnlineMonitor()
{
	//printf("this is run function\n");
	return;
}

void CDataTransferInterface::OnlineMonitorThread(void *arg)
{
    CDataTransferInterface*pObj = (CDataTransferInterface*)arg;
    pObj->OnlineMonitor();
}

void CDataTransferInterface::Run()
{
    if(m_pThread)
       m_pThread->CreateThread(OnlineMonitorThread,this);
}
