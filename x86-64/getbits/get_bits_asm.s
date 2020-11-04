    .text
    .global getbits
getbits:
    mov	$1, %rax
    mov	%dl, %cl
    shl	%cl, %rax
    dec	%rax
    mov	%sil, %cl
    shr	%cl, %rdi
    and	%rdi, %rax
    ret
