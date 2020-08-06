#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

char* __ntoa(unsigned long, unsigned char, bool, bool);
char* __ftoa(double, unsigned int);

unsigned long __aton(char*);

size_t __strlen(const char* str);
char* __strcat(char*, const char*);
char* __strncat(char*, const char*, size_t);

char* __strstr(char*, char*);
char* __strcpy(char*, const char*);
size_t __strspn(const char*, const char*);
size_t __strcspn(const char*, const char*);

char* __strupr(char*);
char* __strlwr(char*);

int __strcmp(const char*, const char*);
