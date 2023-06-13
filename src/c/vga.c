#include <vga.h>

d_u_int *vga_buffer = (d_u_int*)0xB8000;

d_u_int vga_mem(unsigned char ch, u_int fore_color, u_int back_color)
{
  d_u_int ax = 0;
  u_int ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void vga_set_mem(q_u_int mem_pos, d_u_int vga_memory) {
	vga_buffer[mem_pos] = vga_memory;
}

void vga_clear_buffer(u_int color)
{
  for(q_u_int i = 0; i < VGA_BUFFER_SIZE; i++){
	  vga_set_mem(i, vga_mem(NULL, WHITE, color)); 
  }
}

