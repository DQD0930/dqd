// UdpServerInterface.h: interface for the UdpServerInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPSERVERINTERFACE_H__77FFD43C_9B40_4D2A_B761_DB07FA87300B__INCLUDED_)
#define AFX_UDPSERVERINTERFACE_H__77FFD43C_9B40_4D2A_B761_DB07FA87300B__INCLUDED_

#include "DataTransferInterface.h"

class CUdpServerInterface : public CDataTransferInterface  
{
protected:
    int m_nIpAddr;
    short m_nPort;
    UC m_nOnline;
    
public:
	CUdpServerInterface(CThread *pThread);
	virtual ~CUdpServerInterface();

};

#endif // !defined(AFX_UDPSERVERINTERFACE_H__77FFD43C_9B40_4D2A_B761_DB07FA87300B__INCLUDED_)
