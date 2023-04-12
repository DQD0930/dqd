/*
 * Produce_TestData.c
 *
 *  Created on: 2021年11月11日
 *      Author: root
 */

#include "Produce_TestData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "rand_num.h"

unsigned char TestData::DataNUM = 0 ;
unsigned short TestData::IpDataNUM = 0;
unsigned char TestData::RandDataNUM = 0;
unsigned char TestData::IncreaseDataNUM = 0;



TestData::TestData()
{

}

TestData::~TestData()
{

}

int TestData::GetTestData(char* buffer, int len, char DataType)
{
	if(len <= 0 || buffer == NULL)
	{
		return -1;
	}
	if(DataType == SIMPLEDATA)
	{
		ProduceData(buffer, len);
		return len;
	}
	if(DataType == IPDATA)
	{
		ProduceIPData(buffer, len);
		return len;
	}
	if(DataType == RANDDATA)
	{
		ProduceRandData(buffer, len);
		return len;
	}
	if(DataType == INCREDATA)
	{
		ProduceIncreaseData(buffer, len);
		return len;
	}
	return -1;
}

void TestData::ProduceData(char* buffer, int len)
{
	if(DataNUM == MAXDATANUMPACK)
	{
		DataNUM = 0;
	}
	DataNUM++;

	memset(buffer, 0xF0, len);
	buffer[0] = DataNUM;

}
void TestData::ProduceIPData(char* buffer, int len)
{
	/*if(IpDataNUM == MAXDATANUMPACK)
	{
		IpDataNUM = 0;
	}*/
	IpDataNUM++;
	if(len <= 42)
	{
		printf("ip data buf len too short should be more than 42 !!!\r\n");
		exit(-1);
	}

	char* p_tmp = FillUpIpHeader(buffer);
	*p_tmp = 0x61;
    char cnt = 0;
	char* p_end = buffer + len - 1;

	while(1)
	{
		if(p_tmp > p_end)
		{
			break;
		}
		else
		{
			//p_tmp++;
			if(*p_tmp >= 0x77)
			{
				p_tmp++;
				//*p_tmp = 0x61;
				*p_tmp = cnt++;
			}
			else
			{
				char*p = p_tmp;
				p_tmp++;
				//*p_tmp = *p;
				*p_tmp = cnt++;
			}
		}

	}
}
void TestData::ProduceRandData(char* buffer, int len)
{
	if(RandDataNUM == MAXDATANUMPACK)
	{
		RandDataNUM = 0;
	}
	RandDataNUM++;

	for(int i = 0; i < len; i++)
	{
		buffer[i] = Produce_RandNum();
	}
	buffer[0] = RandDataNUM;

}
void TestData::ProduceIncreaseData(char* buffer, int len)
{
	if(IncreaseDataNUM == MAXDATANUMPACK)
	{
		IncreaseDataNUM = 0;
	}
	IncreaseDataNUM++;

	for(int i = 0; i < len; i++)
	{
		buffer[i] = (char)i;
	}
	buffer[0] = IncreaseDataNUM;
}


char* TestData::FillUpIpHeader(char* buffer)
{
	IpDataHeader.destmac[0] = 0xF8;
	IpDataHeader.destmac[1] = 0x75;
	IpDataHeader.destmac[2] = 0xA4;
	IpDataHeader.destmac[3] = 0x0A;
	IpDataHeader.destmac[4] = 0x6D;
	IpDataHeader.destmac[5] = 0xDD;


	IpDataHeader.srcmac[0] = 0xE8;
	IpDataHeader.srcmac[1] = 0x6A;
	IpDataHeader.srcmac[2] = 0x64;
	IpDataHeader.srcmac[3] = 0xD9;
	IpDataHeader.srcmac[4] = 0x00;
	IpDataHeader.srcmac[5] = 0xA8;

	IpDataHeader.Type = 0x0800;

	IpDataHeader.Ip_V_L = 0x45;

	IpDataHeader.Service_Feild = 0x00;

	IpDataHeader.Total_Len = (short)1000;

	IpDataHeader.Identification = (short)IpDataNUM;

	IpDataHeader.OffSet = 0x00;

	IpDataHeader.TTL = 0x80;

	IpDataHeader.protocol = 0x01;

	IpDataHeader.headchecksum = 0x00;

	IpDataHeader.dstip[0] = 0xC0;
	IpDataHeader.dstip[1] = 0xA8;
	IpDataHeader.dstip[2] = 0x64;
	IpDataHeader.dstip[3] = 0x80;

	//Ipheader IpDataHeader;
	IpDataHeader.srcip[0] = 0xC0;
	IpDataHeader.srcip[1] = 0xA8;
	IpDataHeader.srcip[2] = 0x64;
	IpDataHeader.srcip[3] = 0xC8;


	IpDataHeader.type_code = 0x00;

	IpDataHeader.chenksum = 0x0000;

	IpDataHeader.Id = IpDataNUM;

	IpDataHeader.seqnum = IpDataNUM;

	memcpy(buffer, (void*)&IpDataHeader, sizeof(IpDataHeader));

	return (buffer+sizeof(IpDataHeader));

}





