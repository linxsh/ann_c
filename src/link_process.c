#include "link_analyze.h"
#include "reg_opt.h"
#include "common_opt.h"
#include "interrupt_opt.h"

static unsigned int link_pthread = 0;
static IE_REG_OPT* opt_reg = NULL;
static char link_thread_running = 0;

static void link_process(void* data)
{
	int link_handle = -1;
	unsigned int link_addr = ie_get_cmd_list_addr(opt_reg);
	LINK_CMD_STATUS link_status = CMD_ERROR_STATUS;
	LINK_CMD_TYPE link_type = CMD_ERROR;

	if (link_addr == 0xffffffff)
		return;

	link_handle = link_create(link_addr);
	while (link_thread_running) {
		link_type = link_get_cmd_type(link_handle);
		if (link_type == CMD_ERROR) {
			ie_send_int(opt_reg, CMD_ERR_INT_STATUS);
		} else if (link_type == CMD_MULTI_ADD) {
			BOOL sign, b_flag;
			BITS_TYPE bits;
			CELLS indata, para, prdata, outdata;
			MULTI_ADD_PROC_TYPE type;

			sign = link_get_multi_add_sign(link_handle);
			bits = link_get_multi_add_bits(link_handle);
			type = link_get_multi_add_proc_type(link_handle);
			b_flag = link_get_multi_add_b_flag(link_handle);
			link_get_multi_add_cell(link_handle, &para, &indata, &prdata, &outdata);

			multi_add_calc(type, b_flag, bits, sign, &para, &indata, &prdata, &outdata);
		} else if (link_type == CMD_FUNCTION) {
			CELLS indata, para, outdata;
			BOOL limit;

			limit = link_get_function_limit(link_handle);
			link_get_function_cell(link_handle, &para, &indata, &outdata);

			function_calc(limit, FLOAT_BITS, TRUE, &para, &indata, &outdata);
		} else if (link_type == CMD_DOWNSAMPLE) {

		}

		if (link_get_cmd_interrupt(link_handle) == TRUE) {
			if (link_get_cmd_pro_end(link_handle) == TRUE)
				link_set_cmd_pro_end(link_handle);
			ie_send_int(opt_reg, OVER_INT_STATUS);
		}

LINK_CMD_RETRY:
		link_status = link_switch_next(link_handle);
		if (link_status == CMD_ERROR_STATUS) {
			ie_send_int(opt_reg, CMD_ERR_INT_STATUS);
			goto LINK_CMD_EXIT;
		} else if ((link_status == CMD_EMPTY_STATUS) || (link_status == CMD_NOT_EXIST_STATUS)) {
			unsigned int thread_delay = (unsigned int)ie_get_idle_cycle(opt_reg);
			unsigned char thread_type = ie_get_idle_type(opt_reg);

			if (thread_type == 0x1) {
				com_thread_delay(thread_delay);
				if (link_thread_running)
					goto LINK_CMD_RETRY;
				else
					goto LINK_CMD_EXIT;
			} else if (thread_type == 0x0) {
				ie_send_int(opt_reg, IDLE_INT_STATUS);
				goto LINK_CMD_EXIT;
			}
		}
	}

LINK_CMD_EXIT:
	link_destory(link_handle);
	return;
}

int link_start(void)
{
	int ret = -1;

	if ((opt_reg = (IE_REG_OPT*)COM_Reg_RealAddr()) == NULL)
		return -1;

	if (ie_get_work_en(opt_reg) == 0)
		return -1;

	if (link_thread_running)
		return -1;

	link_thread_running = 1;
	ret = com_thread_create("link_process", &link_pthread, link_process, NULL, 32*1024, 9);
	if (ret < 0)
		return -1;

	return 0;
}

void link_stop(void)
{
	if (link_thread_running) {
		link_thread_running = 0;
		com_thread_join(link_pthread);
	}
}
