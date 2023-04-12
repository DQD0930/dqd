/*
 * Extra_IP.cpp
 *
 *  Created on: 2021年4月12日
 *      Author: root
 */

#include "Extract_IP.h"


Extract_ip::Extract_ip()
{

}

void Extract_ip::extract(char* Rawbuf, int &Rawlen, char HeadFlag, char* Dstaddrbuf, char* Srcaddr)
{
	char* ptmp;
	ptmp = Rawbuf;

	//memcpy(tmp_buf, Rawbuf, Rawlen);

	eh = (struct ether_header *)Rawbuf;
	if(Dstaddrbuf != NULL)
	{
		Dstaddrbuf[0] = eh->ether_dhost[0];
		Dstaddrbuf[1] = eh->ether_dhost[1];
		Dstaddrbuf[2] = eh->ether_dhost[2];
		Dstaddrbuf[3] = eh->ether_dhost[3];
		Dstaddrbuf[4] = eh->ether_dhost[4];
		Dstaddrbuf[5] = eh->ether_dhost[5];
		if(Srcaddr != NULL)
		{
			Srcaddr[0] = eh->ether_shost[0];
			Srcaddr[1] = eh->ether_shost[1];
			Srcaddr[2] = eh->ether_shost[2];
			Srcaddr[3] = eh->ether_shost[3];
			Srcaddr[4] = eh->ether_shost[4];
			Srcaddr[5] = eh->ether_shost[5];
			return ;
		}
		return ;
	}


	//*((unsigned int*)ptmp) = (((Rawlen + 1) << 16) + 0xFFFF);//add 1 byte means bussiness type
	//*(ptmp+4) = HeadFlag;
	//memcpy((void*)(ptmp+5), (void*)tmp_buf, Rawlen);
	//Rawlen += 5;


	//*((unsigned int*)ptmp) = (HeadFlag);//add 1 byte means bussiness type
	//*(ptmp) = HeadFlag;
	//memcpy((void*)(ptmp+1), (void*)tmp_buf, Rawlen);
	//Rawlen += 1;

}


