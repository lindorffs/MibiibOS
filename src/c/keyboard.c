#include <keyboard.h>

#include <kernel.h>

#include <tty.h>

u_int shift = 0;
char last_code = NULL;
char get_input_keycode(void) {
	char ret = kernel_in_byte(KEYBOARD_PORT);
	if (last_code == ret) {
		return NULL;
	}
	last_code = ret;
	return ret;
}

KeyEvent new_key_event(u_int key_code) {
	KeyEvent event;
	event.keycode = key_code;
	if (key_code == NULL) {
		event.flags = NULL;
		event.ascii = NULL;
	}
	else if (key_code <= KEY_PRESS_MAX) {
		event.flags = KEY_PRESSED;
		event.ascii = keycode_to_char(key_code); 
		if (event.keycode == KEY_LS_P || event.keycode == KEY_RS_P) {
			if (shift == 1) {
				event.keycode = event.keycode;
			}
			shift = 1;
		}
	} else {
		event.flags = KEY_RELEASED;
		event.ascii = keycode_to_char(key_code - 128);
		if (event.keycode == KEY_LS_R || event.keycode == KEY_RS_R) {
			shift = 0;
		}
	}
	return event;
}

KeyEvent get_key_event(void) {
	KeyEvent event = new_key_event(get_input_keycode());
	return event;
}

void get_input(char *target, d_u_int size) {
	u_int position = 0;
	u_int running = 1;
	KeyEvent keyPress;
	do {
		keyPress = get_key_event();
		if (keyPress.keycode == 0x1C + 128) {
			target[position] = '\0';
			running = 0;
		}
		if (keyPress.flags == KEY_RELEASED) {
			if (keyPress.keycode == 0x8E) {
				if (position - 1 >= 0) {
				target[position--] = '\0';
				remove_entry();
				}
			} else if (keyPress.ascii != NULL) {
				target[position] = keyPress.ascii;
				add_entry(target[position++]);
			}
			if (position + 1 >= size) {
				target[position] = '\0';
				running = 0;
			}
		}
	} while (running == 1);
}

char keycode_to_char(unsigned char keycode) {
	switch (keycode) {
		case KEY_1:
			if (shift) {
				return '!';
			}
			return '1';
		case KEY_2:
			if (shift) {
				return '@';
			}
			return '2';
		case KEY_3:
			if (shift) {
				return '#';
			}
			return '3';
		case KEY_4:
			if (shift) {
				return '$';
			}
			return '4';
		case KEY_5:
			if (shift) {
				return '%';
			}
			return '5';
		case KEY_6:
			if (shift) {
				return '^';
			}
			return '6';
		case KEY_7:
			if (shift) {
				return '&';
			}
			return '7';
		case KEY_8:
			if (shift) {
				return '*';
			}
			return '8';
		case KEY_9:
			if (shift) {
				return '(';
			}
			return '9';
		case KEY_0:
			if (shift) {
				return ')';
			}
			return '0';
		case KEY_DOT:
			return '.';
		case KEY_A_P:
			if (shift) {
				return 'A';
			}
			return 'a';
		case KEY_B_P:
			if (shift) {
				return 'B';
			}
		return 'b';
		case KEY_C_P:
			if (shift) {
				return 'C';
			}
			return 'c';
		case KEY_D_P:
			if (shift) {
				return 'D';
			}
			return 'd';
		case KEY_E_P:
			if (shift) {
				return 'E';
			}
			return 'e';
		case KEY_F_P:
                        if (shift) {
                                return 'F';
                        }
			return 'f';
		case KEY_G_P:
                        if (shift) {
                                return 'G';
                        }
			return 'g';
		case KEY_H_P:
                        if (shift) {
                                return 'H';
                        }
			return 'h';
		case KEY_I_P:
                        if (shift) {
                                return 'I';
                        }
			return 'i';
		case KEY_J_P:
                        if (shift) {
                                return 'J';
                        }
			return 'j';
		case KEY_K_P:
                        if (shift) {
                                return 'K';
                        }
			return 'k';
		case KEY_L_P:
                        if (shift) {
                                return 'L';
                        }
			return 'l';
		case KEY_M_P:
                        if (shift) {
                                return 'M';
                        }
			return 'm';
		case KEY_N_P:
                        if (shift) {
                                return 'N';
                        }
			return 'n';
		case KEY_O_P:
                        if (shift) {
                                return 'O';
                        }
			return 'o';
		case KEY_P_P:
                        if (shift) {
                                return 'P';
                        }
			return 'p';
		case KEY_Q_P:
                        if (shift) {
                                return 'Q';
                        }
			return 'q';
		case KEY_R_P:
                        if (shift) {
                                return 'R';
                        }
			return 'r';
		case KEY_S_P:
                        if (shift) {
                                return 'S';
                        }
			return 's';
		case KEY_T_P:
                        if (shift) {
                                return 'T';
                        }
			return 't';
		case KEY_U_P:
                        if (shift) {
                                return 'U';
                        }
			return 'u';
		case KEY_V_P:
                        if (shift) {
                                return 'V';
                        }
			return 'v';
		case KEY_W_P:
                        if (shift) {
                                return 'W';
                        }
			return 'w';
		case KEY_X_P:
                        if (shift) {
                                return 'X';
                        }
			return 'x';
		case KEY_Y_P:
                        if (shift) {
                                return 'Y';
                        }
			return 'y';
		case KEY_Z_P:
			if (shift) {
                                return 'Z';
                        }
			return 'z';
		case KEY_SPACE:
			return ' ';
		case KEY_FORESLASH:
			return '/';
		case KEY_COMMA:
			return ',';
		default:
			return NULL;
	}
}
