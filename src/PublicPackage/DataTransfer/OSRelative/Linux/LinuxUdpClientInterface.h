// WinUdpClientInterface.h: interface for the CLinuxUdpClientInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINUDPCLIENTINTERFACE_H__D20A06A3_6BA1_4AE5_A310_73CDFAAF450D__INCLUDED_)
#define AFX_WINUDPCLIENTINTERFACE_H__D20A06A3_6BA1_4AE5_A310_73CDFAAF450D__INCLUDED_
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "UdpClientInterface.h"

class CLinuxUdpClientInterface : public CUdpClientInterface  
{
	int m_nWorkSockfd;
	struct sockaddr_in m_nSvrAddr;
	//char* m_nInterface;
	//struct ifreq  m_nSendInterface;

public:
    CLinuxUdpClientInterface(CThread *pThreadObj,int ipAddr,short port);
    CLinuxUdpClientInterface(CThread *pThreadObj,char *pIpAddr,short port);
    virtual ~CLinuxUdpClientInterface();
public:
    virtual int Reset();
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER);
};

#endif // !defined(AFX_WINUDPCLIENTINTERFACE_H__D20A06A3_6BA1_4AE5_A310_73CDFAAF450D__INCLUDED_)
