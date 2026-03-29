void kernel_main(void) {
    volatile unsigned short *vga = (volatile unsigned short *)0xB8000;
    
    // Pula pra linha 2 (offset 80 caracteres)
    int offset = 80;
    const char *msg = "Simple-OS funcionando!";
    int i = 0;
    while (msg[i]) {
        vga[offset + i] = (unsigned short)(0x0F00 | msg[i]);
        i++;
    }

    while (1) {
        __asm__ volatile("hlt");
    }
}