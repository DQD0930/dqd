/*
 * Extra_IP.h
 *
 *  Created on: 2021年4月12日
 *      Author: root
 */

#ifndef SRC_PUBLICPACKAGE_TOOLS_EXTRACT_IP_H_
#define SRC_PUBLICPACKAGE_TOOLS_EXTRACT_IP_H_

#pragma once

#include <net/ethernet.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tools.h>

#define FRAME_HEAD						0xFFFF0000

class Extract_ip
{
public:
	void extract(char* Rawbuf, int &Rawlen, char HeadFlag = 0xFF, char* Dstaddrbuf = NULL, char* Srcaddr = NULL);
	Extract_ip();

private:
	struct ether_header *eh;
	struct iphdr *iph;
	//char* pbuf;
	//char tmp_buf[0x2000];
	short len;
};

#endif /* SRC_PUBLICPACKAGE_TOOLS_EXTRACT_IP_H_ */
