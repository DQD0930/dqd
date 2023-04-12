/*
 * confignet_io.cpp
 *
 *  Created on: 2021年8月31日
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "confignet_io.h"


CONFIG_NETIO::CONFIG_NETIO()
{
	bzero(&ifr, sizeof(ifr));
	bzero(&ifcfig, sizeof(ifcfig));
	bzero(&ifrlist, sizeof(ifrlist));

}
CONFIG_NETIO::~CONFIG_NETIO()
{
	if(sock_fd != 0)
	{
		shutdown(sock_fd, SHUT_RDWR);
	}
}


void CONFIG_NETIO::Query_NetIO(NetIO* netio)
{

	if(netio == NULL)
	{

		sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_fd < 0)
		{
			printf("%m %s %d\r\n", __FUNCTION__, __LINE__);
			exit(-1);
		}
		ifcfig.ifc_len = sizeof(ifrlist);
		ifcfig.ifc_buf = (char*) ifrlist;
		ret = ioctl(sock_fd, SIOCGIFCONF, (char*) &ifcfig);
		if(ret < 0)
		{
			printf("%s %d\r\n:  ", __FUNCTION__, __LINE__);
			perror("SIOCGIFCONF");
			exit(-1);
		}
		netio_count = ifcfig.ifc_len / sizeof(ifr);
		for (int i = 0; i < netio_count; i++)
		{

			printf("interface %s : ", ifrlist[i].ifr_name);

			printf("%s\r\n", inet_ntop(AF_INET, &(((struct sockaddr_in *) &(ifrlist[i].ifr_addr))->sin_addr),ip, INET_ADDRSTRLEN));
			if(ifrlist[i].ifr_addr.sa_family == AF_INET)
			{
				strncpy(ifr.ifr_name, ifrlist[i].ifr_name, IFNAMSIZ - 1);
				ret = ioctl(sock_fd, SIOCGIFHWADDR, &ifr);
				if(ret < 0)
				{
					printf("%s %d\r\n  ", __FUNCTION__, __LINE__);
					perror("SIOCGIFHWADDR");
					exit(-1);
				}
				printf("MAC:%02x:%02x:%02x:%02x:%02x:%02x\r\n\n",
						ifr.ifr_hwaddr.sa_data[0],
						ifr.ifr_hwaddr.sa_data[1],
						ifr.ifr_hwaddr.sa_data[2],
						ifr.ifr_hwaddr.sa_data[3],
						ifr.ifr_hwaddr.sa_data[4],
						ifr.ifr_hwaddr.sa_data[5]
				);
			}

		}
		return ;
	}


}


int CONFIG_NETIO::Set_NetIO_IPADDR(NetIO* netio, NetIO_IPAddr* ipaddr)
{
	if(netio == NULL || ipaddr == NULL)
	{
		printf("IP OR InterFace should not be NULL\r\n");
		return -1;
	}

	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		printf("%m\n");
		return -1;
	}

	bzero(&ifr, sizeof(ifr));
	bzero(&configaddr, sizeof(configaddr));
	strncpy(ifr.ifr_name, netio, IFNAMSIZ - 1);
	configaddr.sin_family = AF_INET;
	inet_pton(AF_INET, ipaddr, &(configaddr.sin_addr));
	memcpy(&ifr.ifr_addr, &configaddr, sizeof(struct sockaddr));
	ret = ioctl(sock_fd, SIOCSIFADDR, &ifr);
	if(ret < 0)
	{
		perror("ioctl");
		return -1;
	}
	close(sock_fd);
	return 0;

}
int CONFIG_NETIO::Set_NetIO_MACADDR(NetIO* netio, NetIO_MacAddr* macaddr)
{
	if(netio == NULL || macaddr == NULL)
	{
		printf("MAC OR InterFace should not be NULL\r\n");
		return -1;
	}

	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		printf("%m\n");
		exit(-1);
	}


	shutdown_interface(netio);

	ifr.ifr_hwaddr.sa_family = ARPHRD_ETHER;
	ifr.ifr_hwaddr.sa_data[0] = macaddr[0];
	ifr.ifr_hwaddr.sa_data[1] = macaddr[1];
	ifr.ifr_hwaddr.sa_data[2] = macaddr[2];
	ifr.ifr_hwaddr.sa_data[3] = macaddr[3];
	ifr.ifr_hwaddr.sa_data[4] = macaddr[4];
	ifr.ifr_hwaddr.sa_data[5] = macaddr[5];
	ret = ioctl(sock_fd, SIOCSIFHWADDR, &ifr);
	if(ret < 0)
	{
		printf("%m %s %d\r\n", __FUNCTION__, __LINE__);
		exit(-1);
	}

	noshutdown_interface(netio);
	close(sock_fd);
	return 0;

}


void CONFIG_NETIO::shutdown_interface(NetIO* netinterf)
{
	bzero(&ifr, sizeof(ifr));
	strncpy(ifr.ifr_name, netinterf, IFNAMSIZ-1);
	ifr.ifr_flags &= ~IFF_UP;
	ret = ioctl(sock_fd, SIOCSIFFLAGS, &ifr);
	if(ret < 0)
	{
		printf("%m %s %d\r\n", __FUNCTION__, __LINE__);
		exit(-1);
	}
	sleep(1);
}
void CONFIG_NETIO::noshutdown_interface(NetIO* netinterf)
{
	//bzero(&ifr, sizeof(ifr));
	strncpy(ifr.ifr_name, netinterf, IFNAMSIZ-1);
	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
	ret = ioctl(sock_fd, SIOCSIFFLAGS, &ifr);
	if(ret < 0)
	{
		printf("%m %s %d\r\n", __FUNCTION__, __LINE__);
		exit(-1);
	}
	sleep(1);
}




