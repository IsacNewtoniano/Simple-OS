#ifndef VGA_H
#define VGA_H

void init_vga(void);
void clear_screen(void);
void print(const char *s);
void print_char(char c);
void print_int(int num);

#endif