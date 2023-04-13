#ifndef TTY_H
#define TTY_H

#include <mibstd.h>

extern d_u_int *vga_buffer;
extern d_u_int vga_mem();

enum tty_color {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        GREY,
        DARK_GREY,
        BRIGHT_BLUE,
        BRIGHT_GREEN,
        BRIGHT_CYAN,
        BRIGHT_RED,
        BRIGHT_MAGENTA,
        YELLOW,
        WHITE,
};

d_u_int tty_cursor = 0;
void new_line() {
	tty_cursor = (tty_cursor / 80 + 1) * 80;
}
void add_entry(unsigned char ch) {
	vga_buffer[tty_cursor++] = vga_mem(ch, CYAN, DARK_GREY);
}

void add_string(char *str) {
	u_int i = 0;
	char c = str[0];
	while (c != '\0') {
		if (c == '\n') {
			new_line();
		} else {
			add_entry(c);
		}
		i += 1;
		c = str[i];
	}
}



#endif
