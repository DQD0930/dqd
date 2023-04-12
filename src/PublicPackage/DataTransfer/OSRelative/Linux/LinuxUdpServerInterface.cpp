/***************************************************************************
 *   Copyright (C) 2008 by lvjian   *
 *   lvjian@localhost.localdomain   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "LinuxUdpServerInterface.h"

CLinuxUdpServerInterface::CLinuxUdpServerInterface(CThread *pThreadObj,short port)
                         :CUdpServerInterface(pThreadObj)
{
    m_nWorkSockfd = -1;
    m_nPort = port;
}


CLinuxUdpServerInterface::~CLinuxUdpServerInterface()
{
    if(m_nWorkSockfd > 0)
    {
        shutdown(m_nWorkSockfd,SHUT_RDWR);
        close(m_nWorkSockfd);
    }
}
/**************************************************************************
原  锟斤拷 int Reset()
锟斤拷  锟斤拷 锟皆接口革拷位
锟斤拷 锟�: 锟斤拷锟斤拷锟斤拷值: 锟斤拷锟斤拷 锟斤拷 锟斤拷 锟斤拷
锟斤拷 锟斤拷 2008.1.5 锟斤拷锟斤拷
***************************************************************************/
int CLinuxUdpServerInterface::Reset()
{

	bzero((char*)&m_nSvrAddr,sizeof(struct sockaddr_in));
	m_nSvrAddr.sin_family      = AF_INET;
	m_nSvrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_nSvrAddr.sin_port        = htons(m_nPort);

	bzero((char*)&m_nClientAddr,sizeof(struct sockaddr_in));
	m_nClientAddr.sin_family      = AF_INET;
	m_nClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_nClientAddr.sin_port        = htons(m_nPort);

	if(m_nWorkSockfd>0)
	{
	   shutdown(m_nWorkSockfd,SHUT_RDWR);
	   shutdown(m_nWorkSockfd,SHUT_RDWR);
	}

	//m_nOnline = 1;            //fhua modify

	m_nWorkSockfd = socket (PF_INET , SOCK_DGRAM , 0 );
	if(m_nWorkSockfd <= 0)
	{
		return -1;
	}

	int broadcast=1;
	if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast))) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
/*
	long RecvBufferSize = 4*1024*1024;
	if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_RCVBUF,(char*)&RecvBufferSize,sizeof(RecvBufferSize))) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
*/
/*
	if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_SNDBUF,(char*)&RecvBufferSize,sizeof(RecvBufferSize))) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
*/
//	printf("set socket recv buff size  = %d\r\n" , RecvBufferSize);
//	printf("set socket send buff size  = %d\r\n" , RecvBufferSize);
/*
	int CurRecvBufSize = -1;
	socklen_t optlen = sizeof(CurRecvBufSize);
	if((getsockopt(m_nWorkSockfd , SOL_SOCKET,SO_RCVBUF , &CurRecvBufSize , &optlen)) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
	printf("Cur socket recv buff size  = %d\r\n" , CurRecvBufSize);
*/
/*
	if((getsockopt(m_nWorkSockfd , SOL_SOCKET,SO_SNDBUF , &CurRecvBufSize , &optlen)) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
	printf("Cur socket send buff size  = %d\r\n" , RecvBufferSize);
*/
	/*if((setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_DONTROUTE,&broadcast,sizeof broadcast)) == -1)
	{
		perror("setsockopt - SO_DONTROUTE");
		return RETURN_FAILED;
	}*/




	if(-1 == bind(m_nWorkSockfd,(struct sockaddr *)&m_nSvrAddr,sizeof(m_nSvrAddr)))
	{
		printf("Linux Udp ServerInterface Bind Error! \n");
		return -1;
	}

	return 0;
}

/**************************************************************************
原  锟斤拷 int Reset()
锟斤拷  锟斤拷 锟斤拷锟斤拷欠锟斤拷盏锟斤拷突锟斤拷锟紻P锟斤拷锟侥ｏ拷锟斤拷锟秸碉拷锟斤拷锟斤拷为锟酵伙拷锟斤拷锟斤拷锟斤拷锟斤拷 锟�: 锟斤拷锟斤拷锟斤拷值: 锟斤拷锟斤拷 锟斤拷 锟斤拷 锟斤拷
锟斤拷 锟斤拷 2008.1.5 锟斤拷锟斤拷
***************************************************************************/
int CLinuxUdpServerInterface::WaitOnline(int )
{
    return RETURN_OK;
    /*if(m_nOnline)
    {
       return RETURN_OK;
    }
    else
    {
       return RETURN_TIMEOUT;
    }*/
}

/**************************************************************************
原  锟斤拷 int SendData(char *pSendBuf,int sendDataLen)
锟斤拷  锟斤拷 锟斤拷锟斤拷锟斤拷锟斤拷锟� 锟�: pSendBuf 锟斤拷锟斤拷锟斤拷锟斤拷锟街革拷锟�        sendDataLen 锟斤拷锟斤拷锟斤拷锟斤拷莩锟斤拷锟斤拷锟斤拷锟街�: RETURN_OK 锟斤拷锟酵成癸拷
        RETURN_FAILED 锟斤拷锟斤拷失锟斤拷锟斤拷 锟斤拷 锟斤拷 锟斤拷
锟斤拷 锟斤拷 2008.1.5 锟斤拷锟斤拷
***************************************************************************/
int CLinuxUdpServerInterface::SendData(char *pSendBuf,int sendDataLen,int timeout)
{
    //return RETURN_FAILED;
    int thissendlen;
    if(RETURN_TIMEOUT == WaitOnline(timeout))
    {
        return RETURN_FAILED;
    }
    thissendlen = sendto (m_nWorkSockfd, pSendBuf, sendDataLen, 0 ,(struct sockaddr *)&m_nClientAddr,sizeof(m_nClientAddr));
    if(thissendlen!=sendDataLen)
    {
        //m_nOnline = 0;
        return RETURN_FAILED;
    }
    return RETURN_OK;
}

/**************************************************************************
原  锟斤拷 int RecvData(char *pRecvBuf,int recvBufLen)
锟斤拷  锟斤拷 锟斤拷锟斤拷锟斤拷锟斤拷锟� 锟�: pSendBuf 锟斤拷锟斤拷锟斤拷锟斤拷锟街革拷锟�        sendDataLen 锟斤拷锟斤拷锟斤拷锟斤拷莩锟斤拷锟斤拷锟斤拷锟街�: >0 锟斤拷锟秸碉拷锟斤拷莩锟斤拷锟�        -1 锟斤拷锟斤拷失锟斤拷锟斤拷 锟斤拷 锟斤拷 锟斤拷
锟斤拷 锟斤拷 2008.1.5 锟斤拷锟斤拷
***************************************************************************/
int CLinuxUdpServerInterface::RecvData(char *pRecvBuf,int recvBufLen,int timeout)
{
    int ret = RETURN_FAILED;
    int clientAddrLen = sizeof(m_nClientAddr);

    if(TIME_WAIT_FOR_EVER == timeout)
    {
       return  recvfrom(m_nWorkSockfd,pRecvBuf,recvBufLen,0,(struct sockaddr *)&m_nClientAddr,(socklen_t*)&clientAddrLen);
    }
    fd_set fdR;
    struct timeval rtimeout;
    rtimeout.tv_sec = timeout/1000;
    rtimeout.tv_usec = 0;
    FD_ZERO(&fdR);
    FD_SET(m_nWorkSockfd,&fdR);
    switch(select(m_nWorkSockfd+1,&fdR,NULL,NULL,&rtimeout))
    {
        case -1:
           return RETURN_FAILED;
        case 0:
           return RETURN_TIMEOUT;
        default:
           ret = recvfrom(m_nWorkSockfd,pRecvBuf,recvBufLen,0,(struct sockaddr *)&m_nClientAddr,(socklen_t*)&clientAddrLen);
           break;
    }

    /*if(ret <= 0)
    {
        m_nOnline = 0;
    }
    else
    {
        m_nOnline = 1;
    }*/
    return ret;
}

int  CLinuxUdpServerInterface::SetNoCheckSum()
{
     int nochecksum = 1;
     return setsockopt(m_nWorkSockfd,SOL_SOCKET,SO_NO_CHECK,&nochecksum,sizeof(nochecksum));
}

void CLinuxUdpServerInterface::OnlineMonitor()
{
    return;
    /*while(1)
    {
        Sleep(1000);
        if(m_nOnline)
        {
            continue;
        }
        Reset();
    }*/
}

