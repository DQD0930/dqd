#ifndef DATA_TRANSFER_INCLUDE_FILES_H
#define DATA_TRANSFER_INCLUDE_FILES_H

#include "stdef.h"

#include "ThreadIncludes.h"

#include "DataTransferInterface.h"
#include "DataTransferInterfaceFactory.h"
#include "NetDataTransferInterfaceFactory.h"
#include "SerialDataTransferInterfaceFactory.h"
#include "SerialInterface.h"
#include "TcpClientInterface.h"
#include "TcpServerInterface.h"
#include "UdpClientInterface.h"
#include "UdpServerInterface.h"

#ifdef LINUX
#include <arpa/inet.h>
#include <termios.h>
#include "OSRelative/Linux/LinuxNetDataTransferInterfaceFactory.h"
#include "OSRelative/Linux/LinuxSerialDataTransferInterfaceFactory.h"
#include "OSRelative/Linux/LinuxSerialInterface.h"
#include "OSRelative/Linux/LinuxTcpClientInterface.h"
#include "OSRelative/Linux/LinuxTcpServerInterface.h"
#include "OSRelative/Linux/LinuxUdpClientInterface.h"
#include "OSRelative/Linux/LinuxUdpServerInterface.h"
#endif

#ifdef WIN32
#include "winsock2.h"
#include "OSRelative\Windows\SerialPort.h"
#include "OSRelative\Windows\WinSerialInterface.h"
#include "OSRelative\windows\WinUdpClientInterface.h"
#include "OSRelative\windows\WinTcpClientInterface.h"
#include "OSRelative\windows\WinUdpServerInterface.h"
#include "OSRelative\windows\WinTcpServerInterface.h"
#include "OSRelative\windows\WinTcpCopyInterface.h"
#include "OSRelative\windows\WinTcpListenInterface.h"
#include "OSRelative\windows\WinDataTransferInterfaceFactory.h"
#endif

#endif
