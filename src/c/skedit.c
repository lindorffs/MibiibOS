#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <tty.h>

extern struct Window osWin;

int skedit(void) {
	struct Window window = new_window("sKediT", 30, 3, 30, 20);

	window_add_string(&osWin, "sKediT - Launched");
	draw_window(&window);

	char data[254];
	u_int data_length = 0;

	enable_vga_cursor();
	KeyEvent key;
        while (key.keycode != KEY_ESC && data_length < sizeof(data)) {
		data[data_length] = '\0';
		key = get_key_event();
		if (key.ascii != NULL && key.flags == KEY_RELEASED) {
			data[data_length++] = key.ascii;
			draw_window(&window);
			window_add_string(&window, data);
		}
	}

        return 0;
}
