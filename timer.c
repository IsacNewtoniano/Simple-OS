#include "timer.h"
#include "pic.h"
#include "io.h"
#include "vga.h"

static uint32_t ticks = 0;

void timer_handler(void) {
    ticks++;
    
    // A cada 100 ticks, printa (só para mostrar que está funcionando)
    if (ticks % 100 == 0) {
        print("Tick\n");
    }
    
    pic_send_eoi(0);  // IRQ0
}

uint32_t timer_get_ticks(void) {
    return ticks;
}

void timer_init(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;
    
    // Comando do PIT (Channel 0, lobyte/hibyte, rate generator)
    outb(0x43, 0x36);
    
    // Envia divisor (low byte, high byte)
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
    
    // Habilita IRQ0
    pic_enable_irq(0);
    
    print("Timer initialized at ");
    print_int(frequency);
    print(" Hz\n");
}