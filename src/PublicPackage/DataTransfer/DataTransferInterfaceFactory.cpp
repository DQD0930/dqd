// TransferInterfaceFactory.cpp: implementation of the CTransferInterfaceFactory class.
//
//////////////////////////////////////////////////////////////////////
#include "DataTransferInterfaceFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDataTransferInterfaceFactory::CDataTransferInterfaceFactory()
{
    m_pThread = NULL;
}

CDataTransferInterfaceFactory::~CDataTransferInterfaceFactory()
{

}

CDataTransferInterface* CDataTransferInterfaceFactory::DataTransferInterfaceStartWork(CDataTransferInterface *pInterface)
{
    if(pInterface)
    {
        if(RETURN_FAILED == pInterface->Reset())
        {
           delete pInterface;
           return NULL;
        }
        pInterface->Run();
    }
    return pInterface;
}
