/*
 * CGlobalVal.cpp
 *
 *  Created on: Nov 24, 2021
 *      Author: root
 */
#include "stdef.h"
#include "CGlobalVal.h"

CGlobalVal* CGlobalVal::m_pGlobalVal = NULL;

CGlobalVal* CGlobalVal::GetpGlobalVal()
{
	if(m_pGlobalVal)
		return m_pGlobalVal;
	if(NULL == m_pGlobalVal)
		m_pGlobalVal = new CGlobalVal();
	return m_pGlobalVal;
}

void CGlobalVal::ResetGlobalVal()
{
	m_nRxUdpTrafficPktNum = 0;
	m_nRxUdpTrafficPktTotalLen = 0;
    m_nL1FrameNum = 0;
    m_nL1FrameTotalLen = 0;
    m_nL1NullFramNum =0;
    m_nPhyFrameNum = 0;
    m_nPhyFrameTotalLen = 0;
    m_nLdpcPktNum = 0;
    m_nLdpcTotalLen = 0;
    m_nTx2PlPktNum = 0;
    m_nTx2PlPktTotalLen = 0;
    m_nRxFromPLPktNum = 0;
    m_nRxFromPlTotalLen = 0;
    m_nPLSpareByte = 0;
    m_nCurModCod = 0;
    memset(m_nRawEthName,0,sizeof(m_nRawEthName));
    m_bSetOnePktPerIntFlag = 0;
    m_nRxPLUdpL1HeadErrCnt = 0;
    m_nRxPLUdpLenErrCnt = 0;
    m_nRxPLUdpPktNum = 0;
    m_bPrintFlag = 0;
    m_nTxMacPktNum = 0;
    m_nTxMacPktErrNum = 0;
    m_bDirectDeliverFlag = 0;
    m_nPlIntNum = 0;
    m_nCurPlFreeByte = 0;
}

void CGlobalVal::SetRawEthName(char* name)
{
    if(strlen(name) > sizeof(m_nRawEthName))
    	return;
    strcpy(m_nRawEthName,name);
}

void CGlobalVal::SetServerIp(char *ip)
{
    if(strlen(ip) > sizeof(m_nServerIp))
    {
        return;
    }
    strcpy(m_nServerIp , ip);
}

CGlobalVal::CGlobalVal()
{
	ResetGlobalVal();
}

CGlobalVal::~CGlobalVal()
{

}
