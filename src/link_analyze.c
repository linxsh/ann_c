#include "link_analyze.h"
#include "common_opt.h"

int link_create(unsigned int address)
{
	LINK_CMD *linkcmd = (LINK_CMD*)com_malloc(sizeof(LINK_CMD));

	linkcmd->prev_addr = 0;
	linkcmd->cur_addr  = address;
	linkcmd->public_cmd_addr  = address;
	linkcmd->private_cmd_addr = address+sizeof(PUBLIC_CMD);

	return (int)linkcmd;
}

void link_destory(int handle)
{
	LINK_CMD *linkcmd = (LINK_CMD*)handle;

	linkcmd->prev_addr = 0;
	linkcmd->cur_addr  = 0;
	linkcmd->public_cmd_addr  = 0;
	linkcmd->private_cmd_addr = 0;
	com_free((void*)linkcmd);

	return;
}

LINK_CMD_STATUS link_switch_next(int handle)
{
	unsigned int next_cmd_addr = 0;
	LINK_CMD   *linkcmd   = (LINK_CMD*)handle;
	PUBLIC_CMD *publiccmd = (PUBLIC_CMD*)linkcmd->public_cmd_addr;

	next_cmd_addr = publiccmd->next_cmd_addr;
	if (next_cmd_addr == 0)
		return CMD_NOT_EXIST_STATUS;
	else if (next_cmd_addr == linkcmd->cur_addr)
		return CMD_EMPTY_STATUS;

	linkcmd->prev_addr = linkcmd->cur_addr;
	linkcmd->cur_addr  = next_cmd_addr;
	linkcmd->public_cmd_addr  = next_cmd_addr;
	linkcmd->private_cmd_addr = next_cmd_addr+sizeof(PUBLIC_CMD);

	return CMD_EXIST_STATUS;
}

BOOL link_get_cmd_interrupt(int handle)
{
	LINK_CMD   *linkcmd   = (LINK_CMD*)handle;
	PUBLIC_CMD *publiccmd = (PUBLIC_CMD*)linkcmd->public_cmd_addr;

	return ((publiccmd->ctrl_word>>22)&0x1);
}

BOOL link_get_cmd_pro_end(int handle)
{
	LINK_CMD   *linkcmd   = (LINK_CMD*)handle;
	PUBLIC_CMD *publiccmd = (PUBLIC_CMD*)linkcmd->public_cmd_addr;

	return ((publiccmd->ctrl_word>>23)&0x1);
}

void link_set_cmd_pro_end(int handle)
{
	LINK_CMD   *linkcmd   = (LINK_CMD*)handle;
	PUBLIC_CMD *publiccmd = (PUBLIC_CMD*)linkcmd->public_cmd_addr;

	publiccmd->ctrl_word |= (0x1<<31);
	return;
}

LINK_CMD_TYPE link_get_cmd_type(int handle)
{
	LINK_CMD   *linkcmd   = (LINK_CMD*)handle;
	PUBLIC_CMD *publiccmd = (PUBLIC_CMD*)linkcmd->public_cmd_addr;
	unsigned char opt_cmd = 0;
	LINK_CMD_TYPE type = CMD_ERROR;

	opt_cmd = (unsigned char)(publiccmd->ctrl_word&0xff);
	switch (opt_cmd) {
	case 0x00:
		type = CMD_MULTI_ADD;
		break;
	case 0x01:
		type = CMD_FUNCTION;
		break;
	case 0x02:
		type = CMD_DOWNSAMPLE;
		break;
	case 0xff:
		type = CMD_OVER;
		break;
	default:
		type = CMD_ERROR;
		break;
	}

	return type;
}

BOOL link_get_multi_add_b_flag(int handle)
{
	LINK_CMD      *linkcmd    = (LINK_CMD*)handle;
	MULTI_ADD_CMD *privatecmd = (MULTI_ADD_CMD*)linkcmd->private_cmd_addr;

	return ((privatecmd->opt_ctrl_word>>4)&0x1);
}

MULTI_ADD_PROC_TYPE link_get_multi_add_proc_type(int handle)
{
	LINK_CMD      *linkcmd    = (LINK_CMD*)handle;
	MULTI_ADD_CMD *privatecmd = (MULTI_ADD_CMD*)linkcmd->private_cmd_addr;
	MULTI_ADD_PROC_TYPE proc_type = RESVERD_PROC;

	switch ((privatecmd->opt_ctrl_word)&0xf)
	{
	case 0x0:
		proc_type = FULL_JOIN_PROC;
		break;
	case 0x1:
		proc_type = ONE_CONVO_PROC;
		break;
	case 0x2:
		proc_type = TWO_CONVO_PROC;
		break;
	case 0x3:
		proc_type = DOT_PRODUCT_PROC;
		break;
	default:
		proc_type = RESVERD_PROC;
		break;
	}

	return proc_type;
}

BOOL link_get_multi_add_sign(int handle)
{
	LINK_CMD      *linkcmd    = (LINK_CMD*)handle;
	MULTI_ADD_CMD *privatecmd = (MULTI_ADD_CMD*)linkcmd->private_cmd_addr;

	return ((privatecmd->data_ctrl_word0>>2)&0x1);
}

BITS_TYPE link_get_multi_add_bits(int handle)
{
	LINK_CMD      *linkcmd    = (LINK_CMD*)handle;
	MULTI_ADD_CMD *privatecmd = (MULTI_ADD_CMD*)linkcmd->private_cmd_addr;
	BITS_TYPE bits = FLOAT_BITS;

	switch ((privatecmd->data_ctrl_word0)&0x3) {
	case 0x1:
		bits = U8_BITS;
		break;
	case 0x2:
		bits = U16_BITS;
		break;
	case 0x3:
		bits = FLOAT_BITS;
		break;
	default:
		bits = FLOAT_BITS;
		break;
	}

	return bits;
}

int link_get_multi_add_cell(int handle, CELLS *para, CELLS* indata, CELLS* prdata, CELLS *outdata)
{
	LINK_CMD      *linkcmd    = (LINK_CMD*)handle;
	MULTI_ADD_CMD *privatecmd = (MULTI_ADD_CMD*)linkcmd->private_cmd_addr;
	MULTI_ADD_PROC_TYPE proc_type = link_get_multi_add_proc_type(handle);

	if (proc_type == FULL_JOIN_PROC) {
		if (para) {
			para->width  = 64;
			para->height = 64;
			para->row    = (privatecmd->opt_ctrl_word>>24)&0xff;
			para->column = (privatecmd->opt_ctrl_word>>16)&0xff;
			para->data   = privatecmd->para_addr;
		}
		if (indata) {
			indata->width  = 1;
			indata->height = 64;
			indata->row    = (privatecmd->opt_ctrl_word>>16)&0xff;
			indata->column = 1;
			indata->data   = privatecmd->in_data_addr;
		}
		if (prdata) {
			prdata->width  = 1;
			prdata->height = 64;
			prdata->row    = (privatecmd->opt_ctrl_word>>24)&0xff;
			prdata->column = 1;
			prdata->data   = privatecmd->pre_data_addr;
		}
		if (outdata) {
			outdata->width  = 1;
			outdata->height = 64;
			outdata->row    = (privatecmd->opt_ctrl_word>>24)&0xff;
			outdata->column = 1;
			outdata->data   = privatecmd->out_data_addr;
		}
	}

	return 0;
}

BOOL link_get_function_limit(int handle)
{
	LINK_CMD     *linkcmd    = (LINK_CMD*)handle;
	FUNCTION_CMD *privatecmd = (FUNCTION_CMD*)linkcmd->private_cmd_addr;

	return ((privatecmd->opt_ctrl_word>>31)&0x1);
}

int link_get_function_cell(int handle, CELLS *para, CELLS* indata, CELLS *outdata)
{
	LINK_CMD     *linkcmd    = (LINK_CMD*)handle;
	FUNCTION_CMD *privatecmd = (FUNCTION_CMD*)linkcmd->private_cmd_addr;

	if (para) {
		para->width  = 1;
		para->height = 12;
		para->row    = 12;
		para->column = 1;
		para->data   = privatecmd->para_addr;
	}
	if (indata) {
		indata->width  = 1;
		indata->height = 64;
		indata->row    = (privatecmd->opt_ctrl_word>>16)&0xff;
		indata->column = 1;
		indata->data   = privatecmd->in_data_addr;
	}
	if (outdata) {
		outdata->width  = 1;
		outdata->height = 64;
		outdata->row    = (privatecmd->opt_ctrl_word>>16)&0xff;
		outdata->column = 1;
		outdata->data   = privatecmd->out_data_addr;
	}

	return 0;
}
