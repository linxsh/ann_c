#ifndef __COMMON_REG_H__
#define __COMMON_REG_H__

#include "reg_opt.h"
#include "common_ie.h"

typedef enum {
	IE_REG_UNKOWN = 0,
	IE_REG_WORK_EN,
	IE_REG_CMD_ERR_INT_CLR,
	IE_REG_OVERTIME_INT_CLR,
	IE_REG_IDLE_INT_CLR,
	IE_REG_OVER_INT_CLR,
} REG_OPT_TYPE;

typedef struct {
	unsigned int virtual_addr;
	unsigned int real_addr;
} REG_MANAGER;

typedef struct {
#define SPECIAL_REG_BITS 32
	unsigned int   offset;
	unsigned int   bits;
	unsigned char  bits_offset;
	REG_OPT_TYPE   type;
} REG_SPECIAL;

#endif
