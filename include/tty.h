#ifndef TTY_H
#define TTY_H

#include <mibstd.h>

#define TTY_WIDTH 80
#define TTY_HEIGHT 25

void tty_init(u_int fore, u_int back);
void tty_reinit(void);
void set_foreground(u_int fore);
void set_tty_cursor(u_int x, u_int y);

void new_line(void);
void add_entry(unsigned const char entry);
void add_string(const char *string);
void put_at(int x, int y, char c);
void put_string_at(int x, int y, char *c);

void remove_entry(void);

#endif
