/*
 void sort(int array[], int dim) {
    for (int i = 0; i < dim - 1; ++i)
        for (int j = 0; j < dim - 1 - i; ++j)
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
}
*/
    .text
    .global sort
 sort:
        push   %r14
        push   %r13
        push   %r12
        push   %rbp
        push   %rbx
        mov    %rdi,%rbp           /*  array   */
        mov    %esi,%r14d          /*  dim  */
        dec    %r14d               /*  dim - 1  */
        mov    $0x0,%r12d          /*  i = 0  */
        jmp    sort_for1_cond
sort_for1:
        mov    $0x0, %ebx          /*  j = 0  */
        jmp    sort_for2_cond
sort_for2:
        movslq %ebx,%rax
        lea    0x0(%rbp,%rax,4),%rdi
        lea    0x4(%rbp,%rax,4),%rsi
        mov    (%rsi),%eax
        cmp    %eax,(%rdi)          /* if (array[j] > array[j + 1])  */
        jle    sort_if_end
        callq  swap
sort_if_end:
        inc    %ebx    				/* ++j */
sort_for2_cond:
        mov    %r14d, %eax          /* j < dim - 1 - i  */
        sub    %r12d, %eax
        cmp    %ebx, %eax
        jg     sort_for2
        inc    %r12d                /* ++i  */
sort_for1_cond:
        cmp    %r12d,%r14d          /* i < dim - 1  */
        jg     sort_for1
 sort_for1_end:
        pop    %rbx
        pop    %rbp
        pop    %r12
        pop    %r13
        pop    %r14
        ret   
