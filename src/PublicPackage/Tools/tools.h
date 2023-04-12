/*
*   AC�����еĹ��߰�
*
*   Copyright (C) 2007-2008 HuaFang (fanghuaice@163.com)
*
*
*	This program is free software; you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation;
*
*/

#ifndef TOOLS_H_
#define TOOLS_H_
#include "stdef.h"

#define CHAR2BCD(x)  ((char) ( ( ( (x) % 100 ) / 10 ) << 4 ) | ( ( (x) % 100) % 10 ) )

#define my_min(x,y) (x>y?y:x)
#define my_max(x,y) (x>y?x:y)

UC   crc_cal_8(UC * ptr, UINT cnt);
US   crc_cal_ccitt_16(UC * ptr, UINT cnt);
UINT BCD2INT(UINT bcd);
UINT INT2BCD(UINT num);

int my_ntohl(int val);
short my_ntohs(short val);

#endif

