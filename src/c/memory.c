#include <memory.h>
#include <kernel.h>
#include <tty.h>

#define MAX_MEMORY_SPACE 1024
unsigned char *memorySpace[MAX_MEMORY_SPACE];
d_u_int last_assigned = 0;

#define MAX_ALLOCATION_UNITS 10
memoryAllocationUnit memoryUnits[MAX_ALLOCATION_UNITS];
u_int number_assigned = 0;

void *memset(void *target, d_u_int value, d_u_int size) {
	unsigned char *buffer_internal = (unsigned char *) target;
	for (d_u_int i = 0; i <= size; i++) {
		buffer_internal[i] = (unsigned char) value;
	}
	return target;
}

void *malloc(d_u_int size) {
	if (last_assigned + size > MAX_MEMORY_SPACE) {
		panic("MAX_MEMORY_SPACE reached!");
	}
	unsigned char *assigned = (void *) &memorySpace[last_assigned];
	last_assigned += size;

	memoryAllocationUnit memoryUnit;
	memoryUnit.data = assigned;
	memoryUnit.size = size;
	memoryUnit.start = last_assigned - size;
	memoryUnit.end = last_assigned;

	if (number_assigned < MAX_ALLOCATION_UNITS) {
		memoryUnits[number_assigned++] = memoryUnit;

		return assigned;
	} else {
		panic("MAX_ALLOCATION_UNITS reached!");
	}
	return 0;
}

void *memcpy(void *target, const void *source, d_u_int size, d_u_int start) {
	unsigned char *target_internal = (unsigned char *) target;
	const unsigned char *source_internal = (unsigned char *) source;
	for (d_u_int i = 0; i < size; i++) {
		target_internal[i+start] = source_internal[i];
	}
	return target;
}

int memcmp(const void *target_a, const void *target_b, d_u_int size) {
	const unsigned char *a_int = (const unsigned char *) target_a;
	const unsigned char *b_int = (const unsigned char *) target_b;
	for (d_u_int i = 0; i < size; i++) {
		if (a_int[i] < b_int[i]) {
			return -1;
		} else if (a_int[i] > b_int[i]) {
			return 1;
		}
	}
	return 0;
}

// Iterates through target and compares value to bytes in target
// returns 1 if all bytes match, 0 if not.
int memchk(const char *target, const unsigned char value, d_u_int size) {
	for (d_u_int i = size; i > 0; i--) {
		if (target[i] != value) {
			return 0;
		}
	}
	return 1;
}

int memory_init() {
	int returnVal = 1;
	add_string("[m] Clearing initial memory space\n");
	memset(memorySpace, NULL, MAX_MEMORY_SPACE);
	io_sleep(0x2ff);
	add_string("[m] Checking initial memory space\n");
	for (size_int i = 0; i + 10 <= MAX_MEMORY_SPACE; i += 10) {
		if (memorySpace[i] == 0) {
			if (i % 100 == 0) {
				add_string(".");
			}
		} else {
			add_string("!");
			returnVal = 0;
		}
		io_sleep(0x2fff);
	}

	return returnVal;
}
