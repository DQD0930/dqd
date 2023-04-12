#include "HSM.h"
#include <string.h>

CHSM::~CHSM()
{
    // �ͷ����е�״̬����
    vector<CState *>::iterator it;
    for (it = m_States.begin(); it < m_States.end(); it ++)
        if (*it)
            delete *it;
}

void CHSM::ActiveDefaultState(const char * lpName)
{
	CState * pState;
	// ����Ŀ��״̬
	if(lpName)
	    pState = GetState(lpName);
	else
		pState = *m_States.begin();
    if (pState)
    {
		// ������Զ��ȱʡ��״̬
		while(pState->GetDefaultChild())
			pState = pState->GetDefaultChild();
		// ����״̬
		pState->Active(this, *m_States.begin());
//		m_Active = pState;
	}
}

void CHSM::TransitTo(const char * lpName)
{
	// ����Ŀ��״̬
    CState * pState = GetState(lpName);
    if (pState)
    {
		// �ҵ���ǰ״̬��Ŀ��״̬�����������״̬
		CState * pCommonAncestor = pState;
		while (! pCommonAncestor->IsActive())
			pCommonAncestor = pCommonAncestor->GetParent();
		// �õ�Ŀ��״̬�������������״̬����ĸ�״̬
		CState* pParent = pState->GetNearAncestor(pCommonAncestor);
		// ֹͣ������״̬�����еĻ״̬
		if(pCommonAncestor->GetActiveLeaf())
			pCommonAncestor->GetActiveLeaf()->Deactive(this);
		if (pParent == pCommonAncestor)
		{
			if(pState != pCommonAncestor)
				//����Ӹ�״̬ת��ֱ����״̬��ֱ�Ӽ���;��֮�����ٴμ��״̬
				pState->Active(this,pState);
		}
		else
		{
			// ����������״̬��Ŀ��״̬������״̬,���������״̬δ�˳������ü���
			pState->Active(this, pParent);
		}
        // ����Ŀ��״̬��ȱʡ��״̬
        pState->ActiveDefaultChild(this);
//		while(pState->GetActiveLeaf())
//			pState = pState->GetActiveLeaf();
//		m_Active = pState;
    }
}

void CHSM::SendEvent(WORD wEvent, WORD wParam, DWORD lParam)
{
	//�����¼�����ǰ�״̬

	m_Active->SendEvent(this, wEvent, wParam, lParam);

}

CState * CHSM::GetState(const char * lpName)
{
    CState * pState = NULL;
    // �������ֵõ�״̬��ָ��
    for (unsigned int i = 0; i < m_States.size(); i++)
        if (! strcmp(m_States[i]->GetName(), lpName))
        {
            pState = m_States[i];
            break;
        }
    return pState;
}
