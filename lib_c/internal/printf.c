#include <stdarg.h>
#include <stdbool.h>

#include "printf_conv.h"
#include "printf.h"
#include "../string.h"
#include "../stdio.h"

#include "../../terminal.h"

/*
Specific I/O functions for the kernel.
*/
void __buf_printio(char char_append, char* restrict buffer, size_t idx)     
{ 
	buffer[idx] = char_append; 
}

void __tty_printio(char char_append, __attribute__((unused)) char* restrict buffer, __attribute__((unused)) size_t idx)     
{
	if (char_append)
		terminal_putchar(char_append);
}

void __strn_print(void (*io_func)(char, char*, size_t), char* str_append, char* buffer, size_t size, size_t* idx) 
{
	char* ptr_str = str_append;
	for (; (size_t)(ptr_str - str_append) < size && *ptr_str; ptr_str++)
		io_func(*ptr_str, buffer, *idx);
}

void __strn_pad_print(void (*io_out)(char, char*, size_t), char* str_append, char* restrict buffer, size_t size, char pad, bool right, size_t* idx) 
{
	if (size == SIZE_MAX)
		return __strn_print(io_out, str_append, buffer, size, idx);

	char buf_append[size + 1];

	size_t n;
	size_t str_len = strlen(str_append);

	if (size < str_len)
		size = str_len;

	for (n = 0; n < size; n++)
	{
		buf_append[n] = pad;

		if (right)
		{
			if (str_len > n)
				buf_append[n] = str_append[n];
		}
		else
		{
			// Is this right...?
			if (str_len + n >= size)
				buf_append[n] = str_append[str_len - size + n];
		}
	}
    
	buf_append[size] = '\0';
	return __strn_print(io_out, buf_append, buffer, size, idx);
}

void __str_print(void (*io_func)(char, char*, size_t), char* str_append, char* buffer, size_t* idx)
{
	__strn_print(io_func, str_append, buffer, -1, idx);
}

/*
Base for printing through a given I/O function.
Use this for any printf-related functions.

[bjrkk] FIXME: Clear this code maybe?
*/

size_t __base_vprintf(char* output_buffer, void (*io_func)(char, char*, size_t), const char* restrict fmt_buffer, size_t max, va_list variadic_list)
{
	size_t idx = 0;
		
	for (size_t i = 0; i < max; i++)
	{
		char idx_char = fmt_buffer[i];

		if (idx_char == '%')
		{
			bool uppercase = false,
				 left_allign = false,
				 append_plus = false,
				 append_zero = false,
				 append_space = false,
				 alternative = false;

			int width = -1, 
				precision = 7;

			int* param_ptr = &width;
			
			char fmt_type = '\0';

			// [bjrkk] Should correctly parse this stuff now;
			char param_char;
			do
			{
				param_char = fmt_buffer[++i];

				if (param_char == FLAG_LEFT_ALLIGN)
					left_allign = true;
				else if (param_char == FLAG_APPEND_PLUS)
					append_plus = true;
				else if (param_char == FLAG_APPEND_ZERO)
					append_zero = true;
				else if (param_char == FLAG_APPEND_SPACE && !append_plus)
					append_space = true;
				else if (param_char == FLAG_ALTERNATIVE)
					alternative = true;
				else if (param_char == NUM_DYNAMIC)
					width = va_arg(variadic_list, int);
				else if (param_char == NUM_PRECISION)
				{
					precision = 0;
					param_ptr = &precision;
				}
				else if (param_char >= '0' && param_char <= '9')
				{
					if (*param_ptr < 0)
						*param_ptr = 0;

					*param_ptr *= 10;
					*param_ptr += param_char - '0';
				}
				else
				{
					fmt_type = param_char;
					break;
				}
			} 
			while (fmt_type == '\0' && param_char != '\0');

			char pad_char = append_zero ? '0' : ' ';

			switch (fmt_type)
			{
				case 'i':
				case 'd':
					if (append_plus)
						io_func('+', output_buffer, idx++);
					else if (append_space)
						io_func(' ', output_buffer, idx++);

					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 10, true, uppercase),
						output_buffer,
						width,
						pad_char,
						left_allign,
						&idx
					);
					break;
				case 'u':
					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, unsigned long), 10, false, uppercase),
						output_buffer,
						width,
						pad_char,
						left_allign,
						&idx
					);
					break;
				case 'F':
					uppercase = true;
				case 'f':
					if (append_plus)
						io_func('+', output_buffer, idx++);
					else if (append_space)
						io_func(' ', output_buffer, idx++);

					__str_print(
						io_func,
						__ftoa(va_arg(variadic_list, double), precision, uppercase),
						output_buffer,
						&idx
					);
					break;
				case 'X':
					uppercase = true;
				case 'x':
					if (alternative)
                    {
						if (uppercase)
                        	__str_print(io_func, "0X", output_buffer, &idx);
                        else
                            __str_print(io_func, "0x", output_buffer, &idx);
					}

					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 16, false, uppercase),
						output_buffer,
						width,
						pad_char,
						left_allign,
						&idx
					);
					break;
				case 'o':
					if (alternative)
                       io_func('0', output_buffer, idx++);

					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 8, false, uppercase),
						output_buffer,
						width,
						pad_char,
						left_allign,
						&idx
					);
					break;
				// [bjrkk] Non-standard. Should probably get removed...?
				case 'b':
					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 2, false, uppercase),
						output_buffer,
						width,
						pad_char,
						left_allign,
						&idx
					);
					break;
				case 's':
					__str_print(
						io_func,
						va_arg(variadic_list, char*),
						output_buffer,
						&idx
					);
					break;
				case 'c':
					// This kind of makes no sense...
					io_func(va_arg(variadic_list, int), output_buffer, idx++);
					break;
				default:
					io_func(fmt_type, output_buffer, idx++);
			}
		} else 
		{
			io_func(idx_char, output_buffer, idx++);
		}

		// Obviously let it add the '\0' aswell...
		if (!idx_char) 
			break;
	}

	return idx;
}

/*
Internal printf functions.
*/

size_t __vprintf(const char* restrict text, va_list variadic_list)                             
{ 
	return __base_vprintf(NULL, __tty_printio, text, -1, variadic_list);
}

size_t __vsnprintf(char* buffer, const char* restrict text, size_t max, va_list variadic_list) 
{ 
	return __base_vprintf(buffer, __buf_printio, text, max, variadic_list); 
}

size_t __vsprintf(char* buffer, const char* restrict text, va_list variadic_list)              
{ 
	return __vsnprintf(buffer, text, -1, variadic_list); 
}