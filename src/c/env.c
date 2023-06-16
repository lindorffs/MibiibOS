#include <builtins/env.h>

#include <os.h>
#include <keyboard.h>
#include <tty.h>
#include <vga.h>
#include <utils.h>

void env_hook(void) {
	char input[2];
	int selection = 0;
	os_print("1 - red\n2 - green\n3 - white\n");
	get_input(input, 1, 1);
	selection = ctoi(input[0]);
	if (selection == 1) {
		set_foreground(RED);
	} else if (selection == 2) {
		set_foreground(GREEN);
	} else {
		set_foreground(WHITE);
	}
	os_print("\nDone.\n");
}
