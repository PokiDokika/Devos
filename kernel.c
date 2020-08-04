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

void kernel_main (void) {
	/* Initialize terminal interface */
	terminal_initialize ();
	printf(
		"DevOS first version boot :)\nVersion %s, compiled on %s\nMagic number: %#0x", 
		K_VERSION, __DATE__, MAGIC_NUMBER
	);
	shell();
}
