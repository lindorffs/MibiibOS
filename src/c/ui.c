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
	window.c_x_i = 1;
	window.c_x = window.c_x_i;
	window.c_y_i = 3;
	window.c_y = window.c_y_i;
	window.width = width;
	window.height = height;
	window.background = BLACK;
	window.foreground = WHITE;
	
	return window;
}

d_u_int x_y_to_vga_address(u_int x, u_int y) {
	return (y * VGA_WIDTH) + x;
}

void draw_region(u_int x, u_int y, u_int width, u_int height, u_int foreground, u_int background) {
	d_u_int region_corner = vga_mem('/', background, foreground);
	d_u_int region_clear = vga_mem(' ', foreground, background);
	d_u_int region_border = vga_mem('#', background, foreground);
	for (u_int y_internal = y; y_internal < y + height; y_internal++) {
		for (u_int x_internal = x; x_internal < x + width ; x_internal++) {
			if (x_internal == x || x_internal == x + width - 1) {
				vga_set_mem(x_y_to_vga_address(x_internal, y_internal), region_border);
			} else if (y_internal == y || y_internal == y + height - 1) {
				vga_set_mem(x_y_to_vga_address(x_internal, y_internal), region_border);
			} else {
				vga_set_mem(x_y_to_vga_address(x_internal, y_internal), region_clear);
			}
		}
	}
	vga_set_mem(x_y_to_vga_address(x,y), region_corner);
}

void draw_window(struct Window *window) {
	draw_region(window->x, window->y, window->width, window->height, WHITE, BLACK);
	draw_region(window->x, window->y, window->width, 3, WHITE, BLACK);
	window_add_string_at(window, 1, 1, window->title);

	window->c_x = window->c_x_i;
	window->c_y = window->c_y_i;
}

q_u_int calculate_vga_offset(u_int start_x, u_int start_y, u_int x, u_int y) {
	return ( (start_y + y) * 80) + (start_x + x);
}

void window_put_at(struct Window *window, u_int x, u_int y, char c) {
	vga_set_mem(calculate_vga_offset(window->x, window->y, x, y), vga_mem(c, window->foreground, window->background));

}

void window_add_string_at(struct Window *window, u_int x, u_int y, char* string) {
	u_int initial_x = x;
	u_int initial_y = y;
	for (int i = 0; i < strlen(string); i++) {
		vga_set_mem(calculate_vga_offset(window->x, window->y, x++, y), vga_mem(string[i], window->foreground, window->background));
		if (x >= window->width - 1) {
			x = initial_x;
			y += 1;
		}
		if (y >= window->height - 1) {
			x = initial_x;
			y = initial_y;
		}
	}
	set_vga_cursor(window->x + x, window->y + y);
}

void window_add_string(struct Window *window, char *string) {
	memcpy(window->data[window->linecount++], string, strlen(string));
	window_add_string_at(window, window->c_x, window->c_y++, string);
}
