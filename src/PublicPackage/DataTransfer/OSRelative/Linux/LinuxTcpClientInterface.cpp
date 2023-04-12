// WinTcpClientInterface.cpp: implementation of the CLinuxTcpClientInterface class.
//
//////////////////////////////////////////////////////////////////////

//#include "TcpClientInterface.h"
#include "LinuxTcpClientInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxTcpClientInterface::CLinuxTcpClientInterface(CThread *pThreadObj,int ipAddr,short port)
                       :CTcpClientInterface(pThreadObj)
{
    m_nSockfd = -1;
    m_nIpAddr = ipAddr;
    m_nPort = port;
}

CLinuxTcpClientInterface::CLinuxTcpClientInterface(CThread *pThreadObj,char *pIpAddr,short port)
                       :CTcpClientInterface(pThreadObj)
{
    m_nSockfd = -1;
    m_nIpAddr = inet_addr(pIpAddr);
    m_nPort = port;
}

CLinuxTcpClientInterface::~CLinuxTcpClientInterface()
{
    if(m_nSockfd > 0)
    {
        shutdown(m_nSockfd,SHUT_RDWR);
        close(m_nSockfd);
    }
}

/**************************************************************************
ԭ  ��: int Reset()
��  ��: �Խӿڸ�λ
��  ��: ��
����ֵ: ��
��  ��: ��  ��
��  ��: 2007.10.24 ����
***************************************************************************/
int CLinuxTcpClientInterface::Reset()
{
    m_nSvrAddr.sin_family      = AF_INET;
    m_nSvrAddr.sin_addr.s_addr = m_nIpAddr;
    m_nSvrAddr.sin_port        = htons(m_nPort);

    if(m_nSockfd>0)
    {
       shutdown(m_nSockfd,SHUT_RDWR);
       close(m_nSockfd);
    }

    m_nSockfd = socket (AF_INET , SOCK_STREAM , 0 );
    if(m_nSockfd == -1)
    {
        return -1;
    }

    m_nOnline = 0;
    return 0;
}

int CLinuxTcpClientInterface::WaitOnline(int timeout)
{
    int passtime=0;
    if(timeout==TIME_WAIT_FOR_EVER)
    {
        while(1)
        {
            if(m_nOnline)
            {
                return RETURN_OK;
            }
            else
            {
                sleep(1);
            }
        }
    }
    else
    {
        while(passtime<timeout)
        {
            if(m_nOnline)
            {
                return RETURN_OK;
            }
            else
            {
                sleep(1);
            }
            passtime += 1000;
        }
    }
    return RETURN_TIMEOUT;
}

/**************************************************************************
ԭ  ��: int SendData(char *pSendBuf,int sendDataLen)
��  ��: ��������
��  ��: pSendBuf ����������ָ��
        sendDataLen ���������ݳ���
����ֵ: RETURN_OK ���ͳɹ�
        RETURN_FAILED ����ʧ��
��  ��: ��  ��
��  ��: 2007.10.24 ����
***************************************************************************/
int CLinuxTcpClientInterface::SendData(char *pSendBuf,int sendDataLen,int timeout)
{
    int allsendlen = 0;
    int thissendlen;

    if(RETURN_TIMEOUT == WaitOnline(timeout))
    {
        return RETURN_FAILED;
    }

    if(m_nOnline)
    {
         while(allsendlen<sendDataLen)
         {
             thissendlen = send (m_nSockfd, pSendBuf+ allsendlen, sendDataLen-allsendlen, 0 );
             if(thissendlen<0)
             {
                 m_nOnline = 0;
                 return RETURN_FAILED;
             }
             allsendlen += thissendlen;
         }
         return RETURN_OK;
    }
    else
    {
        return RETURN_FAILED;
    }

}

/**************************************************************************
ԭ  ��: int RecvData(char *pRecvBuf,int recvBufLen)
��  ��: ��������
��  ��: pSendBuf ����������ָ��
        sendDataLen ���������ݳ���
����ֵ: >0 ���յ����ݳ���
        -1 ����ʧ��
��  ��: ��  ��
��  ��: 2007.10.24 ����
***************************************************************************/
int CLinuxTcpClientInterface::RecvData(char *pRecvBuf,int recvBufLen,int timeout)
{
    int ret = RETURN_FAILED;

    if(RETURN_TIMEOUT == WaitOnline(timeout))
    {
        return RETURN_FAILED;
    }

    if(m_nOnline)
    {
        ret = recv (m_nSockfd , pRecvBuf , recvBufLen , 0 );
        if(ret <= 0)
        {
            m_nOnline = 0;
        }
    }
    return ret;
}

/**************************************************************************
ԭ  ��: void OnlineMonitor()
��  ��: ����TCP����Ƿ�����
��  ��: ��
����ֵ: ��
��  ��: ��  ��
��  ��: 2007.10.24 ����
***************************************************************************/
void CLinuxTcpClientInterface::OnlineMonitor()
{
    while(1)
    {
        sleep(1);
        if(m_nOnline)
        {
            continue;
        }
        if(0 == connect (m_nSockfd, (struct sockaddr*)&m_nSvrAddr,sizeof(m_nSvrAddr)))
        {
            m_nOnline = 1;
        }
        else
        {
            Reset();
            printf("CLinuxTcpClientInterface:: connect Failed, Reset! \n");
        }
    }
}
