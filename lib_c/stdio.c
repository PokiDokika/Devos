#include <stdarg.h>
#include <stddef.h>

#include "internal/printf.h"
#include "string.h"
#include "../terminal.h"

void putc(int c) 
{
	terminal_putchar(c);
	update_cursor();
}

void puts(const char* restrict text) 
{
	terminal_write(text);
	update_cursor();
}

size_t printf(const char* restrict text, ...)
{
	va_list variadic_list;
	va_start(variadic_list, text);

	size_t return_idx = __vprintf(text, variadic_list);
	update_cursor();

	va_end(variadic_list);

	return return_idx;
}

size_t sprintf(char* buffer, const char* restrict text, ...)
{
	va_list variadic_list;
	va_start(variadic_list, text);

	size_t return_idx = __vsprintf(buffer, text, variadic_list);

	va_end(variadic_list);

	return return_idx;
}

size_t snprintf(char* buffer, size_t max, const char* restrict text, ...)
{
	va_list variadic_list;
	va_start(variadic_list, text);

	size_t return_idx = __vsnprintf(buffer, text, max, variadic_list);

	va_end(variadic_list);

	return return_idx;
}