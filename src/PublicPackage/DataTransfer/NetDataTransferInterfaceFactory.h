/*
 * CNetDataTransferInterfaceFactory.h
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */

#ifndef CNETDATATRANSFERINTERFACEFACTORY_H_
#define CNETDATATRANSFERINTERFACEFACTORY_H_

#include "TcpClientInterface.h"
#include "TcpServerInterface.h"
#include "UdpClientInterface.h"
#include "UdpServerInterface.h"


#include "DataTransferInterfaceFactory.h"

class CNetDataTransferInterfaceFactory: public CDataTransferInterfaceFactory
{
protected:
    static CDataTransferInterfaceFactory *m_pDataTransferInterfaceFactory;


protected:
	CNetDataTransferInterfaceFactory();
	virtual ~CNetDataTransferInterfaceFactory();
public:
	static void Destroy();

	virtual CDataTransferInterface *CreateTcpClientInterface (int ipAddr,   short port)=0;
	virtual CDataTransferInterface *CreateTcpClientInterface (char *pIpAddr,short port)=0;
	virtual CDataTransferInterface *CreateTcpServerInterface (short port)=0;

	virtual CDataTransferInterface *CreateUdpClientInterface (int ipAddr,   short port)=0;
	virtual CDataTransferInterface *CreateUdpClientInterface (char *pIpAddr,short port)=0;
	virtual CDataTransferInterface *CreateUdpServerInterface (short port)=0;

};

#endif /* CNETDATATRANSFERINTERFACEFACTORY_H_ */
