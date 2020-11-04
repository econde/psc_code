
my_strcpy:
	mov	(%rsi), %al
	mov	%al, (%rdi)
	inc	%rdi
	inc	%rsi
	cmp	$0, %al
	jnz	my_strcpy
	ret
