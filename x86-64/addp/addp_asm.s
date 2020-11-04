	.text
	.global addp
addp:
	pushq	%rbx
	movq	%rdx, %rbx
	movl	(%rsi), %esi
	movl	(%rdi), %edi
	call	add
	movl	%eax, (%rbx)
	popq	%rbx
	ret
