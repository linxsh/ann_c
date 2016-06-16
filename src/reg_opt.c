#include "reg_opt.h"

/*******************************************************
 ************** get module contorl reg *****************
********************************************************/
inline unsigned short ie_get_idle_cycle(IE_REG_OPT *reg)
{
	return ((reg->work_ctrl>>16)&0xffff);
}

inline unsigned char ie_get_idle_type(IE_REG_OPT *reg)
{
	return (unsigned char)((reg->work_ctrl>>4)&0x1);
}

inline BOOL ie_get_work_en(IE_REG_OPT *reg)
{
	return (reg->work_ctrl&0x1);
}

/*******************************************************
 ************ get module interrupt en reg **************
********************************************************/
inline BOOL ie_get_cmd_err_int_en(IE_REG_OPT *reg)
{
	return ((reg->int_en>>12)&0x1);
}

inline BOOL ie_get_overtime_int_en(IE_REG_OPT *reg)
{
	return ((reg->int_en>>8)&0x1);
}

inline BOOL ie_get_idle_int_en(IE_REG_OPT *reg)
{
	return ((reg->int_en>>4)&0x1);
}

inline BOOL ie_get_over_int_en(IE_REG_OPT *reg)
{
	return ((reg->int_en)&0x1);
}

/*******************************************************
 ************ get module clear reg *********************
********************************************************/
inline BOOL ie_get_cmd_err_int_clr(IE_REG_OPT *reg)
{
	return ((reg->int_clr>>12)&0x1);
}

inline BOOL ie_get_overtime_int_clr(IE_REG_OPT *reg)
{
	return ((reg->int_clr>>8)&0x1);
}

inline BOOL ie_get_idle_int_clr(IE_REG_OPT *reg)
{
	return ((reg->int_clr>>4)&0x1);
}

inline BOOL ie_get_over_int_clr(IE_REG_OPT *reg)
{
	return ((reg->int_clr)&0x1);
}

inline void ie_clr_cmd_err_int_clr(IE_REG_OPT *reg)
{
	reg->int_clr &= ~(0x1<<12);
}

inline void ie_clr_overtime_int_clr(IE_REG_OPT *reg)
{
	reg->int_clr &= ~(0x1<<8);
}

inline void ie_clr_idle_int_clr(IE_REG_OPT *reg)
{
	reg->int_clr &= ~(0x1<<4);
}

inline void ie_clr_over_int_clr(IE_REG_OPT *reg)
{
	reg->int_clr &= ~(0x1);
}
/*******************************************************
 ************** set module status reg ******************
********************************************************/
inline void ie_set_cmd_err_status(IE_REG_OPT *reg)
{
	reg->int_status |= (0x1<<12);
}

inline void ie_set_overtime_status(IE_REG_OPT *reg)
{
	reg->int_status |= (0x1<<8);
}

inline void ie_set_idle_status(IE_REG_OPT *reg)
{
	reg->int_status |= (0x1<<4);
}

inline void ie_set_over_status(IE_REG_OPT *reg)
{
	reg->int_status |= (0x1);
}

inline void ie_clr_cmd_err_status(IE_REG_OPT *reg)
{
	reg->int_status &= ~(0x1<<12);
}

inline void ie_clr_overtime_status(IE_REG_OPT *reg)
{
	reg->int_status &= ~(0x1<<8);
}

inline void ie_clr_idle_status(IE_REG_OPT *reg)
{
	reg->int_status &= ~(0x1<<4);
}

inline void ie_clr_over_status(IE_REG_OPT *reg)
{
	reg->int_status &= ~(0x1);
}
/*******************************************************
 ************ get module cmd list address **************
********************************************************/
inline unsigned int ie_get_cmd_list_addr(IE_REG_OPT *reg)
{
	return reg->link_addr;
}

/*******************************************************
 ************** get module over time gate **************
********************************************************/
inline unsigned int ie_get_cmd_over_time_gate(IE_REG_OPT *reg)
{
	return reg->over_time_thr;
}

/*******************************************************
 ************** get module opt priority ****************
********************************************************/
inline unsigned char ie_get_downsample_priority(IE_REG_OPT *reg)
{
	return ((reg->opt_priority>>12)&0x3);
}

inline unsigned char ie_get_function_priority(IE_REG_OPT *reg)
{
	return ((reg->opt_priority>>8)&0x3);
}

inline unsigned char ie_get_multi_add_priority(IE_REG_OPT *reg)
{
	return ((reg->opt_priority>>4)&0x3);
}

inline unsigned char ie_get_cmd_priority(IE_REG_OPT *reg)
{
	return ((reg->opt_priority)&0x3);
}

/*******************************************************
 ********** get module opt over time gate **************
********************************************************/
inline unsigned short ie_get_multi_add_thr(IE_REG_OPT *reg)
{
	return ((reg->ddr_ctrl0>>16)&0xffff);
}

inline unsigned short ie_get_cmd_thr(IE_REG_OPT *reg)
{
	return ((reg->ddr_ctrl0)&0xffff);
}

inline unsigned short ie_get_downsample_thr(IE_REG_OPT *reg)
{
	return ((reg->ddr_ctrl1>>16)&0xffff);
}

inline unsigned short ie_get_function_thr(IE_REG_OPT *reg)
{
	return ((reg->ddr_ctrl1)&0xffff);
}

/*******************************************************
 ****************** set module version  ****************
********************************************************/
inline void ie_set_major_version(IE_REG_OPT *reg, unsigned char version)
{
	unsigned int tmp = (unsigned int)version;
	reg->version = (((reg->version)&(~(0xff<<8)))|(tmp<<8));
}

inline void ie_set_minor_version(IE_REG_OPT *reg, unsigned char version)
{
	unsigned int tmp = (unsigned int)version;
	reg->version = (((reg->version)&(~(0xff)))|(tmp));
}

/*******************************************************
 *************** set cur cmd address/cost time *********
********************************************************/
inline void ie_set_cmd_cur_addr(IE_REG_OPT *reg, unsigned int address)
{
	reg->cmd_addr = address;
}

inline void ie_set_cmd_cost_time(IE_REG_OPT *reg, unsigned int times)
{
	reg->cost_time = times;
}
