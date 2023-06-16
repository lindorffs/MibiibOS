#include <keyboard.h>

#include <kernel.h>
#include <memory.h>
#include <tty.h>

u_int shift = 0;
char get_input_keycode(void) {
	unsigned char ch = 0;
	ch = in_byte(KEYBOARD_PORT);
	if (ch == 0x2A || ch == 0x36) {
		if (shift == 0) {
			shift = 1;
		}
		return NULL;
	}
	if (ch == 0xAA || ch == 0xB6) {
		if (shift == 1) {
			shift = 0;
		}
		return NULL;
	}
	if (ch >= 0x01 && ch <= 0x58) {
		return ch;
	} 
	return NULL;
}

void get_input(char *target, u_int max, int display) {
	char final[max];
	u_int position = 0;
	char ch = 0x0;
	u_int running = 1;
	while (running == 1) {
		io_sleep(0x2FFFF);
		ch = get_input_keycode();
		if (ch == NULL) {
		
		} else if ((ch == KEY_ENTER) || position >= max) {
			final[position] = '\0';
			running = 0;
			io_sleep(0x2FFFF);
		} else if (ch == KEY_BACKSPACE && position >= 1) {
			final[--position] = '\0';
			remove_entry();
		} else {
			char new = keycode_to_char(ch, shift);
			if (new != NULL) {
				if (display) {
					add_entry(new);
				} else {
					add_entry('*');
				}
				final[position++] = new;
			}
		}
	}
	memcpy(target, (const char *) final, max,0);
}

char keycode_to_char(unsigned char keycode, u_int flags) {
	switch (keycode) {
		case KEY_1:
			if (flags) {
				return '!';
			}
			return '1';
		case KEY_2:
			if (flags) {
				return '@';
			}
			return '2';
		case KEY_3:
			if (flags) {
				return '#';
			}
			return '3';
		case KEY_4:
			if (flags) {
				return '$';
			}
			return '4';
		case KEY_5:
			if (flags) {
				return '%';
			}
			return '5';
		case KEY_6:
			if (flags) {
				return '^';
			}
			return '6';
		case KEY_7:
			if (flags) {
				return '&';
			}
			return '7';
		case KEY_8:
			if (flags) {
				return '*';
			}
			return '8';
		case KEY_9:
			if (flags) {
				return '(';
			}
			return '9';
		case KEY_0:
			if (flags) {
				return ')';
			}
			return '0';
		case KEY_DOT:
			return '.';
		case KEY_A_P:
			if (flags) {
				return 'A';
			}
			return 'a';
		case KEY_B_P:
			if (flags) {
				return 'B';
			}
		return 'b';
		case KEY_C_P:
			if (flags) {
				return 'C';
			}
			return 'c';
		case KEY_D_P:
			if (flags) {
				return 'D';
			}
			return 'd';
		case KEY_E_P:
			if (flags) {
				return 'E';
			}
			return 'e';
		case KEY_F_P:
                        if (flags) {
                                return 'F';
                        }
			return 'f';
		case KEY_G_P:
                        if (flags) {
                                return 'G';
                        }
			return 'g';
		case KEY_H_P:
                        if (flags) {
                                return 'H';
                        }
			return 'h';
		case KEY_I_P:
                        if (flags) {
                                return 'I';
                        }
			return 'i';
		case KEY_J_P:
                        if (flags) {
                                return 'J';
                        }
			return 'j';
		case KEY_K_P:
                        if (flags) {
                                return 'K';
                        }
			return 'k';
		case KEY_L_P:
                        if (flags) {
                                return 'L';
                        }
			return 'l';
		case KEY_M_P:
                        if (flags) {
                                return 'M';
                        }
			return 'm';
		case KEY_N_P:
                        if (flags) {
                                return 'N';
                        }
			return 'n';
		case KEY_O_P:
                        if (flags) {
                                return 'O';
                        }
			return 'o';
		case KEY_P_P:
                        if (flags) {
                                return 'P';
                        }
			return 'p';
		case KEY_Q_P:
                        if (flags) {
                                return 'Q';
                        }
			return 'q';
		case KEY_R_P:
                        if (flags) {
                                return 'R';
                        }
			return 'r';
		case KEY_S_P:
                        if (flags) {
                                return 'S';
                        }
			return 's';
		case KEY_T_P:
                        if (flags) {
                                return 'T';
                        }
			return 't';
		case KEY_U_P:
                        if (flags) {
                                return 'U';
                        }
			return 'u';
		case KEY_V_P:
                        if (flags) {
                                return 'V';
                        }
			return 'v';
		case KEY_W_P:
                        if (flags) {
                                return 'W';
                        }
			return 'w';
		case KEY_X_P:
                        if (flags) {
                                return 'X';
                        }
			return 'x';
		case KEY_Y_P:
                        if (flags) {
                                return 'Y';
                        }
			return 'y';
		case KEY_Z_P:
			if (flags) {
                                return 'Z';
                        }
			return 'z';
		case KEY_SPACE:
			return ' ';
		case KEY_FORESLASH:
			return '/';
		default:
			return NULL;
	}
}
