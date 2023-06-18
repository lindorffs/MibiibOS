#include <os.h>
#include <tty.h>
#include <vga.h>
#include <keyboard.h>
#include <utils.h>
#include <memory.h>

#include <builtins/echo.h>
#include <builtins/free.h>
#include <builtins/env.h>
#include <builtins/mibedit.h>
#include <builtins/mibview.h>

#define INPUT_BUFFER_SIZE 32

#define NUM_BUILTINS 10

extern char *tty_buffer_a, *tty_buffer_b, *current_tty;

const char *builtins[NUM_BUILTINS] = {"/lock", "/reinit", "/help", "/echo", "/free", "/edit", "/view", "/create", "/env", "/clear"};

void shell_help() {
	os_print("Available Commands:\n");
	for (int i = 0; i < NUM_BUILTINS; i++) {
		os_print(builtins[i]);
		os_print("\n");
	}
}

void mkfile(void) {
	char filename[8] = "\0";
	os_print("File Name <<< ");
	get_input(filename, 8, 1);
	malloc(128,filename);	
	os_print("\n");
}

void (*builtins_func[NUM_BUILTINS]) (void) = {
	&os_lock,
	&os_init,
	&shell_help,
	&echo_hook,
	&free_hook,
	&editor_hook,
	&viewer_hook,
	&mkfile,
	&env_hook,
	&tty_reinit
};

// Takes in user input, and if it matches
// a built in command, calls the built in commands
// related function pointer, then returns 0 upon
// the called function returning. Returns 1 upon
// a valid input not being provided.
int shell_parse(const char *input) {
	for (int i = 0; i < NUM_BUILTINS; i++) {
		if(streq(builtins[i], input) == 0) {
			(*builtins_func[i])();
			return 0;
		}
	}
	return 1;
}

void shell_prompt(void) {
	os_prtuser();
	os_print("@");
	os_prthost();
	os_print(">>> ");
}

// Prints host information, grabs the user input
// and passes it to the shell parser. If the parser
// returns 1, parsing has failed, and notify user.
// If not, do nothing.
void shell_loop() {
	current_tty = tty_buffer_a;
	tty_init(GREEN, BLACK);
	char input[INPUT_BUFFER_SIZE];
	while (1 == 1) {
	memset(input, NULL, INPUT_BUFFER_SIZE);

	shell_prompt();
	get_input(input, 32, 1);
	os_print("\n");

	if (shell_parse(input) == 1) {
		os_print("<<< Failed to parse input. Try /help\n");
	} else {
	}
	}
}

