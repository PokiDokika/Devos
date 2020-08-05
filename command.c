#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib_c/stdio.h"
#include "lib_c/string.h"
#include "terminal.h"

// [bjrkk] FIXME: implement it as part of lib_c maybe?
unsigned long __aton(char* buffer)
{
    unsigned long buf_conversion = 0;

    for (; *buffer; buffer++)
    {
        char c = *buffer - '0';
        if (c < 0 || c > 9) continue;

        buf_conversion *= 10;
        buf_conversion += c;
    }

    return buf_conversion;
}

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
	else if (!strcmp(cmd_name, "clear") || !strcmp(cmd_name, "cls"))
		terminal_clear();
	else if (!strcmp(cmd_name, "fg"))
	{
		uint8_t new_color = (terminal_color & 0xF0) + (__aton(cmd_args) & 0x0F);
		terminal_setcolor(new_color);
	}
	else if (!strcmp(cmd_name, "bg"))
	{
		uint8_t new_color = (terminal_color & 0x0F) + ((__aton(cmd_args) & 0x0F) << 4);
		terminal_setcolor(new_color);
	}
	else
		printf("Unimplemented command\n");
	

	printf("ran: %s (%s)\n", cmd_name, cmd_args);
}
