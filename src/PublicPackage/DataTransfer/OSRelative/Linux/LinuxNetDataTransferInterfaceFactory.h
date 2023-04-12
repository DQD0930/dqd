/*
 * CLinuxNetDataTransferInterfaceFactory.h
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */

#ifndef CLINUXNETDATATRANSFERINTERFACEFACTORY_H_
#define CLINUXNETDATATRANSFERINTERFACEFACTORY_H_

#include <Thread/OSRelative/Linux/LinuxThread.h>

#include "LinuxTcpClientInterface.h"
#include "LinuxTcpServerInterface.h"
#include "LinuxUdpClientInterface.h"
#include "LinuxUdpServerInterface.h"

#include "NetDataTransferInterfaceFactory.h"

class CLinuxNetDataTransferInterfaceFactory: public CNetDataTransferInterfaceFactory
{
protected:
	CLinuxNetDataTransferInterfaceFactory();
	virtual ~CLinuxNetDataTransferInterfaceFactory();
public:
    static CDataTransferInterfaceFactory * GetDataTransferInterfaceFactory();

	virtual CDataTransferInterface *CreateTcpClientInterface (int ipAddr,   short port);
	virtual CDataTransferInterface *CreateTcpClientInterface (char *pIpAddr,short port);
	virtual CDataTransferInterface *CreateTcpServerInterface (short port);

	virtual CDataTransferInterface *CreateUdpClientInterface (int ipAddr,   short port);
	virtual CDataTransferInterface *CreateUdpClientInterface (char *pIpAddr,short port);
	virtual CDataTransferInterface *CreateUdpServerInterface (short port);
};

#endif /* CLINUXNETDATATRANSFERINTERFACEFACTORY_H_ */
