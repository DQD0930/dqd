// WinTcpClientInterface.h: interface for the CWinTcpClientInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINTCPCLIENTINTERFACE_H__6F15EC52_6F1C_423B_952E_12339B3A78CA__INCLUDED_)
#define AFX_WINTCPCLIENTINTERFACE_H__6F15EC52_6F1C_423B_952E_12339B3A78CA__INCLUDED_
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <arpa/inet.h>

#include "TcpClientInterface.h"

class CLinuxTcpClientInterface : public CTcpClientInterface  
{
    int m_nSockfd;
    struct sockaddr_in m_nSvrAddr;
public:
    CLinuxTcpClientInterface(CThread *pThreadObj,int ipAddr,short port);
    CLinuxTcpClientInterface(CThread *pThreadObj,char *pIpAddr,short port);
    virtual ~CLinuxTcpClientInterface();
private:
    int WaitOnline(int timeout);
protected:
    virtual void OnlineMonitor();
public:
    virtual int Reset();
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER);
};

#endif // !defined(AFX_WINTCPCLIENTINTERFACE_H__6F15EC52_6F1C_423B_952E_12339B3A78CA__INCLUDED_)
