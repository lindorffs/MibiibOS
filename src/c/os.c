#include <os.h>

#include <kernel.h>
#include <memory.h>
#include <keyboard.h>
#include <vga.h>
#include <tty.h>
#include <utils.h>
#include <shell.h>

OSInfo osData;

#define HOSTNAME_LENGTH 8 
#define USERNAME_LENGTH 8
#define PASSWORD_LENGTH 8

extern char *tty_buffer_a, *tty_buffer_b, *current_tty;

char *motd = "MibiibOS - Lighter, Simpler, Easier.";

void unreachable(void) {
	while (1==1) {};
	unreachable();
}


void os_prtuser(void) {
	add_string(osData.username);
}

void os_prthost(void) {
	add_string(osData.hostname);
}


// Prompts the user for a username and a password.
// If the provided data matches, returns a 1.
// If not, it returns a 0. It does not retry by itself.
u_int os_auth() {
char in_user[USERNAME_LENGTH];
	memset(in_user, NULL, USERNAME_LENGTH);
	char in_password[PASSWORD_LENGTH];
	memset(in_password, NULL, PASSWORD_LENGTH);

	os_prthost();
	add_string("/login [username] <<< ");
	get_input(in_user, USERNAME_LENGTH, 1);
	add_string(" [password] <<< ");
	get_input(in_password, PASSWORD_LENGTH, 0);
	new_line();

	return (streq(in_password, osData.password) == 0 && streq(in_user, osData.username) == 0);
}

// Locks the OS and waits for os_auth to return
// if os_auth returns 0, os_lock finishes and
// returns to caller. if not, the tty is cleared
// the motd is printed, a new line is printed,
// and os_auth is called again.
void os_lock() {
	swap_tty();
	tty_clear();
	tty_init(YELLOW, BLACK);
	os_print(motd);
	new_line();
	do {
	}
	while (os_auth() == 0);
	tty_clear();
	swap_tty();
}

void os_prthostinfo(void) {
	os_prtuser();
	add_string("@");
	os_prthost();
}

void os_print(const char *string) {
	add_string(string);
}


void os_assert(int comparison, const char *good, const char *bad) {
	if (comparison != 0) {
		os_print(good);
	} else {
		panic(bad);
	}
}

void os_setusr(void) {
	add_string("Set user information:");
	new_line();
	
	char inputName[USERNAME_LENGTH];
	memset(inputName, NULL, USERNAME_LENGTH);
	add_string("Username: ");
	get_input(inputName, USERNAME_LENGTH, 1);
	memcpy(osData.username, inputName, USERNAME_LENGTH, 0);
	memset(inputName, NULL, USERNAME_LENGTH);
	new_line();

	char inputPassword[PASSWORD_LENGTH];
	memset(inputPassword, NULL, PASSWORD_LENGTH);
	add_string("Password: ");
	get_input(inputPassword, PASSWORD_LENGTH, 0);
	memcpy(osData.password, inputPassword, PASSWORD_LENGTH, 0);
	memset(inputPassword, NULL, PASSWORD_LENGTH);
	new_line();

}

//  Clears and sets the hostname
void os_sethost(void) {
	add_string("Hostname: ");
	get_input(osData.hostname, HOSTNAME_LENGTH, 1);
	new_line();
}

// Calls the shell loop, waits for return
// and calls the os_loop again, thus creating the
// infinite system loop.
void os_loop(void) {
	shell_loop();
	os_loop();
	unreachable();
}

// First start of OS, grab user name, password
// hostname, create an inital lock, then drop
// to the os_loop().
void os_begin(void) {
	tty_init(BLUE, WHITE);
	os_print("OS_BEGIN Entry.\n");
	new_line();
	os_print("Gathering user information\n");
	os_setusr();
	os_print("Gathering host information\n");
	os_sethost();

	os_lock();
	tty_clear();
	os_loop();
	
	unreachable();
	panic("OS_BEGIN PASSED UNREACHABLE");
}

void os_init(void) {
	tty_init(BLUE, WHITE);
	tty_clear();
	os_print("OS_INIT Entry.");
	new_line();
	
	osData.hostname = (char *)malloc(HOSTNAME_LENGTH,"/etc/hs\0");
	osData.username = (char *)malloc(USERNAME_LENGTH,"/etc/un\0");
	osData.password = (char *)malloc(PASSWORD_LENGTH,"/etc/pw\0");
	tty_buffer_a = (char *)malloc(2001,"/tty/ta\0");
	tty_buffer_b = (char *)malloc(2001,"/tty/tb\0");
	current_tty = tty_buffer_a;

	tty_clear();

	os_begin();
	unreachable();
	panic("OS_INIT PASSED UNREACHABLE");
}
