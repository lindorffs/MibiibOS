#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <tty.h>

void render_board(u_int x, u_int y, unsigned char values[9]) {
        u_int indexer = 0;
        put_string_at(x,y-1,"1 2 3 ");
        put_string_at(x-2,y+1,"1");
        put_string_at(x-2,y+3,"2");
        put_string_at(x-2,y+5,"3");
        for (u_int y_internal = y; y_internal < y + 6; y_internal++) {
                for (u_int x_internal = x; x_internal < x + 6; x_internal++) {
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

extern struct Window osWin;

int ttt_launcher(void) {
	struct Window tttWin = new_window("TikTaks", 40, 4, 18, 16);

        u_int turn = 0;
        u_int last_turn = 0;

        unsigned char board[9] = {NULL, NULL, NULL, NULL,
                NULL, NULL, NULL, NULL, NULL};

	window_add_string(osWin, 1, 4, "TikTaks - Enter plays as:");
	window_add_string(osWin, 1, 5, "TikTaks - y,x");
	window_add_string(osWin, 1, 6, "TikTaks - Enter 'quit'");
	window_add_string(osWin, 1, 7, "TikTaks - to exit.");

        while (turn != 12) {
                char input[5];
		draw_window(tttWin);
                render_board(tttWin.x+7, tttWin.y+4, board);
                if (last_turn != turn) {
                        if (turn == 0) {
                                window_add_string(tttWin, 1, 14, "X Goes");
                                last_turn = turn;
                        } else if (turn == 1) {
                                window_add_string(tttWin, 1, 14, "O Goes");
                                last_turn = turn;
                        }
                }

		region(1, TTY_HEIGHT-2, 78, 1);
		set_tty_cursor(1, TTY_HEIGHT-2);
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
                	}
		}
	}

        return 0;
}
