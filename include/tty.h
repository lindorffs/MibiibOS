#ifndef TTY_H
#define TTY_H

#include <mibstd.h>

void tty_init();

void new_line();
void add_entry(unsigned char entry);
void add_string(char *string);

#endif
