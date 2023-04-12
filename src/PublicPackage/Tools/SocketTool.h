#ifndef SOCKET_TOOL_H
#define SOCKET_TOOL_H

#include <linux/if_packet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/ether.h>

#include "stdef.h"
#include "MutexSignalIncludes.h"
#include "Fifo.h"

#define INVALID_SOCKET -1

#define MY_ETH1_DEST_MAC0  0x00//0xF8//
#define MY_ETH1_DEST_MAC1  0x0C//0x75//
#define MY_ETH1_DEST_MAC2  0x29//0xA4//
#define MY_ETH1_DEST_MAC3  0xD0//0x0F//
#define MY_ETH1_DEST_MAC4  0x09//0x98//
#define MY_ETH1_DEST_MAC5  0x03//0xBE//

#define DEFAULT_SEND_IF  "eth0"

#define BUF_SIZ  1600
#define ETHER_TYPE  0x0800


typedef int SOCKET;

class RAWTool
{
public:
	RAWTool(CMutexSignalFactory *pMutexSignalFactory,char *ifRecvName);
	virtual ~RAWTool();
	int RecvPkt2Fifo();
	int GetPktFromFifo(char* buffer, int len, int timeout=TIME_WAIT_FOR_EVER);
	int sendData(char *databuf, int datalen);
	int RecvProc(char* buf, const int buflen);
	int InsertData(char* buf, const int len);
	SOCKET Init(unsigned short fifoNum, unsigned short FifoLen);
protected:
	struct sockaddr_in client_addr;
	socklen_t client_len;
	struct ifreq If_idx;
	struct sockaddr_ll Socket_address;
	char m_pIfSendName[IFNAMSIZ];
	char m_pIfRecvName[IFNAMSIZ];
	SOCKET m_nRecvSocket;	//recv socket
private:
	void UpdateCntVal(unsigned short val);
private:
	CFifo* m_pRawFifo;
	CMutexSignalFactory *m_pMutexSignalFactory;
};
#endif
