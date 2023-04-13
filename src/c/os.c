#include <os.h>

#include <vga.h>
#include <keyboard.h>

void shell_hook(void) {
	u_int count = 0;
	char in_key = 1;
	char last_key = 0;
	vga_clear_buffer();
	tty_init();
	add_string("[ MibiibOS ShieShell ]\n");
	add_string("Esc - Exit Shell\n");
	add_string(" P  - Shutdown\n");
	do {
		in_key = get_input_keycode();
		if (last_key == in_key) {
			io_sleep(0x0FFFFF);
		} else {
			switch (in_key) {
				case KEY_P:
					panic("Shutdown");
					break;
				default:
					break;
			}
			last_key = in_key;
		}
		io_sleep(0x0FFFFF);
	} while (in_key != KEY_ESC);
	return;
}

void os_entry(void) {
	vga_clear_buffer();
	tty_init();
	io_sleep(0xFFFFFF);
	add_string("[o] Hand off from kernel received!\n");
	add_string(">> Welcome User. Press space to begin.\n");

	do {
		io_sleep(0x02FFFF);
	} while (get_input_keycode() != KEY_SPACE);

	shell_hook();
	return;
}
