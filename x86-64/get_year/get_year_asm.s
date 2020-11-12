/*
int get_year(const char *date) {
	char buffer[strlen(date)] + 1;
	strcpy(buffer, date);
	return atoi(strtok(buffer, "-/ "));
}
*/

	.section .rodata
sep:	.asciz	"/- "

	.text
	.global get_year
get_year:
	push	%rbp
	mov	%rsp, %rbp
	push	%rbx
	mov	%rdi, %rbx
	sub	$8, %rsp
	call	strlen
	inc	%eax
	add	$15, %eax
	and	$-16, %eax
	sub	%rax, %rsp
	mov	%rsp, %rdi
	mov	%rbx, %rsi
	call strcpy
	mov	%rsp, %rdi
	lea sep(%rip), %rsi
	call strtok
	mov	%rax, %rdi
	call atoi
	mov	-8(%rbp), %rbx
	mov	%rbp, %rsp
	pop	%rbp
	ret
