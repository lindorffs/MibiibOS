#include <ui.h>
#include <keyboard.h>
#include <utils.h>
#include <tty.h>

extern struct Window osWin;
u_int selected = 0;

void render_board(u_int x, u_int y, unsigned char values[9]) {
        u_int indexer = 0;
        for (u_int y_internal = y; y_internal < y + 6; y_internal++) {
                for (u_int x_internal = x; x_internal < x + 6; x_internal++) {
                        if (x_internal % 2 == 0) {
                        } else if (y_internal % 2 == 0) {
                        } else {
				if (indexer == selected) {
					set_vga_cursor(x_internal, y_internal);
				}
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


int ttt(void) {
	struct Window tttWin = new_window("TikTaks", 1, 3, 18, 16);
	unsigned char board[9] = {NULL, NULL, NULL, NULL,
                NULL, NULL, NULL, NULL, NULL};
	draw_window(&tttWin);
	render_board(tttWin.x + 5, tttWin.y+4, board);
	selected = 0;

        u_int turn = 0;
        u_int last_turn = 0;

	KeyEvent key;
	enable_vga_cursor();
        while (key.keycode != KEY_ESC) {
		key = get_key_event();
		if (key.keycode == KEY_RIGHT + 128 && selected + 1 < 9) { 
			selected += 1;
			render_board(tttWin.x + 5, tttWin.y+4, board);
		} else if (key.keycode == KEY_LEFT + 128 && selected - 1 >= 0) {
			selected -= 1;
			render_board(tttWin.x + 5, tttWin.y+4, board);
		} else if (key.keycode == KEY_UP + 128 && selected - 3 >= 0) {
			selected -= 3;
			render_board(tttWin.x + 5, tttWin.y+4, board);
		} else if (key.keycode == KEY_DOWN + 128 && selected + 3 < 9) {
			selected += 3;
			render_board(tttWin.x + 5, tttWin.y+4, board);
		} else if (key.keycode == KEY_ENTER + 128 && board[selected] == NULL) {
			board[selected] = turn == 0 ? 'X' : 'O';
			turn = turn == 0 ? 1 : 0;
			render_board(tttWin.x + 5, tttWin.y+4, board);
		}

	}

	disable_vga_cursor();

        return 0;
}
