OBJECTS = boot.o kernel.o vga.o tty.o os.o
BUILD_DIR := build/obj/

main: clean os.bin

os.bin: $(OBJECTS) 
	ld -m elf_i386 -T src/link.ld $^ -o build/os.bin -nostdlib

%.o: src/asm/%.s
	as --32 $^ -o $@

%.o: src/c/%.c
	gcc -m32 -Iinclude/ -c $^ -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra 

clean:
	rm -fv  *.o
	rm -fv build/os.bin
	rm -fv isodir/boot/mibiibos.bin
	rm -fv isodir/boot/grub/grub.cfg
	rm -fv build/MibiibOS.iso

iso: main
	cp build/os.bin isodir/boot/mibiibos.bin
	cp src/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/MibiibOS.iso isodir

run: iso
	qemu-system-x86_64 -cdrom build/MibiibOS.iso
