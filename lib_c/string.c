// well

#include <stdint.h>
#include <stddef.h>

#include "./string.h" // so it don't get confusd
#include "./stdio.h"

#include "./internal/str.h"
#include "./internal/mem.h"

/*
Memory functions.
*/

void* memset(void* ptr, int value, size_t num)
{ 
	return __memset(ptr, value, num);
}
void* memcpy(void* dest, const void* src, size_t num)
{ 
	return __memcpy(dest, src, num);
}
char memcmp(const void* a, const void* b, size_t num)
{ 
	return __memcmp(a, b, num);
}
void* memchr(const void* ptr, int value, size_t num)
{ 
	return __memchr(ptr, value, num);
}

/*
String functions.
*/

size_t strlen(const char* str)			  
{ 
	return __strlen(str);
}
char* strcat(char* dest, const char* src)	   
{ 
	return __strcat(dest, src);
}
char* strncat(char* dest, const char* src, size_t num)
{ 
	return __strncat(dest, src, num);
}
char* strstr(char* scan, char* sequence)
{ 
	return __strstr(scan, sequence);
}
char* strcpy(char* dest, const char* src)
{ 
	return __strcpy(dest, src);
}
const char* strchr(const char* scan, int character)
{
	return __strchr(scan, character);
}
size_t strspn(const char* str, const char* chars)
{
	return __strspn(str, chars);
}
size_t strcspn(const char* str, const char* chars)
{
	return __strcspn(str, chars);
}
int strcmp(const char* str1, const char* str2)
{ 
	return __strcmp(str1, str2);
}
/*
[bjrkk] Are those even part of the C standard?
*/
char* strupr(char* src)
{
	return __strupr(src);
}
char* strlwr(char* src)
{
	return __strlwr(src);
}
