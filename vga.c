#include "vga.h"

static volatile unsigned short *vga_buffer = (volatile unsigned short *)0xB8000;
static int row = 0;
static int col = 0;

void init_vga(void) {
    row = 0;
    col = 0;
    clear_screen();
}

void print_int(int num) {
    char buffer[12];
    int i = 0;
    
    if (num == 0) {
        print_char('0');
        return;
    }
    
    if (num < 0) {
        print_char('-');
        num = -num;
    }
    
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    while (i > 0) {
        print_char(buffer[--i]);
    }
}

void print_char(char c) {
    if (c == '\n') {
        row++;
        col = 0;
        if (row >= 25) row = 0;
    } else {
        vga_buffer[row * 80 + col] = 0x0F00 | c;
        col++;
        if (col >= 80) {
            col = 0;
            row++;
            if (row >= 25) row = 0;
        }
    }
}

void print(const char *s) {
    while (*s) {
        print_char(*s++);
    }
}

void clear_screen(void) {
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = 0x0F00 | ' ';
    }
    row = 0;
    col = 0;
}