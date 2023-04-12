// WinSerialInterface.h: interface for the CWinSerialInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINSERIALINTERFACE_H__CBE30B84_D3D3_4A7C_A616_4E9AFAB46C4A__INCLUDED_)
#define AFX_WINSERIALINTERFACE_H__CBE30B84_D3D3_4A7C_A616_4E9AFAB46C4A__INCLUDED_
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

#include "SerialInterface.h"

class CLinuxSerialInterface : public CSerialInterface
{
    int m_nSerialFd;
    char m_nDeviceName[16];
    struct termios newtio;
public:
    CLinuxSerialInterface(CThread *pThreadObj,UINT portnr, UINT baud, char parity, UINT databits, UINT stopsbits);
    CLinuxSerialInterface(CThread *pThreadObj,char *devName, UINT baud, char parity, UINT databits, UINT stopsbits);
    virtual ~CLinuxSerialInterface();
    virtual int SetCmd(UINT cmd, UINT para);
private:
    int WaitOnline(int timeout);
    tcflag_t TransformIntBaudToTcFlag(UINT baud);
protected:
    virtual void OnlineMonitor();
public:
    virtual int Reset();
    virtual int SendData(char *pSendBuf,int sendDataLen,int timeout=TIME_WAIT_FOR_EVER);
    virtual int RecvData(char *pRecvBuf,int recvBufLen,int timeout=TIME_WAIT_FOR_EVER);
};

#endif // !defined(AFX_WINSERIALINTERFACE_H__CBE30B84_D3D3_4A7C_A616_4E9AFAB46C4A__INCLUDED_)
