#include <os.h>

#include <kernel.h>
#include <keyboard.h>
#include <vga.h>
#include <tty.h>
#include <utils.h>

extern unsigned char osSpace[];
extern unsigned char userSpace[];

void border(int x_start, int y_start, int width, int height) {
	for (int y = y_start; y < y_start + height; y++) {
		for (int x = x_start; x < x_start + width; x++) {
			if (y == y_start || y == y_start + height - 1) {
				put_at(x, y, '#');
			} else if (x == x_start || x == x_start + width - 1) {
				put_at(x, y, '#');
			}
		}
	}
}
void region(int x_start, int y_start, int width, int height) {
	for (int y = y_start; y < y_start + height; y++) {
		for (int x = x_start; x < x_start + width; x++) {
			put_at(x, y, ' ');
		}
	}
}



extern void _stop(void);


void os_get_input(char input[79]) {
	set_tty_cursor(1, TTY_HEIGHT-2);
	region(1, TTY_HEIGHT-2, TTY_WIDTH-2, 1);
	get_input(input, 79);
}

void os_ui(void) {
	tty_init(BLUE, WHITE);
	border(0, 0, TTY_WIDTH, 3);
	set_tty_cursor(1,1);
	add_string("Version: ");
	add_string(itoa(OS_MAJOR, (char*)NULL));
	add_entry('.');
	add_string(itoa(OS_MINOR, (char*)NULL));
	add_entry('.');
	add_string(itoa(OS_V, (char*)NULL));
	add_entry(' ');
	add_string(OS_VERSION);

	put_string_at((TTY_WIDTH)/2 - (strlen("MibiibOS")/2), 1, "MibiibOS");

	put_string_at((TTY_WIDTH)/2 - (strlen("Would you like to play a game?")/2), TTY_HEIGHT/2, "Would you like to play a game?");

	border(0, TTY_HEIGHT-3, TTY_WIDTH, 3);
}


int shell_prompt(void) {
	char input[79];
	os_get_input(input);
	if (streq(input, "/quit") == 0) {
		return 0;
	}
	if (streq(input, "/run") == 0) {
		put_string_at(1, 3, "Enter the following commands to run the described action.");
		put_string_at(1, 4, "panic - triggers a panic");
		put_string_at(1, 5, "shutdown - triggers a shutdown");
		put_string_at(1, 6, "ttt - tic-tac-toe");
		os_get_input(input);
		if (streq(input, "panic") == 0) {
			userSpace[0x101] = 'p';
		} else if (streq(input, "shutdown") == 0) {
			userSpace[0x101] = 's';
		} else if (streq(input, "ttt")==0) {
			userSpace[0x101] = 't';
		}
	}

	return 1;
}

void render_board(u_int x, u_int y, unsigned char values[9]) {
	u_int indexer = 0;
	put_string_at(x,y-1," 1 2 3 ");
	put_string_at(x-1,y+1,"1");
	put_string_at(x-1,y+3,"2");
	put_string_at(x-1,y+5,"3");
	for (u_int y_internal = y; y_internal < y + 7; y_internal++) {
		for (u_int x_internal = x; x_internal < x + 7; x_internal++) {
			if (x_internal % 2 == 0) {
			} else if (y_internal % 2 == 0) {
			} else {
				if (values[indexer] == NULL) {
					put_at(x_internal, y_internal, '#');
				} else {
					put_at(x_internal, y_internal, values[indexer]);
				}
				indexer += 1;	
			}
		}
	}
}

void tic_tac_toe(void) {
	tty_init(GREEN, BLACK);
	border(0, 0, TTY_WIDTH, 3);
	
	put_string_at((TTY_WIDTH)/2 - (strlen("TikTaks")/2), 1, "TikTaks");

	u_int turn = 0;
	u_int last_turn = 0;
	
	char board[9] = {NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL};

	while (turn != 12) {
		char input[5];
		render_board((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-4, board);
		set_tty_cursor(1, TTY_HEIGHT-2);
		if (last_turn != turn) {
			region((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, 6, 1);
			if (turn == 0) {
				put_string_at((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, "X Goes");
				last_turn = turn;
			} else if (turn == 1) {
				put_string_at((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, "O Goes");
				last_turn = turn;
			}
		}

		border(0, TTY_HEIGHT-3, TTY_WIDTH, 3);
		region(1, TTY_HEIGHT-2, TTY_WIDTH-2, 1);
		get_input(input, 5);
		if (streq(input, "quit") == 0) {
			turn = 12;
		}
		if (ctoi(input[0]) <= 3 && ctoi(input[2]) <= 3 && ctoi(input[0]) != 0 && ctoi(input[0]) != 0){
			u_int y = ctoi(input[0]) - 1;
			u_int x = ctoi(input[2]) - 1;
			u_int t = x + y*3;
			if (board[t] == NULL) {
				switch (turn) {
					case 0:
						board[t] = 'X';
						break;
					case 1:
						board[t] = 'O';
						break;
				}
				last_turn = turn;
				if (turn == 0) {
					turn = 1;
				} else {
					turn = 0;
				}
			} else {
				region((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, 6, 1);
				put_string_at((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, "Occupy");
			}
		} else {
			region((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, 6, 1);
			put_string_at((TTY_WIDTH)/2-4, (TTY_HEIGHT)/2-7, "Not #");
		}
	}
}
	

void os_init(void) {

	os_ui();
	while (shell_prompt()) {
		os_ui();
		if (userSpace[0x101] == 'p') {
			put_string_at(1,3,"Panicing! Please enter 'now'");
			char input[79];
			os_get_input(input);
			if (streq(input, "now") == 0) {
				kernel_panic("!!!");
			}
			os_ui();
			userSpace[0x101] = NULL;
		} else if (userSpace[0x101] == 's') {
			put_string_at(1,3,"Are you sure? [yes]");
			char input[79];
			os_get_input(input);
			if(streq(input, "yes") == 0) {
				_stop();
			}
			os_ui();
			userSpace[0x101] = NULL;
		} else if (userSpace[0x101] == 't') {
			tic_tac_toe();
			os_ui();
			userSpace[0x101] = NULL;
		}
	}
	_stop();
}
