// CheckFrame.cpp: implementation of the CCheckFrame class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdef.h>
#include "CheckFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CLASS_NAME CCheckFrame

BEGIN_STATE_TRANSITION(CheckFrameState)
END_STATE_TRANSITION

BEGIN_STATE_TRANSITION(CheckFrameIdleState)
    ON_ENTRY(CheckHead)

    ON_EVENT_INTERNAL(CLASS_NAME::EVENT_ADD_DATA, True, CheckHead)

    ON_EVENT_TRANSITION(CLASS_NAME::EVENT_FOUND_HEAD, True, Void,CheckFrameFoundHeadState)
END_STATE_TRANSITION

BEGIN_STATE_TRANSITION(CheckFrameFoundHeadState)
    ON_ENTRY(CheckTail)
    ON_EVENT_INTERNAL(CLASS_NAME::EVENT_ADD_DATA, True, CheckTail)
	ON_EVENT_INTERNAL(CLASS_NAME::EVENT_OVERFLOW, True, Reset)
	ON_EVENT_INTERNAL(CLASS_NAME::EVENT_FORCE_RESET, True, Reset)
	ON_EVENT_INTERNAL(CLASS_NAME::EVENT_FOUND_TAIL, True, CheckOutFrame)
    ON_EVENT_TRANSITION(CLASS_NAME::EVENT_RESET_OK, True, Void,CheckFrameIdleState)
	ON_EVENT_TRANSITION(CLASS_NAME::EVENT_CHECKOUT_OK, True, Void,CheckFrameIdleState)
END_STATE_TRANSITION

CCheckFrame::CCheckFrame(UC headTailSameFlag)
{
	m_pDataBuf = NULL;
	m_nFrameIndex = 0;
	m_nFrameLen = 0;
	m_nDataBufLen = 0;
	m_nDataLen = 0;
	m_nHeadTailSameFlag = headTailSameFlag;
}

CCheckFrame::~CCheckFrame()
{
	if(m_pDataBuf)
	{
		delete m_pDataBuf;
	}
}

int CCheckFrame::Create(int maxFrameLen)
{
	m_nDataBufLen = 2*maxFrameLen;
	m_pDataBuf = new UC[m_nDataBufLen];
	if(m_pDataBuf == NULL)
		exit(1);
    INIT_ROOT_STATE(CheckFrameState)
        INIT_STATE(CheckFrameState, CheckFrameIdleState)
        INIT_STATE(CheckFrameState, CheckFrameFoundHeadState)
	SET_DEFAULT_STATE(CheckFrameState,CheckFrameIdleState)
    ActiveDefaultState();
	return RETURN_OK;
}

bool CCheckFrame::CheckHead(WORD , DWORD )
{
	if(FindHead()==RETURN_OK)
	{
		SendEvent(CCheckFrame::EVENT_FOUND_HEAD, 0, 0);
	}
	return true;
}

bool CCheckFrame::CheckTail(WORD , DWORD )
{
	if(FindTail()==RETURN_OK)
	{
		SendEvent(CCheckFrame::EVENT_FOUND_TAIL, 0, 0);
	}
	return true;
}

bool CCheckFrame::Reset(WORD , DWORD )
{
	if(Reset()==RETURN_OK)
	{
		SendEvent(CCheckFrame::EVENT_RESET_OK, 0, 0);
	}
	return true;
}

bool CCheckFrame::CheckOutFrame(WORD , DWORD )
{
	if((m_nFrameIndex+m_nFrameLen)<=m_nDataBufLen)//single mode
	{
		CheckFrame(m_pDataBuf+m_nFrameIndex,m_nFrameLen);
		m_nDataLen -= m_nFrameLen;
		m_nFrameIndex = (m_nFrameIndex+m_nFrameLen)%m_nDataBufLen;
		m_nFrameLen=0;
	}
	else//back mode
	{
		int this_copy_len;
		this_copy_len = m_nDataBufLen - m_nFrameIndex;
		CheckFrame(m_pDataBuf+m_nFrameIndex,this_copy_len, m_pDataBuf, m_nFrameLen-this_copy_len);
		m_nDataLen -= m_nFrameLen;
		m_nFrameIndex = (m_nFrameIndex+m_nFrameLen)%m_nDataBufLen;
		m_nFrameLen = 0;
	}
	SendEvent(CCheckFrame::EVENT_CHECKOUT_OK, 0, 0);
	return true;
}

int CCheckFrame::AddData(UC *pAddData,int addLen)
{
	if(addLen>(m_nDataBufLen-m_nDataLen))
	{

		SendEvent(CCheckFrame::EVENT_OVERFLOW, 0, 0);
		return RETURN_FAILED;
	}
	int freeLen = m_nDataBufLen-(m_nDataLen+m_nFrameIndex);
	if(freeLen<=0)//back directly
	{

		memcpy(m_pDataBuf+(m_nFrameIndex+m_nDataLen)%m_nDataBufLen,pAddData,addLen);
		m_nDataLen += addLen;
    	SendEvent(CCheckFrame::EVENT_ADD_DATA, 0, 0);
        return addLen;
	}
	if(addLen<=freeLen)//don't add data when backward
	{

		memcpy(m_pDataBuf + m_nFrameIndex + m_nDataLen, pAddData, addLen);
		m_nDataLen += addLen;
		SendEvent(CCheckFrame::EVENT_ADD_DATA, 0, 0);
		return addLen;
	}
	else//need add data when backward
	{

		int this_add_len;
		memcpy(m_pDataBuf+m_nFrameIndex+m_nDataLen,pAddData,freeLen);
		m_nDataLen += freeLen;
		this_add_len = addLen - freeLen;
		pAddData += freeLen;
		this_add_len = m_nFrameIndex<this_add_len?m_nFrameIndex:this_add_len;
		memcpy(m_pDataBuf,pAddData,this_add_len);
		m_nDataLen += this_add_len;
		SendEvent(CCheckFrame::EVENT_ADD_DATA, 0, 0);
		return freeLen+this_add_len;
	}
}

void CCheckFrame::ForceReset()
{
	SendEvent(CCheckFrame::EVENT_FORCE_RESET, 0, 0);
}

int CCheckFrame::Reset()
{
	m_nFrameIndex = 0;
	m_nFrameLen = 0;
	m_nDataLen = 0;
    return RETURN_OK;
}
