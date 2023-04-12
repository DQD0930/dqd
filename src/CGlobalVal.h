/*
 * CGlobalVal.h
 *
 *  Created on: Nov 24, 2021
 *      Author: root
 */

#ifndef SRC_CGLOBALVAL_H_
#define SRC_CGLOBALVAL_H_

#define HAVE_PS_PL_BRAM
#define DEBUG_DATA_FLOW

#define ACCESS_ROUTE    1
#define LIGHTWEIGHT     2
#define MUILTE_ROUTE    3

#define PRINTF_LOG      1

class CGlobalVal {
public:
    static CGlobalVal* GetpGlobalVal();
    void ResetGlobalVal();

    void SetRxUdpTrafficPktNum(unsigned int val) {m_nRxUdpTrafficPktNum = val;}
    void IncRxUdpTrafficPktNum(){m_nRxUdpTrafficPktNum++;}
    void SetRxUdpTrafficPktTotalLen(unsigned long long val) {m_nRxUdpTrafficPktTotalLen = val;}
    void IncRxUdpTrafficPktTotalLen(unsigned short val){m_nRxUdpTrafficPktTotalLen += val;}
    void SetL1FrameNum(unsigned int val) {m_nL1FrameNum = val;}
    void IncL1FrameNum(){m_nL1FrameNum++;}
    void IncL1NullFrameNum(unsigned char cnt){m_nL1NullFramNum += cnt;}
    void SetL1FrameTotalLen(unsigned long long val) {m_nL1FrameTotalLen = val;}
    void InctL1FrameTotalLen(unsigned short val){m_nL1FrameTotalLen += val;}
    void SetPhyFrameNum(unsigned int val) {m_nPhyFrameNum = val;}
    void IncPhyFrameNum(){m_nPhyFrameNum++;}
    void SetPhyFrameTotalLen(unsigned long long val) {m_nPhyFrameTotalLen = val;}
    void IncPhyFrameTotalLen(unsigned int val){m_nPhyFrameTotalLen+= val;}
    void SetLdpcPktNum(unsigned int val) {m_nLdpcPktNum = val;}
    void IncLdpcPktNum(){m_nLdpcPktNum++;}
    void SetLdpcTotalLen(unsigned long long val) {m_nLdpcTotalLen = val;}
    void InctLdpcTotalLen(unsigned short val){m_nLdpcTotalLen+=val;}
    void SetTx2PlPktNum(unsigned int val) {m_nTx2PlPktNum = val;}
    void IncTx2PlPktNum(){m_nTx2PlPktNum++;}
    void SetTx2PlPktTotalLen(unsigned long long val) {m_nTx2PlPktTotalLen = val;}
    void IncTx2PlPktTotalLen(unsigned short val){m_nTx2PlPktTotalLen += val;}
    void SetRxFromPLPktNum(unsigned int val) {m_nRxFromPLPktNum = val;}
    void SetRxFromPlTotalLen(unsigned long long val) {m_nRxFromPlTotalLen = val;}

    void IncRxPLL1HeadErrPktNum(){m_nRxPLUdpL1HeadErrCnt++;}
    void IncRxPLLenErrPktNum(){m_nRxPLUdpLenErrCnt++;}
    void IncRxPLUdpPktNum(){m_nRxPLUdpPktNum++;}
    void IncTxMacPktNum(){m_nTxMacPktNum++;}
    void IncTxMacPktErrNum(){m_nTxMacPktErrNum++;}
	void IncPlIntNum(){m_nPlIntNum++;}
	void SetCurPlFreeByte(unsigned int val){m_nCurPlFreeByte = val;}

    void SetPLSpareByte(unsigned int val){m_nPLSpareByte =val;}
    void SetCurModCod(unsigned char val){m_nCurModCod = val;}

    void SetRawEthName(char* name);
    void SetOnePktPerIntFlag(char val){m_bSetOnePktPerIntFlag = val;}
    void SetPrintFlag(char val){m_bPrintFlag = val;}
    void SetDirectDeliverFlag(char val){m_bDirectDeliverFlag = val;}

    unsigned int GetRxUdpTrafficPktNum() {return m_nRxUdpTrafficPktNum;}
    unsigned long long GetRxUdpTrafficPktTotalLen() {return m_nRxUdpTrafficPktTotalLen;}
    unsigned int GetL1FrameNum() {return m_nL1FrameNum;}
    unsigned int GetL1NullFrameNum(){return m_nL1NullFramNum;}
    unsigned long long GetL1FrameTotalLen() {return m_nL1FrameTotalLen;}
    unsigned int GetPhyFrameNum(){return m_nPhyFrameNum;}
    unsigned long long GetPhyFrameTotalLen() {return m_nPhyFrameTotalLen;}
    unsigned int GetLdpcPktNum(){return m_nLdpcPktNum;}
	long long GetLdpcTotalLen() {return m_nLdpcTotalLen;}
    unsigned int GetTx2PlPktNum(){return m_nTx2PlPktNum;}
    unsigned long long GetTx2PlPktTotalLen() {return m_nTx2PlPktTotalLen;}
    unsigned int GetRxFromPLPktNum(){return m_nRxFromPLPktNum;}
    unsigned long long GetRxFromPlTotalLen() {return m_nRxFromPlTotalLen;}

    unsigned int GetRxPLL1HeadErrPktNum(){return m_nRxPLUdpL1HeadErrCnt;}
    unsigned int GetRxPLLenErrPktNum(){return m_nRxPLUdpLenErrCnt;}
    unsigned int GetRxPLUdpPktNum(){return m_nRxPLUdpPktNum;}
    unsigned int GetTxMacPktNum(){return m_nTxMacPktNum;}
    unsigned int GetTxMacPktErrNum(){return m_nTxMacPktErrNum;}
    unsigned int GetPlIntNum(){return m_nPlIntNum;}
    unsigned int GetCurPlFreeByte(){return m_nCurPlFreeByte;}

    unsigned int GetPLSpareByte() {return m_nPLSpareByte;}
    unsigned char GetCurModCod(){return m_nCurModCod;}

    char*  GetRawEthName(){return m_nRawEthName;}
    char   GetOnePktPerIntFlag(){return m_bSetOnePktPerIntFlag;}
    char   GetPrintFlag(){return m_bPrintFlag;}
    char   GetDierctDeliverFlag(){return m_bDirectDeliverFlag;}


	void IncRcvRawMacNum(){m_nRecvRawMacNum++;};
	unsigned int GetRcvRawMacNum(){
#ifdef USER_IPACC
		return m_nRecvRawMacNum;
#else
		return m_nRxUdpTrafficPktNum;
#endif
	};
	void IncSendUdpPktNum(){m_nSendUdpPktNum++;};
	unsigned int GetSendUdpPktNum(){return m_nSendUdpPktNum;};
	void IncRcvUdpPktNum(){m_nRecvUdpPktNum++;};
	unsigned int GetRcvUdpPktNum(){return m_nRecvUdpPktNum;};

	void IncRcvUdpPktLen(unsigned int val){m_nRecvUdpPktLen += val;};
	unsigned int GetRcvUdpPktLen(){return m_nRecvUdpPktLen;};
	
	void IncSendRawMacNum(){m_nSendRawMacNum++;};
	unsigned int GetSendRawMacNum(){return m_nSendRawMacNum;};

	void IncSendRawMacLen(unsigned int val){m_nSendRawMacLen += val;};
	unsigned int GetSendRawMacLen(){return m_nSendRawMacLen;};

	void IncCurRcvRawMacLen(unsigned int val){m_nCurrRecvMacLen += val;};
	unsigned int GetCurRcvRawMacLen(){return m_nCurrRecvMacLen;};

	void IncTxUdpPktLen(unsigned int val){m_nTxUdpPktLen += val;};
	unsigned int GetTxUdpPktLen(){return m_nTxUdpPktLen;};

	void SetFifoUseNum(unsigned int val){m_nFifoUseNum = val;};
	void MaxFifoUseNum(unsigned int val){
		if(val < m_nFifoUseNum)
			m_nFifoUseNum = val;
	};
	unsigned int GetFifoUseNum(){return m_nFifoUseNum;};

	void MaxUdpFifoUseNum(unsigned int val){
		if(val > m_nUdpFifoMaxNum)
			m_nUdpFifoMaxNum = val;
	};
	unsigned int GetUdpFifoUseNum(){return m_nUdpFifoMaxNum;};


	void IncFifoFreeNum(){m_nFifoFreeNum++;};
	void CntFifoFreeNum(){m_nFifoFreeNum--;};
	unsigned int GetFifoFreeNum(){return m_nFifoFreeNum;};
	
    void SetServerIp(char *ip);
    void SetServerPort(short port){m_nServerPort = port;};
    char* GetServerIp(){return m_nServerIp;};
    short GetServerPort(){return m_nServerPort;};
	
    void SetLocalPort(short port){m_nLocalPort = port;};
    short GetLocalPort(){return m_nLocalPort;};

    void SetRouteProtocolType(char protocoltype){m_nRouteProtocol = protocoltype;};
    char GetRouteProtocolType(){return m_nRouteProtocol;};

    void SetNeedQueryIpAddr(int ip){m_nNeedQueryIp = ip;};
    int GetNeesQueryIpAddr(){return m_nNeedQueryIp;};

    void SetSendProtocolType(int type){m_nSendProtocoltype = type;};
    int GetSendProtocolType(){return m_nSendProtocoltype;};

    void IncRxLanRouteNum(char num){m_nRxLanRouteNum += num;};
    int GetRxLanRouteNum(){return m_nRxLanRouteNum;};

    void IncTxLanRouteNum(char num){m_nTxLanRouteNum += num;};
    int GetTxLanRouteNum(){return m_nTxLanRouteNum;};

    void IncRxWanRouteNum(char num){m_nRxWanRouteNum += num;};
    int GetRxWanRouteNum(){return m_nRxWanRouteNum;};

    void IncTxWanRouteNum(char num){m_nTxWanRouteNum += num;};
    int GetTxWanRouteNum(){return m_nTxWanRouteNum;};

    void SetPrintLogLevel(char level){m_nPrintLogLevel = level;};
    int GetPrintLogLevel(){return m_nPrintLogLevel;};

    void IncLabelNum(char num){m_nLabelNum += num;};
    int GetLabelNum(){return m_nLabelNum;};

    void IncTxUdpIpPktNum(){m_nTxUdpIpPktNum++;};
    int GetTxUdpIpPktNum(){return m_nTxUdpIpPktNum;};

    int GetIGMPFlag(){return m_nMulticastPIMFlag;};
    void SetIGMPFlag(int value){m_nMulticastPIMFlag = value;};

    void SetPIMType(int value){m_nPIMtype = value;};
    int GetPIMType(){return m_nPIMtype;};

    void SetPIMSMISSRC(int value){m_nPIMSMISNOTSRC = value;};
    int GetPIMSMISSRC(){return m_nPIMSMISNOTSRC;};

    void SetPacketMode(int value){m_nPacketMode = value;};
    int GetPacketMode(){return m_nPacketMode;};

    void SetPerformanceTest(int value){ m_nPerformanceTest = value;};
    int GetPerformanceTest(){return m_nPerformanceTest;};

protected:
	CGlobalVal();
	virtual ~CGlobalVal();
private:
	static CGlobalVal* m_pGlobalVal;
	unsigned int m_nRxUdpTrafficPktNum;
	unsigned long long m_nRxUdpTrafficPktTotalLen;
    unsigned int m_nL1FrameNum;
    unsigned int m_nL1NullFramNum;
    unsigned long long m_nL1FrameTotalLen;
    unsigned int m_nPhyFrameNum;
    unsigned long long m_nPhyFrameTotalLen;
    unsigned int m_nLdpcPktNum;
    unsigned long long m_nLdpcTotalLen;
    unsigned int m_nTx2PlPktNum;
    unsigned long long m_nTx2PlPktTotalLen;
    unsigned int m_nRxFromPLPktNum;
    unsigned long long m_nRxFromPlTotalLen;
    unsigned int m_nPLSpareByte;
    unsigned char m_nCurModCod;
    unsigned int m_nRxPLUdpPktNum;
    unsigned int m_nRxPLUdpL1HeadErrCnt;
    unsigned int m_nRxPLUdpLenErrCnt;
    unsigned int m_nTxMacPktNum;
    unsigned int m_nTxMacPktErrNum;
    unsigned int m_nPlIntNum;
    unsigned int m_nCurPlFreeByte;


	unsigned int m_nRecvRawMacNum;
	unsigned int m_nSendUdpPktNum;
	unsigned int m_nRecvUdpPktNum;
	unsigned int m_nRecvUdpPktLen;
	unsigned int m_nSendRawMacNum;
	unsigned int m_nSendRawMacLen;

	unsigned int m_nCurrRecvMacLen;
	unsigned int m_nTxUdpPktLen;

	unsigned int m_nFifoFreeNum;
	
	unsigned int m_nFifoUseNum;
	unsigned int m_nFifoUseMaxNum;

	unsigned int m_nUdpFifoMaxNum;
	
    char m_nRawEthName[10];
    char m_bSetOnePktPerIntFlag;
    char m_bPrintFlag;
    char m_bDirectDeliverFlag;        // rx raw mac or udp and direct send to PL


    char m_nServerIp[20];
    short m_nServerPort;
    short m_nLocalPort;

    char m_nRouteProtocol;
    int m_nNeedQueryIp;
    char m_nSendProtocoltype;

    int m_nRxLanRouteNum;
    int m_nTxLanRouteNum;
    int m_nRxWanRouteNum;
    int m_nTxWanRouteNum;

    char m_nPrintLogLevel;

    int m_nLabelNum;

    int m_nTxUdpIpPktNum;

    int m_nMulticastPIMFlag;

    int m_nPIMtype;
    int m_nPIMSMISNOTSRC;

    int m_nPacketMode;

    int m_nPerformanceTest;


};







#endif /* SRC_CGLOBALVAL_H_ */
