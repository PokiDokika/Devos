#pragma once

#include <stdarg.h>
#include <stddef.h>

void putchar(int c);
size_t print(const char* restrict text);
size_t printf(const char* restrict text, ...);
size_t sprintf(char* buffer, const char* restrict text, ...);
size_t snprintf(char* buffer, size_t max, const char* restrict text, ...);