.section .text
.align 4
.long 0x1BADB002
.long 0x0
.long -(0x1BADB002 + 0)

.section .text
.global _start
_start:
    call kernel_main
1:  hlt
    jmp 1b