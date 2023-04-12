/*
 * Match.cpp
 *
 *  Created on: 2020年11月24日
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <linux/ip.h>

#include "Match.h"

Match::Match()
{
	IPaddress[0] = 192;
	IPaddress[1] = 168;
	IPaddress[2] = 000;
	IPaddress[3] = 010;
	Macaddress[0] = 0x0A;
	Macaddress[1] = 0x55;
	Macaddress[2] = 0x20;
	Macaddress[3] = 0x11;
	Macaddress[4] = 0x20;
	Macaddress[5] = 0x01;
}

int Match::MatchMsg(char *matchbuf, char *p_IPaddress, char *p_Macaddress, int k)
{

	eh = (struct ether_header *)matchbuf;
	iph = (struct iphdr *)(matchbuf + sizeof(struct ether_header));
	p_SrcIP = (char *)&iph->saddr;
	p_DstIP = (char *)&iph->daddr;
	int switch_index = ntohs(eh->ether_type)&0xFFFF;

	if(p_IPaddress == NULL)
	{
		p_IPaddress = IPaddress;
	}
	if(p_IPaddress == NULL)
	{
		p_Macaddress = Macaddress;
	}

	switch(switch_index)
	{
		case	ETHERTYPE_PUP:
			printf("MAC TYPE :   ETHERTYPE_PUP\n");
			break;
		case ETHERTYPE_SPRITE:
			printf("MAC TYPE :   ETHERTYPE_SPRITE\n");
			break;
		case	ETHERTYPE_IP:
			printf("MAC TYPE :   ETHERTYPE_IP\n");
			break;
		case	ETHERTYPE_ARP:
			printf("MAC TYPE :   ETHERTYPE_ARP\n");
			break;
		case	ETHERTYPE_REVARP:
			printf("MAC TYPE :   ETHERTYPE_REVARP\n");
			break;
		case ETHERTYPE_AT:
			printf("MAC TYPE :   ETHERTYPE_AT\n");
			break;
		case ETHERTYPE_AARP:
			printf("MAC TYPE :   ETHERTYPE_AARP\n");
			break;
		case	ETHERTYPE_VLAN:
			printf("MAC TYPE :   ETHERTYPE_VLAN\n");
			break;
		case ETHERTYPE_IPX:
			printf("MAC TYPE :   ETHERTYPE_IPX\n");
			break;
		case	ETHERTYPE_IPV6:
			printf("MAC TYPE :   ETHERTYPE_IPV6\n");
			break;
		case ETHERTYPE_LOOPBACK:
			printf("MAC TYPE :   ETHERTYPE_LOOPBACK\n");
			break;
		default:
			{
				printf("Raw Message is :  \n");
				int i = 0;
				while( i!= k)
				{
					printf("[%d]:%c | ", i, matchbuf[i]);
					i++;
				}
				printf("\n");
				return 1;
			}
			break;
	}

#if 1

	printf("SRCIPTODSTIP:   %d:%d:%d:%d    >>>>>>>>>>>>>    %d:%d:%d:%d \n",\
			p_SrcIP[0], p_SrcIP[1],p_SrcIP[2],p_SrcIP[3],\
			p_DstIP[0], p_DstIP[1],p_DstIP[2],p_DstIP[3]);

	printf("SRCMAC2DSTMAC:  %x:%x:%x:%x:%x:%x >>>>>>>>>>>>> %x:%x:%x:%x:%x:%x\n",\
			eh->ether_shost[0],eh->ether_shost[1],eh->ether_shost[2],eh->ether_shost[3],eh->ether_shost[4],eh->ether_shost[5],\
			eh->ether_dhost[0],eh->ether_dhost[1],eh->ether_dhost[2],eh->ether_dhost[3],eh->ether_dhost[4],eh->ether_dhost[5]);

	printf("Message is :  ");
	int i = 0;
	while((k - 42) > 0 && i!= k-42)
	{
		printf("%c", matchbuf[42 + i]);
		i++;
	}
	printf("\n");


#endif
	return 0;
}

