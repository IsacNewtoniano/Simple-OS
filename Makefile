CC  = clang
LLD = "/c/LLVM/bin/ld.lld.exe"
CFLAGS  = -ffreestanding -nostdlib -m32 -target i386-pc-none-elf -c -I.
ASFLAGS = -m32 -target i386-pc-none-elf -c

OBJS = start.o kernel.o gdt.o idt.o vga.o isr.o pic.o timer.o keyboard.o

kernel.bin: $(OBJS)
	$(LLD) -T linker.ld $(OBJS) -o kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) $(ASFLAGS) $< -o $@

run: kernel.bin
	qemu-system-x86_64 -kernel kernel.bin -m 128M

clean:
	rm -f *.o kernel.bin