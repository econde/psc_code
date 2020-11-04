/*
int find_bigger(int array[], size_t array_size) {
eax                 rdi              rsi
	int bigger = array[0];
		rdx
	for (size_t i = 1; i < array_size; ++i)
		if (array[i] > bigger)
			bigger = array[i];
	return bigger;
}
*/

    .text
    .global find_bigger
find_bigger:
    mov	(%rdi), %eax
    mov	$1, %rdx
for:
    cmp	%rsi, %rdx
    jnb	for_end
    mov	(%rdi,%rcx,4), %ecx
    cmp	%eax, %ecx
    jle	if_end
    mov	%ecx, %eax
if_end:
    add	$1, %rdx
    jmp	for
for_end:
    ret
