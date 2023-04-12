/*
 * rand_num.c
 *
 *  Created on: 2021年9月15日
 *      Author: root
 */
#include "rand_num.h"

int Produce_RandNum()
{
		rand_num++;
		srand(rand_num);
		return rand();
}



