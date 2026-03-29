CC  = clang
LLD = "/c/LLVM/bin/ld.lld.exe"
CFLAGS  = -ffreestanding -nostdlib -m32 -target i386-pc-none-elf -c
ASFLAGS = -m32 -target i386-pc-none-elf -c

kernel.bin: multiboot.o start.o kernel.o
	$(LLD) -T linker.ld multiboot.o start.o kernel.o -o kernel.bin

multiboot.o: multiboot.s
	$(CC) $(ASFLAGS) multiboot.s -o multiboot.o

start.o: start.s
	$(CC) $(ASFLAGS) start.s -o start.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c -o kernel.o

run: kernel.bin
	qemu-system-x86_64 -kernel kernel.bin -m 128M

clean:
	rm -f kernel.bin kernel.o start.o multiboot.o