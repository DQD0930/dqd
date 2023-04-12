/*
 * Match.h
 *
 *  Created on: 2020年11月24日
 *      Author: root
 */

#ifndef SRC_MATCH_H_
#define SRC_MATCH_H_

#include "SocketTool.h"
#define IPADDLEN 4
#define MACADDLEN 6

class Match
{
public:
	int MatchMsg(char *matchbuf,char *p_IPaddress, char *p_Macaddress, int k);
	Match();
private:
	char *p_SrcIP;
	char *p_DstIP;
	struct ether_header *eh;
	struct iphdr *iph;
	char IPaddress[IPADDLEN];
	char Macaddress[MACADDLEN];
};

#endif /* SRC_MATCH_H_ */
