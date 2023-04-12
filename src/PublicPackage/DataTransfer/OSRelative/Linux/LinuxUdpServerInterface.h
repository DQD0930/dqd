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
#ifndef LINUXUDPSERVERINTERFACE_H_
#define LINUXUDPSERVERINTERFACE_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <arpa/inet.h>

#include "UdpServerInterface.h"

class CLinuxUdpServerInterface : public CUdpServerInterface
{

public:
    CLinuxUdpServerInterface(CThread *pThreadObj,short port);
    int m_nWorkSockfd;
    struct sockaddr_in m_nSvrAddr;
    struct sockaddr_in m_nClientAddr;
    ~CLinuxUdpServerInterface();
private:
    virtual void OnlineMonitor();
    int WaitOnline(int timeout);
public:
    virtual int Reset();
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int SetNoCheckSum();
};

#endif
