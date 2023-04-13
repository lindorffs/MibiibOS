#include <tty.h>

#include <vga.h>

d_u_int tty_cursor;

void tty_init() {
	tty_cursor = 0;
}

void new_line() {
	tty_cursor = (tty_cursor / 80 + 1) * 80;
}

void add_entry(unsigned char entry) {
	((d_u_int*)0xB8000)[tty_cursor++] = vga_mem(entry, CYAN, DARK_GREY);
}

void add_string(char *string) {
	u_int i = 0;
	char c = string[0];
	while (c != '\0') {
		if (c == '\n') {
			new_line();	
		} else {
			add_entry(c);
		}
		i += 1;
		c = string[i];
	}
}
