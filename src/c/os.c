#include <os.h>

#include <kernel.h>
#include <keyboard.h>
#include <vga.h>
#include <tty.h>
#include <utils.h>
#include <ui.h>

extern unsigned char osSpace[];
extern unsigned char userSpace[];

extern void _stop(void);

extern struct Window osWin;

void os_get_input(char input[79]) {
	set_tty_cursor(1, TTY_HEIGHT-2);
	region(1, TTY_HEIGHT-2, TTY_WIDTH-2, 1);
	get_input(input, 79);
}
int shell_prompt(int p) {
	if (p == 0) {
		draw_window(osWin);
		window_add_string(osWin, 1, 3, "Enter command...");
	}
	char input[79];
	os_get_input(input);
	if (streq(input, "panic") == 0) {
			userSpace[0x101] = 'p';
	} else if (streq(input, "shutdown") == 0) {
			userSpace[0x101] = 's';
	} else if (streq(input, "ttt")==0) {
			userSpace[0x101] = 't';
	} else if (streq(input, "uimanager")==0) {
			userSpace[0x101] = 'u';
	}
	else {
		p = !p;
	}

	return p;
}

void tview(void) {
	tty_init(YELLOW, BLACK);
	border(0, 0, TTY_WIDTH, 3);
	
	put_string_at((TTY_WIDTH)/2 - (strlen("T-View")/2), 1, "T-View");

	u_int turn = 0;
	u_int last_turn = 0;
	
	unsigned char board[9] = {NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL};

	while (turn != 12) {
		char input[6];
		border(0, TTY_HEIGHT-3, TTY_WIDTH, 3);
		region(1, TTY_HEIGHT-2, TTY_WIDTH-2, 1);
		get_input(input, 6);
		if (streq(input, "quit") == 0) {
			turn = 12;
		}
	}
}
	
void os_init(void) {
	osWin = new_window("MibiibTerm", 4,4, 30, 12);
	os_ui();
	draw_window(osWin);
	int ret = shell_prompt(0);

	while (1==1) {
		os_ui();
		draw_window(osWin);
		if (userSpace[0x101] == 'p') {
			kernel_panic("!!!");
			osSpace[0x1] = 'p';
			userSpace[0x101] = NULL;
		} else if (userSpace[0x101] == 's') {
			osSpace[0x1] = 's';
			userSpace[0x101] = NULL;
		} else if (userSpace[0x101] == 't') {
			window_add_string(osWin, 1, 3, "Launching TikTaks");
			ret = ttt_launcher();
			osSpace[0x11] = 'r';
			userSpace[0x101] = NULL;
		} else if (userSpace[0x101] == 'u') {
			ret = ui_manager();
			osSpace[0x11] = 'r';
			userSpace[0x101] = NULL;
		} else {
			window_add_string(osWin, 1, 3, "panic");
			window_add_string(osWin, 1, 4, "shutdown");
			window_add_string(osWin, 1, 5, "ttt");
		}
	

		if (osSpace[0x1] == 'p') {
			osSpace[0x1] = NULL;
			osSpace[0x100] = 'p';
			call_kset();
		} else if (osSpace[0x1] == 's') {
			osSpace[0x1] = NULL;
			osSpace[0x100] = 's';
			call_kset();
		}

		if (osSpace[0x11] == 'r') {
			os_ui();
			draw_window(osWin);
			osSpace[0x11] = NULL;
		}
		ret = shell_prompt(ret);
	}
	_stop();
}
