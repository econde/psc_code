    .text
    .global main
main:
	sub	$16, %rsp
	movl	$10, 12(%rsp)
	movl	$20, 8(%rsp)
	lea	4(%rsp), %rdx
	lea	8(%rsp), %rsi
	lea	12(%rsp), %rdi
	call	addp
	mov	$0, %eax
	add	$16, %rsp
    ret
