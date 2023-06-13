#include <keyboard.h>

#include <kernel.h>
#include <memory.h>
#include <tty.h>

char get_input_keycode(void) {
	char ch = 0;
	while ((ch = in_byte(KEYBOARD_PORT)) != 0) {
		if (ch > 0) {
			return ch;
		}
	}
	return ch;
}

void get_input(char *target, u_int max) {
	char final[max];
	u_int position = 0;
	char ch = 0x0;
	u_int running = 1;
	while (running == 1) {
		io_sleep(0x02ffff);
		ch = get_input_keycode();
		io_sleep(0x02ffff);
		if (ch == KEY_ENTER || position == max) {
			final[position] = '\0';
			running = 0;
		} else {
			if (ch == KEY_BACKSPACE) {
				final[--position] = '\0';
				remove_entry();
			}
			ch = keycode_to_char(ch);
			if (ch != NULL) {
				add_entry(ch);
				final[position++] = ch;
			}
		}
	}
	memcpy(target, (const char *) final, position,0);
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
		case KEY_FORESLASH:
			return '/';
		default:
			return NULL;
	}
}
