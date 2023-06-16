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

void set_foreground(u_int fore) {
	foreground_color = fore;
}

void tty_reinit() {
	tty_init(foreground_color, background_color);
}

void new_line() {
	tty_cursor = (tty_cursor / 80 + 1) * 80;
	if ((tty_cursor / 80) >= 25) {
		tty_reinit();
	}
}

void add_entry(unsigned const char entry) {
	if (entry == '\n') {
		new_line();
		return;
	}
	vga_set_mem(tty_cursor++, vga_mem(entry, foreground_color, background_color));
}
void remove_entry(void) {
	vga_set_mem(--tty_cursor, vga_mem(' ', foreground_color, background_color));
}

void add_string(const char *string) {
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
