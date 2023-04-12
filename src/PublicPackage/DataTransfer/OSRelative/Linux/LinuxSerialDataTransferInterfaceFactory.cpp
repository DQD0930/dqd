/*
 * CLinuxSerialDataTransferInterfaceFactory.cpp
 *
 *  Created on: Sep 16, 2009
 *      Author: fhua
 */

#include "LinuxSerialDataTransferInterfaceFactory.h"

CLinuxSerialDataTransferInterfaceFactory::CLinuxSerialDataTransferInterfaceFactory()
{
	m_pThread = CLinuxThread::GetThread();
}

CLinuxSerialDataTransferInterfaceFactory::~CLinuxSerialDataTransferInterfaceFactory()
{

}

CDataTransferInterfaceFactory* CLinuxSerialDataTransferInterfaceFactory::GetDataTransferInterfaceFactory()
{
    if(!m_pDataTransferInterfaceFactory)
    {
        m_pDataTransferInterfaceFactory = new CLinuxSerialDataTransferInterfaceFactory;
    }
    return m_pDataTransferInterfaceFactory;
}


CDataTransferInterface *CLinuxSerialDataTransferInterfaceFactory::CreateSerialInterface(UINT portnr, UINT baud, char parity, UINT databits, UINT stopsbits )
{
    CLinuxSerialInterface * pInterface;
    pInterface = new CLinuxSerialInterface(m_pThread,portnr, baud, parity, databits, stopsbits);
    return DataTransferInterfaceStartWork(pInterface);
}

CDataTransferInterface *CLinuxSerialDataTransferInterfaceFactory::CreateSerialInterface(char *devName, UINT baud, char parity, UINT databits, UINT stopsbits)
{
    CLinuxSerialInterface * pInterface;
    pInterface = new CLinuxSerialInterface(m_pThread,devName, baud, parity, databits, stopsbits);
    return DataTransferInterfaceStartWork(pInterface);
}
