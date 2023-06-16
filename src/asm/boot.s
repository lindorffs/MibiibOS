# set magic number to 0x1BADB002 to identified by bootloader 
.set MAGIC,    0x1BADB002

# set flags to 0
.set FLAGS,    0

# set the checksum
.set CHECKSUM, -(MAGIC + FLAGS)

# set multiboot enabled
.section .multiboot

# define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM


# set the stack bottom 
stackBottom:

.skip 4096

# set the stack top which grows from higher to lower
stackTop:

.section .text
.global _start
.type _start, @function

_start:
	cli
  # assign current stack pointer location to stackTop
	mov $stackTop, %esp

  # call the kernel main source
	call kernel_entry


# put system in infinite loop
hltLoop:

	hlt
	jmp hltLoop

.size _start, . - _start

