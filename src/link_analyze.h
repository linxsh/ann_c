#ifndef __LINK_ANALYZE_H__
#define __LINK_ANALYZE_H__

#include "common_ie.h"
#include "cell_unit.h"

/*********************************************
 * cmd : PUBLIC_CMD + any Opt CMD **********
 * *******************************************/

typedef struct {
	unsigned int prev_addr;
	unsigned int cur_addr;
	unsigned int public_cmd_addr;
	unsigned int private_cmd_addr;
} LINK_CMD;

typedef enum {
	CMD_EXIST_STATUS = 0,
	CMD_EMPTY_STATUS,
	CMD_NOT_EXIST_STATUS,
	CMD_ERROR_STATUS,
} LINK_CMD_STATUS;

typedef enum {
	CMD_MULTI_ADD = 0,
	CMD_FUNCTION,
	CMD_DOWNSAMPLE,
	CMD_OVER,
	CMD_ERROR,
} LINK_CMD_TYPE;

typedef struct {
	unsigned int ctrl_word;
	unsigned int next_cmd_addr;
} PUBLIC_CMD;

typedef struct {
	unsigned int opt_ctrl_word;
	unsigned int para_addr;
	unsigned int in_data_addr;
	unsigned int pre_data_addr;
	unsigned int out_data_addr;
	unsigned int data_ctrl_word0;
	unsigned int data_ctrl_word1;
	unsigned int data_ctrl_word2;
} MULTI_ADD_CMD;

typedef struct {
	unsigned int opt_ctrl_word;
	unsigned int para_addr;
	unsigned int in_data_addr;
	unsigned int out_data_addr;
} FUNCTION_CMD;

typedef struct {
	unsigned int opt_ctrl_word;
	unsigned int in_data_addr;
	unsigned int pre_data_addr;
	unsigned int out_data_addr;
	unsigned int data_ctrl_word0;
	unsigned int data_ctrl_word1;
} DOWNSAMPLE_CMD;

extern int link_create(unsigned int address);
extern void link_destory(int handle);
extern LINK_CMD_STATUS link_switch_next(int handle);
extern BOOL link_get_cmd_interrupt(int handle);
extern BOOL link_get_cmd_pro_end(int handle);
extern void link_set_cmd_pro_end(int handle);
extern LINK_CMD_TYPE link_get_cmd_type(int handle);

extern BOOL link_get_multi_add_sign(int handle);
extern BITS_TYPE link_get_multi_add_bits(int handle);
extern BOOL link_get_multi_add_b_flag(int handle);
extern MULTI_ADD_PROC_TYPE link_get_multi_add_proc_type(int handle);
extern int link_get_multi_add_cell(int handle, CELLS *para, CELLS* indata, CELLS* prdata, CELLS *outdata);

extern BOOL link_get_function_limit(int handle);
extern int link_get_function_cell(int handle, CELLS *para, CELLS* indata, CELLS *outdata);


extern int link_start(void);
extern void link_stop(void);

#endif
