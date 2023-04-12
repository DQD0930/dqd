// WinTcpServerInterface.cpp: implementation of the CLinuxTcpServerInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "LinuxTcpServerInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxTcpServerInterface::CLinuxTcpServerInterface(CThread *pThreadObj,short port)
                       :CTcpServerInterface(pThreadObj)
{
    m_nListenSockfd = -1;
    m_nWorkSockfd = -1;
    m_nPort = port;
    m_bFirstReset = true;
}

CLinuxTcpServerInterface::~CLinuxTcpServerInterface()
{
    if(m_nListenSockfd > 0)
    {
        shutdown(m_nListenSockfd,SHUT_RDWR);
        close(m_nListenSockfd);
    }
    if(m_nWorkSockfd > 0)
    {
        shutdown(m_nWorkSockfd,SHUT_RDWR);
        close(m_nWorkSockfd);
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
int CLinuxTcpServerInterface::Reset()
{
    if(!m_bFirstReset)
    {
        m_nOnline = 0;
    }
    else
    {
        m_bFirstReset = false;
    }
    m_nSvrAddr.sin_family      = AF_INET;
    m_nSvrAddr.sin_addr.s_addr = INADDR_ANY;
    m_nSvrAddr.sin_port        = htons(m_nPort);

    m_nOnline = 0;

    if(m_nListenSockfd > 0)
    {
        shutdown(m_nListenSockfd,SHUT_RDWR);
        close(m_nListenSockfd);
    }

    m_nListenSockfd = socket (AF_INET , SOCK_STREAM , 0 );
    if(m_nListenSockfd <=0 )
    {
        printf("Error: (Tcp ServerInterface) m_nListenSockfd = %d\n",m_nListenSockfd);
        return -1;
    }

    int yes = 1;
    if(setsockopt(m_nListenSockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
    {
        printf("Error: (Tcp ServerInterface) setsockopt SO_REUSEADDR return failed!\n");
        return -1;
    }
    if(-1 == bind(m_nListenSockfd,(struct sockaddr *)&m_nSvrAddr,sizeof(m_nSvrAddr)))
    {
        printf("Error: (Tcp ServerInterface) bind return failed!\n");
        return -1;
    }

    if(-1 == listen(m_nListenSockfd,1))
    {
        printf("Error: (Tcp ServerInterface) listen return failed!\n");
        return -1;
    }
    return 0;
}

int CLinuxTcpServerInterface::WaitOnline(int timeout)
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
int CLinuxTcpServerInterface::SendData(char *pSendBuf,int sendDataLen,int timeout)
{
    int allsendlen = 0;
    int thissendlen;

    /*if(RETURN_TIMEOUT == WaitOnline(timeout))
    {
        return RETURN_FAILED;
    }*/

    if(m_nOnline && m_nWorkSockfd)
    {
         while(allsendlen<sendDataLen)
         {
             thissendlen = send (m_nWorkSockfd, pSendBuf+ allsendlen, sendDataLen-allsendlen, 0 );
             if(thissendlen<0)
             {
                 //m_nOnline = 0;
                 printf("CLinuxTcpServerInterface:: SendData to sockfd=%d ,return Failed!\n",m_nWorkSockfd);
                 return RETURN_FAILED;
             }
             allsendlen += thissendlen;
         }
         //printf("CLinuxTcpServerInterface:: SendData to sockfd=%d ,return OK!\n",m_nWorkSockfd);
         return RETURN_OK;
    }
    else
    {
        printf("CLinuxTcpServerInterface:: SendData to sockfd=%d ,return Failed!\n",m_nWorkSockfd);
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
int CLinuxTcpServerInterface::RecvData(char *pRecvBuf,int recvBufLen,int timeout)
{
    int ret = RETURN_FAILED;

    /*if(RETURN_TIMEOUT == WaitOnline(timeout))
    {
        return RETURN_FAILED;
    }*/

    //if(m_nOnline)
    if(m_nWorkSockfd>0)
    {
        ret = recv (m_nWorkSockfd , pRecvBuf , recvBufLen , 0 );
        if(ret <= 0)
        {
            m_nOnline = 0;
            printf("CLinuxTcpServerInterface: Recv From SockFd = %d ,ret=%d \n",m_nWorkSockfd,ret);
            return RETURN_FAILED;          //modify by fhua
        }
        else
        {
           m_nOnline = 1;
           //printf("CLinuxTcpServerInterface: Recv From SockFd = %d ,ret=%d \n",m_nWorkSockfd,ret);
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
void CLinuxTcpServerInterface::OnlineMonitor()
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int newSockfd;
    while(1)
    {
        sleep(1);
        #if 0
        if(m_nOnline)
        {
            continue;
        }
        #endif
        newSockfd = accept(m_nListenSockfd, (struct sockaddr*)&clientAddr,&clientAddrSize);
        printf("Tcp ServerInterface: newSockfd=%d m_nListenSockfd=%d \n",newSockfd,m_nListenSockfd);
        if( newSockfd>0 )
        {

            if(m_nWorkSockfd > 0)
            {
               shutdown(m_nWorkSockfd,SHUT_RDWR);
               close(m_nWorkSockfd);
            }
            m_nWorkSockfd = newSockfd;
            m_nOnline = 1;
        }
        else
        {
            perror("tcp server accept");
            //Reset();    //fhua add
        }
    }
}
