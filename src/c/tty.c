#include <tty.h>

#include <vga.h>
#include <memory.h>

q_u_int tty_cursor;

u_int foreground_color;
u_int background_color;

char *tty_buffer_a, *tty_buffer_b, *current_tty;
q_u_int tty_a_cursor = 0, tty_b_cursor = 0;

void tty_init(u_int fore, u_int back) {
	foreground_color = fore;
	background_color = back;
	vga_clear_buffer(background_color);
	dump_buffer();
}

void tty_clear(void) {
	tty_cursor = 0;
	memset(current_tty, NULL, 2001);
	dump_buffer();
}

void swap_tty(void) {
	if (current_tty == tty_buffer_a) {
		tty_a_cursor = tty_cursor;
		current_tty = tty_buffer_b;
	} else {
		tty_b_cursor = tty_cursor;
		current_tty = tty_buffer_a;
	}
}

void set_foreground(u_int fore) {
	foreground_color = fore;
}

void tty_reinit() {
	tty_init(foreground_color, background_color);
}

void new_line() {
	tty_cursor = (tty_cursor / 80 + 1) * 80;
}

void dump_buffer(void) {
	q_u_int draw_cursor = 0;
	for (q_u_int i = 0; i < tty_cursor; i++) {
		if (current_tty[i] == '\n') {
			draw_cursor += (draw_cursor / 80 + 1) * 80;
		} else {
			vga_set_mem(draw_cursor, vga_mem(current_tty[i], foreground_color, background_color));
			draw_cursor += 1;
		}
	}
}

void add_entry(unsigned const char entry) {
	if (entry == '\n') {
		new_line();
		return;
	}
	current_tty[tty_cursor++] = entry;
	dump_buffer();
}

void remove_entry(void) {
	current_tty[--tty_cursor] = ' ';
	vga_set_mem(tty_cursor, vga_mem(' ', foreground_color, background_color));
	dump_buffer();
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
