// TcpServerInterface.cpp: implementation of the CTcpServerInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "TcpServerInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpServerInterface::CTcpServerInterface(CThread *pThread)
                    :CDataTransferInterface(pThread)
{
    m_nOnline = 0;
}

CTcpServerInterface::~CTcpServerInterface()
{

}

