#pragma once

#include <stdarg.h>
#include <stddef.h>

/*
[bjrkk] FIXME:

    Return values for those should be changed to int
    according to the C standard.

    Early design flaws, oh well.
    ( or we could just make up our own standard :^) )

*/

void putc(int c);
void puts(const char* restrict text);

size_t printf(const char* restrict text, ...);
size_t sprintf(char* buffer, const char* restrict text, ...);
size_t snprintf(char* buffer, size_t max, const char* restrict text, ...);