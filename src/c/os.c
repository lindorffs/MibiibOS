#include <os.h>

#include <kernel.h>
#include <memory.h>
#include <keyboard.h>
#include <vga.h>
#include <tty.h>
#include <utils.h>

const char *songlol1 = "\ntwinkle twinkle little star\ntwinkle twinkle little star\nhow I wonder what you are.\n";
const char *songlol2 = "\nway up high\nin the sky\n";

void egg(const char *in) {
	for (u_int i = 0; i < strlen(in); i++) {
		add_entry(in[i]);
		io_sleep(0x02FFF8);
	}	
}

void os_shell() {
	while(1 == 1) {
		add_string("\n>>> ");
		char input[32];
		memset(input, NULL, 32);
		get_input(input, 32);
		if (streq(input, "/CLS") == 0) {
			tty_init(GREEN, BLACK);
		} else if (streq(input, "/TTLS") == 0) {
			egg(songlol1);
		} else if (streq(input, "/WUHIS") == 0) {
			egg(songlol2);
		} else if (streq(input, "/FULL") == 0) {
			egg(songlol1);
			egg(songlol1);
			egg(songlol2);
			egg(songlol1);
		}
	}
}

void os_print(char *string) {
	add_string(string);
}

void os_entry(void) {
	tty_init(GREEN, BLACK);
	os_print("[o] Hand off from kernel received!\n");

	os_shell();
}
