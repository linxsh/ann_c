#ifndef __INTERRUPT_OPT_H__
#define __INTERRUPT_OPT_H__

#include "common_ie.h"
#include "reg_opt.h"

typedef enum {
	OVER_INT_EN      = (1<<0),
	CMD_ERR_INT_EN   = (1<<1),
	OVER_TIME_INT_EN = (1<<2),
	IDLE_INT_EN      = (1<<3)
} IE_INT_EN;

typedef enum {
	OVER_INT_STATUS      = (1<<0),
	CMD_ERR_INT_STATUS   = (1<<1),
	OVER_TIME_INT_STATUS = (1<<2),
	IDLE_INT_STATUS      = (1<<3)
} IE_INT_STATUS;

extern void ie_send_int(IE_REG_OPT* reg, IE_INT_STATUS status);
extern void ie_clr_int_status(IE_REG_OPT* reg, IE_INT_STATUS status);
extern IE_INT_EN ie_get_int_en(IE_REG_OPT* reg);

#endif
