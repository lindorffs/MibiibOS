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
		int a = 2^31;
		a = a + a;
		asm volatile("nop");
	}
}

void io_sleep(int timer_count)
{
	wait_for_io(timer_count * 1000);
}

void panic(const char *str) {
	tty_init(RED, BLACK);

	add_string("[k] !!! PANIC RAISED !!!\n[o] !!! PANIC: ");
	add_string(str);
	add_string(" !!!\n");
	while (1) {

	}
}

void kernel_entry()
{
  tty_init(WHITE, BLACK);
  if (memory_init() != 1) {
	  panic("Memory Initialization Error");
  }
  os_init();
  panic("ERROR");
}
