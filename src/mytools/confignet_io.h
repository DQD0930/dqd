/*
 * confignet_io.h
 *
 *  Created on: 2021年8月31日
 *      Author: root
 */

#ifndef SRC_PUBLICPACKAGE_TOOLS_CONFIGNET_IO_H_
#define SRC_PUBLICPACKAGE_TOOLS_CONFIGNET_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>

typedef char  NetIO;
typedef char  NetIO_IPAddr;
typedef char  NetIO_MacAddr;

class CONFIG_NETIO
{
public:
	CONFIG_NETIO();
	virtual ~CONFIG_NETIO();
	void Query_NetIO(NetIO* netio = NULL);
	int Set_NetIO_IPADDR(NetIO* netio, NetIO_IPAddr* ipaddr);
	int Set_NetIO_MACADDR(NetIO* netio, NetIO_MacAddr* ipaddr);
private:
	struct ifreq ifr;
	struct ifreq ifrlist[10];
	struct ifconf ifcfig;
	int sock_fd, ret, netio_count;
	char ip[INET_ADDRSTRLEN];
	char mac[ETH_ALEN];
	struct sockaddr_in configaddr;
	void shutdown_interface(NetIO* netinterf);
	void noshutdown_interface(NetIO* netinterf);
};




#endif /* SRC_PUBLICPACKAGE_TOOLS_CONFIGNET_IO_H_ */
