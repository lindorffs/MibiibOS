#include <kernel.h>
#include <keyboard.h>

u_int inb(d_u_int port)
{
  u_int ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(d_u_int port, u_int data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
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

void sleep(u_int timer_count)
{
  wait_for_io(timer_count);
}

void panic(char *str) {
	vga_clear_buffer(&vga_buffer);
	tty_cursor = 0;
	add_string("!!! KERNEL PANIC: ");
	add_string(str);
	add_string(" !!!");
	new_line();
	add_string("Please view the relevant documentation at: http://0.0.0.0/0/1");
	while (1) {

	}
}

void kernel_entry()
{
  vga_buffer = (d_u_int*)0xB8000;
  vga_clear_buffer(&vga_buffer);

  add_string("MibiibKern V0.0.3 -- Initializng");
  new_line();


  add_string("[!] Kernel handing off to OS.\n");
  add_string("[!] Exiting kSpace.\n");
  os_entry();  
  vga_clear_buffer(&vga_buffer);
  return;
}
