#include <memory.h>

void *memset(void *target, d_u_int value, int size) {
	unsigned char *buffer_internal = (unsigned char *) target;
	for (d_u_int i = 0; i < size; i++) {
		buffer_internal[i] = (unsigned char) value;
	}
	return target;
}

void *memcpy(void *target, const void *source, d_u_int size) {
	unsigned char *target_internal = (unsigned char *) target;
	const unsigned char *source_internal = (unsigned char *) source;
	for (d_u_int i = 0; i < size; i++) {
		target_internal[i] = source_internal[i];
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
