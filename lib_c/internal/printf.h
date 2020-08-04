#pragma once
#include <stdarg.h>
#include <stdbool.h>

#define FLAG_LEFT_ALLIGN        '-'
#define FLAG_APPEND_PLUS        '+'
#define FLAG_APPEND_ZERO        '0'
#define FLAG_APPEND_SPACE       ' '
#define FLAG_APOSTROPHE         '`'
#define FLAG_ALTERNATIVE        '#'
#define FLAG_DYNAMIC            '*'

/*
Specific I/O functions for the kernel.
*/
void __buf_printio(char char_append, char* restrict buffer, size_t idx);
void __tty_printio(char char_append, char* restrict buffer, size_t idx);

void __strn_print(void (*io_func)(char, char*, size_t), char* str_append, char* buffer, size_t max, size_t* idx);
void __strn_pad_print(void (*io_out)(char, char*, size_t), char* str_append, char* restrict buffer, size_t size, char pad, bool right, size_t* idx);
void __str_print(void (*io_func)(char, char*, size_t), char* str_append, char* buffer, size_t* idx);

size_t __base_vprintf(char* output_buffer, void (*io_func)(char, char*, size_t), const char* restrict fmt_buffer, size_t max, va_list variadic_list);

/*
Internal printf functions.
*/

size_t __vprintf(const char* restrict text, va_list variadic_list);
size_t __vsnprintf(char* buffer, const char* restrict text, size_t max, va_list variadic_list);
size_t __vsprintf(char* buffer, const char* restrict text, va_list variadic_list);