# Grub Multiboot
.set MAGIC, 0x1BADB002
.set FLAGS, 0x0

.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot

.long MAGIC
.long FLAGS
.long CHECKSUM

.section .data

.section .text
.code16

.global _boot_main
_boot_main:

cli

jmp _boot_32

.code32
_boot_32:
mov $0x8000, %ebp
mov %ebp, %esp

call kernel_entry

.global _stop
_stop:

hlt
