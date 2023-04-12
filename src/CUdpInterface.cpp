/*
 * myfunc.cpp
 *
 *  Created on: Jun 30, 2016
 *      Author: root
 */
#include <stdio.h>

#include "CUdpInterface.h"
#include "CGlobalVal.h"

CUdpInterface::CUdpInterface(CMutexSignalFactory *pMutexSignalFactory,CDataTransferInterfaceFactory *pDataTransferInterfaceFactory)
{
	m_pMutexSignalFactory = pMutexSignalFactory;
	m_pNetDataTransferIntFactory = pDataTransferInterfaceFactory;
	m_pUdpFifo = NULL;
	m_pUdpInterface = NULL;
	m_pTestData = NULL;
}

CUdpInterface::~CUdpInterface() {

	if(m_pUdpFifo)
		delete m_pUdpFifo;
	if(m_pTestData)
		delete m_pTestData;
	if(m_pUdpInterface)
		delete m_pUdpInterface;
}

int CUdpInterface::Init(unsigned short port, unsigned short fifoNum, unsigned short FifoLen)
{
	if((NULL==m_pMutexSignalFactory) || (NULL == m_pNetDataTransferIntFactory))
		return -1;

	m_pUdpInterface =((CLinuxNetDataTransferInterfaceFactory*) m_pNetDataTransferIntFactory)->CreateUdpServerInterface(port);
	if (NULL == m_pNetDataTransferIntFactory)
	{
		printf("%s %d : Fatal Error! new p_CDataTransferClientInterface Failed! \n", __func__, __LINE__);
		return -1;
	}

	m_pUdpFifo =  new CFifo();
	if (NULL == m_pUdpFifo) {
		printf("%s %d : Fatal Error! new CFifo Failed! \n", __func__, __LINE__);
		return -1;
	}
	if (RETURN_OK != m_pUdpFifo->Create(m_pMutexSignalFactory, fifoNum, FifoLen))
	{
		printf("%s %d : Fatal Error! CFifo Create Failed! \n", __func__, __LINE__);
		return -1;
	}

	m_pTestData = new TestData();
	if(m_pTestData == NULL)
	{
		printf("%s %d : Fatal Error! new m_pTestData Failed! \n", __func__, __LINE__);
	    return -1;
	}
	return 0;
}

int CUdpInterface::Init(char* ServerIPAddr, unsigned short port, unsigned short fifoNum, unsigned short FifoLen)
{
	if((NULL==m_pMutexSignalFactory) || (NULL == m_pNetDataTransferIntFactory))
		return -1;

	m_pUdpInterface =((CLinuxNetDataTransferInterfaceFactory*) m_pNetDataTransferIntFactory)->CreateUdpClientInterface(ServerIPAddr, port);
	if (NULL == m_pNetDataTransferIntFactory)
	{
		printf("%s %d : Fatal Error! new p_CDataTransferClientInterface Failed! \n", __func__, __LINE__);
		return -1;
	}

	m_pUdpFifo =  new CFifo();
	if (NULL == m_pUdpFifo) {
		printf("%s %d : Fatal Error! new CFifo Failed! \n", __func__, __LINE__);
		return -1;
	}
	if (RETURN_OK != m_pUdpFifo->Create(m_pMutexSignalFactory, fifoNum, FifoLen))
	{
		printf("%s %d : Fatal Error! CFifo Create Failed! \n", __func__, __LINE__);
		return -1;
	}

	m_pTestData = new TestData();
	if(m_pTestData == NULL)
	{
		printf("%s %d : Fatal Error! new m_pTestData Failed! \n", __func__, __LINE__);
	    return -1;
	}
	return 0;
}

int CUdpInterface::GetUdpPktFromFifo(char* buffer, int len)
{
	if(NULL == m_pUdpFifo)
		return -1;
	return m_pUdpFifo->Get(buffer,len);
}

void CUdpInterface::UpdateCntVal(unsigned short val)
{
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();
	if(pGlobalVal)
	{
	  // pGlobalVal->IncRxUdpTrafficPktNum();
	   pGlobalVal->IncRcvUdpPktNum();
	   pGlobalVal->IncRcvUdpPktLen(val);
	   // pGlobalVal->IncPhyFrameTotalLen(val);
	  // pGlobalVal->IncFifoUseNum();
	   
	}
}

int CUdpInterface::RecvUdpPkt2Fifo()
{
	if((NULL == m_pUdpInterface) || (NULL == m_pUdpFifo))
		return -1;
	unsigned char rxBuffer[MAX_MAC_LENGTH] = { 0 };
	int rxLen = -1;
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();
	//BB_UdpFrame_t *pUdpFrame = (BB_UdpFrame_t *)rxBuffer;
	
	rxLen = m_pUdpInterface->RecvData((char*) rxBuffer, sizeof(rxBuffer));
	if (rxLen > 0)
	{
		UpdateCntVal(rxLen);

		//pGlobalVal->MaxUdpFifoUseNum(m_pUdpFifo->GetUsedNum());
		
		//printf("CFIFO USED NUM [%d]\r\n" , m_pUdpFifo->GetUsedNum());
		//return 0;
		return m_pUdpFifo->Put((char*) rxBuffer, rxLen);
	}
	return -1;
}

int CUdpInterface::GenTestUdpPkt2Fifo(unsigned short macLen)
{
	if((NULL == m_pTestData) || (NULL == m_pUdpFifo))
		return -1;
	if(macLen > MAX_MAC_LENGTH)
		return -1;
	unsigned char rxBuffer[MAX_MAC_LENGTH] = { 0 };
	int rxLen = macLen;
	rxLen = m_pTestData->GetTestData((char*) rxBuffer, rxLen, IPDATA);
	if(rxLen < 0)
		return -1;

#if 0
	printf("Gen Test Udp Pkt: \n");
	for(unsigned int i=0; i<rxLen; i++)
		printf("%02x ",rxBuffer[i]);
	printf("\n\n");
#endif

	UpdateCntVal(rxLen);
#ifdef DEBUG_DATA_FLOW
	//printf("-----> Rx UDP Traffic Len %d \n",rxLen);
#endif
	return m_pUdpFifo->Put((char*) (rxBuffer), rxLen);
}

int CUdpInterface::SendData(char* buffer, int len)
{
	if((NULL == m_pUdpInterface) )
		return -1;
    return m_pUdpInterface->SendData(buffer,len);
}

int CUdpInterface::RecvData(char* buffer, int len)
{
	if((NULL == m_pUdpInterface) )
		return -1;
    return m_pUdpInterface->RecvData(buffer,len);
}

int CUdpInterface::SetNoUdpCheckSum()
{
	if((NULL == m_pUdpInterface) )
		return -1;
    return ((CLinuxUdpServerInterface*)m_pUdpInterface)->SetNoCheckSum();
}
