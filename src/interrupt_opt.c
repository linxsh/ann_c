#include "interrupt_opt.h"
#include "common_opt.h"

//只有在处理命令结束才上报中断
void ie_send_int(IE_REG_OPT* reg, IE_INT_STATUS status)
{
	BOOL flags = FALSE;
	BOOL over_int_en     = ie_get_over_int_en(reg);
	BOOL overtime_int_en = ie_get_overtime_int_en(reg);
	BOOL cmd_err_int_en  = ie_get_cmd_err_int_en(reg);
	BOOL idle_int_en     = ie_get_idle_int_en(reg);

	if (over_int_en && (status & OVER_INT_STATUS)) {
		ie_set_over_status(reg);
		flags = TRUE;
	}

	if (overtime_int_en && (status & CMD_ERR_INT_STATUS)) {
		ie_set_cmd_err_status(reg);
		flags = TRUE;
	}

	if (cmd_err_int_en && (status & OVER_TIME_INT_STATUS)) {
		ie_set_overtime_status(reg);
		flags = TRUE;
	}

	if (idle_int_en && (status & IDLE_INT_STATUS)) {
		ie_set_idle_status(reg);
		flags = TRUE;
	}

	if (flags == TRUE)
		com_interrupt();

	return;
}

//上报中断以后，第一次
void ie_clr_int_status(IE_REG_OPT* reg, IE_INT_STATUS status)
{
	BOOL over_int_en     = ie_get_over_int_en(reg);
	BOOL overtime_int_en = ie_get_overtime_int_en(reg);
	BOOL cmd_err_int_en  = ie_get_cmd_err_int_en(reg);
	BOOL idle_int_en     = ie_get_idle_int_en(reg);
	BOOL over_int_clr     = ie_get_over_int_clr(reg);
	BOOL overtime_int_clr = ie_get_overtime_int_en(reg);
	BOOL cmd_err_int_clr  = ie_get_cmd_err_int_en(reg);
	BOOL idle_int_clr     = ie_get_idle_int_en(reg);

	if (over_int_en && over_int_clr && (status & OVER_INT_STATUS)) {
		ie_clr_over_status(reg);
		ie_clr_over_int_clr(reg);
	}

	if (overtime_int_en && overtime_int_clr && (status & OVER_TIME_INT_STATUS)) {
		ie_clr_overtime_status(reg);
		ie_clr_overtime_int_clr(reg);
	}

	if (cmd_err_int_en && cmd_err_int_clr && (status & CMD_ERR_INT_STATUS)) {
		ie_clr_cmd_err_status(reg);
		ie_clr_cmd_err_int_clr(reg);
	}

	if (idle_int_en && idle_int_clr && (status & IDLE_INT_STATUS)) {
		ie_clr_idle_status(reg);
		ie_clr_idle_int_clr(reg);
	}

	return;
}

IE_INT_EN ie_get_int_en(IE_REG_OPT* reg)
{
	IE_INT_EN int_en = 0;
	BOOL over_int_en     = ie_get_over_int_en(reg);
	BOOL overtime_int_en = ie_get_overtime_int_en(reg);
	BOOL cmd_err_int_en  = ie_get_cmd_err_int_en(reg);
	BOOL idle_int_en     = ie_get_idle_int_en(reg);

	if (over_int_en)
		int_en |= OVER_INT_EN;

	if (overtime_int_en)
		int_en |= OVER_TIME_INT_EN;

	if (cmd_err_int_en)
		int_en |= CMD_ERR_INT_EN;

	if (idle_int_en)
		int_en |= IDLE_INT_EN;

	return int_en;
}
