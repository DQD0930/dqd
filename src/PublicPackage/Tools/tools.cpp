/*
*
*   Copyright (C) 2007-2008 HuaFang (fanghuaice@163.com)
*
*
*	This program is free software; you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation;
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdef.h"
#include "tools.h"

int my_ntohl(int val)
{
    char byte0 = val & 0x000000FF;
    char byte1 = (val & 0x0000FF00)>>8;
    char byte2 = (val & 0x00FF0000)>>16;
    char byte3 = (val & 0xFF000000)>>24;
    return ((byte0)<<24) | (byte1<<16) | (byte2<<8) | byte3;
}

short my_ntohs(short val)
{
    char byte0 = val & 0x00FF;
    char byte1 = (val & 0xFF00)>>8;
    return ((byte0)<<8) | (byte1);
}

UINT INT2BCD(UINT num)
{
    UINT value = 0;
    UINT mod = 100000000;
    num %= mod;
    for(int i=7;i>=0;i--)
    {
        mod /= 10;
        value |= (num / mod) << i*4 ;
        num %= mod;
    }
    return value;
}

UINT BCD2INT(UINT num)
{
    UINT value = 0;
    UINT mul = 1;

    for(UC i=0;i<8;i++)
    {
        value += (num & 0x0000000F)*mul;
        num >>= 4;
        mul *= 10;
    }
    return value;
}

//X8+X2+X+1
UC crc_table_8[256]=
{
    	0x00,0x07,0x0E,0x09,0x1C,0x1B,0x12,0x15,
		0x38,0x3F,0x36,0x31,0x24,0x23,0x2A,0x2D,
		0x70,0x77,0x7E,0x79,0x6C,0x6B,0x62,0x65,
		0x48,0x4F,0x46,0x41,0x54,0x53,0x5A,0x5D,
		0xE0,0xE7,0xEE,0xE9,0xFC,0xFB,0xF2,0xF5,
		0xD8,0xDF,0xD6,0xD1,0xC4,0xC3,0xCA,0xCD,
		0x90,0x97,0x9E,0x99,0x8C,0x8B,0x82,0x85,
		0xA8,0xAF,0xA6,0xA1,0xB4,0xB3,0xBA,0xBD,
		0xC7,0xC0,0xC9,0xCE,0xDB,0xDC,0xD5,0xD2,
		0xFF,0xF8,0xF1,0xF6,0xE3,0xE4,0xED,0xEA,
		0xB7,0xB0,0xB9,0xBE,0xAB,0xAC,0xA5,0xA2,
		0x8F,0x88,0x81,0x86,0x93,0x94,0x9D,0x9A,
		0x27,0x20,0x29,0x2E,0x3B,0x3C,0x35,0x32,
		0x1F,0x18,0x11,0x16,0x03,0x04,0x0D,0x0A,
		0x57,0x50,0x59,0x5E,0x4B,0x4C,0x45,0x42,
		0x6F,0x68,0x61,0x66,0x73,0x74,0x7D,0x7A,
		0x89,0x8E,0x87,0x80,0x95,0x92,0x9B,0x9C,
		0xB1,0xB6,0xBF,0xB8,0xAD,0xAA,0xA3,0xA4,
		0xF9,0xFE,0xF7,0xF0,0xE5,0xE2,0xEB,0xEC,
		0xC1,0xC6,0xCF,0xC8,0xDD,0xDA,0xD3,0xD4,
		0x69,0x6E,0x67,0x60,0x75,0x72,0x7B,0x7C,
		0x51,0x56,0x5F,0x58,0x4D,0x4A,0x43,0x44,
		0x19,0x1E,0x17,0x10,0x05,0x02,0x0B,0x0C,
		0x21,0x26,0x2F,0x28,0x3D,0x3A,0x33,0x34,
		0x4E,0x49,0x40,0x47,0x52,0x55,0x5C,0x5B,
		0x76,0x71,0x78,0x7F,0x6A,0x6D,0x64,0x63,
		0x3E,0x39,0x30,0x37,0x22,0x25,0x2C,0x2B,
		0x06,0x01,0x08,0x0F,0x1A,0x1D,0x14,0x13,
		0xAE,0xA9,0xA0,0xA7,0xB2,0xB5,0xBC,0xBB,
		0x96,0x91,0x98,0x9F,0x8A,0x8D,0x84,0x83,
		0xDE,0xD9,0xD0,0xD7,0xC2,0xC5,0xCC,0xCB,
		0xE6,0xE1,0xE8,0xEF,0xFA,0xFD,0xF4,0xF3
};

UC crc_cal_8(UC * ptr, UINT cnt)
{
    UC crc = 0;
    while (cnt--)
    {
        crc = crc_table_8[crc ^ *ptr++];
    }
    return crc;
}


//X16+X12+X5+1
US crc_table_ccitt_16[256]=
{
        0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,
		0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,0xE1CE,0xF1EF,
		0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,
		0x9339,0x8318,0xB37B,0xA35A,0xD3BD,0xC39C,0xF3FF,0xE3DE,
		0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,
		0xA56A,0xB54B,0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,
		0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
		0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,
		0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,0x2802,0x3823,
		0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,
		0x5AF5,0x4AD4,0x7AB7,0x6A96,0x1A71,0x0A50,0x3A33,0x2A12,
		0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,
		0x6CA6,0x7C87,0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,
		0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
		0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,
		0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,0x9F59,0x8F78,
		0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,
		0x1080,0x00A1,0x30C2,0x20E3,0x5004,0x4025,0x7046,0x6067,
		0x83B9,0x9398,0xA3FB,0xB3DA,0xC33D,0xD31C,0xE37F,0xF35E,
		0x02B1,0x1290,0x22F3,0x32D2,0x4235,0x5214,0x6277,0x7256,
		0xB5EA,0xA5CB,0x95A8,0x8589,0xF56E,0xE54F,0xD52C,0xC50D,
		0x34E2,0x24C3,0x14A0,0x0481,0x7466,0x6447,0x5424,0x4405,
		0xA7DB,0xB7FA,0x8799,0x97B8,0xE75F,0xF77E,0xC71D,0xD73C,
		0x26D3,0x36F2,0x0691,0x16B0,0x6657,0x7676,0x4615,0x5634,
		0xD94C,0xC96D,0xF90E,0xE92F,0x99C8,0x89E9,0xB98A,0xA9AB,
		0x5844,0x4865,0x7806,0x6827,0x18C0,0x08E1,0x3882,0x28A3,
		0xCB7D,0xDB5C,0xEB3F,0xFB1E,0x8BF9,0x9BD8,0xABBB,0xBB9A,
		0x4A75,0x5A54,0x6A37,0x7A16,0x0AF1,0x1AD0,0x2AB3,0x3A92,
		0xFD2E,0xED0F,0xDD6C,0xCD4D,0xBDAA,0xAD8B,0x9DE8,0x8DC9,
		0x7C26,0x6C07,0x5C64,0x4C45,0x3CA2,0x2C83,0x1CE0,0x0CC1,
		0xEF1F,0xFF3E,0xCF5D,0xDF7C,0xAF9B,0xBFBA,0x8FD9,0x9FF8,
		0x6E17,0x7E36,0x4E55,0x5E74,0x2E93,0x3EB2,0x0ED1,0x1EF0
};

US crc_cal_ccitt_16(UC * ptr, UINT cnt)
{
    US crc = 0;
    UC  da;
    while (cnt--)
    {
        da = crc >> 8;
        crc <<= 8;
        crc ^= crc_table_ccitt_16[da ^ *ptr++];
    }
    return crc;
}
