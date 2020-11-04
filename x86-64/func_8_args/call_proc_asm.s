	.if	0
/*
long x1 = 1;
int x2 = 2;
short x3 = 3;
char x4 = -4;

long call_proc1() {
	func(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
	return (x1 + x2) * (x3 - x4);
}
*/

	.data
x1:
	.quad	1
x2:
	.int	2
x3:
	.word	3
x4:
	.byte	-1

	.text
	.global call_proc
call_proc:
    sub     $8, %rsp
    lea     x4(%rip), %rax
    push    %rax
    movsbl  x4(%rip), %eax
    push    %rax
    lea     x3(%rip), %r9
    movswl  x3(%rip), %r8d
    lea     x2(%rip), %rcx
    mov     x2(%rip), %edx
    lea     x1(%rip), %rsi
    mov     x1(%rip), %rdi
    call    proc
    movslq  x2(%rip), %rax
    add     $16, %rsp
    add     x1(%rip), %rax
    movswl  x3(%rip), %edx
    movsbl  x4(%rip), %ecx
    sub     %ecx, %edx
    movslq   %edx, %rdx
    imul    %rdx, %rax
    add     $8, %rsp
    ret

	.else

/*
long call_proc2() {
	long x1 = 1;
	int x2 = 2;
	short x3 = 3;
	char x4 = -4;

	func(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
	return (x1 + x2) * (x3 - x4);
}
*/
    .text
    .global	call_proc
call_proc:
    push    %rbp
    mov     %rsp, %rbp
    sub     $16, %rsp
    movq    $1, -8(%rbp)
    movl    $2, -12(%rbp)
    movw    $3, -14(%rbp)
    movb     $-4, -15(%rbp)
    lea     -15(%rbp), %r8
    push    %r8
    movsbl  -15(%rbp), %edi
    push    %rdi
    lea     -14(%rbp), %r9
    movswl  -14(%rbp), %r8d
    lea     -12(%rbp), %rcx
    movl     -12(%rbp), %edx
    lea     -8(%rbp), %rsi
    movq    -8(%rbp), %rdi
    call    proc
    movslq  -12(%rbp), %rdx
    movq    -8(%rbp), %rcx
    add     %rdx, %rcx
    movswl  -14(%rbp), %edx
    movsbl  -15(%rbp), %eax
    sub     %eax, %edx
    mov     %edx, %eax
    cltq
    imul    %rcx, %rax
    mov 	%rsp, %rbp
    pop     %rbp
    ret
	.endif
