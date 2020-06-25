#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.c"

/* this is really bad 
void cmd_run () {
	extern char cmd[255];
	printf ("\nran: "); printf (cmd);
} */

extern char cmd[255];
void cmd_run () {
	printf ("\nran: "); printf (cmd);
}
