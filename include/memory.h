#ifndef MEMORY_H
#define MEMORY_H

#include <mibstd.h>

typedef struct memoryAllocationUnit {
	void *data;
	d_u_int size;
	d_u_int start;
	d_u_int end;
} memoryAllocationUnit;


memoryAllocationUnit *get_allocation_by_id(u_int);
void *malloc(d_u_int);
void *memset(void *, d_u_int, d_u_int);
void *memcpy(void *, const void*, d_u_int, d_u_int);
int memcmp(const void *, const void *, d_u_int);
u_int get_allocation_count(void);
int memory_init(void);

#endif
