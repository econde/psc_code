/*
Person *get_taller(Person *people, size_t n_people) {
rax                         rdi             rsi
	size_t taller = 0;
	        rax
	for (size_t i = 1; i < n_people; ++i)
	           rdx
		if (people[i].height > people[taller].height)
			taller = i;
	return &people[taller];
}
*/

	.global	get_taller
get_taller:
	movq	$0, %rax		#	size_t taller = 0;
	movq	$1, %rdx		#	for (size_t i = 1; ...
	jmp	for_cond
for:
	addq	$1, %rdx		#	for (... ; ... ; ++i)
for_cond:					#	for ( ...; i < n_people; ...)
	cmpq	%rsi, %rdx
	jnb	for_end
	movq	%rdx, %r8
	salq	$5, %r8			#	r8 = i * sizeof people[0]
	movq	%rax, %rcx
	salq	$5, %rcx		#	rcx = taller * sizeof people[0]
	movl	28(%rdi, %rcx), %ecx	#	ecx = people[taller].height
	cmpl	%ecx, 28(%rdi, %r8)		#	if (people[i].height > ecx)
	jle	for
	movq	%rdx, %rax			#	taller = i;
	jmp	for
for_end:
	salq	$5, %rax			# rax = taller * sizeof people[0]
	addq	%rdi, %rax			# rax = &people[taller]
	ret
