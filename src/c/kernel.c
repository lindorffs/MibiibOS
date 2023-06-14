#include <kernel.h>

#include <memory.h>
#include <mibstd.h>
#include <vga.h>
#include <tty.h>
#include <os.h>

#define MB 1000

#define KERNEL_HEAP_SIZE 5120
#define HEAP_BLOCK 256


/*
 *
 * KERNEL CORE FUNCTIONALITY
 *
 */

u_int in_byte(d_u_int port)
{
  u_int ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void out_byte(d_u_int port, u_int data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

void wait_for_io(q_u_int timer_count)
{
 	for (q_u_int i = 0; i < timer_count; i++) {
		int a = 4^31;
		a = a + a;
		asm volatile("nop");
	}
}

void io_sleep(int timer_count)
{
	for (int i = 0; i < 1000; i++) {
		wait_for_io(timer_count);
	}
}

void panic(char *str) {
	vga_clear_buffer(BLACK);
	tty_init(RED, BLACK);

	add_string("[k] !!! PANIC RAISED !!!\n[o] !!! PANIC: ");
	add_string(str);
	add_string(" !!!\n");
	while (1) {

	}
}

void kernel_entry()
{
  os_entry();
  panic("ERROR");
}
