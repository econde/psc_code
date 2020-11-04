	.text
	.global add
add:
	lea	(%rdi, %rsi), %eax
	ret
