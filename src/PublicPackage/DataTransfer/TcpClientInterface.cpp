// TcpClientInterface.cpp: implementation of the CTcpClientInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "TcpClientInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpClientInterface::CTcpClientInterface(CThread *pThread)
                    :CDataTransferInterface(pThread)
{
    m_nOnline = 0;
}

CTcpClientInterface::~CTcpClientInterface()
{

}
