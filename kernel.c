#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.c"
#include "keyboard.c" 
#include "shell.c"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 

void kernel_main (void) {
	/* Initialize terminal interface */
	terminal_initialize ();
 
	printf ("DevOS first version boot :)\nVersion 0.01");
	shell ();
}
