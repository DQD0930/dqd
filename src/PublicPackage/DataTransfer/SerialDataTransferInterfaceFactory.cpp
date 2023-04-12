/*
 * CSerialDataTransferInterfaceFactory.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */
#include "SerialDataTransferInterfaceFactory.h"

CDataTransferInterfaceFactory* CSerialDataTransferInterfaceFactory::m_pDataTransferInterfaceFactory = NULL;

CSerialDataTransferInterfaceFactory::CSerialDataTransferInterfaceFactory()
{

}

CSerialDataTransferInterfaceFactory::~CSerialDataTransferInterfaceFactory()
{

}

void CSerialDataTransferInterfaceFactory::Destroy()
{
   if(m_pDataTransferInterfaceFactory)
	   delete m_pDataTransferInterfaceFactory;
}
