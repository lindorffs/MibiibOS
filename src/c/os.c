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

void os_init(void) {
	tty_init(WHITE, BLACK);

	shell();	

	_stop();
}
