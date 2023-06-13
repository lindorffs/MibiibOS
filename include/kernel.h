#ifndef KERNEL_H
#define KERNEL_H

#include <mibstd.h>

#define MIN_BUFFER_SIZE 8
#define MAX_BUFFER_SIZE 128

#define KERNEL_VERSION "1.0.5"

char *malloc(int block_size);

u_int in_byte(d_u_int port);
void io_sleep(int);

void panic(char *str);

#endif
