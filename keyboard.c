#include "keyboard.h"
#include "io.h"
#include "vga.h"

// Esta função será chamada diretamente do assembly
void keyboard_handler_c(void) {
    uint8_t scancode = inb(0x60);
    
    // Printa o scancode
    print("\nSCANCODE: ");
    
    // Converte para caractere simples
    char c = '?';
    if (scancode >= 2 && scancode <= 11) {
        c = '0' + (scancode - 2);
    } else if (scancode == 16) {
        c = 'q';
    } else if (scancode == 17) {
        c = 'w';
    } else if (scancode == 18) {
        c = 'e';
    } else if (scancode == 19) {
        c = 'r';
    } else if (scancode == 20) {
        c = 't';
    } else if (scancode == 21) {
        c = 'y';
    } else if (scancode == 22) {
        c = 'u';
    } else if (scancode == 23) {
        c = 'i';
    } else if (scancode == 24) {
        c = 'o';
    } else if (scancode == 25) {
        c = 'p';
    }
    
    print_char(c);
}