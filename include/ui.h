#ifndef _UI_H_
#define _UI_H_

#include <mibstd.h>

struct Window {
	char *title;
	u_int width, height, x, y;
	u_int c_x, c_y, c_x_i, c_y_i;
	u_int foreground, background;
	char *data[32];
	u_int linecount;
};

struct Window new_window(char *title, u_int x, u_int y, u_int width, u_int height);

void draw_window(struct Window *window);

void window_add_string_at(struct Window *window, u_int x, u_int y, char *string);

void window_add_string(struct Window *window, char *string);

void os_ui(void);

#endif
