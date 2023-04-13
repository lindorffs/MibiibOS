#ifndef VGA_H
#define VGA_H

#include "mibstd.h"

#define VGA_ADDRESS 0xB8000
#define VGA_BUFFER_SIZE 2200
#define VGA_WIDTH 80

d_u_int *vga_buffer;
d_u_int vga_buffer_position;

enum vga_color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE,
};

void vga_clear_buffer(d_u_int **buffer);
d_u_int vga_mem(unsigned char ch, u_int foreground, u_int background);

#endif
