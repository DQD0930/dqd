// TcpServerInterface.h: interface for the CTcpServerInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSERVERINTERFACE_H__4FA184CB_CB0F_4278_9629_4EF1506B245A__INCLUDED_)
#define AFX_TCPSERVERINTERFACE_H__4FA184CB_CB0F_4278_9629_4EF1506B245A__INCLUDED_

#include "DataTransferInterface.h"

class CTcpServerInterface : public CDataTransferInterface  
{
protected:
    int m_nIpAddr;
    short m_nPort;
    UC m_nOnline;

public:
	CTcpServerInterface(CThread *pThread);
	virtual ~CTcpServerInterface();
};

#endif // !defined(AFX_TCPSERVERINTERFACE_H__4FA184CB_CB0F_4278_9629_4EF1506B245A__INCLUDED_)
