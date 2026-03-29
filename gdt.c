#include "gdt.h"

static struct gdt_entry gdt[3];
static struct gdt_ptr   gdt_p;

static void gdt_set(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[i].base_low   = base & 0xFFFF;
    gdt[i].base_mid   = (base >> 16) & 0xFF;
    gdt[i].base_high  = (base >> 24) & 0xFF;
    gdt[i].limit_low  = limit & 0xFFFF;
    gdt[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[i].access     = access;
}

void gdt_init(void) {
    gdt_set(0, 0, 0,          0x00, 0x00); // null
    gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // código ring 0
    gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // dados ring 0

    gdt_p.limit = sizeof(gdt) - 1;
    gdt_p.base  = (uint32_t)&gdt;

    __asm__ volatile(
        "lgdt %0\n"
        "mov $0x10, %%ax\n"  // segmento de dados (entrada 2)
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "ljmp $0x08, $1f\n"  // segmento de código (entrada 1)
        "1:\n"
        :: "m"(gdt_p) : "ax"
    );
}