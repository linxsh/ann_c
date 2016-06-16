#include "common_reg.h"
#include "common_opt.h"
#include "link_analyze.h"
#include "interrupt_opt.h"

static REG_MANAGER mreg;
static REG_SPECIAL sreg[5] = {
	{0x00, 0x00000001,  0, IE_REG_WORK_EN},
	{0x08, 0x00001000, 12, IE_REG_CMD_ERR_INT_CLR},
	{0x08, 0x00000100,  8, IE_REG_OVERTIME_INT_CLR},
	{0x08, 0x00000010,  4, IE_REG_IDLE_INT_CLR},
	{0x08, 0x00000001,  0, IE_REG_OVER_INT_CLR},
};

static void __special_reg_opt(unsigned int old_value, unsigned int value, REG_OPT_TYPE type)
{
	switch (type) {
		case IE_REG_WORK_EN:
			{
				if ((old_value == 0) && (value == 1)) {
					link_start();
				} else if ((old_value == 1) && (value == 0)) {
					link_stop();
				}
			}
			break;
		case IE_REG_CMD_ERR_INT_CLR:
			ie_clr_int_status((IE_REG_OPT*)mreg.real_addr, CMD_ERR_INT_STATUS);
			break;
		case IE_REG_OVERTIME_INT_CLR:
			ie_clr_int_status((IE_REG_OPT*)mreg.real_addr, OVER_TIME_INT_STATUS);
			break;
		case IE_REG_IDLE_INT_CLR:
			ie_clr_int_status((IE_REG_OPT*)mreg.real_addr, IDLE_INT_STATUS);
			break;
		case IE_REG_OVER_INT_CLR:
			ie_clr_int_status((IE_REG_OPT*)mreg.real_addr, OVER_INT_STATUS);
			break;
		default:
			break;
	}
	return;
}

void COM_Reg_Init(unsigned int virtual_addr)
{
	extern COMMON_FUNCTION linux_func;

	com_register_func(&linux_func);
	memset(&mreg, 0, sizeof(REG_MANAGER));
	mreg.real_addr = (unsigned int)com_malloc(sizeof(IE_REG_OPT));
	memset((unsigned char*)mreg.real_addr, 0, sizeof(IE_REG_OPT));
	mreg.virtual_addr = virtual_addr;

	return;
}

void COM_Reg_Destory(void)
{
	if (mreg.real_addr)
		com_free((void*)mreg.real_addr);
	mreg.real_addr = 0;
	return;
}

unsigned int COM_Reg_Read(unsigned int virtual_addr)
{
	unsigned int offset = (virtual_addr - mreg.virtual_addr);
	unsigned int *value_addr = (unsigned int *)mreg.real_addr;
	unsigned int index = offset/sizeof(unsigned int);

	if (offset < 0 || offset > sizeof(IE_REG_OPT))
		com_printf("[%s][%d], waring, reg error\n", __FUNCTION__, __LINE__);

	return value_addr[index];
}

void COM_Reg_Write(unsigned int virtual_addr, unsigned int new_value)
{
	int i = 0;
	unsigned int offset = (virtual_addr - mreg.virtual_addr);
	unsigned int *value_addr = (unsigned int *)mreg.real_addr;
	unsigned int index = offset/sizeof(unsigned int);
	unsigned int change_flags = 0;
	unsigned int old_value = 0;

	if (offset < 0 || offset > sizeof(IE_REG_OPT))
		com_printf("[%s][%d], waring, reg error\n", __FUNCTION__, __LINE__);

	old_value = value_addr[index];
	value_addr[index] = new_value;
	for (i = 0; i < sizeof(sreg)/sizeof(REG_SPECIAL); i++) {
		if (offset == sreg[i].offset) {
			change_flags = old_value^new_value;
			if (change_flags & sreg[i].bits) {
				unsigned int old_reg_value = (old_value & sreg[i].bits) >> sreg[i].bits_offset;
				unsigned int new_reg_value = (new_value & sreg[i].bits) >> sreg[i].bits_offset;

				__special_reg_opt(old_reg_value, new_reg_value, sreg[i].type);
			}
		}
	}

	return;
}

unsigned int COM_Reg_RealAddr(void)
{
	return mreg.real_addr;
}
