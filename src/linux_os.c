#include <stdlib.h>
#include <pthread.h>
#include "common_opt.h"

static int lm_thread_create(const char *name, unsigned int *tid,
		void(*func)(void*), void* arg, unsigned int size, unsigned int priority)
{
	int ret = -1;

	ret = pthread_create((pthread_t*)tid, NULL, (void*)func, arg);
	return ret;
}

static int lm_thread_join(unsigned int tid)
{
	int ret = -1;
	ret = pthread_join((pthread_t)tid, NULL);
	return ret;
}

static void lm_thread_delay(unsigned int time_ms)
{
	usleep(time_ms*1000);
}

static void lm_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, format, args);
	va_end(args);
}

static void* lm_malloc(unsigned int size)
{
	void *ptr = NULL;

	ptr = malloc(size);
	return ptr;
}

static void lm_free(void* ptr)
{
	if (ptr != NULL)
		free(ptr);
}

static char lm8_add(BOOL sign, char  x, char y)
{
	return (x+y);
}

static char lm8_sub(BOOL sign, char  x, char y)
{
	return (x-y);
}

static char lm8_mul(BOOL sign, char  x, char y)
{
	return (x*y);
}

static short lm16_add(BOOL sign, short x, short y)
{
	return (x+y);
}

static short lm16_sub(BOOL sign, short x, short y)
{
	return (x-y);
}

static short lm16_mul(BOOL sign, short x, short y)
{
	return (x*y);
}

static float l_float_add(float x, float y)
{
	return (x+y);
}

static float l_float_sub(float x, float y)
{
	return (x-y);
}

static float l_float_mul(float x, float y)
{
	return (x*y);
}

COMMON_FUNCTION linux_func = {
	.name = "linux os",
	.m_thread_create = lm_thread_create,
	.m_thread_join   = lm_thread_join,
	.m_thread_delay  = lm_thread_delay,
	.m_printf        = lm_printf,
	.m_malloc        = lm_malloc,
	.m_free          = lm_free,
	.m8_add          = lm8_add,
	.m8_sub          = lm8_sub,
	.m8_mul          = lm8_mul,
	.m16_add         = lm16_add,
	.m16_sub         = lm16_sub,
	.m16_mul         = lm16_mul,
	.float_add       = l_float_add,
	.float_sub       = l_float_sub,
	.float_mul       = l_float_mul,
};
