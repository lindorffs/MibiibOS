#ifndef TTY_H
#define TTY_H

#include <mibstd.h>
#include <vga.h>

#define TTY_WIDTH VGA_WIDTH 
#define TTY_HEIGHT VGA_HEIGHT

void tty_init(u_int fore, u_int back);
void tty_reinit(void);
void set_tty_foreground(u_int fore);
void set_tty_background(u_int back);
void set_tty_cursor(u_int x, u_int y);
u_int get_tty_cursor_x();
u_int get_tty_cursor_y();


void new_line(void);
void add_entry(unsigned const char entry);
void add_string(const char *string);
void put_at(int x, int y, char c);
void put_string_at(int x, int y, char *c);
void border(u_int x_start, u_int y_start, u_int width, u_int height);
void region(u_int x_start, u_int y_start, u_int width, u_int height);

void remove_entry(void);

#endif
