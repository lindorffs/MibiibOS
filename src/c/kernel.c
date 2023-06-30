#include <kernel.h>
#include <tty.h>
#include <vga.h>
#include <keyboard.h>
#include <utils.h>
#include <os.h>
#include <ui.h>
/**
#include <memory.h>
#include <mibstd.h>
#include <vga.h>
#include <tty.h>
#include <os.h>


*
 *
 * KERNEL CORE FUNCTIONALITY
 *
 *
**/

#define MB 1000
extern int tty_x, tty_y;
extern struct Window osWin;

u_int kernel_in_byte(d_u_int port)
{
  u_int ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}
void kernel_out_byte(d_u_int port, u_int data)
{
  asm volatile("outb %0, %1":: "a"(data),  "Nd"(port));
}

void kernel_wait_for_io(size_int timer_count)
{
 	for (q_u_int i = 0; i < timer_count && i < 0xFFFFFF; i++) {
		int a = 2^31;
		a = a + a;
		asm volatile("nop");
	}
}

void kernel_io_sleep(size_int timer_count)
{
	kernel_wait_for_io(timer_count * 1000);
}


void kernel_panic(const char *str) {
	tty_init(RED, BLACK);

	add_string("[k] !!! PANIC RAISED !!!\n[o] !!! PANIC: ");
	add_string(str);
	add_string(" !!!\n");
	while (1) {

	}
}

char *runString = "... SYSTEM INITIALIZED ... PRESS ANY KEY TO BEGIN.";
char *stopString = "... SYSTEM CLEARED ... PRESS ANY KEY TO SHUTDOWN.";
void kernel_entry()
{
	disable_vga_cursor();
	add_string(runString);
	get_input((void*)NULL, 1);
	os_init();
}
