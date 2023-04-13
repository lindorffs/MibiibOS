#ifndef KERNEL_H
#define KERNEL_H

#include <mibstd.h>

extern d_u_int *vga_buffer;
extern void vga_clear_buffer();

extern d_u_int tty_cursor;
extern void add_string();

extern void os_entry();
extern void new_line();
#endif
