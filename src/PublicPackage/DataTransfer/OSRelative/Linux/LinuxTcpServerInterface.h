// WinTcpServerInterface.h: interface for the CLinuxTcpServerInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINTCPSERVERINTERFACE_H__D6549C2E_4E8E_4428_832F_3F61772EB485__INCLUDED_)
#define AFX_WINTCPSERVERINTERFACE_H__D6549C2E_4E8E_4428_832F_3F61772EB485__INCLUDED_
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <arpa/inet.h>

#include "TcpServerInterface.h"

class CLinuxTcpServerInterface : public CTcpServerInterface  
{
    int m_nListenSockfd;
    int m_nWorkSockfd;
    struct sockaddr_in m_nSvrAddr;
    UC m_bFirstReset;
public:
    CLinuxTcpServerInterface(CThread *pThreadObj,short port);
    virtual ~CLinuxTcpServerInterface();
private:
    int WaitOnline(int timeout);
protected:
    virtual void OnlineMonitor();
public:
    virtual int Reset();
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER);
};

#endif // !defined(AFX_WINTCPSERVERINTERFACE_H__D6549C2E_4E8E_4428_832F_3F61772EB485__INCLUDED_)
