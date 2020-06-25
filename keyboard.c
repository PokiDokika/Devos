#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "keyboard.h"

// Reads and returns data from the keyboard
static inline uint8_t inb (uint16_t port) {
	uint8_t data;
	asm volatile ("inb %1, %0" : "=a"(data) : "Nd" (port));
	return data;
}

uint8_t get_key () {
	uint8_t keycode = 0;
	// Check the keyboard status
	uint8_t status = inb (KEYBOARD_STATUS);
	if (status & 0x01) {
		while ((keycode = inb (KEYBOARD_PORT)) != 0) {
			if (keycode > 0)
			return keycode;
		}
  	}
	return keycode;
} 

// This is horrible. If you can come up with a better method then please replace this.
char get_char (uint8_t code) {
	switch (code) {
		case KEY_A : return 'a';
		case KEY_B : return 'b';
		case KEY_C : return 'c';
		case KEY_D : return 'd';
		case KEY_E : return 'e';
		case KEY_F : return 'f';
		case KEY_G : return 'g';
		case KEY_H : return 'h';
		case KEY_I : return 'i';
		case KEY_J : return 'j';
		case KEY_K : return 'k';
		case KEY_L : return 'l';
		case KEY_M : return 'm';
		case KEY_N : return 'n';
		case KEY_O : return 'o';
		case KEY_P : return 'p';
		case KEY_Q : return 'q';
		case KEY_R : return 'r';
		case KEY_S : return 's';
		case KEY_T : return 't';
		case KEY_U : return 'u';
		case KEY_V : return 'v';
		case KEY_W : return 'w';
		case KEY_X : return 'x';
		case KEY_Y : return 'y';
		case KEY_Z : return 'z';
            
           	case KEY_0 : return '0';
           	case KEY_1 : return '1';
		case KEY_2 : return '2';
		case KEY_3 : return '3';
           	case KEY_4 : return '4';
            	case KEY_5 : return '5';
            	case KEY_6 : return '6';
            	case KEY_7 : return '7';
            	case KEY_8 : return '8';
            	case KEY_9 : return '9';


            	case KEY_SPACE: return ' ';
            	case KEY_DOT: return '.';
            	case KEY_COMMA: return ',';
            	case KEY_SEMICOLON: return ';';
           	case KEY_EQUAL : return '=';
            	case KEY_DASH : return '-';
            	case KEY_FORESLASH : return '/';
            	case KEY_BACKSLASH : return '\\';
            	case KEY_SQUARE_OPEN_BRACKET : return '[';
            	case KEY_SQUARE_CLOSE_BRACKET : return ']';
            	case KEY_APOSTROPHE : return '\'';
            	case KEY_TILDE : return '~';

            	case KEY_ENTER : return '\r';
            	case KEY_BACKSPACE : return '\b';
            	case KEY_DELETE : return '\e';

            	default : return 0;
	}
}
