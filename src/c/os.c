#include <os.h>

#include <kernel.h>
#include <memory.h>
#include <keyboard.h>
#include <vga.h>
#include <tty.h>
#include <shell.h>

#define OS_VERSION "1.0.0"

char *username;

void os_print(char *string) {
	add_string(string);
}

char *os_get_user(void) {
	return username;
}

void os_entry(void) {
	io_sleep(0x0FFFFF);

	vga_clear_buffer(DARK_GREY);
	tty_init(CYAN, DARK_GREY);
	username = "";
	io_sleep(0x02FFFF);

	add_string("[o] Hand off from kernel received!\n");
	add_string("Username: ");
	username = get_input();

	shell_hook();
	return;
}
