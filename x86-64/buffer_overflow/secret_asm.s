	.text
secrets:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movb	$97, -1(%rbp)
	movb	$98, -2(%rbp)
	leaq	-9(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	gets@PLT
	cmpb	$65, -1(%rbp)
	jne	.L5
	movl	$1, %edi
	call	print_secret
.L5:
	cmpb	$66, -2(%rbp)
	jne	.L7
	movl	$2, %edi
	call	print_secret
.L7:
	nop
	leave
	ret
