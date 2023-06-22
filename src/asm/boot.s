.set MAGIC,    0x1BADB002
# set magic number
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

.section data
# set the stack bottom 
.global stackBottom
stackBottom:

.skip 10000

# set the stack top which grows from higher to lower
.global stackTop
stackTop:


.section .text
.global _start
_start:
	cli
  # assign current stack pointer location to stackTop
	mov $stackTop, %esp

  # call the kernel main source
	call kernel_entry
.global _stop
.type _stop, @function
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
# put system in infinite loop
hltLoop:

	hlt
	jmp hltLoop

.size _start, . - _start

