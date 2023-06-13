#ifndef TTY_H
#define TTY_H

#include <mibstd.h>

void tty_init(u_int fore, u_int back);

void new_line();
void add_entry(unsigned char entry);
void add_string(char *string);

#endif
