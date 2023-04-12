/*
 * CSerialDataTransferInterfaceFactory.h
 *
 *  Created on: Sep 14, 2009
 *      Author: fhua
 */

#ifndef CSERIALDATATRANSFERINTERFACEFACTORY_H_
#define CSERIALDATATRANSFERINTERFACEFACTORY_H_

#include "SerialInterface.h"
#include "DataTransferInterfaceFactory.h"

class CSerialDataTransferInterfaceFactory: public CDataTransferInterfaceFactory
{
protected:
  static CDataTransferInterfaceFactory *m_pDataTransferInterfaceFactory;
protected:
	CSerialDataTransferInterfaceFactory();
	virtual ~CSerialDataTransferInterfaceFactory();
public:
	static void Destroy();
	virtual CDataTransferInterface *CreateSerialInterface (UINT portnr = 1, \
			                 UINT baud = 38400,\
			                 char parity = 'N',\
			                 UINT databits = 8,\
			                 UINT stopsbits =1) = 0;
	virtual CDataTransferInterface *CreateSerialInterface (char *devName, \
							 UINT baud = 38400,\
							 char parity = 'N',\
							 UINT databits = 8,\
							 UINT stopsbits =1) = 0;
};

#endif /* CSERIALDATATRANSFERINTERFACEFACTORY_H_ */
