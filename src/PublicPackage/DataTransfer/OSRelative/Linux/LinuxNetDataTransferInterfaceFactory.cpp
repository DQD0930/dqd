/*
 * CLinuxNetDataTransferInterfaceFactory.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */

#include "LinuxNetDataTransferInterfaceFactory.h"

CLinuxNetDataTransferInterfaceFactory::CLinuxNetDataTransferInterfaceFactory()
{
    m_pThread = CLinuxThread::GetThread();
}

CLinuxNetDataTransferInterfaceFactory::~CLinuxNetDataTransferInterfaceFactory()
{

}

CDataTransferInterfaceFactory* CLinuxNetDataTransferInterfaceFactory::GetDataTransferInterfaceFactory()
{
    if(!m_pDataTransferInterfaceFactory)
    {
        m_pDataTransferInterfaceFactory = new CLinuxNetDataTransferInterfaceFactory();
    }
    return m_pDataTransferInterfaceFactory;
}


CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateTcpClientInterface(char * pIpAddr,short port)
{
    CTcpClientInterface * pInterface;
    pInterface = new CLinuxTcpClientInterface(m_pThread,pIpAddr,port);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateTcpClientInterface(int ipAddr,short port)
{
    CTcpClientInterface * pInterface;
    pInterface = new CLinuxTcpClientInterface(m_pThread,ipAddr,port);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateTcpServerInterface(short port)
{
    CTcpServerInterface * pInterface;
    pInterface = new CLinuxTcpServerInterface(m_pThread,port);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateUdpClientInterface(char * pIpAddr,short port)
{
    CUdpClientInterface * pInterface;
    pInterface = new CLinuxUdpClientInterface(m_pThread,pIpAddr,port);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateUdpClientInterface(int ipAddr,short port)
{
    CUdpClientInterface * pInterface;
    pInterface = new CLinuxUdpClientInterface(m_pThread,ipAddr,port);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface* CLinuxNetDataTransferInterfaceFactory::CreateUdpServerInterface(short port)
{
	CUdpServerInterface * pInterface;
	pInterface = new CLinuxUdpServerInterface(m_pThread,port);
	return DataTransferInterfaceStartWork(pInterface);
}


