.section .text

# Handler do teclado (IRQ1 = interrupção 33)
.global irq33
irq33:
    cli
    pusha
    call keyboard_handler_wrapper
    popa
    sti
    iret

# Função wrapper que chama o C
keyboard_handler_wrapper:
    # Chama a função C
    call keyboard_handler_c
    # Envia EOI para o PIC
    mov $0x20, %al
    outb %al, $0x20
    ret