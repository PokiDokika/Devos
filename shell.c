#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib_c/stdio.h"
#include "terminal.h"
#include "command.h"
#include "keyboard.h"

// For handling inputs.
char cmd [255];
uint8_t index = 0;

void shell_command () { 
	/*
	[bjrkk] Redundancy...?

	printf("\n");
	printf(cmd);
	*/
	
	cmd_run (cmd);
}

void shell_putchar (char c) {
	cmd [index] = c;
	index++;
	terminal_putchar (c);
}

void shell_removechar () {
	if (index > 0) {
		index--;
		cmd [index] = 0;
		terminal_removechar ();
	}
}

void shell_newline () {
	print("\n");
	if (cmd [0] != '\0') {
		shell_command(cmd);
		for (uint8_t i = index; i > 0; i--) {cmd[i-1] = '\0';}
	}
	index = 0;
	printf ("\nDevos> ");
}

// Devos shell. 
void shell () {
	uint8_t key;
	shell_newline(cmd, index);
	for (;;) {
		key = get_key ();
		char c = get_char (key);
		switch (c) {
			case 0 		: break;
			case '\r' 	: shell_newline (); break;
			case '\b' 	: shell_removechar (); break;
			default   	: shell_putchar (c); break;
		}
	}
}
