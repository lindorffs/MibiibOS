#include <shell.h>
#include <tty.h>
#include <vga.h>
#include <kernel.h>
#include <memory.h>
#include <keyboard.h>
#include <os.h>
#include <utils.h>
#include <test.h>

void shell_error(char *input) {
	os_print("!!! ");
	os_print(input);
	os_print("\n");
}

char *shell_prompt() {
	const char *output;
	os_print(">>> ");
	output = get_input();
	os_print("\n");
	return output;
}


void shell_parser(const char *input) {
	if (streq(input, "TEST") == 0) {
		test_call();
	} else if (streq(input, "INFO") == 0) {
		os_print("MibiibKern V");
		os_print(KERNEL_VERSION);
		os_print("\nMibiibOS V");
		os_print(OS_VERSION);
		os_print("\nMibiibShieShell V");		
		os_print(SHELL_VERSION);
		os_print("\nUser: ");
		os_print(os_get_user());
		os_print("\n");
	} else {
		shell_error("Invalid input");
	}
}
void shell_hook() {
	char *input = "";
	vga_clear_buffer(BLACK);
	tty_init(GREEN, BLACK);
	io_sleep(0x02FFFF);
	os_print("[ MibiibOS ShieShell ]\n");
	io_sleep(0x02FFFF);

	do {
		io_sleep(0x02FFFF);

		input = shell_prompt();
		shell_parser(input);

		memset(input, NULL, strlen(input)+0);

		io_sleep(0x02FFFF);
	} while (1 == 1);
}
