#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "keyboard.h"
// [bjrkk] Kill
#include "cpu/i386/cpudef.h"

uint8_t get_key () {
	uint8_t keycode = 0;
	// Check the keyboard status
	uint8_t status = IO_Inb(KEYBOARD_STATUS);
	if (status & 0x01) {
		while ((keycode = IO_Inb(KEYBOARD_PORT)) != 0) {
			if (keycode > 0)
			return keycode;
		}
  	}
	return keycode;
}

// This is horrible. If you can come up with a better method then please replace this.

/* 
[bjrkk] i gotcha fam

Once this kernel gets a functioning IDT, *use the keyboard interrupt instead.*
*/

#include "lib_c/stdio.h"

char get_char (uint8_t code) {
	static bool shift = false;

	if (code == 0x2A || code == 0xAA) 
		shift = !shift;

	// Key up detected, just return nothing.
	if (code & 0x80)
		return 0;

	if (shift)
		code += 90;

	return en_map[code];
}
