// UdpClientInterface.h: interface for the CUdpClientInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPCLIENTINTERFACE_H__3C44D4F7_221D_437D_BE1E_337614B476BF__INCLUDED_)
#define AFX_UDPCLIENTINTERFACE_H__3C44D4F7_221D_437D_BE1E_337614B476BF__INCLUDED_

#include "DataTransferInterface.h"

class CUdpClientInterface : public CDataTransferInterface  
{
protected:
    int m_nIpAddr;
    short m_nPort;
//    UC m_nOnline;

public:
	CUdpClientInterface(CThread *pThread);
	virtual ~CUdpClientInterface();

};

#endif // !defined(AFX_UDPCLIENTINTERFACE_H__3C44D4F7_221D_437D_BE1E_337614B476BF__INCLUDED_)
