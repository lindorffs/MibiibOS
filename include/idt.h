#ifndef IDT_H
#define IDT_H

#include <mibstd.h>

typedef struct {
	d_u_int isr_low;
	d_u_int kernel_cs;
	u_int reserved;
	u_int attributes;
	d_u_int isr_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	d_u_int limit;
	q_u_int base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

__attribute__((aligned(0x10)))
	static idt_entry_t idt[256];

#endif
