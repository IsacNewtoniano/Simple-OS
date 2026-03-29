.section .text
.global isr0
.type isr0, @function
isr0:
    cli
    pushl $0          # Código de erro fake (algumas exceções não têm)
    pushl $0          # Número da interrupção
    jmp isr_common

# Vamos criar uma macro para gerar ISRs repetitivos
.macro isr_no_err num
.global isr\num
isr\num:
    cli
    pushl $0
    pushl $\num
    jmp isr_common
.endm

.macro isr_err num
.global isr\num
isr\num:
    cli
    pushl $\num
    jmp isr_common
.endm

# ISRs 0-31 (exceções do processador)
isr_no_err 0   # Divisão por zero
isr_no_err 1   # Debug
isr_no_err 2   # NMI
isr_no_err 3   # Breakpoint
isr_no_err 4   # Overflow
isr_no_err 5   # Bound range exceeded
isr_no_err 6   # Invalid opcode
isr_no_err 7   # Device not available
isr_err    8   # Double fault
isr_no_err 9   # Coprocessor segment overrun
isr_err    10  # Invalid TSS
isr_err    11  # Segment not present
isr_err    12  # Stack fault
isr_err    13  # General protection fault
isr_err    14  # Page fault
isr_no_err 15  # Reserved
isr_no_err 16  # FPU error
isr_err    17  # Alignment check
isr_no_err 18  # Machine check
isr_no_err 19  # SIMD error
# ... 20-31 reservados, podemos preencher depois

# Handler comum que salva contexto e chama C
isr_common:
    pusha              # Salva todos registradores
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    
    # Carrega segmentos do kernel
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    # Chama handler em C: void isr_handler(uint32_t int_num, uint32_t err_code)
    pushl 32(%esp)     # Código de erro (pusha + pushes = offset 32)
    pushl 36(%esp)     # Número da interrupção
    call isr_handler
    add $8, %esp       # Limpa stack
    
    # Restaura segmentos
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa               # Restaura registradores
    add $8, %esp       # Remove erro e número da stack
    sti
    iret               # Retorna da interrupção