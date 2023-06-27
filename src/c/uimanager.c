#include <applications/uimanager.h>

#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <vga.h>
#include <tty.h>

extern struct Window osWin;

struct Window uiManagerWin;

void ui_manager_info(void) {
	window_add_string(uiManagerWin, 1, 4, "Control OS Window:");
	window_add_string(uiManagerWin, 1, 5, "setwin [x/y]");
	window_add_string(uiManagerWin, 1, 6, "setcolor [fore/back]");
}

void ui_manager_ui(void) {
	draw_window(uiManagerWin);
	ui_manager_info();
}

void ui_manager_color_set(int i) {
	char input[79];
	draw_window(uiManagerWin);
	window_add_string(uiManagerWin, 1, 4, "white");
	window_add_string(uiManagerWin, 1, 5, "blue");
	window_add_string(uiManagerWin, 1, 6, "green");
	window_add_string(uiManagerWin, 1, 7, "black");
	
	os_get_input(input);

	if (streq(input, "white") == 0) {
		if (i == 0) {
			set_tty_foreground(WHITE);
		} else {
			set_tty_background(WHITE);
		}
	} else if (streq(input, "blue") == 0) {
		if (i == 0) {
			set_tty_foreground(BLUE);
		} else {
			set_tty_background(BLUE);
		}

	} else if (streq(input, "green") == 0) {
		if (i == 0) {
			set_tty_foreground(GREEN);
		} else {
			set_tty_background(GREEN);
		}

	} else if (streq(input, "black") == 0) {
		if (i == 0) {
			set_tty_foreground(BLACK);
		} else {
			set_tty_background(BLACK);
		}
	}
}

int ui_manager(void) {
	char input[79];
	uiManagerWin = new_window("UI Manager", 20, 4, 30, 15);

	window_add_string(osWin, 1, 4, "uimanager launched.");

	while (streq(input, "quit") != 0) {
		os_ui();
		ui_manager_ui();
		os_get_input(input);

		if (streq(input, "setwin x") == 0) {
		os_ui();
		draw_window(osWin);
                window_add_string(osWin, 1, 3, "where?");
                os_get_input(input);
                u_int bx = osWin.x;
                osWin.x = atoi(input);
                draw_window(osWin);
                window_add_string(osWin, 1, 3, "here?");
                os_get_input(input);
                if (streq(input, "yes") != 0) {
                        osWin.x = bx;
                } else {
			os_ui();
		}
		} else if (streq(input, "setwin y") == 0) {
			os_ui();
			                draw_window(osWin);
                window_add_string(osWin, 1, 3, "where?");
                os_get_input(input);
                u_int by = osWin.y;
                osWin.y = atoi(input);
                draw_window(osWin);
                window_add_string(osWin, 1, 3, "here?");
                os_get_input(input);
                if (streq(input, "yes") != 0) {
                        osWin.y = by;
                } else {
			os_ui();
		}
		} else if (streq(input, "setcolor fore") == 0) {
			ui_manager_color_set(0);
			tty_reinit();
		} else if (streq(input, "setcolor back") == 0) {
			ui_manager_color_set(1);
		}
	}
	return 0;
}
