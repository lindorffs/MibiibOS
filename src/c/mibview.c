#include <builtins/echo.h>

#include <mibstd.h>
#include <keyboard.h>
#include <os.h>
#include <tty.h>
#include <vga.h>

#include <memory.h>
#include <utils.h>

extern memoryAllocationUnit memoryUnits[];
extern u_int number_assigned;

void viewer_hook(void) {
	int num_target = 0;
	for (u_int i = 0; i < number_assigned; i++) {
		char number[5];
		itoa(i+1, number);
		os_print(number);
		os_print(": ");
		os_print((char *) memoryUnits[i].data);
		os_print("\n");
	}
	os_print("<<< ");
	char input[1];
	get_input(input, 1, 1);
	num_target = ctoi(input[0]) - 1;
	tty_init(BLUE, WHITE);
	os_print("~~~ MibView ~~~\n");
	os_print(memoryUnits[num_target].data);
	os_print("\n\nPRESS ANY KEY TO QUIT");
	get_input(NULL, 0, 0);
	tty_init(GREEN, BLACK);
}

