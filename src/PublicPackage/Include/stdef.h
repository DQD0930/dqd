#ifndef STDEF_H_
#define STDEF_H_
#define LINUX
#ifdef WIN32
#pragma warning( disable : 4200)
#endif

#include <string.h>                  //for memcpy, memset
#include <stdlib.h>                  //for abort

#ifdef LINUX
   #include <unistd.h>                  //for usleep
   #include <netinet/in.h>              //for ntohs, ntohl
   #define PACKED __attribute__((packed))
#endif

#ifdef WIN32
   #include <winsock2.h>
   #define PACKED
#endif

//powerpc series define big endian
#undef   BIT_ORDER_BIG_ENDIAN
//x86 seriers defines little endian
#define  BIT_ORDER_LITTLE_ENDIAN

typedef unsigned char  UC;
typedef unsigned int   UINT;
typedef unsigned short US;


const int TIME_WAIT_FOR_EVER = 0xFFFFFFFF;
const int TIME_NO_WAIT       = 0;


const int RETURN_TIMEOUT     = -2;
const int RETURN_FAILED      = -1;
const int RETURN_OK          = 0;

const UC  MAX_ALOHA_CHANNEL_NUM  = 16;

#ifdef LINUX
#include <unistd.h>
#define Sleep(x) sleep((x)/1000)
#endif

#endif
