#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib_c/stdio.h"
#include "lib_c/string.h"

extern char cmd[255];
void cmd_run() 
{
	// [bjrkk] Simple standard library test.

	char* cmd_name = &cmd[0];
	char* cmd_args = &cmd[0];

	for (;; cmd_args++)
		if (*cmd_args == ' ')
		{
			*cmd_args = '\0';
			cmd_args++;
			break;
		}

	if (!strcmp(cmd_name, "ping"))
		printf("Pong!\n");
	else if (!strcmp(cmd_name, "echo"))
		printf("%s\n", cmd_args);
	else
		printf("Unimplemented command\n");
	

	printf("ran: %s (%s)\n", cmd_name, cmd_args);
}
