// WinUdpClientInterface.cpp: implementation of the CLinuxUdpClientInterface class.
//
//////////////////////////////////////////////////////////////////////
#include "LinuxUdpClientInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxUdpClientInterface::CLinuxUdpClientInterface(CThread *pThreadObj,int ipAddr,short port)
                       :CUdpClientInterface(pThreadObj)
{
    m_nWorkSockfd = -1;
    m_nIpAddr = ipAddr;
    m_nPort = port;
}

CLinuxUdpClientInterface::CLinuxUdpClientInterface(CThread *pThreadObj,char *pIpAddr,short port)
                       :CUdpClientInterface(pThreadObj)
{
    m_nWorkSockfd = -1;
    m_nIpAddr = inet_addr(pIpAddr);   //if pIpAddr="xx.xx.xx.255", udp broadcast!
    m_nPort = port;
    //m_nInterface = interface;
    //printf("send interface = %s\r\n", m_nInterface);
}

CLinuxUdpClientInterface::~CLinuxUdpClientInterface()
{
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
��  ��: 2008.1.5 ����
***************************************************************************/
int CLinuxUdpClientInterface::Reset()
{
    m_nSvrAddr.sin_family      = AF_INET;
    m_nSvrAddr.sin_addr.s_addr = m_nIpAddr;
    m_nSvrAddr.sin_port        = htons(m_nPort);



    if(m_nWorkSockfd > 0)
    {
        shutdown(m_nWorkSockfd,SHUT_RDWR);
        close(m_nWorkSockfd);
    }
    m_nWorkSockfd = socket (PF_INET , SOCK_DGRAM , 0 );
    if(m_nWorkSockfd == -1)
    {
        return RETURN_FAILED;
    }

#if 1
    int broadcast=1;
    if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast))) == -1)
    {
        perror("setsockopt - SO_SOCKET ");
        return RETURN_FAILED;
    }
#endif
#if 0
    strncpy(m_nSendInterface.ifr_ifrn.ifrn_name, m_nInterface, sizeof(m_nSendInterface));
    if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_BINDTODEVICE,(char*)&m_nSendInterface,sizeof(m_nSendInterface))) == -1)
    {
    	perror("Failed to SO_BINDTODEVICE \r\n");
		return RETURN_FAILED;
	}
    printf("socket set %s success \r\n", m_nInterface);
#endif
    /*long SendBufferSize = 65535;
    if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_RCVBUF,(char*)&SendBufferSize,sizeof(SendBufferSize))) == -1)
    {
        perror("setsockopt - SO_SOCKET ");
        return RETURN_FAILED;
    }*/

    /*if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_DONTROUTE,&broadcast,sizeof broadcast)) == -1)
    {
        perror("setsockopt - SO_DONTROUTE");
        return RETURN_FAILED;
    }*/
    //fhua modify
    /*struct sockaddr_in sendaddr;
    sendaddr.sin_family = AF_INET;
    sendaddr.sin_port = htons(m_nPort);
    sendaddr.sin_addr.s_addr = INADDR_ANY;
    memset(sendaddr.sin_zero,'\0',sizeof sendaddr.sin_zero);

    if(-1 == bind(m_nWorkSockfd,(struct sockaddr*)&sendaddr,sizeof sendaddr))
    {
       perror("Linux UdpClientInterface Bind");
       return RETURN_FAILED;
    }*/

    return RETURN_OK;
}

/**************************************************************************
ԭ  ��: int Reset()
��  ��: �����Ƿ��յ��ͻ���UDP���ģ����յ�����Ϊ�ͻ�������
��  ��: ��
����ֵ: ��
��  ��: ��  ��
��  ��: 2008.1.5 ����
***************************************************************************/
//int CLinuxUdpClientInterface::WaitOnline(int timeout)
//{
//
//    if(m_nOnline)
//    {
//       return RETURN_OK;
//    }
//    else
//    {
//       return RETURN_TIMEOUT;
//    }
//}

/**************************************************************************
ԭ  ��: int SendData(char *pSendBuf,int sendDataLen)
��  ��: ��������
��  ��: pSendBuf ����������ָ��
        sendDataLen ���������ݳ���
����ֵ: RETURN_OK ���ͳɹ�
        RETURN_FAILED ����ʧ��
��  ��: ��  ��
��  ��: 2008.1.5 ����
***************************************************************************/
int CLinuxUdpClientInterface::SendData(char *pSendBuf,int sendDataLen,int )
{
    int thissendlen;

    thissendlen = sendto (m_nWorkSockfd, pSendBuf, sendDataLen, 0 ,(struct sockaddr *)&m_nSvrAddr,sizeof(m_nSvrAddr));
    if(thissendlen!=sendDataLen)
    {
//        m_nOnline = 0;
        return RETURN_FAILED;
    }
    return RETURN_OK;
}

/**************************************************************************
ԭ  ��: int RecvData(char *pRecvBuf,int recvBufLen)
��  ��: ��������
��  ��: pSendBuf ����������ָ��
        sendDataLen ���������ݳ���
����ֵ: >0 ���յ����ݳ���
        -1 ����ʧ��
��  ��: ��  ��
��  ��: 2008.1.5 ����
***************************************************************************/
int CLinuxUdpClientInterface::RecvData(char *pRecvBuf,int recvBufLen,int )
{
    return RETURN_FAILED;
    //actually, udp client interface should NOT recvData
    //use udpServer interface instead!
    /*int ret = RETURN_FAILED;
    ret = recv(m_nWorkSockfd , pRecvBuf , recvBufLen , 0);
    printf("----++++++++----Udp Client Interface Recv %d \n",ret);
//    if(ret <= 0)
//    {
//        m_nOnline = 0;
//    }
//    else
//    {
//        m_nOnline = 1;
//    }*/
    //return ret;
}
