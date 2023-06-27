#ifndef _UI_H_
#define _UI_H_

#include <mibstd.h>

struct Window {
	char *title;
	u_int width, height, x, y;
};

struct Window new_window(char *title, u_int x, u_int y, u_int width, u_int height);

void draw_window(struct Window window);

void window_add_string(struct Window window, u_int x, u_int y, char *string);

void os_ui(void);

#endif
