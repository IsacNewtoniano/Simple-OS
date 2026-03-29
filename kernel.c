#include "gdt.h"
#include "idt.h"
#include "vga.h"
#include "pic.h"

void kernel_main(void) {
    init_vga();
    print("=== Keyboard Test ===\n");
    
    gdt_init();
    print("GDT OK\n");
    
    pic_remap();
    print("PIC OK\n");
    
    // Habilita só o teclado
    pic_enable_irq(1);
    print("Keyboard enabled\n");
    
    idt_init();
    print("IDT OK - Press keys!\n");
    
    while (1) {
        __asm__("hlt");
    }
}