#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <tty.h>

extern struct Window osWin;

int bytes(void) {
	struct Window window = new_window("byteZ", 0, 0, 30, 20);

	window_add_string(&osWin, "byteZ - Launched");
	draw_window(&window);

	char input[79];

        while (streq(input, "quit") != 0) {
		set_tty_cursor(1, TTY_HEIGHT-2);
                get_input(input, 79);
		
		draw_window(&window);
		if (streq(input, "getcur") == 0) {
			d_u_int pos = 0;
			kernel_out_byte(0x3D4, 0x0F);
			pos |= kernel_in_byte(0x3D5);
			kernel_out_byte(0x3D4, 0x0E);
			pos |= ((d_u_int)kernel_in_byte(0x3D5)) << 8;
			window_add_string(&window, itoa(pos, (char*)NULL));
		} else if (streq(input, "kecho") == 0) {
			window_add_string(&window, "Sending Keyboard Echo 0xEE");
			kernel_out_byte(KEYBOARD_PORT, 0xEE);
			window_add_string(&window, "Reading Keyboard Response");
			unsigned char byte = kernel_in_byte(KEYBOARD_PORT);
			if (byte == 0xFE) {
				window_add_string(&window, "Got Resend");
			} else if (byte == 0xEE) {
				window_add_string(&window, "Got Echo");
			}
		}
	}

        return 0;
}
