#include <kernel.h>
#include <tty.h>
#include <vga.h>
#include <keyboard.h>
#include <utils.h>
#include <os.h>
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
extern char *stackBottom;
extern char *stackTop;
extern int tty_x, tty_y;
unsigned char kernelSpace[10 * MB];
unsigned char osSpace[20 * MB];
unsigned char userSpace[30 * MB];

u_int kernel_in_byte(d_u_int port)
{
  u_int ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}
void kernel_out_byte(d_u_int port, u_int data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
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

void call_kset() {
	if(streq((char*)&osSpace[0x100], "mem") == 0) {
		kernel_panic("mem");
	}	
}

void kernel_panic(const char *str) {
	tty_init(RED, BLACK);

	add_string("[k] !!! PANIC RAISED !!!\n[o] !!! PANIC: ");
	add_string(str);
	add_string(" !!!\n");
	while (1) {

	}
}

void *memcpy(void *target, const void *source, size_int size) {
	unsigned char *target_internal = (unsigned char *)target;
	const unsigned char *source_internal = (unsigned char *) source;
	for (size_int i = 0; i < size && i < 0xFFFFFFFF; i++) {
		target_internal[i] = source_internal[i];
	}
	return target;
}

char *runString = "... SYSTEM INITIALIZED... PRESS ANY KEY TO BEGIN.";

void userSpace_init() {
	add_string("User Space Size (Bytes): ");
	add_string(itoa(sizeof(userSpace), (void*)NULL));
	add_entry('\n');
	add_string("User Space Start [Byte]: ");
	add_string(itoa((int)&userSpace, (void*)NULL));
	add_entry('\n');
	add_string("Clearing User Space\n");
	for (size_int i = 0; i < sizeof(userSpace); i++) {
		userSpace[i] = NULL;
	}
	add_string("Checking User Space\n");
	for (size_int i = 0; i < sizeof(userSpace); i += 10) {
		if (userSpace[i] == 8) {
			userSpace[i] = NULL;
			if (i % MB == 0) {
				add_entry('.');
			}
			if (i + 10 < sizeof(userSpace)) {
				userSpace[i + 10] = 8;
			}
		} else {
			userSpace[i] = 8;
			i -= 10;
		}
	}
	add_entry('\n');
}

void osSpace_init() {
	add_string("OS Space Size (Bytes): ");
	add_string(itoa(sizeof(osSpace), (void*)NULL));
	add_entry('\n');
	add_string("OS Space Start [Byte]: ");
	add_string(itoa((int)&osSpace, (void*)NULL));
	add_entry('\n');
	add_string("Clearing OS Space\n");
	for (size_int i = 0; i < sizeof(osSpace); i++) {
		osSpace[i] = NULL;
	}
	add_string("Checking OS Space\n");
	for (size_int i = 0; i < sizeof(osSpace); i += 10) {
		if (osSpace[i] == 8) {
			osSpace[i] = NULL;
			if (i % MB == 0) {
				add_entry('.');
			}
			if (i + 10 < sizeof(osSpace)) {
				osSpace[i + 10] = 8;
			}
		} else {
			osSpace[i] = 8;
			i -= 10;
		}
	}
	add_entry('\n');
}
	

void kernel_init() {
	tty_init(WHITE, BLACK); // vga_clear
 
	add_string("Kernel: ");
	add_string(itoa(KERNEL_MAJOR, (void*)NULL));
	add_entry('.');
	add_string(itoa(KERNEL_MINOR, (void*)NULL));
	add_entry('.');
	add_string(itoa(KERNEL_VERSION, (void*)NULL));
	add_string(" - ");
        add_string(KERNEL_STRING);
	add_entry('\n');

	add_string("Stack Top [Byte]: ");
	add_string(itoa((int)&stackTop, (void*)NULL));
	add_entry('\n');
	add_string("Stack Bottom [Byte]: ");
	add_string(itoa((int)&stackBottom, (void*)NULL));
	add_entry('\n');
	add_string("Stack Size: ");
	add_string(itoa((int)&stackTop - (int)&stackBottom, (void*)NULL));
	add_entry('\n');
	add_string("Kernel Space Size (MiBytes): ");
	add_string(itoa(sizeof(kernelSpace), (void*)NULL));
	add_entry('\n');
	add_string("Kernel Space Start [Byte]: ");
	add_string(itoa((int)&kernelSpace, (void*)NULL));
	add_entry('\n');
	add_string("Clearing Kernel Space\n");
	for (size_int i = 0; i < sizeof(kernelSpace); i++) {
		kernelSpace[i] = NULL;
	}
	add_string("Checking Kernel Space\n");
	for (size_int i = 0; i < sizeof(kernelSpace); i += 10) {
		if (kernelSpace[i] == NULL) {
			if (i % MB == 0) {
				add_entry('.');
			}
		} else {
			add_entry('!');
		}
	}
	add_entry('\n');
}

void kernel_entry()
{
	get_input((void*)NULL, 1);

	kernel_init();
	osSpace_init();
	userSpace_init();
	add_string(runString);
	get_input((void*)NULL, 1);
	os_init();
}
