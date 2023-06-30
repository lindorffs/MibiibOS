# Grub Multiboot
.set MAGIC, 0x1BADB002
.set FLAGS, 0x0

.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot

.long MAGIC
.long FLAGS
.long CHECKSUM

.section .rodata

.section .data
# C Stack
stack_bottom:
.skip 4096
stack_top:
.section .text

.global _boot_main
_boot_main:
jmp handoff
# GDT
gdt:
#NULL ENTRY
.word 0x0000 # limit 16
.word 0x0000 # base_low 16
.byte 0x00   # middle 8
.byte 0x00   # access 8
.byte 0x00   # granularity 8
.byte 0x00   # base_high
gdt_code:
.word 0xFFFF # limit 16
.word 0x0000 # base_low 16
.byte 0x00   # middle 8
.byte 0b10011000# access 8
.byte 0b11001111   # granularity 8
.byte 0x00   # base_high
gdt_data:
.word 0xFFFF # limit 16
.word 0x0000 # base_low 16
.byte 0x00   # middle 8
.byte 0b10010000   # access 8
.byte 0b11001111 # :
.byte 0x00   # granularity 8
gdt_end:

gdtr:
.word gdt_end - gdt
.long gdt

CODE_SEG = gdt_code - gdt
DATA_SEG = gdt_data - gdt

handoff:

_load_gdt:
	lgdt gdtr

	mov $0x10, %ax
#	mov %ax, %ds
#	mov %ax, %es
#	mov %ax, %fs
#	mov %ax, %gs


	jmp $CODE_SEG, $_boot_32
.code32
_boot_32:
	mov $DATA_SEG, %ax

	call kernel_entry

.global _stop
_stop:
	mov $0x5301, %ax
	xor %bx, %bx
	int $0x15
	mov $0x530e, %ax
	xor %bx, %bx
	mov $0x0102, %cx
	int $0x15
	mov $0x5307, %ax
	mov $0x0001, %bx
	mov $0x0003, %cx
	int $0x15
hlt
