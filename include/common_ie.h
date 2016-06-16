#ifndef __COMMON_IE_H__
#define __COMMON_IE_H__

typedef void  (*COM_INTERRUPT)(void);

extern void COM_Register_Int_Func(COM_INTERRUPT interrupt);
extern void COM_Reg_Init(unsigned int virtual_addr);
extern void COM_Reg_Destory(void);
extern unsigned int COM_Reg_Read(unsigned int virtual_addr);
extern void COM_Reg_Write(unsigned int virtual_addr, unsigned int value);
extern unsigned int COM_Reg_RealAddr(void);

#endif
