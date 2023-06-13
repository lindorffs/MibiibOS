#include <utils.h>

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
