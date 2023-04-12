/*
 * CNetDataTransferInterfaceFactory.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */
#include "NetDataTransferInterfaceFactory.h"

CDataTransferInterfaceFactory* CNetDataTransferInterfaceFactory::m_pDataTransferInterfaceFactory = NULL;

CNetDataTransferInterfaceFactory::CNetDataTransferInterfaceFactory()
{


}

CNetDataTransferInterfaceFactory::~CNetDataTransferInterfaceFactory()
{

}

void CNetDataTransferInterfaceFactory::Destroy()
{
   if(m_pDataTransferInterfaceFactory)
	   delete m_pDataTransferInterfaceFactory;
}

