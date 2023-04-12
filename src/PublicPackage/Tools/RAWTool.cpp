#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>    // SIOCGIFFLAGS
#include <sys/socket.h>
#include <errno.h>        // errno
#include <netinet/in.h>   // IPPROTO_IP
#include <net/if.h>       // IFF_*, ifreq
#include <netinet/ether.h>
#include <linux/ip.h>

#include "stdef.h"
#include "SocketTool.h"
#include "Match.h"
#include "CGlobalVal.h"

//#include "BBUdpDataStructDef.h"

struct ifreq if_veth;
struct ifreq ifopts;

#define ERROR(fmt, ...) do { printf(fmt, __VA_ARGS__); return -1;  } while(0)

RAWTool::RAWTool(CMutexSignalFactory *pMutexSignalFactory,char *ifRecvName)
{
	m_nRecvSocket = -1;
	memset(&client_addr, 0, sizeof(client_addr));
	client_len = 0;
	if(ifRecvName != NULL)
		strcpy(m_pIfRecvName, ifRecvName);
	else
		strcpy(m_pIfRecvName, DEFAULT_SEND_IF);
	m_pMutexSignalFactory = pMutexSignalFactory;
}


RAWTool::~RAWTool()
{
    if(m_nRecvSocket > 0)
        shutdown(m_nRecvSocket, SHUT_RDWR);
    if(m_pRawFifo)
    	delete m_pRawFifo;
}

SOCKET RAWTool::Init(unsigned short fifoNum, unsigned short FifoLen)
{
	int sockopt = 0;
	struct sockaddr_ll haddr;
	int ret = 0;
	struct ifreq ifr;

	//create recv raw socket
	if((m_nRecvSocket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
	{
		printf("create raw recv socket error!\n");
		return -1;
	}	
	
	strncpy(ifopts.ifr_name, m_pIfRecvName, IFNAMSIZ-1);
	ioctl(m_nRecvSocket, SIOCGIFFLAGS, &ifopts);
	ifopts.ifr_flags |= IFF_PROMISC;
	//ifopts.ifr_flags &=~ IFF_PROMISC; ///for test
	ioctl(m_nRecvSocket, SIOCSIFFLAGS, &ifopts);

	memset(&haddr, 0, sizeof(haddr));
	haddr.sll_family = PF_PACKET;
	haddr.sll_protocol = htons(ETH_P_ALL);
	haddr.sll_pkttype = PACKET_BROADCAST|PACKET_OTHERHOST;
	memset(&ifr, 0, sizeof(ifr));
	//strcpy(ifr.ifr_name, "veth1");
	strcpy(ifr.ifr_name, m_pIfRecvName);
	if(ioctl(m_nRecvSocket, SIOCGIFINDEX, &ifr) == -1)
	{
		printf("RawSocket ioctl error \n");
		return -1;
	}
	haddr.sll_ifindex = ifr.ifr_ifindex;

	ret = bind(m_nRecvSocket, (struct sockaddr *)&haddr, sizeof(struct sockaddr_ll));
	if(ret < 0)
	{
		printf("failed to bind raw socket! \n");
		return -1;
	}
	printf("RawSocket: bind OK -----------\n");

	if(setsockopt(m_nRecvSocket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt)) == -1)
	{
		printf("RawSocket: setsocketopt REUSEADDR error\n");
		close(m_nRecvSocket);
		return -1;
	}

	if(setsockopt(m_nRecvSocket, SOL_SOCKET, SO_BINDTODEVICE, m_pIfRecvName, IFNAMSIZ-1) == -1)
	{
		printf("RawSocket: setsocketopt BINDTODEVICE error\n");
		close(m_nRecvSocket);
		return -1;
	}
/*
	long RecvBufferSize = 1*1024*1024;
	if((setsockopt(m_nRecvSocket,SOL_SOCKET,SO_RCVBUF,(char*)&Re
int RAWTool::RecvPkt2Fifo()
{

	if((NULL == m_pRawFifo))
		return -1;
	unsigned char rxBuffer[BUF_SIZ] = { 0 };
	int rxLen = -1;
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();

	BB_UdpFrame_t *pudpframe = (BB_UdpFrame_t *)rxBuffer;
	pudpframe->business_type = MAC_DATA;
	
	rxLen = RecvProc((char*)pudpframe->buf , sizeof(rxBuffer) - sizeof(BB_UdpFrame_t));

	if (rxLen > 0)
	{
		UpdateCntVal(rxLen);
	    if(pGlobalVal->GetPrintFlag())
	    {
		   printf("recved raw mac packet: \n");
		   for(unsigned short j=0; j<rxLen; j++ )
			   printf("%02x ",rxBuffer[j]);
		   printf("-----------------------------------------\n\n");
	    }
		//return 0;
		
		return m_pRawFifo->Put((char*) (rxBuffer), rxLen + sizeof(BB_UdpFrame_t));
	}
	return -1;

}

int RAWTool::GetPktFromFifo(char* buffer, int len,int timeout)
{

	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();

	pGlobalVal->SetFifoUseNum(m_pRawFifo->GetFreeNum());

	if((NULL == m_pRawFifo))
		return -1;
    return 	m_pRawFifo->Get(buffer,len,timeout);

}
cvBufferSize,sizeof(RecvBufferSize))) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}

	if((setsockopt(m_nRecvSocket,SOL_SOCKET,SO_SNDBUF,(char*)&RecvBufferSize,sizeof(RecvBufferSize))) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}

	printf("set Raw sock recv buff size  = %d\r\n" , RecvBufferSize);
	printf("set Raw sock send buff size  = %d\r\n" , RecvBufferSize);

	int CurRecvBufSize = -1;
	socklen_t optlen = sizeof(CurRecvBufSize);
	if((getsockopt(m_nRecvSocket , SOL_SOCKET,SO_RCVBUF , &CurRecvBufSize , &optlen)) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
	printf("Cur Raw socket recv buff size  = %d\r\n" , CurRecvBufSize);

	if((getsockopt(m_nRecvSocket , SOL_SOCKET,SO_SNDBUF , &CurRecvBufSize , &optlen)) == -1)
	{
		perror("setsockopt - SO_SOCKET ");
		return RETURN_FAILED;
	}
	printf("Cur Raw socket send buff size  = %d\r\n" , CurRecvBufSize);
*/

	m_pRawFifo =  new CFifo();
	if (NULL == m_pRawFifo) {
		printf("%s %d : Fatal Error! new CFifo Failed! \n", __func__, __LINE__);
		return -1;
	}
	if (RETURN_OK != m_pRawFifo->Create(m_pMutexSignalFactory, fifoNum, FifoLen))
	{
		printf("%s %d : Fatal Error! CFifo Create Failed! \n", __func__, __LINE__);
		return -1;
	}


	return m_nRecvSocket;
}


int RAWTool::RecvProc(char* buf, const int buflen)
{
	//unsigned char buf[BUF_SIZ+1]={0};
	struct sockaddr_storage their_addr;
	char sender[INET6_ADDRSTRLEN];
	struct ether_header *eh;
	struct iphdr *iph;
	struct ifreq if_ip;
	int k=0;

	//Match match;

	eh = (struct ether_header *)buf;
	iph = (struct iphdr *)(buf + sizeof(struct ether_header));
	if(m_nRecvSocket <= 0)
	{
		printf("RawSocket: RecvSocket has not created!\n");
		return RETURN_FAILED;
	}

	k = recvfrom (m_nRecvSocket , buf, buflen , 0, NULL, NULL);

	//match.MatchMsg((char*)buf, NULL, NULL, k);

	if(k<=0)
	{
		return RETURN_FAILED;
	}

	((struct sockaddr_in *)&their_addr)->sin_addr.s_addr = iph->saddr;
	inet_ntop(AF_INET, &((struct sockaddr_in *)&their_addr)->sin_addr, sender, sizeof sender);
	strncpy(if_ip.ifr_name, m_pIfRecvName, IFNAMSIZ-1);
	if(ioctl(m_nRecvSocket, SIOCGIFADDR, &if_ip) >= 0) {
	   /*ignore if I send it*/
		if((strcmp(sender, inet_ntoa(((struct sockaddr_in *)&if_ip.ifr_addr)->sin_addr)) == 0)|| (strcmp("127.0.0.1", sender) == 0))
		{
			//printf("Self Send MAC \n");
			return 0;
		}
	}
	return k;
}

int RAWTool::sendData(char *databuf, int datalen)
{
	int len = 0;
	struct sockaddr_ll socket_address;

	if(datalen > BUF_SIZ)
	{
		printf("Error: SendTo RawSocket DataLen = %d > %d !\n",datalen,BUF_SIZ);
		return RETURN_FAILED;
	}

	if(ioctl(m_nRecvSocket, SIOCGIFINDEX, &ifopts)<0)
		perror("SIOCGINDEX");
	struct ether_header* pMacHead = (struct ether_header *)databuf;

	socket_address.sll_ifindex = ifopts.ifr_ifindex;
	socket_address.sll_halen = ETH_ALEN;
	memcpy(socket_address.sll_addr,pMacHead->ether_dhost,sizeof(pMacHead->ether_dhost));

	len = sendto(m_nRecvSocket, databuf, datalen, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll));
	if(len < 0)
	{
		printf("RawSocket: Send failed, len=%d \n", len);
		perror("RAW SEND ERROR--------\n");
		#if 0
		   printf("******* tx mac failed pkt: \n");
		   for(unsigned short i=0; i<datalen; i++)
			   printf("%02x ",databuf[i]);
		   printf("--------------------------------------------\n");
		#endif

		return RETURN_FAILED;
	}
	//printf("rawtool send data ret: %d \n",len);
	return len;
}

void RAWTool::UpdateCntVal(unsigned short val)
{
#if 0
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();
	if(pGlobalVal)
	{
	   pGlobalVal->IncRxUdpTrafficPktNum();
	   pGlobalVal->IncPhyFrameTotalLen(val);
	}
#endif
}

int RAWTool::InsertData(char* buf, const int len)
{
	if((NULL == m_pRawFifo))
		return -1;
	return m_pRawFifo->Put(buf, len);
}

int RAWTool::RecvPkt2Fifo()
{
	if((NULL == m_pRawFifo))
		return -1;
	unsigned char rxBuffer[BUF_SIZ] = { 0 };
	int rxLen = -1;
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();

	//BB_UdpFrame_t *pudpframe = (BB_UdpFrame_t *)rxBuffer;
	//pudpframe->business_type = MAC_DATA;
	
	rxLen = RecvProc((char*)rxBuffer , sizeof(rxBuffer));

	if (rxLen > 0)
	{
		UpdateCntVal(rxLen);
		pGlobalVal->IncRcvRawMacNum();
		return m_pRawFifo->Put((char*) (rxBuffer), rxLen);
	}
	return -1;
}

int RAWTool::GetPktFromFifo(char* buffer, int len,int timeout)
{
	CGlobalVal* pGlobalVal = CGlobalVal::GetpGlobalVal();

	if((NULL == m_pRawFifo))
		return -1;
    return 	m_pRawFifo->Get(buffer,len,timeout);
}


