#ifndef MEMORY_H
#define MEMORY_H

#include <mibstd.h>

void *memset(void *, d_u_int, int);
void *memcpy(void *, const void*, d_u_int);
int memcmp(const void *, const void *, d_u_int);

#endif
