#include <tty.h>
#include <vga.h>

q_u_int tty_cursor;

u_int foreground_color;
u_int background_color;

int tty_x = 0, tty_y = 0;

q_u_int tty_cursor_to_address() {
	return (tty_y * 80) + tty_x;
}

void set_tty_cursor(u_int x, u_int y) {
	if (x > TTY_WIDTH) {
		x = 0;
		y += 1;
	}
	if (y > TTY_HEIGHT) {
		y = 0;
		x = 0;
		tty_init(foreground_color, background_color);
	}
	tty_x = x;
	tty_y = y;
}

void set_tty_foreground(u_int color) {
	foreground_color = color;
}

void set_tty_background(u_int color) {
	background_color = color;
}

void tty_init(u_int fore, u_int back) {
	set_tty_cursor(0, 0);
	set_tty_foreground(fore);
	set_tty_background(back);
	vga_clear_buffer(background_color);
}

void put_at(int x, int y, char c) {
	int bk_x = tty_x;
	int bk_y = tty_y;
	set_tty_cursor(x, y);
	add_entry(c);
	set_tty_cursor(bk_x, bk_y);	
}

void put_string_at(int x, int y, char *string) {
	int bk_x = tty_x;
	int bk_y = tty_y;
	set_tty_cursor(x, y);
	add_string(string);
	set_tty_cursor(bk_x, bk_y);
}

void tty_reinit() {
	tty_init(foreground_color, background_color);
}

void new_line() {
	set_tty_cursor(0, tty_y+1);
}

void add_entry(unsigned const char entry) {
	if (entry == '\n') {
		new_line();
		return;
	}
	vga_set_mem(tty_cursor_to_address(), vga_mem(entry, foreground_color, background_color));
	set_tty_cursor(tty_x + 1, tty_y);
}
void remove_entry(void) {
	set_tty_cursor(tty_x - 1, tty_y);
	vga_set_mem(tty_cursor_to_address(), vga_mem(' ', foreground_color, background_color));
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
