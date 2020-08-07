#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../stdio.h"
#include "./mem.h"

size_t __strlen(const char* str)
{
	size_t return_val = 0; 
	for (; str[return_val]; return_val++);
	return return_val;
}

char* __strncat(char* dest, const char* src, size_t num)		  
{ 
	for (; *dest; dest++);
	for (size_t i = 0; i < num && src[i]; i++)
		dest[i] = src[i];

	return dest;
}

char* __strcat(char* dest, const char* src)					   
{ 
	// Don't know if I should be doing this, but it'll do the job for now.
	return __strncat(dest, src, -1);
}

char* __strstr(char* scan, char* sequence)
{
	char* seq_ptr;
    char* scan_ptr;

	for (; *scan; scan++)
	{
        seq_ptr = sequence;
        scan_ptr = scan;
        for (; *seq_ptr && *seq_ptr == *scan_ptr++; seq_ptr++);

        if (!*seq_ptr)
			return scan;
	}

	return NULL;
}

int __strcmp(const char* str1, const char* str2)
{
	// Implementation taken from musl
	for (; *str1==*str2 && *str1; str1++, str2++);
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

const char* __strchr(const char* scan, int character)
{
	for (; *scan != character && character && *scan; scan++);
    if (!*scan)
        return NULL;
	
    return scan;
}

// [bjrkk] FIXME: Probably a bad idea...
char* __strcpy(char* dest, const char* src) 
{ 
	return (char*)__memcpy(dest, src, __strlen(src) + 1);
} // I think this is how gclib does it? With the +1? 


/* FIXME the strspn & strcspn functions are better done
 * with lookup tables */
size_t __strspn(const char *str, const char *chars)
{
	// This is probably terrible.
	// ^ [bjrkk] gotcha fam

	size_t count = 0;
	const char* chr_ptr;

	for (; *str; str++)
	{
		for (chr_ptr = chars; *chr_ptr && *chr_ptr != *str; chr_ptr++);
		
		if (*chr_ptr)
			count++;
		else
			break;
	}

	return count;
}

size_t __strcspn(const char *str, const char *chars)
{ 
	// THIS IS GUARANTEED TERRIBLE
	// ^ [bjrkk] gotcha again fam

    size_t count = 0;
	const char* chr_ptr;
	
	for (; str[count]; count++)
		for (chr_ptr = chars; *chr_ptr; chr_ptr++)
			if (str[count] == *chr_ptr)
				goto L;

	L:
	return count;
}

/*
Non-standard functions.
Only for internal use (?)
*/
char* __strupr(char* str)
{
	for (; *str; str++)
	{
		if (*str >= 'a' && *str <= 'z') 
			*str -= 32;
	}
	
	return str;
}

char* __strlwr(char* str)
{
	for (; *str; str++)
	{
		if (*str >= 'A' && *str <= 'Z') 
			*str += 32;
	}

	return str;
}
