.global _start

.section .init
_start:
    ldr sp, =0x80000
    bl kernel_main

hang:
    b hang