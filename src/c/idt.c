#include <idt.h>
__attribute__((noreturn))
	void exception_handler(void);
	void exception_handler() {
		__asm__ volatile ("cli; hlt"):
	}

void idt_set_descriptor(d_u_int vector, void* isr, d_u_int flags);
void idt_set_descriptor(d_u_int vector, void* isr, d_u_int flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void idt_init(void) {
	idtr.base = (u_int *)&idt[0];
	idtr.limit = (d_u_int *)&48 *
