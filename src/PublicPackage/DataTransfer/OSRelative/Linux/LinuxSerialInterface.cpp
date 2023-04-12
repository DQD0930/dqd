// WinSerialInterface.cpp: implementation of the CWinSerialInterface class.
//
//////////////////////////////////////////////////////////////////////
//#include "SerialInterface.h"
#include "LinuxSerialInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinuxSerialInterface::CLinuxSerialInterface(CThread *pThreadObj, UINT portnr,
		UINT baud, char parity, UINT databits, UINT stopsbits) :
		CSerialInterface(pThreadObj) {
	m_nSerialFd = -1;
	m_nPortNum = portnr - 1; //com1->ttyS0
	m_nBaud = baud;
	m_nParity = parity;
	m_nDatabits = databits;
	m_nStopsbits = stopsbits;
	memset(m_nDeviceName, 0, sizeof(m_nDeviceName));
}

CLinuxSerialInterface::CLinuxSerialInterface(CThread *pThreadObj, char *devName,
		UINT baud, char parity, UINT databits, UINT stopsbits) :
		CSerialInterface(pThreadObj) {
	m_nPortNum = -1;
	m_nSerialFd = -1;
	m_nBaud = baud;
	strcpy(m_nDeviceName, devName);
	m_nParity = parity;
	m_nDatabits = databits;
	m_nStopsbits = stopsbits;
}

CLinuxSerialInterface::~CLinuxSerialInterface() {
	if (m_nSerialFd > 0) {
		close(m_nSerialFd);
	}
}

/**************************************************************************
 ԭ  ��: int Reset()
 ��  ��: �Խӿڸ�λ
 ��  ��: ��
 ����ֵ: ��
 ��  ��: ��  ��
 ��  ��: 2007.10.24 ����
 ***************************************************************************/
int CLinuxSerialInterface::Reset() {
	m_nOnline = 0;
	if (m_nSerialFd > 0) {
		close(m_nSerialFd);
	}
	if (m_nPortNum >= 0)
		sprintf(m_nDeviceName, "/dev/ttyS%d", m_nPortNum);

	m_nSerialFd = open(m_nDeviceName, O_RDWR | O_NOCTTY);

	if (m_nSerialFd <= 0) {
		printf("ERROR:Can't open serial port at %s!\n", m_nDeviceName);
		return -1;
	}
	printf(
			"open %s success, baud is %d, Databits is %d, parity=%c, stopbits=%d!\n",
			m_nDeviceName, m_nBaud, m_nDatabits, m_nParity, m_nStopsbits);
	bzero(&newtio, sizeof(struct termios));

	tcflag_t baudFlag;
	baudFlag = TransformIntBaudToTcFlag(m_nBaud);

	UINT cs = CS8;
	switch (m_nDatabits) {
	case 5:
		cs = CS5;
		break;
	case 6:
		cs = CS6;
		break;
	case 7:
		cs = CS7;
		break;
	case 8:
		cs = CS8;
		break;
	default:
		printf("Invalid number of data bits! set to CS8!\n");
		break;
	}

	newtio.c_cflag = CLOCAL | CREAD | baudFlag | cs;
	if (2 == m_nStopsbits)
		newtio.c_cflag = CLOCAL | CREAD | baudFlag | cs | CSTOPB;
	switch (m_nParity) {
	case 'n':
	case 'N':
		newtio.c_iflag = 0;
		break;
	case 'o':
	case 'O':
		newtio.c_cflag = newtio.c_cflag | PARENB | PARODD;
		break;
	case 'e':
	case 'E':
		newtio.c_cflag = newtio.c_cflag | PARENB;
		break;
	}

	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 1;
	tcflush(m_nSerialFd, TCIOFLUSH);
	tcsetattr(m_nSerialFd, TCSANOW, &newtio);

	m_nOnline = 1;
	return RETURN_OK;
}

tcflag_t CLinuxSerialInterface::TransformIntBaudToTcFlag(UINT baud) {
	tcflag_t baudFlag;
	switch (baud) {
	case 50:
		baudFlag = B50;
		break;
	case 75:
		baudFlag = B75;
		break;
	case 150:
		baudFlag = B150;
		break;
	case 300:
		baudFlag = B300;
		break;
	case 600:
		baudFlag = B600;
		break;
	case 1200:
		baudFlag = B1200;
		break;
	case 1800:
		baudFlag = B1800;
		break;
	case 2400:
		baudFlag = B2400;
		break;
	case 4800:
		baudFlag = B4800;
		break;
	case 9600:
		baudFlag = B9600;
		break;
	case 19200:
		baudFlag = B19200;
		break;
	case 38400:
		baudFlag = B38400;
		break;
	case 57600:
		baudFlag = B57600;
		break;
	case 115200:
		baudFlag = B115200;
		break;
	case 230400:
		baudFlag = B230400;
		break;
	default:
		baudFlag = B9600;
		break;
	}
	return baudFlag;
}

int CLinuxSerialInterface::SetCmd(UINT cmd, UINT para) {
	switch (cmd) {
	case SET_CMD_SET_BAUDRATE:
		if (m_nSerialFd < 0)
			return RETURN_FAILED;
		m_nBaud = para;
		return Reset();
	default:
		break;
	}
	return RETURN_OK;
}

int CLinuxSerialInterface::WaitOnline(int timeout) {
	int passtime = 0;
	if (timeout == TIME_WAIT_FOR_EVER) {
		while (1) {
			if (m_nOnline) {
				return RETURN_OK;
			} else {
				sleep(1);
			}
		}
	} else {
		while (passtime < timeout) {
			if (m_nOnline) {
				return RETURN_OK;
			} else {
				sleep(1);
			}
			passtime += 1000;
		}
	}
	return RETURN_TIMEOUT;
}

/**************************************************************************
 ԭ  ��: int SendData(char *pSendBuf,int sendDataLen)
 ��  ��: ��������
 ��  ��: pSendBuf ����������ָ��
 sendDataLen ���������ݳ���
 ����ֵ: RETURN_OK ���ͳɹ�
 RETURN_FAILED ����ʧ��
 ��  ��: ��  ��
 ��  ��: 2007.10.24 ����
 ***************************************************************************/
int CLinuxSerialInterface::SendData(char *pSendBuf, int sendDataLen,
		int timeout) {
	int allsendlen = 0;
	int thissendlen;

	//printf("CLinuxSerialInterface SendData: len=%d \n",sendDataLen);

	if (RETURN_TIMEOUT == WaitOnline(timeout)) {
		return RETURN_TIMEOUT;
	}

	if (m_nOnline) {
		while (allsendlen < sendDataLen) {
			//printf("be4 write to serial port! \n");
			thissendlen = write(m_nSerialFd, pSendBuf + allsendlen,
					sendDataLen - allsendlen);
			//printf("write to serial port ret = %d! \n",thissendlen);
			if (thissendlen < 0) {
				m_nOnline = 0;
				return RETURN_FAILED;
			}
			allsendlen += thissendlen;
		}
		return RETURN_OK;
	} else {
		return RETURN_FAILED;
	}

}

/**************************************************************************
 ԭ  ��: int RecvData(char *pRecvBuf,int recvBufLen)
 ��  ��: ��������
 ��  ��: pSendBuf ����������ָ��
 sendDataLen ���������ݳ���
 ����ֵ: >0 ���յ����ݳ���
 RETURN_FAILED ����ʧ��
 ��  ��: ��  ��
 ��  ��: 2007.10.24 ����
 ***************************************************************************/
int CLinuxSerialInterface::RecvData(char *pRecvBuf, int recvBufLen,
		int timeout) {
	int ret = RETURN_FAILED;

	if (RETURN_TIMEOUT == WaitOnline(timeout)) {
		return RETURN_TIMEOUT;
	}
	//printf("CLinuxSerialInterface::Begin Read m_nSerialFd=%d! \n",m_nSerialFd);
	if (m_nOnline) {
		if (TIME_WAIT_FOR_EVER == timeout)
			return read(m_nSerialFd, pRecvBuf, recvBufLen);
#if 1
		fd_set fdR;
		struct timeval rtimeout;
		rtimeout.tv_sec = timeout / 1000;
		rtimeout.tv_usec = 0;
		FD_ZERO(&fdR);
		FD_SET(m_nSerialFd, &fdR);
		switch (select(m_nSerialFd + 1, &fdR, NULL, NULL, &rtimeout)) {
		case -1:
			return RETURN_FAILED;
		case 0:
			return RETURN_TIMEOUT;
		default:
			ret = read(m_nSerialFd, pRecvBuf, recvBufLen);
			break;
		}
#endif

		//ret = read(m_nSerialFd,pRecvBuf , recvBufLen);  //just for test
		if (ret == RETURN_FAILED) {
			m_nOnline = 0;
		}
	}
	return ret;
}

/**************************************************************************
 ԭ  ��: void OnlineMonitor()
 ��  ��: ����TCP����Ƿ�����
 ��  ��: ��
 ����ֵ: ��
 ��  ��: ��  ��
 ��  ��: 2007.10.24 ����
 ***************************************************************************/
void CLinuxSerialInterface::OnlineMonitor() {
	while (1) {
		sleep(1);
		if (m_nOnline) {
			continue;
		}
		Reset();
	}
}
