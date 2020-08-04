#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void shell_command();
void shell_putchar (char c);

void shell_removechar();

void shell_newline();
// Devos shell. 
void shell ();