#include <vga.h>

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

void vga_clear_buffer(d_u_int **buffer)
{
  q_u_int i;
  for(i = 0; i < VGA_BUFFER_SIZE; i++){
    (*buffer)[i] = vga_mem(NULL, WHITE, DARK_GREY);
  }
}

