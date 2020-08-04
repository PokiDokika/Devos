#include <stdarg.h>
#include <stddef.h>

void* __memset(void* ptr, int value, size_t num);
void* __memcpy(void* dest, const void* src, size_t num);
char __memcmp(const void* a, const void* b, size_t num);
void* __memchr(const void* ptr, int value, size_t num);