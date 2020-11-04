    .data
a:
    .int   10
b:
    .int   20

    .bss
c:
    .zero  4

    .text
    .global main
main:
    lea	c(%rip), %rdx
    lea	b(%rip), %rsi
    lea	a(%rip), %rdi
    call	subp
    mov	$0, %eax
    ret
