// DataTransferInterface.h: interface for the CDataTransferInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATATRANSFERINTERFACE_H__3202DE13_B2B9_438A_BDF8_B2E3D102EAB1__INCLUDED_)
#define AFX_DATATRANSFERINTERFACE_H__3202DE13_B2B9_438A_BDF8_B2E3D102EAB1__INCLUDED_

#include <stdef.h>
#include <Thread.h>

class CThread;
class CDataTransferInterface
{
protected:
    CThread *m_pThread;
public:
	CDataTransferInterface(CThread *pThread);
	virtual ~CDataTransferInterface();
protected:
    virtual void OnlineMonitor();
    static void OnlineMonitorThread(void *);
public:
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER)=0;
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER)=0;
    virtual int Reset()=0;
    virtual void Run();
    //cmd Type, parameter , para len
	virtual int SetPara(char , char *, int ){return RETURN_OK;}
	//cmd Type, para
	virtual int SetCmd(UINT, UINT){return RETURN_OK;}
	//cmd Type, para, para len
	virtual int GetAddInfo(char , char *, int &) const{return RETURN_OK;}
};

#endif // !defined(AFX_DATATRANSFERINTERFACE_H__3202DE13_B2B9_438A_BDF8_B2E3D102EAB1__INCLUDED_)
