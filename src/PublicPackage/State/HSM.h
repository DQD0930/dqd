#if !defined(AFX_HSM_H__336B4996_DF5B_4CFE_BBF4_9D771F19CB23__INCLUDED_)
#define AFX_HSM_H__336B4996_DF5B_4CFE_BBF4_9D771F19CB23__INCLUDED_

#include <vector>
#include "State.h"

using namespace std;

class CHSM
{
public:
    CHSM() {}
    virtual ~CHSM();
    void SetRootState(CState * pRoot){m_Root = pRoot;}
//    void ActiveDefaultState();
	void ActiveDefaultState(const char* lpName=NULL);
    void TransitTo(const char * lpName);
    void SendEvent(WORD wEvent, WORD wParam, DWORD lParam);
    CState * GetActiveLeaf(){return m_Active;}
    CState * GetState(const char * lpName);
	void SetActiveState(CState* pState){m_Active = pState;}
protected:
    vector<CState *>    m_States; // ËùÓÐµÄ×´Ì¬
	CState * m_Root;
	CState * m_Active;
};

#endif // !defined(AFX_HSM_H__336B4996_DF5B_4CFE_BBF4_9D771F19CB23__INCLUDED_)

