/*
 * PhyDataStructDef.h
 *
 *  Created on: Jun 28, 2016
 *      Author: fhua
 */

#ifndef PHYDATASTRUCTDEF_H_
#define PHYDATASTRUCTDEF_H_

#include "stdef.h"
#include "ThreadIncludes.h"
#include "MutexSignalIncludes.h"
#include "DataTransferIncludes.h"
#include "Fifo.h"

#include "Produce_TestData.h"

#define MAX_MAC_LENGTH 						1600

class CUdpInterface
{
public:
	CUdpInterface(CMutexSignalFactory *pMutexSignalFactory,CDataTransferInterfaceFactory *pDataTransferInterfaceFactory);
	virtual ~CUdpInterface();
	int Init(unsigned short port, unsigned short fifoNum, unsigned short FifoLen);
	int Init(char* ServerIPAddr, unsigned short port, unsigned short fifoNum, unsigned short FifoLen);
	int GetUdpPktFromFifo(char* buffer, int len);
	int RecvUdpPkt2Fifo();
	int GenTestUdpPkt2Fifo(unsigned short macLen = MAX_MAC_LENGTH);
	int SendData(char* buffer, int len);
	int RecvData(char* buffer, int len);
	int SetNoUdpCheckSum();
private:
	void UpdateCntVal(unsigned short val);
private:
	CMutexSignalFactory *m_pMutexSignalFactory;
	CDataTransferInterfaceFactory* m_pNetDataTransferIntFactory;
	CFifo* m_pUdpFifo;
	TestData* m_pTestData;
	CDataTransferInterface* m_pUdpInterface;
};

#endif /* PHYDATASTRUCTDEF_H_ */

