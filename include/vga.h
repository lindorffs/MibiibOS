#ifndef VGA_H
#define VGA_H

#include <mibstd.h>

#define VGA_ADDRESS 0xB8000
#define VGA_BUFFER_SIZE 2200

#define VGA_CTRL 0x3D4
#define VGA_DATA 0x3D5
#define VGA_OFFSET_LOW 0x0F
#define VGA_OFFSET_HIGH 0x0E

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

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

void vga_clear_buffer(u_int color);
void vga_set_mem(q_u_int mem_pos, d_u_int vga_mem);
void set_vga_cursor(u_int x, u_int y);
void disable_vga_cursor();
d_u_int vga_mem(unsigned char ch, u_int foreground, u_int background);

#endif
