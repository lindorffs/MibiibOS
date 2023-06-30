#include <applications/uimanager.h>

#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <vga.h>
#include <tty.h>

extern struct Window osWin;

struct Window uiManagerWin;

void ui_manager_info(void) {
	window_add_string(&uiManagerWin, "MibiibTerm:");
	window_add_string(&uiManagerWin,"setwin [x/y]");
	window_add_string(&uiManagerWin, "");
	window_add_string(&uiManagerWin, "TTY Settings");
	window_add_string(&uiManagerWin, "setcolor [fore/back]");
	window_add_string(&uiManagerWin, "");
	window_add_string(&uiManagerWin, "VGA:");
	window_add_string(&uiManagerWin, "enable/disable cursor");
}

void ui_manager_ui(void) {
	draw_window(&uiManagerWin);
	ui_manager_info();
}

void ui_manager_color_set(int i) {
	char input[79];
	draw_window(&uiManagerWin);
	window_add_string(&uiManagerWin, "white");
	window_add_string(&uiManagerWin, "blue");
	window_add_string(&uiManagerWin, "green");
	window_add_string(&uiManagerWin, "black");
	
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

	window_add_string(&osWin, "uimanager launched.");

	while (streq(input, "quit") != 0) {
	}
	return 0;
}
