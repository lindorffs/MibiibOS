#ifndef KERNEL_H
#define KERNEL_H

#include <mibstd.h>

#define KERNEL_MAJOR 1
#define KERNEL_MINOR 1
#define KERNEL_V 5

u_int in_byte(d_u_int port);
void out_byte(d_u_int port, u_int data);
void io_sleep(int);

void panic(const char *str);

#endif
