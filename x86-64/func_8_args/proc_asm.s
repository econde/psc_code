    .text
    .globl  proc
proc:
    add     %rdi, (%rsi)
    add     %edx, (%rcx)
    add     %r8w, (%r9)
    mov     8(%rsp), %dl
    mov     16(%rsp), %rax
    add     %dl, (%rax)
    ret
