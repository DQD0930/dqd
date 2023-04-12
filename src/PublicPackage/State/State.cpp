#include "State.h"
#include "HSM.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CState::CState(CHSM * pFSM, const char * lpName, const char * lpParent) :
		m_pDefault(NULL), m_pActive(NULL), m_pName(lpName) {
	if (lpParent)
		m_pParent = pFSM->GetState(lpParent);
	else {
		m_pParent = NULL;
		pFSM->SetRootState(this);
	}
}

/*
 *  ���¼����ݸ���ǰ�״̬�������ǰ״̬�������򽻸���״̬����
 */
bool CState::SendEvent(CHSM * pFSM, WORD wEvent, WORD wParam, DWORD lParam) {
	bool ret = OnEvent(pFSM, wEvent, wParam, lParam);
	if (!ret && m_pParent)
		return m_pParent->SendEvent(pFSM, wEvent, wParam, lParam);
	else
		return ret;
}

/*  ��Ŀ��״̬��ʼ������Ŀ��״̬��Ҷ��״̬֮�������ȱʡ��״̬
 *  ������Щ״̬����ڶ�����˳���Ŀ��״̬��Ҷ��״̬��������Ŀ��״̬
 */
void CState::ActiveDefaultChild(CHSM * pFSM) {
	if (m_pDefault) {
		// ����ȱʡ��״̬����ڶ���
		m_pActive = m_pDefault;
		pFSM->SetActiveState(m_pDefault);
		m_pDefault->OnEvent(pFSM, EVENT_ENTRY, 0, 0);
		// ����ȱʡ��״̬
		m_pDefault->ActiveDefaultChild(pFSM);
	}
}

/*
 *  ˳�򼤻��ָ��״̬��Ŀ��״̬֮�������״̬,������Щ״̬����ڶ���
 */
void CState::Active(CHSM * pFSM, CState * pStop) {
	if (this != pStop && m_pParent) {
		// ���״̬
		m_pParent->Active(pFSM, pStop);
		//m_pParent->m_pActive = this;
	}
	pFSM->SetActiveState(this); //�Լ��ǵ�ǰ�״̬
	// �����Լ�����ڶ���
	if (m_pParent)
		m_pParent->m_pActive = this;
	OnEvent(pFSM, EVENT_ENTRY, 0, 0);
}

/*
 *  ˳��ֹͣ��Ҷ��״̬����ǰ״̬�����л״̬��������Щ״̬���˳�����
 */
void CState::Deactive(CHSM * pFSM) {
	if (m_pActive) {
		// ֹͣ���״̬
		m_pActive->Deactive(pFSM);
		//m_pActive = NULL;
	}
	pFSM->SetActiveState(m_pParent);
	if (m_pParent)
		m_pParent->m_pActive = NULL;
	// �����Լ����˳�����
	OnEvent(pFSM, EVENT_EXIT, 0, 0);
}

bool CState::IsActive() {
	if (!m_pParent)
		// ��״̬���ǻ��
		return true;
	else if (m_pParent->m_pActive == this)
		return true;
	else
		return false;
}

/*
 *  ��ȡĿǰ״̬����ָ��״̬ancestor����ĸ�״̬
 */
CState* CState::GetNearAncestor(CState* ancestor) {
	if (this == ancestor) {    //ָ��״̬����Ŀǰ״̬
		return this;
	}
	if (this->m_pParent == ancestor) {    //ָ��״̬��Ŀǰ״̬��ֱ�Ӹ�״̬
		return ancestor;
	}
	CState* tmp = this->m_pParent;
	while ((tmp->m_pParent) && (tmp->m_pParent != ancestor))
		tmp = tmp->m_pParent;
	return tmp;
}
