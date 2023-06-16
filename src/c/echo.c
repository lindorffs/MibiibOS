#include <builtins/echo.h>

#include <keyboard.h>
#include <os.h>
#include <tty.h>
#include <vga.h>

#include <memory.h>
#include <utils.h>


void echo_hook(void) {
	char data[32];

	os_print("<<< ");
	get_input(data, 32, 1);

	os_print("\n");
	os_print(data);
	os_print("\n");
}
