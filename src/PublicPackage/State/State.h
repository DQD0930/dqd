#if !defined(AFX_STATE_H__14FA61D4_5DB9_4683_9895_336EC8BF24D2__INCLUDED_)
#define AFX_STATE_H__14FA61D4_5DB9_4683_9895_336EC8BF24D2__INCLUDED_

#ifdef WIN32
#pragma warning( disable : 4065)
#endif

#ifdef ON_EVENT
#undef ON_EVENT
#endif

#ifndef NULL
#define NULL    0
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#define STATE_CLASS_NAME(state_name)                                            	\
    CHSM_STATE_CLASS_##state_name

#ifdef HSM_ADD_FIRST_STATE_AS_DEFAULT
#define DEFINE_STATE_CLASS(state_name)                                          	\
    class STATE_CLASS_NAME(state_name) : public CState                          	\
    {                                                                           							\
    public:                                                                     	\
        STATE_CLASS_NAME(state_name)(CHSM * pFSM, const char * lpName,          	\
            const char * lpParent) : CState(pFSM, lpName, lpParent) {           	\
		if (m_pParent && ! m_pParent->GetDefaultChild())									\
			m_pParent->SetDefaultChild(this);}													\
        bool OnEvent(CHSM * pFSM, WORD wEvent, WORD wPAram, DWORD lParam);      	\
    };
#else
#define DEFINE_STATE_CLASS(state_name)                                          	\
    class STATE_CLASS_NAME(state_name) : public CState                          	\
    {                                                                           							\
    public:                                                                     	\
        STATE_CLASS_NAME(state_name)(CHSM * pFSM, const char * lpName,          	\
            const char * lpParent) : CState(pFSM, lpName, lpParent) {}          	\
        bool OnEvent(CHSM * pFSM, WORD wEvent, WORD wPAram, DWORD lParam);      	\
    };
#endif

#define INIT_ROOT_STATE(state_name){                                            	\
	CState* pState = new STATE_CLASS_NAME(state_name)(this,#state_name, NULL);  	\
	if(pState){																							\
    m_States.push_back(pState);								                    			\
	m_Root = pState;}}

#define INIT_STATE(parent_state, state_name){                                   	\
	CState* pState = new STATE_CLASS_NAME(state_name)(this,#state_name,				\
															#parent_state);							\
	if(pState){m_States.push_back(pState);}}

#define SET_DEFAULT_STATE(parent_state, state_name){                            \
    CState* pParent = GetState(#parent_state);							        \
	if(pParent){ CState* pState = GetState(#state_name);						\
	if(pState){ pParent->SetDefaultChild(pState);}}}

#define BEGIN_STATE_TRANSITION(state_name)                                      \
    bool STATE_CLASS_NAME(state_name)::OnEvent(CHSM * pFSM, WORD wEvent,        \
                                               WORD wParam, DWORD lParam)       \
    {                                                                           \
        CLASS_NAME * pClass = dynamic_cast<CLASS_NAME *>(pFSM);					\
		switch (wEvent)															\
		{
#define ON_ENTRY(action_name)                                                   \
        case EVENT_ENTRY:			                                            		\
            pClass->action_name(wParam, lParam);											\
			return true;

#define ON_EXIT(action_name)                                                    \
        case EVENT_EXIT:		                                                \
            pClass->action_name(wParam, lParam);								\
			return true;

#define ON_EVENT_TRANSITION(event, guard_name, action_name, target_state)       \
        case event:																\
            if (pClass->guard_name(wParam, lParam))                             \
            {                                                                   \
                pClass->action_name(wParam, lParam);		                    \
                pClass->TransitTo(#target_state);                               \
            }			                                                        \
			return true;

#define ON_EVENT_INTERNAL(event, guard_name, action_name)                       \
        case event:			                                                    \
            if (pClass->guard_name(wParam, lParam))                             \
                pClass->action_name(wParam, lParam);							\
			return true;

#define END_STATE_TRANSITION                                                    \
		default:																\
			return false;                                                       \
		}																		\
    }

class CHSM;

class CState {
protected:
	// ������뿪�������¼�ID
	enum {
		EVENT_ENTRY = 0xfffe, EVENT_EXIT
	} ENUM_EVENT_PRESERVE;

public:
	CState(CHSM * pFSM, const char * pName, const char * pParent);
	virtual ~CState() {
	}

	CState * GetParent() const {
		return m_pParent;
	}
	void SetDefaultChild(CState* pChild) {
		m_pDefault = pChild;
	}
	CState * GetDefaultChild(void) {
		return m_pDefault;
	}
	bool SendEvent(CHSM * pFSM, WORD wEvent, WORD wParam, DWORD lParam);
	virtual bool OnEvent(CHSM * pFSM, WORD wEvent, WORD wPAram,
			DWORD lParam) = 0;

	void ActiveDefaultChild(CHSM * pFSM);
	void Active(CHSM * pFSM, CState * pStop);
	void Deactive(CHSM * pFSM);

	CState * GetActiveLeaf() {
		return m_pActive;
	}
	bool IsActive();
	const char * GetName() const {
		return m_pName;
	}
	CState * GetNearAncestor(CState* ancestor);

protected:
	CState * m_pParent;          // ��״̬
	CState * m_pDefault;         // ȱʡ��״̬
	CState * m_pActive;          // ��ǰ�Ļ��״̬
	const char * m_pName;           // ״̬������
};

#endif // !defined(AFX_STATE_H__14FA61D4_5DB9_4683_9895_336EC8BF24D2__INCLUDED_)
