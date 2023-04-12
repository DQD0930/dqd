// UdpServerInterface.cpp: implementation of the UdpServerInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "UdpServerInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUdpServerInterface::CUdpServerInterface(CThread *pThread)
                    :CDataTransferInterface(pThread)
{
    m_nOnline = 0;
}

CUdpServerInterface::~CUdpServerInterface()
{

}
