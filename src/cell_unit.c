#include "cell_unit.h"
#include "common_opt.h"

static inline char bits8_add(BOOL sign, char x, char y)
{
	return com_8_add(sign, x, y);
}

static inline short bits16_add(BOOL sign, short x, short y)
{
	return com_16_add(sign, x, y);
}

static inline float float_add(float x, float y)
{
	return com_float_add(x, y);
}

static inline char bits8_sub(BOOL sign, char x, char y)
{
	return com_8_sub(sign, x, y);
}

static inline short bits16_sub(BOOL sign, short x, short y)
{
	return com_16_sub(sign, x, y);
}

static inline float float_sub(float x, float y)
{
	return com_float_sub(x, y);
}

static inline char bits8_mul(BOOL sign, char x, char y)
{
	return com_8_mul(sign, x, y);
}

static inline short bits16_mul(BOOL sign, short x, short y)
{
	return com_16_mul(sign, x, y);
}

static inline float float_mul(float x, float y)
{
	return com_float_mul(x, y);
}

#define ADD_CALC(bits, sign, back, x, y, z, i, j, k) do {        \
	if (bits == U8_BITS) {                                       \
		char* tmp1 = (char*)x;                                   \
		char* tmp2 = (char*)y;                                   \
		char* tmp3 = (char*)z;                                   \
		if (back == TRUE) {                                      \
			char tmp;                                            \
			tmp = bits8_add(sign, tmp1[i], tmp2[j]);             \
			tmp3[k] = bits8_add(sign, tmp3[i], tmp);             \
		} else {                                                 \
			tmp3[k] = bits8_add(sign, tmp1[i], tmp2[j]);         \
		}                                                        \
	} else if (bits == U16_BITS) {                               \
		short* tmp1 = (short*)x;                                 \
		short* tmp2 = (short*)y;                                 \
		short* tmp3 = (short*)z;                                 \
		if (back == TRUE) {                                      \
			short tmp;                                           \
			tmp = bits16_add(sign, tmp1[i], tmp2[j]);            \
			tmp3[k] = bits16_add(sign, tmp3[k], tmp);            \
		} else {                                                 \
			tmp3[k] = bits16_add(sign, tmp1[i], tmp2[j]);        \
		}                                                        \
	} else if (bits == FLOAT_BITS) {                             \
		float* tmp1 = (float*)x;                                 \
		float* tmp2 = (float*)y;                                 \
		float* tmp3 = (float*)z;                                 \
		if (back == TRUE) {                                      \
			float tmp;                                           \
			tmp = float_add(tmp1[i], tmp2[j]);                   \
			tmp3[k] = float_add(tmp3[k], tmp);                   \
		} else {                                                 \
			tmp3[k] = float_add(tmp1[i], tmp2[j]);               \
		}                                                        \
	}                                                            \
} while(0)

#define SUB_CALC(bits, sign, back, x, y, z, i, j, k) do {        \
	if (bits == U8_BITS) {                                       \
		char* tmp1 = (char*)x;                                   \
		char* tmp2 = (char*)y;                                   \
		char* tmp3 = (char*)z;                                   \
		if (back == TRUE) {                                      \
			char tmp;                                            \
			tmp = bits8_sub(sign, tmp1[i], tmp2[j]);             \
			tmp3[k] = bits8_add(sign, tmp3[k], tmp);             \
		} else {                                                 \
			tmp3[k] = bits8_sub(sign, tmp1[i], tmp2[j]);         \
		}                                                        \
	} else if (bits == U16_BITS) {                               \
		short* tmp1 = (short*)x;                                 \
		short* tmp2 = (short*)y;                                 \
		short* tmp3 = (short*)z;                                 \
		if (back == TRUE) {                                      \
			short tmp;                                           \
			tmp = bits16_sub(sign, tmp1[i], tmp2[j]);            \
			tmp3[k] = bits16_add(sign, tmp3[k], tmp);            \
		} else {                                                 \
			tmp3[k] = bits16_sub(sign, tmp1[i], tmp2[j]);        \
		}                                                        \
	} else if (bits == FLOAT_BITS) {                             \
		float* tmp1 = (float*)x;                                 \
		float* tmp2 = (float*)y;                                 \
		float* tmp3 = (float*)z;                                 \
		if (back == TRUE) {                                      \
			float tmp;                                           \
			tmp = float_sub(tmp1[i], tmp2[j]);                   \
			tmp3[k] = float_add(tmp3[k], tmp);                   \
		} else {                                                 \
			tmp3[k] = float_sub(tmp1[i], tmp2[j]);               \
		}                                                        \
	}                                                            \
} while(0)

#define MUL_CALC(bits, sign, back, w1, w2, w3, c, i, j, x, y, z) do {     \
	int k = 0;                                                      \
	if (bits == U8_BITS) {                                          \
		char* tmp1 = (char*)x;                                      \
		char* tmp2 = (char*)y;                                      \
		char* tmp3 = (char*)z;                                      \
		char sub_tmp = 0;                                           \
		for (k = 0; k < c; k++) {                                   \
			char tmp;                                               \
			tmp     = bits8_mul(sign, tmp1[i*w1+k], tmp2[k*w2+j]);  \
			sub_tmp = bits8_add(sign, sub_tmp, tmp);                \
		}                                                           \
		if (back == TRUE) {                                         \
			tmp3[i*w3+j] = bits8_add(sign, tmp3[i*w3+j], sub_tmp);  \
		} else {                                                    \
			tmp3[i*w3+j] = sub_tmp;                                 \
		}                                                           \
	} else if (bits == U16_BITS) {                                  \
		short* tmp1 = (short*)x;                                    \
		short* tmp2 = (short*)y;                                    \
		short* tmp3 = (short*)z;                                    \
		short  sub_tmp = 0;                                         \
		for (k = 0; k < c; k++) {                                   \
			short tmp;                                              \
			tmp     = bits16_mul(sign, tmp1[i*w1+k], tmp2[k*w2+j]); \
			sub_tmp = bits16_add(sign, sub_tmp, tmp);               \
		}                                                           \
		if (back == TRUE) {                                         \
			tmp3[i*w3+j] = bits16_add(sign, tmp3[i*w3+j], sub_tmp); \
		} else {                                                    \
			tmp3[i*w3+j] = sub_tmp;                                 \
		}                                                           \
	} else if (bits == FLOAT_BITS) {                                \
		float* tmp1 = (float*)x;                                    \
		float* tmp2 = (float*)y;                                    \
		float* tmp3 = (float*)z;                                    \
		float  sub_tmp = 0;                                         \
		for (k = 0; k < c; k++) {                                   \
			float tmp;                                              \
			tmp     = float_mul(tmp1[i*w1+k], tmp2[k*w2+j]);        \
			sub_tmp = float_add(sub_tmp, tmp);                      \
		}                                                           \
		if (back == TRUE) {                                         \
			tmp3[i*w3+j] = float_add(tmp3[i*w3+j], sub_tmp);        \
		} else {                                                    \
			tmp3[i*w3+j] = sub_tmp;                                 \
		}                                                           \
	}                                                               \
} while(0)

#define FUNCTION_CALC(limit, bits, sign, w1, w2, w3, c, i, j, x, y, z)  do {     \
	int k = 0;                                                      \
	if (bits == U8_BITS) {                                          \
		char* tmp1 = (char*)x;                                      \
		char* tmp2 = (char*)y;                                      \
		char* tmp3 = (char*)z;                                      \
		char tmp = 0;                                               \
		char sub_tmp = 0;                                           \
		char mul_tmp = 1;                                           \
		for (k = 0; k < c; k++) {                                   \
			tmp = bits8_mul(sign, tmp1[i*w1+j], mul_tmp);           \
			sub_tmp = bits8_add(sign, sub_tmp, tmp);                \
			mul_tmp = bits8_mul(sign, tmp2[i*w2+j], mul_tmp);       \
		}                                                           \
		if ((limit == TRUE) && (sign == TRUE)) {                    \
			if (sub_tmp < 0)                                        \
				sub_tmp = 0;                                        \
		}                                                           \
		tmp3[i*w3+j] = sub_tmp;                                     \
	} else if (bits == U16_BITS) {                                  \
		short* tmp1 = (short*)x;                                    \
		short* tmp2 = (short*)y;                                    \
		short* tmp3 = (short*)z;                                    \
		short tmp = 0;                                              \
		short sub_tmp = 0;                                          \
		short mul_tmp = 1;                                          \
		for (k = 0; k < c; k++) {                                   \
			tmp = bits8_mul(sign, tmp1[i*w1+j], mul_tmp);           \
			sub_tmp = bits8_add(sign, sub_tmp, tmp);                \
			mul_tmp = bits8_mul(sign, tmp2[i*w2+j], mul_tmp);       \
		}                                                           \
		if ((limit == TRUE) && (sign == TRUE)) {                    \
			if (sub_tmp < 0)                                        \
				sub_tmp = 0;                                        \
		}                                                           \
		tmp3[i*w3+j] = sub_tmp;                                     \
	} else if (bits == FLOAT_BITS) {                                \
		float* tmp1 = (float*)x;                                    \
		float* tmp2 = (float*)y;                                    \
		float* tmp3 = (float*)z;                                    \
		float tmp = 0;                                              \
		float sub_tmp = 0;                                          \
		float mul_tmp = 1;                                          \
		for (k = 0; k < c; k++) {                                   \
			tmp = bits8_mul(sign, tmp1[i*w1+j], mul_tmp);           \
			sub_tmp = bits8_add(sign, sub_tmp, tmp);                \
			mul_tmp = bits8_mul(sign, tmp2[i*w2+j], mul_tmp);       \
		}                                                           \
		if (limit == TRUE) {                                        \
			if (sub_tmp < 0)                                        \
				sub_tmp = 0;                                        \
		}                                                           \
		tmp3[i*w3+j] = sub_tmp;                                     \
	}                                                               \
} while(0)

#define CHECK_CELLS(x)  if ((x->height < x->row) || (x->width < x->column)) return -1;

/********************************************************************
// bits: bits of data
// sign: data sign or not sign, FLOAT_BITS is sign data
// back: data add out data or not
// process: data add, sub or mul
**********************************************************************/
int kernel_calc_unit(BITS_TYPE bits, BOOL sign, BOOL back, PROCESS_TYPE process,
		CELLS *in0, CELLS *in1, CELLS *out)
{
	int i = 0, j = 0;

	if ((process == ADD_PROCESS) || (process == SUB_PROCESS)) {
		int row = 0, column = 0;

		if ((in0->row != in1->row) || (in0->column != in1->column))
			return -1;

		row    = in0->row;
		column = in0->column;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				if (process == ADD_PROCESS) {
					ADD_CALC(bits, sign, back,
							in0->data, in1->data, out->data,
							(i*in0->width+j), (i*in1->width+j), (i*out->width+j));
				} else if (process == SUB_PROCESS){
					SUB_CALC(bits, sign, back,
							in0->data, in1->data, out->data,
							(i*in0->width+j), (i*in1->width+j), (i*out->width+j));
				}
			}
		}
		out->row = row;
		out->column = column;
	} else if (process == MUL_PROCESS) {
		int row = in0->row, column = in1->column;
		int column0 = in0->column, row1 = in1->row;

		if (column0 != row1)
			return -1;

		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				MUL_CALC(bits, sign, back,
						in0->width, in1->width, out->width,
						column0, i, j, in0->data, in1->data, out->data);
			}
		}
		out->row = row;
		out->column = column;
	}

	return 0;
}

int multi_add_calc(MULTI_ADD_PROC_TYPE type, BOOL b_flag,
		BITS_TYPE bits, BOOL sign, CELLS *para, CELLS *indata, CELLS *prdata, CELLS *outdata)
{
	int ret = -1;

	CHECK_CELLS(para);
	CHECK_CELLS(indata);
	CHECK_CELLS(prdata);
	CHECK_CELLS(outdata);

	if (type == FULL_JOIN_PROC) {
		if (prdata->data == outdata->data) {
			kernel_calc_unit(bits, sign, 1, MUL_PROCESS, para, indata, outdata);
		} else{
			kernel_calc_unit(bits, sign, 0, MUL_PROCESS, para, indata, outdata);
			if (prdata->data != 0xffffffff)
				kernel_calc_unit(bits, sign, 0, ADD_PROCESS, outdata, prdata, outdata);
		}

		if (b_flag == TRUE) {
			CELLS b_data;

			b_data.width  = 1;
			b_data.height = para->height;
			b_data.row    = outdata->row;
			b_data.column = 1;
			if (bits == U8_BITS) {
				unsigned char* pdata = (unsigned char*)para->data;
				b_data.data = (unsigned int)&pdata[64*64];
			} else if (bits == U16_BITS) {
				unsigned short* pdata = (unsigned short*)para->data;
				b_data.data = (unsigned int)&pdata[64*64];
			} else if (bits == FLOAT_BITS) {
				float* pdata = (float*)para->data;
				b_data.data = (unsigned int)&pdata[64*64];
			}
			kernel_calc_unit(bits, sign, 0, ADD_PROCESS, outdata, &b_data, outdata);
		}
		ret = 0;
	} else if (type == ONE_CONVO_PROC) {
	} else if (type == TWO_CONVO_PROC) {
	} else if (type == DOT_PRODUCT_PROC) {
	}

	return ret;
}

int function_calc(BOOL limit,
		BITS_TYPE bits, BOOL sign, CELLS *para, CELLS *in, CELLS *out)
{
	int i = 0, j = 0;
	CHECK_CELLS(para);
	CHECK_CELLS(in);
	CHECK_CELLS(out);

	for (i = 0; i < in->row; i++) {
		for (j = 0; j < in->column; j++) {
			FUNCTION_CALC(limit, bits, sign,
					para->width, in->width, out->width,
					para->row, i, j, para->data, in->data, out->data);
		}
	}

	out->row    = in->row;
	out->column = in->column;
	return 0;
}
