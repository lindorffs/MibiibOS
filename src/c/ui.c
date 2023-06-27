#include <ui.h>

#include <tty.h>
#include <vga.h>
#include <utils.h>
#include <os.h>

struct Window osWin;

struct Window new_window(char *title, u_int x, u_int y, u_int width, u_int height) {
	struct Window window;
	window.title = title;
	window.x = x;
	window.y = y;
	window.width = width;
	window.height = height;
	
	return window;
}

void draw_window(struct Window window) {
	region(window.x, window.y, window.width, window.height);
	border(window.x, window.y, window.width, window.height);
	border(window.x, window.y, window.width, 3);
	put_string_at(window.x, window.y, "/");

	window_add_string(window, 1,1, window.title);
}

void window_add_string(struct Window window, u_int x, u_int y, char *string) {
	put_string_at(window.x+x, window.y+y, string);
}

void os_ui(void) {
	tty_reinit();
        border(0, 0, TTY_WIDTH, 3);
        set_tty_cursor(1,1);
        add_string("Version: ");
        add_string(itoa(OS_MAJOR, (char*)NULL));
        add_entry('.');
        add_string(itoa(OS_MINOR, (char*)NULL));
        add_entry('.');
        add_string(itoa(OS_V, (char*)NULL));
        add_entry(' ');
        add_string(OS_VERSION);

        put_string_at((TTY_WIDTH)/2 - (strlen("MibiibOS")/2), 1, "MibiibOS");

        border(0, TTY_HEIGHT-3, TTY_WIDTH, 3);
	draw_window(osWin);
}

