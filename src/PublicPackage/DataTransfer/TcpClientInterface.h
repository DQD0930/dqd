// TcpClientInterface.h: interface for the CTcpClientInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPCLIENTINTERFACE_H__906E4846_3782_430A_8A90_51958A137ABD__INCLUDED_)
#define AFX_TCPCLIENTINTERFACE_H__906E4846_3782_430A_8A90_51958A137ABD__INCLUDED_

#include "DataTransferInterface.h"

class CTcpClientInterface : public CDataTransferInterface  
{
protected:
    int m_nIpAddr;
    short m_nPort;
    UC m_nOnline;

public:
	CTcpClientInterface(CThread *pThread);
	virtual ~CTcpClientInterface();
};

#endif // !defined(AFX_TCPCLIENTINTERFACE_H__906E4846_3782_430A_8A90_51958A137ABD__INCLUDED_)
