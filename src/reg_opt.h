#ifndef __REG_OPT_H__
#define __REG_OPT_H__

#include "common_ie.h"
#include "common_opt.h"

typedef struct {
	unsigned int work_ctrl;
	unsigned int int_en;
	unsigned int int_clr;
	unsigned int int_status;
	unsigned int link_addr;
	unsigned int over_time_thr;
	unsigned int reserve0[2];
	unsigned int opt_priority;
	unsigned int ddr_ctrl0;
	unsigned int ddr_ctrl1;
	unsigned int reserve1[21];
	unsigned int version;
	unsigned int reserve2[31];
	unsigned int cmd_addr;
	unsigned int cost_time;
	unsigned int reserve3[2];
	unsigned int ma_status0;
	unsigned int ma_status1;
	unsigned int ma_para_addr0;
	unsigned int ma_para_addr1;
	unsigned int ma_data_addr0;
	unsigned int ma_data_addr1;
	unsigned int ma_pre_data_addr0;
	unsigned int ma_pre_data_addr1;
	unsigned int reserve4[4];
	unsigned int act_status0;
	unsigned int act_status1;
	unsigned int act_para_addr0;
	unsigned int act_para_addr1;
	unsigned int act_data_addr0;
	unsigned int act_data_addr1;
	unsigned int reserve5[10];
	unsigned int ds_status0;
	unsigned int ds_status1;
}IE_REG_OPT;

#define bIE_WORK_EN       (0)
#define mIE_WORK_EN       (0x01<<bIE_WORK_EN)

#define bIE_IDLE_TYPE     (4)
#define mIE_IDLE_TYPE     (0x1<<bIE_IDLE_TYPE)

#define bIE_IDLE_CYCLE    (16)
#define mIE_IDLE_CYCLE    (0xFF<<bIE_IDLE_CYCLE)

extern inline unsigned short ie_get_idle_cycle(IE_REG_OPT *reg);
extern inline unsigned char ie_get_idle_type(IE_REG_OPT *reg);
extern inline BOOL ie_get_work_en(IE_REG_OPT *reg);
extern inline BOOL ie_get_cmd_err_int_en(IE_REG_OPT *reg);
extern inline BOOL ie_get_overtime_int_en(IE_REG_OPT *reg);
extern inline BOOL ie_get_idle_int_en(IE_REG_OPT *reg);
extern inline BOOL ie_get_over_int_en(IE_REG_OPT *reg);
extern inline BOOL ie_get_cmd_err_int_clr(IE_REG_OPT *reg);
extern inline BOOL ie_get_overtime_int_clr(IE_REG_OPT *reg);
extern inline BOOL ie_get_idle_int_clr(IE_REG_OPT *reg);
extern inline BOOL ie_get_over_int_clr(IE_REG_OPT *reg);
extern inline void ie_clr_cmd_err_int_clr(IE_REG_OPT *reg);
extern inline void ie_clr_overtime_int_clr(IE_REG_OPT *reg);
extern inline void ie_clr_idle_int_clr(IE_REG_OPT *reg);
extern inline void ie_clr_over_int_clr(IE_REG_OPT *reg);
extern inline void ie_set_cmd_err_status(IE_REG_OPT *reg);
extern inline void ie_set_overtime_status(IE_REG_OPT *reg);
extern inline void ie_set_idle_status(IE_REG_OPT *reg);
extern inline void ie_set_over_status(IE_REG_OPT *reg);
extern inline void ie_clr_cmd_err_status(IE_REG_OPT *reg);
extern inline void ie_clr_overtime_status(IE_REG_OPT *reg);
extern inline void ie_clr_idle_status(IE_REG_OPT *reg);
extern inline void ie_clr_over_status(IE_REG_OPT *reg);
extern inline unsigned int ie_get_cmd_list_addr(IE_REG_OPT *reg);
extern inline unsigned int ie_get_cmd_over_time_gate(IE_REG_OPT *reg);
extern inline unsigned char ie_get_downsample_priority(IE_REG_OPT *reg);
extern inline unsigned char ie_get_function_priority(IE_REG_OPT *reg);
extern inline unsigned char ie_get_multi_add_priority(IE_REG_OPT *reg);
extern inline unsigned char ie_get_cmd_priority(IE_REG_OPT *reg);
extern inline unsigned short ie_get_multi_add_thr(IE_REG_OPT *reg);
extern inline unsigned short ie_get_cmd_thr(IE_REG_OPT *reg);
extern inline unsigned short ie_get_downsample_thr(IE_REG_OPT *reg);
extern inline unsigned short ie_get_function_thr(IE_REG_OPT *reg);
extern inline void ie_set_major_version(IE_REG_OPT *reg, unsigned char version);
extern inline void ie_set_minor_version(IE_REG_OPT *reg, unsigned char version);
extern inline void ie_set_cmd_cur_addr(IE_REG_OPT *reg, unsigned int address);
extern inline void ie_set_cmd_cost_time(IE_REG_OPT *reg, unsigned int times);

#endif
