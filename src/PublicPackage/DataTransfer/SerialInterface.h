// SerialInterface.h: interface for the CSerialInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALINTERFACE_H__F2CC0EE3_E4D9_4D9C_8BC9_C916F1DAD6F2__INCLUDED_)
#define AFX_SERIALINTERFACE_H__F2CC0EE3_E4D9_4D9C_8BC9_C916F1DAD6F2__INCLUDED_

#include "DataTransferInterface.h"

#define SET_CMD_SET_BAUDRATE   0

class CSerialInterface : public CDataTransferInterface
{

protected:
    int m_nPortNum;
    UINT m_nBaud;
    char m_nParity;
    UINT m_nDatabits;
    UINT m_nStopsbits;
    UC   m_nOnline;

public:
	CSerialInterface(CThread *pThread);
	virtual ~CSerialInterface();
};

#endif // !defined(AFX_SERIALINTERFACE_H__F2CC0EE3_E4D9_4D9C_8BC9_C916F1DAD6F2__INCLUDED_)
