#include <stdarg.h>
#include <stddef.h>

#include "i386/mem_i386.h"

#ifdef __i386__
#define __memset(ptr, value, num)	__memset_i386(ptr, value, num)
#define __memcpy(dest, src, num)	__memcpy_i386(dest, src, num)
#define __memcmp(a, b, num)			__memcmp_i386(a, b, num)
#else
void* __memset(void* ptr, int value, size_t num);
void* __memcpy(void* dest, const void* src, size_t num);
char  __memcmp(const void* a, const void* b, size_t num);
#endif

void* __memchr(const void* ptr, int value, size_t num);