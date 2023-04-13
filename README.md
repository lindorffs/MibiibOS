# MibiibOS
## A research kernel and quasi-operating system
### WARNING: EXPERIMENTAL AT BEST. DANGEROUS AT WORST.

A BIOS Capable, extremely lightweight and featureless, kernel and *operating system* designed as a basis for reserach into operating system and kernel development. Uses the GRUB Multiboot standard to load the kernel, which then calls os_entry() from kernel_entry()

Based on Pritam Zopes tutorial: https://www.codeproject.com/Articles/1225196/Create-Your-Own-Kernel-In-C-2

## Dependencies

GNU Assembler V2.39
GNU ld V2.39

GCC 12.2.0

## Running
### Dependencies
	QEMU Emulator 7.0.0

	''' make run '''

