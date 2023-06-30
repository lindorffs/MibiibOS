#include <vga.h>
#include <kernel.h>

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
}

void enable_vga_cursor() {
	kernel_out_byte(0x3D4, 0x0A);
	kernel_out_byte(0x3D5, (kernel_in_byte(0x3D5) & 0xC0) | 0);
	kernel_out_byte(0x3D4, 0x0B);
	kernel_out_byte(0x3D5, (kernel_in_byte(0x3D5) & 0xE0) | 15);
}

void disable_vga_cursor() {
	kernel_out_byte(0x3D4, 0x0A);
	kernel_out_byte(0x3D5, 0x20);
}

void set_vga_cursor(u_int x, u_int y) {
	d_u_int pos = (y * VGA_WIDTH) + x;
	kernel_out_byte(0x3D4, 0x0F);
	kernel_out_byte(0x3D5, (pos & 0xFF));
	kernel_out_byte(0x3D4, 0x0E);
	kernel_out_byte(0x3D5, ((pos >> 8) & 0xFF));
}
