#ifndef TTY_H
#define TTY_H

#include <mibstd.h>

void tty_init(u_int fore, u_int back);
void set_foreground(u_int fore);

void new_line(void);
void add_entry(unsigned const char entry);
void add_string(const char *string);

void remove_entry(void);

#endif
