#include "idt.h"
#include "vga.h"
#include "keyboard.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

// Declara os handlers do assembly
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void irq32(void);  // Timer
extern void irq33(void);  // Keyboard

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].flags = flags;
}

#include "idt.h"
#include "vga.h"
#include "io.h"
#include "keyboard.h"  // você já adicionou

void isr_handler(uint32_t int_num, uint32_t err_code) {
    // Print simples e claro
    char num_str[4];
    num_str[0] = '0' + (int_num / 100);
    num_str[1] = '0' + ((int_num / 10) % 10);
    num_str[2] = '0' + (int_num % 10);
    num_str[3] = '\0';
    
    print("\n[INT ");
    print(num_str);
    print("]");
    
    if (int_num == 33) {
        uint8_t scancode = inb(0x60);
        print(" KEY=");
        char key_str[4];
        key_str[0] = '0' + (scancode / 100);
        key_str[1] = '0' + ((scancode / 10) % 10);
        key_str[2] = '0' + (scancode % 10);
        key_str[3] = '\0';
        print(key_str);
        outb(0x20, 0x20);  // EOI
    }
}

void idt_init(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;
    
    // Limpa toda IDT
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    
    // SÓ configura o teclado (IRQ1 = interrupção 33)
    idt_set_gate(33, (uint32_t)irq33, 0x08, 0x8E);
    
    // Carrega IDT
    __asm__ volatile("lidt (%0)" : : "r" (&idtp));
    __asm__ volatile("sti");
}