/*

int get_pixel(Icon **icons, int id, unsigned int x, unsigned int y) {
eax					rdi			esi        edx          ecx
    for (Icon *icon = *icons; icon != NULL; icon = *++icons)
               rax
		if (icon->id == id) {
			unsigned int idx = icon->dx * y + x;
			return (icon->bitmap[idx >> 5] >> (idx & 0x1f)) & 1;
		}
    return -1;
}
*/
	.text
	.global	get_pixel

get_pixel:
	movq	(%rdi), %rax
for:
	testq	%rax, %rax
	je	for_end
	cmpl	%esi, (%rax)
	je	if_then
	addq	$8, %rdi
	movq	(%rdi), %rax
	jmp	for
if_then:
	imull	4(%rax), %ecx
	addl	%edx, %ecx
	movq	16(%rax), %rdx
	movl	%ecx, %eax
	shrl	$5, %eax
	movl	%eax, %eax
	movl	(%rdx,%rax,4), %eax
	shrl	%cl, %eax
	andl	$1, %eax
	ret
for_end:
	movl	$-1, %eax
	ret
