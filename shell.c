#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.c"

// Devos shell. 

void shell () {
	uint8_t k;
	char cmd [255];
	uint8_t index = 0;
	shell_newline (cmd,index);
	while (1) {
		k = get_key ();
		char c = get_char (k);
		switch (c) {
			case 0 : break;
			case '\r' : shell_newline (cmd,index); index = 0; break;
			case '\b' : shell_removechar (cmd, index); break;
			default : shell_putchar (cmd, index, c); break;
		}
	}
}

// For handling inputs.

void shell_command (char* cmd) { 
	printf ("\n");
	printf (cmd);
}

void shell_putchar (char* cmd, uint8_t index, char c) {
	cmd [index] = c;
	index++;
	terminal_putchar (c);
}

void shell_removechar (char* cmd, uint8_t index) {
	printf (index);
//	if (index > 0) {
		index--;
		cmd [index] = 0;
		terminal_removechar ();
//	}
}

void shell_newline (char* cmd, uint8_t index) {
	if (cmd [0] != '\0') {
		shell_command(cmd);
		for (uint8_t i = index; i > 0; i--) {cmd[i-1] = '\0';}
	}
	printf ("\nDevos> ");
}
