#include <kernel.h>

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


int memcmp(const void *a_ext, const void *b_ext, d_u_int size) {
	const unsigned char *a_int = (const unsigned char*) a_ext;
	const unsigned char *b_int = (const unsigned char*) b_ext;
	for (d_u_int i = 0; i < size; i++) {
		if (a_int[i] < b_int[i])
			return -1;
		else if (b_int[i] < a_int[i])
			return 1;
	}
	return 0;
}

void *memset(void *set_ext, d_u_int value, d_u_int size) {
	unsigned char *buffer = (unsigned char*) set_ext;
	for (d_u_int i = 0; i < size; i++) {
		buffer[i] = (unsigned char) value;
	}
	return  set_ext;
}

void *memcpy(void* restrict destination, const void* restrict source, d_u_int size) {
	unsigned char* destination_internal = (unsigned char*) destination;
	const unsigned char* source_internal = (const unsigned char*) source;
	for (d_u_int i = 0; i < size; i++) {
		destination_internal[i] = source_internal[i];
	}
	return destination;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(q_u_int timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void io_sleep(int timer_count)
{
  wait_for_io(timer_count);
}

void panic(char *str) {
	vga_clear_buffer();
	tty_init();
	add_string("!!! KERNEL PANIC: ");
	add_string(str);
	add_string(" !!!\n");
	add_string("Please view the relevant documentation at: http://0.0.0.0/0/1");
	while (1) {

	}
}

void kernel_entry()
{
  vga_clear_buffer();
  tty_init();
  add_string("[k] MibiibKern V0.0.1 -- Initializng\n");
  add_string("[k] Exiting kSpace.\n");
  os_entry();  
  vga_clear_buffer();
  return;
}
