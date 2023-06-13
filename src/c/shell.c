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

void shell_prompt() {
	os_print(">>> ");
}



void shell_hook() {
	os_print("[ MibiibOS ShieShell ]\n");
	shell_prompt();
	while (1 == 1) {
	}
}
