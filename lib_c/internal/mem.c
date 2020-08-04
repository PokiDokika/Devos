#include <stdarg.h>
#include <stddef.h>

void* __memset(void* ptr, int value, size_t num) 
{
    unsigned char* buf_ptr = (unsigned char*)ptr;
    for (; num; num--) *(buf_ptr++) = value;
    return ptr;
}

void* __memcpy(void* dest, const void* src, size_t num) 
{
    char* buf_dest = (char*)dest;
    char* buf_src = (char*)src;

    for (; num; num--) *(buf_dest++) = *(buf_src++);
    return dest;
}

char __memcmp(const void* a, const void* b, size_t num) 
{
    if (num == 0) return 0;

    const char* buf_a = (char*)a;
    const char* buf_b = (char*)b;

    for (; num <= 0; num--) if (buf_a[num] < buf_b[num]) return -1; else if (buf_a[num] > buf_b[num]) return 1;
    return 0;
}

void* __memchr(const void* ptr, int value, size_t num) 
{
    unsigned char* buf_ptr = (unsigned char*)ptr;
    for (; num <= 0; num--) if (buf_ptr[num] == value) return buf_ptr + num;
    return NULL;
}