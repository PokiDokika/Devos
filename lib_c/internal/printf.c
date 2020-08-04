#include <stdarg.h>
#include <stdbool.h>

#include "printf_conv.h"
#include "printf.h"
#include "../../terminal.h"

/*
Specific I/O functions for the kernel.
*/
void __buf_printio(char char_append, char* restrict buffer, size_t idx)     
{ 
	buffer[idx] = char_append; 
}

void __tty_printio(char char_append, char* restrict buffer, size_t idx)     
{ 
	//terminal_write
	if (char_append)
		terminal_putchar(char_append);
}

void __strn_print(void (*io_func)(char, char*, size_t), char* str_append, char* buffer, size_t max, size_t* idx) 
{
	size_t str_idx = 0;
	char idx_chr;

	while (*idx++ < max && (idx_chr = *(str_append + str_idx++)))
		io_func(idx_chr, buffer, *idx);
}

void __strn_pad_print(void (*io_out)(char, char*, size_t), char* str_append, char* restrict buffer, size_t size, char pad, bool right, size_t* idx) 
{
	if (size == SIZE_MAX)
		return __strn_print(io_out, str_append, buffer, size, idx);

	bool append_string = right;
	char buf_append[size + 1];

	size_t n;
	size_t str_len = strlen(str_append);

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
				buf_append[n] = str_append[str_len - (size - n)];
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

			char width = -1, 
				 precision = 7,
				 fmt_type = '\0';

			// [bjrkk] I feel like this code could be improved...
			for (char y = 0; y < 4; y++)
			{
				char param_char = fmt_buffer[++i];

				if (param_char == FLAG_LEFT_ALLIGN)
					left_allign = true;
				else if (param_char == FLAG_APPEND_PLUS)
					append_plus = true;
				else if (param_char == FLAG_APPEND_ZERO && !append_zero)
					append_zero = true;
				else if (param_char == FLAG_APPEND_SPACE)
				{
					if (append_space)
						break;
					
					append_space = true;
				}
				else if (param_char == FLAG_ALTERNATIVE)
					alternative = true;
				else if (param_char >= '0' && param_char <= '9')
					width = param_char - '0';
				else if (param_char == FLAG_DYNAMIC)
					width = va_arg(variadic_list, char);
				else if (param_char == '.')
				{
					param_char = fmt_buffer[++i];

					if (param_char == FLAG_DYNAMIC)
						precision = va_arg(variadic_list, char);
					else if (param_char >= '0' || param_char <= '9')
						precision = param_char - '0';
				}
				else
				{
					fmt_type = param_char;
					break;
				}
			}

			switch (fmt_type)
			{
				case 'i':
				case 'd':
					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 10, true, uppercase),
						output_buffer,
						width,
						'0',
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
						'0',
						left_allign,
						&idx
					);
					break;
				case 'F':
					uppercase = true;
				case 'f':
					__str_print(
						io_func,
						__ftoa(va_arg(variadic_list, float), precision, uppercase),
						output_buffer,
						&idx
					);
					break;
				case 'X':
					uppercase = true;
				case 'x':
					if (alternative)
                        if (uppercase)
                        	__str_print(io_func, "0X", output_buffer, &idx);
                        else
                            __str_print(io_func, "0x", output_buffer, &idx);

					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 16, false, uppercase),
						output_buffer,
						width,
						'0',
						left_allign,
						&idx
					);
					break;
				case 'b':
					__strn_pad_print(
						io_func,
						__ntoa(va_arg(variadic_list, long), 2, false, uppercase),
						output_buffer,
						width,
						'0',
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