#include <keyboard.h>

#include <kernel.h>
#include <tty.h>

char get_input_keycode() {
	char ch = 0;
	while ((ch = in_byte(KEYBOARD_PORT)) != 0) {
		if (ch > 0) {
			return ch;
		}
	}
	return ch;
}

char *get_input() {
	char *output = "";
	int position = 0;
	char ch = 0x0;
	while (1 == 1) {
		ch = get_input_keycode();
		if (ch == KEY_ENTER) {
			output[position] = '\0';
			return output;
		} else {
			ch = keycode_to_char(ch);
			if (ch != NULL) {
				output[position++] = ch;
				add_entry(ch);
			}
		}
	}
}

char keycode_to_char(char keycode) {
	switch (keycode) {
		case KEY_A:
			return 'A';
		case KEY_B:
			return 'B';
		case KEY_C:
			return 'C';
		case KEY_D:
			return 'D';
		case KEY_E:
			return 'E';
		case KEY_F:
			return 'F';
		case KEY_G:
			return 'G';
		case KEY_H:
			return 'H';
		case KEY_I:
			return 'I';
		case KEY_J:
			return 'J';
		case KEY_K:
			return 'K';
		case KEY_L:
			return 'L';
		case KEY_M:
			return 'M';
		case KEY_N:
			return 'N';
		case KEY_O:
			return 'O';
		case KEY_P:
			return 'P';
		case KEY_Q:
			return 'Q';
		case KEY_R:
			return 'R';
		case KEY_S:
			return 'S';
		case KEY_T:
			return 'T';
		case KEY_U:
			return 'U';
		case KEY_V:
			return 'V';
		case KEY_W:
			return 'W';
		case KEY_X:
			return 'X';
		case KEY_Y:
			return 'Y';
		case KEY_Z:
			return 'Z';
		case KEY_SPACE:
			return ' ';
		default:
			return NULL;
	}
}
