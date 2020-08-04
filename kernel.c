#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib_c/stdio.h"
#include "lib_c/string.h"
#include "keyboard.h" 
#include "shell.h"
#include "terminal.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
#define K_VERSION "0.01"
#define MAGIC_NUMBER 0xDEADBEEF

// [bjrkk] Probably should remove this later on :v
int generate_magic_number()
{
	char* time = __TIME__;
	char* date = __DATE__;

	int magic = 0;
	int data_idx = 0;

	for (; *time; time++)
	{
		magic ^= *time;
		for (int i = 0; i < 16; i++)
		{
			if (magic & 1)
				magic = (magic >> 1) ^ (date[++data_idx % 11] + magic * (i + 1));
			else
				magic >>= 1;
		}
	}

	return magic;
}

void kernel_main (void) {
	/* Initialize terminal interface */
	terminal_initialize();

	printf(
		"DevOS first version boot :)\nVersion %s, compiled on %s\nMagic number: 0x%08X", 
		K_VERSION, __DATE__, generate_magic_number()
	);

	shell();
}
