#ifndef __COMMON_OPT_H__
#define __COMMON_OPT_H__
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include "common_ie.h"

#define TRUE   (1)
#define FALSE  (0)
typedef unsigned char BOOL;

typedef struct {
	const char* name;
	int   (*m_thread_create)(const char *name, unsigned int *tid,
			void(*func)(void*), void* arg, unsigned int size, unsigned int priority);
	int   (*m_thread_join)(unsigned int tid);
	void  (*m_thread_delay)(unsigned int time_ms);
	void  (*m_printf)(const char *format, ...);
	void* (*m_malloc)(unsigned int size);
	void  (*m_free)(void* ptr);
	char  (*m8_add) (BOOL sign, char  x, char y);
	char  (*m8_sub) (BOOL sign, char  x, char y);
	char  (*m8_mul) (BOOL sign, char  x, char y);
	short (*m16_add)(BOOL sign, short x, short y);
	short (*m16_sub)(BOOL sign, short x, short y);
	short (*m16_mul)(BOOL sign, short x, short y);
	float (*float_add)(float x, float y);
	float (*float_sub)(float x, float y);
	float (*float_mul)(float x, float y);
} COMMON_FUNCTION;

extern void com_register_func(COMMON_FUNCTION* s_func);
extern int  com_thread_create(const char *name, unsigned int *tid,
		void(*func)(void*), void* arg, unsigned int size, unsigned int priority);
extern int  com_thread_join(unsigned int tid);
extern void com_thread_delay(unsigned int time_ms);
extern void com_interrupt(void);
extern void *com_malloc(unsigned int size);
extern void com_free(void* ptr);
extern void com_printf(const char *format, ...);
extern char  com_8_add(BOOL sign, char x,  char y);
extern char  com_8_sub(BOOL sign, char x,  char y);
extern char  com_8_mul(BOOL sign, char x,  char y);
extern short com_16_add(BOOL sign, short x, short y);
extern short com_16_sub(BOOL sign, short x, short y);
extern short com_16_mul(BOOL sign, short x, short y);
extern float com_float_add(float x, float y);
extern float com_float_sub(float x, float y);
extern float com_float_mul(float x, float y);
#endif
