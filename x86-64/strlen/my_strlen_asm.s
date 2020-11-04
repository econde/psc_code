	.text
	.global	my_strlen
my_strlen:
	mov	$0, %rax
my_strlen_for:
	cmpb	$0, (%rdi, %rax)
	je	my_strlen_return
	inc   %rax
	jmp   my_strlen_for
my_strlen_return:
	ret
