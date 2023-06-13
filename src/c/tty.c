#include <tty.h>

#include <vga.h>

q_u_int tty_cursor;

u_int foreground_color;
u_int background_color;

void tty_init(u_int fore, u_int back) {
	tty_cursor = 0;
	foreground_color = fore;
	background_color = back;
	vga_clear_buffer(background_color);
}

void new_line() {
	tty_cursor = (tty_cursor / 80 + 1) * 80;
}

void add_entry(unsigned char entry) {
	vga_set_mem(tty_cursor++, vga_mem(entry, foreground_color, background_color));
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
