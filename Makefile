CC = clang
LD = "/c/LLVM/bin/ld.lld.exe"
CFLAGS = -ffreestanding -nostdlib -m32 -target i386-pc-none-elf -c -I.
ASFLAGS = -m32 -target i386-pc-none-elf -c

OBJS = boot/start.o \
       kernel/kernel.o \
       kernel/gdt.o \
       kernel/idt.o \
       kernel/isr.o \
       kernel/pic.o \
       kernel/keyboard.o \
       drivers/vga.o

kernel.bin: $(OBJS)
	$(LD) -T linker.ld $(OBJS) -o kernel.bin

boot/%.o: boot/%.s
	$(CC) $(ASFLAGS) $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/%.o: kernel/%.s
	$(CC) $(ASFLAGS) $< -o $@

drivers/%.o: drivers/%.c
	$(CC) $(CFLAGS) $< -o $@

run: kernel.bin
	qemu-system-x86_64 -kernel kernel.bin -m 128M

clean:
	rm -f $(OBJS) kernel.bin