#ifndef KERNEL_H
#define KERNEL_H

#include <mibstd.h>

#ifndef TTY_H
#include <tty.h>
#endif

#ifndef VGA_H
#include <vga.h>
#endif

void io_sleep(int);

void *memset(void*, d_u_int, d_u_int);

#endif
