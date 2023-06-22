#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <kernel.h>

#define KEYBOARD_PORT 0x60

#define KEY_A_P 0x1E
#define KEY_B_P 0x30
#define KEY_C_P 0x2E
#define KEY_D_P 0x20
#define KEY_E_P 0x12
#define KEY_F_P 0x21
#define KEY_G_P 0x22
#define KEY_H_P 0x23
#define KEY_I_P 0x17
#define KEY_J_P 0x24
#define KEY_K_P 0x25
#define KEY_L_P 0x26
#define KEY_M_P 0x32
#define KEY_N_P 0x31
#define KEY_O_P 0x18
#define KEY_P_P 0x19
#define KEY_Q_P 0x10
#define KEY_R_P 0x13
#define KEY_S_P 0x1F
#define KEY_T_P 0x14
#define KEY_U_P 0x16
#define KEY_V_P 0x2F
#define KEY_W_P 0x11
#define KEY_X_P 0x2D
#define KEY_Y_P 0x15
#define KEY_Z_P 0x2C
#define KEY_LS_P 0x2A
#define KEY_RS_P 0x36

#define KEY_PRESS_MAX 0x58

#define KEY_A_R 0x9E 
#define KEY_B_R 0xB0
#define KEY_C_R 0xAE
#define KEY_D_R 0xA0
#define KEY_E_R 0x92
#define KEY_F_R 0xA1
#define KEY_G_R 0xA2
#define KEY_H_R 0xA3
#define KEY_I_R 0x97
#define KEY_J_R 0xA4
#define KEY_K_R 0xA5
#define KEY_L_R 0xA6
#define KEY_M_R 0xB2
#define KEY_N_R 0xB1
#define KEY_O_R 0x98
#define KEY_P_R 0x99
#define KEY_Q_R 0x90
#define KEY_R_R 0x93
#define KEY_S_R 0x9F
#define KEY_T_R 0x94
#define KEY_U_R 0x96
#define KEY_V_R 0xAF
#define KEY_W_R 0x91
#define KEY_X_R 0xAD
#define KEY_Y_R 0x95
#define KEY_Z_R 0xAC
#define KEY_LS_R 0xAA
#define KEY_RS_R 0xB6

#define KEY_SHIFT_FLAGS KEY_RS_R + KEY_LS_R + KEY_LS_P + KEY_RS_P

#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B
#define KEY_MINUS 0x0C
#define KEY_EQUAL 0x0D
#define KEY_SQUARE_OPEN_BRACKET 0x1A
#define KEY_SQUARE_CLOSE_BRACKET 0x1B
#define KEY_SEMICOLON 0x27
#define KEY_BACKSLASH 0x2B
#define KEY_COMMA 0x33
#define KEY_DOT 0x34
#define KEY_FORESLASH 0x35
#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x85
#define KEY_F12 0x86
#define KEY_BACKSPACE 0x0E
#define KEY_DELETE 0x53
#define KEY_DOWN 0x50
#define KEY_END 0x4F
#define KEY_ENTER 0x1C
#define KEY_ESC 0x01
#define KEY_HOME 0x47
#define KEY_INSERT 0x52
#define KEY_KEYPAD_5 0x4C
#define KEY_KEYPAD_MUL 0x37
#define KEY_KEYPAD_Minus 0x4A
#define KEY_KEYPAD_PLUS 0x4E
#define KEY_KEYPAD_DIV 0x35
#define KEY_LEFT 0x4B
#define KEY_PAGE_DOWN 0x51
#define KEY_PAGE_UP 0x49
#define KEY_PRINT_SCREEN 0x37
#define KEY_RIGHT 0x4D
#define KEY_SPACE 0x39
#define KEY_TAB 0x0F
#define KEY_UP 0x48

typedef struct KeyEvent {
	u_int flags;
#define KEY_PRESSED 0b1
#define KEY_RELEASED 0b10
	u_int keycode;
	char ascii;
} KeyEvent;

char get_input_keycode(void);

KeyEvent get_key_event(void);

void get_input(char *, d_u_int);

char keycode_to_char(unsigned char);

#endif
