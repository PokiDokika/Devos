#pragma once
#include <stdarg.h>
#include <stdbool.h>

#define FLAG_LEFT_ALLIGN        '-'
#define FLAG_APPEND_PLUS        '+'
#define FLAG_APPEND_ZERO        '0'
#define FLAG_APPEND_SPACE       ' '
#define FLAG_APOSTROPHE         '`'
#define FLAG_ALTERNATIVE        '#'

#define NUM_DYNAMIC             '*'
#define NUM_PRECISION           '.'

/*
Specific I/O functions for the kernel.
*/
void __buf_printio(char, char* restrict, size_t);
void __tty_printio(char, char* restrict, size_t);

void __strn_print(void (*)(char, char*, size_t), char*, char*, size_t, size_t*);
void __strn_pad_print(void (*)(char, char*, size_t), char*, char* restrict, size_t, char, bool, size_t*);
void __str_print(void (*)(char, char*, size_t), char*, char*, size_t*);

size_t __base_vprintf(char* output_buffer, void (*)(char, char*, size_t), const char* restrict, size_t, va_list);

/*
Internal printf functions.
*/

size_t __vprintf(const char* restrict, va_list);
size_t __vsnprintf(char*, const char* restrict, size_t, va_list);
size_t __vsprintf(char*, const char* restrict, va_list);