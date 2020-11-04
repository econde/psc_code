    .text
    .global subp
subp:
    pushq	%rbx
    movq	%rdx, %rbx
    movl	(%rsi), %esi
    movl	(%rdi), %edi
    call	sub
    movl	%eax, (%rbx)
    popq	%rbx
    ret
