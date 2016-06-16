#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include "iecmodel/common_ie.h"

static float multi_para_arry[4160];
static float multi_indata_arry[64];
static float multi_outdata_arry[64];
static float func_para_arry[12] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2};
static int complete = 0;

static void reg_interrupt(void)
{
	int i = 0;
	unsigned int value = 0;

	value = COM_Reg_Read(0xC);
	if (value & (0x1)) {
		for (i = 1; i <= 64; i++) {
			printf("%0.2f ", multi_outdata_arry[i-1]);
			if (i%16 == 0)
				printf("\n");
		}
		complete = 1;
	}
	return;
}

int main(void)
{
	int i = 0, j = 0;
	unsigned int value = 0;
	unsigned int *ptr0 = NULL, *ptr1 = NULL;

	complete = 0;
	COM_Register_Int_Func(reg_interrupt);
	COM_Reg_Init(0x0);
	value = ((0x1<<12)|(0x1<<8)|(0x1<<4)|(0x1));
	COM_Reg_Write(0x4, value);
	COM_Reg_Write(0x8, value);

	ptr0 = (unsigned int *)malloc(10*sizeof(unsigned int));
	ptr1 = (unsigned int *)malloc(6*sizeof(unsigned int));

	for (i = 0; i < 65; i++) {
		for (j = 0; j < 64; j++) {
				multi_para_arry[i*64+j] = (float)(i+j)/(10000);
		}
	}
//	for (i = 0; i < 4160; i++)
//		multi_para_arry[i] = (float)(((float)rand())/(RAND_MAX));

	for (i = 0; i < 64; i++)
		multi_indata_arry[i] = (float)(64-i)/64;

	value = (unsigned int)ptr0;
	ptr0[0] = (unsigned int)((0x1<<23)|(0x1<<22)|0x0);
	ptr0[1] = (unsigned int)ptr0;
	ptr0[2] = (unsigned int)((0x40<<24)|(0x40<<16)|(0x1<<4)|0x0);
	ptr0[3] = (unsigned int)multi_para_arry;
	ptr0[4] = (unsigned int)multi_indata_arry;
	ptr0[5] = (unsigned int)0xffffffff;
	ptr0[6] = (unsigned int)multi_outdata_arry;
	ptr0[7] = (unsigned int)((0x1<<2)|0x3);
	ptr0[8] = (unsigned int)(0x0);
	ptr0[9] = (unsigned int)(0x0);
	ptr1[0] = (unsigned int)((0x1<<23)|(0x1<<22)|0x1);
	ptr1[1] = (unsigned int)ptr1;
	ptr1[2] = (unsigned int)((0x0<<31)|(0x40<<16));
	ptr1[3] = (unsigned int)func_para_arry;
	ptr1[4] = (unsigned int)multi_outdata_arry;
	ptr1[5] = (unsigned int)multi_outdata_arry;
	COM_Reg_Write(0x10, value);

	value = (unsigned int)((0x64<<16)|(0x1<<4)|0x0);
	COM_Reg_Write(0x0, value);
	value = (unsigned int)((0x64<<16)|(0x1<<4)|0x1);
	COM_Reg_Write(0x0, value);

	while (!complete) sleep(1);

	value = 0x0;
	COM_Reg_Write(0x4, value);
	value = (unsigned int)((0x64<<16)|(0x1<<4)|0x0);
	COM_Reg_Write(0x0, value);

	return 0;
}
