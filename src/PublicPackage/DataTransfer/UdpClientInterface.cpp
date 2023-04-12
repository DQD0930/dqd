// UdpClientInterface.cpp: implementation of the CUdpClientInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "UdpClientInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUdpClientInterface::CUdpClientInterface(CThread *pThread)
                    :CDataTransferInterface(pThread)
{
//    m_nOnline = 0;
}

CUdpClientInterface::~CUdpClientInterface()
{

}
