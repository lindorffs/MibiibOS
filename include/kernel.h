#ifndef KERNEL_H
#define KERNEL_H

#include <mibstd.h>

#define KERNEL_MAJOR 1
#define KERNEL_MINOR 1
#define KERNEL_VERSION 6 
#define KERNEL_STRING "Leapure"

#define sizeof(type) (size_int)((char *)(&type+1)-(char*)(&type))

u_int kernel_in_byte(d_u_int port);
void kernel_out_byte(d_u_int port, u_int data);
void kernel_io_sleep(size_int);
void kernel_panic(const char *str);
void *memcpy(void *target, const void *source, size_int size);
#endif
