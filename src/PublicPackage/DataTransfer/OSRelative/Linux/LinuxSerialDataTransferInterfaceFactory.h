/*
 * CLinuxSerialDataTransferInterfaceFactory.h
 *
 *  Created on: Sep 16, 2009
 *      Author: fhua
 */

#ifndef CLINUXSERIALDATATRANSFERINTERFACEFACTORY_H_
#define CLINUXSERIALDATATRANSFERINTERFACEFACTORY_H_

#include <Thread/OSRelative/Linux/LinuxThread.h>
#include "SerialDataTransferInterfaceFactory.h"

#include "LinuxSerialInterface.h"

class CLinuxSerialDataTransferInterfaceFactory: public CSerialDataTransferInterfaceFactory
{
protected:
	CLinuxSerialDataTransferInterfaceFactory();
	virtual ~CLinuxSerialDataTransferInterfaceFactory();
public:
    static CDataTransferInterfaceFactory * GetDataTransferInterfaceFactory();
	virtual CDataTransferInterface *CreateSerialInterface (UINT portnr = 1, \
			                 UINT baud = 38400,\
			                 char parity = 'N',\
			                 UINT databits = 8,\
			                 UINT stopsbits =1) ;
	virtual CDataTransferInterface *CreateSerialInterface (char *devName, \
							 UINT baud = 38400,\
							 char parity = 'N',\
							 UINT databits = 8,\
							 UINT stopsbits =1);
};

#endif /* CLINUXSERIALDATATRANSFERINTERFACEFACTORY_H_ */
