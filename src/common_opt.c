#include "common_opt.h"

COMMON_FUNCTION *func = NULL;
COM_INTERRUPT interrupt = NULL;

void COM_Register_Int_Func(COM_INTERRUPT inter)
{
	interrupt = inter;
}

void com_register_func(COMMON_FUNCTION* s_func)
{
	func = s_func;
}

void *com_malloc(unsigned int size)
{
	void *ptr = NULL;

	if (func && func->m_malloc)
		ptr = func->m_malloc(size);

	return ptr;
}

void com_free(void* ptr)
{
	if (func && func->m_free)
		func->m_free(ptr);
	return;
}

void com_printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	if (func && func->m_printf)
		func->m_printf(format, args);
	va_end(args);

	return;
}

char com_8_add(BOOL sign, char x,  char y)
{
	if (func && func->m8_add)
		return func->m8_add(sign, x, y);
	return 0;
}

char com_8_sub(BOOL sign, char x,  char y)
{
	if (func && func->m8_sub)
		return func->m8_sub(sign, x, y);
	return 0;
}

char com_8_mul(BOOL sign, char x,  char y)
{
	if (func && func->m8_mul)
		return func->m8_mul(sign, x, y);
	return 0;
}

short com_16_add(BOOL sign, short x, short y)
{
	if (func && func->m16_add)
		return func->m16_add(sign, x, y);
	return 0;
}

short com_16_sub(BOOL sign, short x, short y)
{
	if (func && func->m16_sub)
		return func->m16_sub(sign, x, y);
	return 0;
}

short com_16_mul(BOOL sign, short x, short y)
{
	if (func && func->m16_mul)
		return func->m16_mul(sign, x, y);
	return 0;
}

float com_float_add(float x, float y)
{
	if (func && func->float_add)
		return func->float_add(x, y);
	return 0;
}

float com_float_sub(float x, float y)
{
	if (func && func->float_sub)
		return func->float_sub(x, y);
	return 0;
}

float com_float_mul(float x, float y)
{
	if (func && func->float_mul)
		return func->float_mul(x, y);
	return 0;
}

int  com_thread_create(const char *name, unsigned int *tid,
		void(*function)(void*), void* arg, unsigned int size, unsigned int priority)
{
	int ret = -1;

	if (func && func->m_thread_create)
		ret = func->m_thread_create(name, tid, function, arg, size, priority);

	return ret;
}

int  com_thread_join(unsigned int tid)
{
	int ret = -1;

	if (func && func->m_thread_join)
		ret = func->m_thread_join(tid);

	return ret;
}

void com_thread_delay(unsigned int ms)
{
	if (func && func->m_thread_delay)
		func->m_thread_delay(ms);
	return;
}

void com_interrupt(void)
{
	if (interrupt)
		interrupt();
	return;
}
