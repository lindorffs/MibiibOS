#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <vga.h>
#include <tty.h>

int shell(void) {
	tty_init(WHITE, BLACK);
	struct Window window = new_window("q_shell", 0, 0, VGA_WIDTH, VGA_HEIGHT);

	window_add_string(&window, "q_shell");
	draw_window(&window);

	char input[79];

	enable_vga_cursor();
	while (streq(input, "quit") != 0) {
		set_tty_cursor(1, VGA_HEIGHT-2);
       		get_input(input, 79);
		window_add_string(&window, input);
		if (streq(input, "cls") == 0) {
			draw_window(&window);
		} else if (streq(input, "skedit.c") == 0) {
			skedit();
		} else if (streq(input, "ttt.game") == 0) {
			ttt();
		} else if (streq(input, "bytez.s") == 0) {
			bytes();
		} else {
			window_add_string(&window, "???");
		}
	}

        return 0;
}
