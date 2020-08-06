#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
char memcmp(const void* a, const void* b, size_t num);
void* memchr(const void* ptr, int value, size_t num);


size_t strlen(const char*);
char* strcat(char*, const char*);
char* strncat(char*, const char*, size_t);
char* strstr(char*, char*);
char* strcpy(char*, const char*);
size_t strspn(const char*, const char*);
size_t strcspn(const char*, const char*);
int strcmp(const char*, const char*);
char* strupr(char*);
char* strlwr(char*);
