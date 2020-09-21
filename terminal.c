#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "keyboard.h"
#include "terminal.h"
#include "lib_c/string.h"
#include "cpu/i386/cpudef.h"

// Devos terminal.

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_clear()
{
	terminal_row = 0;
	terminal_column = 0;

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_initialize (void) {
	terminal_color = vga_entry_color (VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	
	terminal_clear();
}

void update_cursor()
{
	uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;
 
	IO_Outb(0x3D4, 0x0F);
	IO_Outb(0x3D5, (uint8_t)(pos & 0xFF));
	IO_Outb(0x3D4, 0x0E);
	IO_Outb(0x3D5, (uint8_t)(pos >> 8));
}
 
void terminal_setcursorpos(int x, int y)
{
	terminal_column = x;
	terminal_row = y;

	update_cursor();
}

void terminal_setcursorindex(int i)
{
	terminal_column = i % VGA_WIDTH;
	terminal_row = i / VGA_WIDTH;

	update_cursor();
}

void terminal_setcolor (uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat (char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer [index] = vga_entry (c, color);
}
 
void terminal_newline () {
	if (++terminal_row == VGA_HEIGHT)
	{
		memcpy
		(
			terminal_buffer, 
			terminal_buffer + VGA_WIDTH, 
			VGA_WIDTH * VGA_HEIGHT * sizeof(terminal_buffer[0])
		);

		terminal_row--;
	}
	
	terminal_column = 0;
}

void terminal_putchar (char c) {
	if (c == '\n') 
	{
		terminal_newline(); 
		return;
	}
	
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_newline();
	}
}

void terminal_removechar () {
	terminal_putentryat (0, terminal_color, --terminal_column, terminal_row);
	if (terminal_column == 0) {
		terminal_column = VGA_WIDTH;
		if (--terminal_row == 0) {
			terminal_row = VGA_HEIGHT;
		}
	}	
}

void terminal_write(const char* data) {
	for (char data_c; (data_c = *data); data++)
		terminal_putchar(data_c);
}

void terminal_writen(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar (data [i]);
}