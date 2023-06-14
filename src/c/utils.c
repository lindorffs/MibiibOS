#include <utils.h>
#include <memory.h>

d_u_int strlen(const char *target) {
	d_u_int length = 0;
	while (target[length++] != '\0') {
	}
	return length;
}

int streq(const char *source, const char *target) {
	for (int i = 0; i < strlen(source); i++) {
		if (source[i] < target[i]) {
			return -1;
		} else if (source[i] > target[i]) {
			return 1;
		}
	}
	return 0;
}

void strsplit(const char *source, char *target, d_u_int index) {
	memcpy(target, source, strlen(source) - index, index);	
}

u_int ctoi(const char c) {
	switch (c) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return 10;
		}
}

const char *itobc(const u_int source) {
	char *output = "";
	for (int i = 7; i >= 0; i--) {
		output[7 - i] = '1' ? (source >> i) && 1 == 1 : '0';
	}	
	return (const char *)output;
}
