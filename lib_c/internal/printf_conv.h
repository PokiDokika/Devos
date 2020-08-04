#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

char* __ntoa(unsigned long, unsigned char, bool, bool);
char* __ftoa(double, unsigned int, bool);