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

void *specialMemCpy(void *target, const char *source, size_int start, size_int stop) {
	unsigned char *target_internal = (unsigned char*)target;
	const unsigned char *source_internal = (const unsigned char*)source;
	for (size_int i = start; i < stop && i < 0xFFFFFFFF; i++) {
		target_internal[i] = source_internal[i];
	}
	return target;
}

void strsplit(const char *source, char *target_l, char* target_r, char split) {
	for (size_int i = 0; i < strlen(source); i++) {
		if (source[i] == split) {
			specialMemCpy(target_l, source, 0, i);
			specialMemCpy(target_r, source, i+1, strlen(source));
		}
	}
	specialMemCpy(target_l, source, 0, strlen(source));	
	specialMemCpy(target_r, source, 0, strlen(source));	
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

void reverse(char *str, d_u_int length) {
	d_u_int start = 0;
	d_u_int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}
}

char *itoa(q_u_int number, char *output) {
	int i = 0;
	if (number == 0) {
		output[i++] = '0';
	}	
	while (number > 0) {
		int remainder = number % (10);
		number = number / 10;
		output[i++] = remainder + '0';
	}
	reverse(output, i);
	output[i] = '\0';
	return output;
}
