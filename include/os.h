#ifndef OS_H_
#define OS_H_

#include <mibstd.h>

#include <keyboard.h>

extern void sleep();
extern void panic();

extern d_u_int *vga_buffer;
extern void vga_clear_buffer();
extern d_u_int vga_mem;

extern void add_entry();
extern d_u_int tty_cursor;

extern char get_input_keycode();
#endif
