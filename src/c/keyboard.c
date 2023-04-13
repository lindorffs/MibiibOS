#include <keyboard.h>

char get_input_keycode() {
	char ch = 0;
	while ((ch = in_byte(KEYBOARD_PORT)) != 0) {
		if (ch > 0) {
			return ch;
		}
	}
	return ch;
}
