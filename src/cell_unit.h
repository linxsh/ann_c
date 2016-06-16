#ifndef __CELL_UNIT_H__
#define __CELL_UNIT_H__

#include "common_ie.h"
#include "common_opt.h"

typedef enum {
	ADD_PROCESS,
	SUB_PROCESS,
	MUL_PROCESS,
	DIV_PROCESS,
	RESVERD,
} PROCESS_TYPE;

typedef enum {
	U8_BITS,
	U16_BITS,
	FLOAT_BITS
} BITS_TYPE;

typedef enum {
	FULL_JOIN_PROC = 0,
	ONE_CONVO_PROC,
	TWO_CONVO_PROC,
	DOT_PRODUCT_PROC,
	RESVERD_PROC,
} MULTI_ADD_PROC_TYPE;

typedef struct {
	unsigned char width;
	unsigned char height;
	unsigned char row;
	unsigned char column;
	unsigned int  data;
} CELLS;

extern int kernel_calc_unit(BITS_TYPE bits, BOOL sign, BOOL back,
		PROCESS_TYPE process, CELLS *in0, CELLS *in1, CELLS *out);

extern int multi_add_calc(MULTI_ADD_PROC_TYPE type, BOOL b_flag,
		BITS_TYPE bits, BOOL sign, CELLS *para, CELLS *indata, CELLS *prdata, CELLS *outdata);

extern int function_calc(BOOL limit,
		BITS_TYPE bits, BOOL sign, CELLS *para, CELLS *in, CELLS *out);

#endif
