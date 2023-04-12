// CheckFrame.h: interface for the CCheckFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKFRAME_H__95816DC3_E754_4C78_A7FA_69E6EBFA3B4F__INCLUDED_)
#define AFX_CHECKFRAME_H__95816DC3_E754_4C78_A7FA_69E6EBFA3B4F__INCLUDED_

#include <HSM.h>

DEFINE_STATE_CLASS(CheckFrameState)
   DEFINE_STATE_CLASS(CheckFrameIdleState)
   DEFINE_STATE_CLASS(CheckFrameFoundHeadState)

class CCheckFrame : public CHSM
{
public:
    enum ENUM_EVENT
    {
        EVENT_ADD_DATA,
        EVENT_FOUND_HEAD,
		EVENT_FOUND_TAIL,
        EVENT_CHECKOUT_OK,
        EVENT_RESET_OK,
        EVENT_OVERFLOW,
		EVENT_FORCE_RESET
    };
protected:
	UC *m_pDataBuf;
	int m_nFrameIndex;
	int m_nFrameLen;
	int m_nDataBufLen;
	int m_nDataLen;
	UC m_nHeadTailSameFlag;
public:
	CCheckFrame(UC headTailSameFlag=0);
	virtual ~CCheckFrame();
	int Create(int maxFrameLen);
public:
    bool True(WORD , DWORD ) { return true; }
    bool Void(WORD , DWORD ) { return true; }
    bool CheckHead(WORD wParam, DWORD lParam);
    bool CheckTail(WORD wParam, DWORD lParam);
    bool Reset(WORD wParam, DWORD lParam);
    bool CheckOutFrame(WORD wParam, DWORD lParam);
public:
	virtual int AddData(UC *pAddData,int addLen);
	void ForceReset();
protected:
	virtual int Reset();
	virtual int FindHead() =0;
	virtual int FindTail() =0;
	virtual int CheckFrame(UC *pGetDataBuf,int frameLen, UC *pAppendDataBuf=NULL, int appendDataLen=0)=0;
};

#endif // !defined(AFX_CHECKFRAME_H__95816DC3_E754_4C78_A7FA_69E6EBFA3B4F__INCLUDED_)
