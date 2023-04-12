/*
 * Produce_TestData.h
 *
 *  Created on: 2021年11月11日
 *      Author: root
 */

#ifndef SRC_PUBLICPACKAGE_TOOLS_PRODUCE_TESTDATA_H_
#define SRC_PUBLICPACKAGE_TOOLS_PRODUCE_TESTDATA_H_

#include "stdef.h"

#define MAXDATANUMPACK      20
//#define MAXDATANUMPACK      20
#define SIMPLEDATA			 1
#define IPDATA					 2
#define RANDDATA				 3
#define INCREDATA				 4

typedef struct Ipheader
{
	/*mac header*/
	unsigned char destmac[6];
	unsigned char srcmac[6];
	unsigned short Type;
	/*ip header*/
	unsigned char Ip_V_L;
	unsigned char Service_Feild;		/*moren 00*/
	unsigned short Total_Len;
	unsigned short Identification;
	unsigned short OffSet;
	unsigned char TTL;
	unsigned char protocol;
	unsigned short headchecksum;
	unsigned char dstip[4];
	unsigned char srcip[4];
	unsigned short type_code;  		/*moren 0000*/
	unsigned short chenksum;
	unsigned short Id;
	unsigned short seqnum;
}PACKED Ipheader;

class TestData
{

public:
	TestData();
	~TestData();
	int GetTestData(char* buffer, int len, char DataType);
private:
	static unsigned char DataNUM;
	static unsigned short IpDataNUM;
	static unsigned char RandDataNUM;
	static unsigned char IncreaseDataNUM;

	Ipheader IpDataHeader;

	void ProduceData(char* buffer, int len);
	void ProduceIPData(char* buffer, int len);
	void ProduceRandData(char* buffer, int len);
	void ProduceIncreaseData(char* buffer, int len);
	char* FillUpIpHeader(char* buffer);


};




#endif /* SRC_PUBLICPACKAGE_TOOLS_PRODUCE_TESTDATA_H_ */
