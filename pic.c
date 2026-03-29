#include "pic.h"
#include "io.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define ICW1_ICW4    0x01
#define ICW1_INIT    0x10

void pic_remap(void) {
    // Salva máscaras atuais
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);
    
    // Inicia PICs
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    
    // Remapeia IRQs: IRQ0-7 -> 0x20-0x27, IRQ8-15 -> 0x28-0x2F
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    
    // Configura mestre-escravo
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    
    // Modo 8086
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    
    // Restaura máscaras
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void pic_enable_irq(uint8_t irq) {
    uint16_t port;
    uint8_t mask;
    
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    
    mask = inb(port) & ~(1 << irq);
    outb(port, mask);
}

void pic_disable_irq(uint8_t irq) {
    uint16_t port;
    uint8_t mask;
    
    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    
    mask = inb(port) | (1 << irq);
    outb(port, mask);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}