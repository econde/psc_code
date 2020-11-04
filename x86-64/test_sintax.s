/*
	Instruções avulso para testes diversos
*/
	
	.bss

stack_buffer:
	.space 	(1024*1024*1024*1)
stack_top:
	.byte	0
	.word
	
	.data
table:
	.byte 10, 20, 30, 40, 50
	
maska:
	.word
maskb:
	.word
var:
	.quad 1	

i:
	.8byte 	0

	.text

	.global	syntax
syntax:

	mov		$0xff0ffffffffffff0, %rax
	and		%rax, %rdx
	mov		$0x80001000, %rbx
	mov		(%rbx), %rcx
	and		$0x00ff00ff, %rcx
	mov		%rcx, 4(%rbx)
	mov		$0, %rdx
	mov		4(%rbx, %rdx), %al
	sub		$' ', %al
	mov		%al, 4(%rbx, %rdx)
	inc 	%rdx

	mov	$11, %rax
	mov 0x33445566(%rax, %rbx, 4), %r10
	mov	0xfedcba9876543211, %rax
	mov	%rcx, %rax
	movq	$stack_buffer, %rsp
	movq	$stack_top, %rsp
	mov	$0, %rax
	movabs	$0, %rax
	mov	$0xfedcba9876543211, %rax
	movabsq	$0xfedcba9876543211, %rax
	movw	%cx, table(%rdi)
	movq $1<<3, mask
	mov	%rdx, i
	
	
	
	movsbw %dl, %cx
	movsbl %al, %eax
	movsbq %dl, %rax
	movswl %ax, %eax
	movswq %dx, %rax

	movsbw %dl, %cx
	movsbl %al, %eax
	movsbq %dl, %rax
	movswl %ax, %eax
	movswq %dx, %rax
	movsbw char, %r10w
	movsbl char, %r10d
	movsbq (%rbx),%r10
	movswl mask, %eax
	movswq i, %r12

	movsxd %eax, %r15
	movslq %eax, %r15
	movsxd var, %r15
	movslq var, %r15

push 	%rax
push	(%rbx)
push	$0

pop %rdx
pop i

xchg var, %rsi
xchg %al, %bl

lea	 var(%rbp, %rsi, 8), %rbx
lahf
pushfq
pushf
clc
cmc
stc
cld
std
cli
sti

cbw
cwde
cdqe

cbw
cwde
cdqe
cltq
cwd
cdq
cltd
cqo
cqto


add %rcx, %rax
add name(%rbx), %r8
add %bl, temp
add $1, %cl
addq $2, alpha

adc %rsi, %rax
adc beta(%rsi), %rdx
adc %rdi, key(%rsi)
adc $256, %rbx
adcq $0x30, gamma

sub %rcx, %rdx
sub math(%rsi, %rbx, 2), %r10
sub %cl, 2(%rbx)
sub $5280, %r14
subq $1000, amount

sbb %r12, %r11
sbb pay(,%rsi, 4), %rdi
sbb %rax, balance
sbb $1, %cl
sbbb $10, count(%rsi)

dec %al
decw array(%rdi)

neg %al
negl multiplier

cmp %cx, %bx
cmp alpha, %dl
cmp %si, 2(%rbp)
cmp $2, %bl
cmpq $0x3420, x(%rbx)


imul %cl
imulb rate

imul %bx
imulw red(%rbp, %rdi) 

imul %ebx
imulw (%rsi)

imul %r10
imulq (%r10)

imul %rax, %rbx
imul $4, %r14

imul $54, %ax, %bx
imul $3, n, %r13

mul %bl
mulb month(%rsi)

mul %cx
mulw baund_rate

mul %ebx
mull (%rsi)

mul %rbx
mulq (%rsi)

div  %cl
divb alpha

div  %bx
divw table(%rsi)

div  %ebx
divl (%rsi)

div  %rbx
divq (%rsi)

shrd $23, %r10, %r11

mov (%rsi), %rax
shld $7, %rax, 8(%rsi)

shrd $23, %r10, %r11
shrd %cl, %r10, var

sal %cl, %rdi
shl $5, %ax
sal %cl, stor_cnt
shlq $3, status(%rbx)


shr %cl, %rsi
shr $1, %si
shrb %cl, input
shrq $1, by(%rsi, %rbx)

sar %cl, %di 
sar $1, %dx
sarw %cl, n_blocks
sarb $2, n_blocks


rol %cl, %di
rol $1, %bx
rolq %cl, alpha
rolb $2, byte(%rdi)

rcl %cl, %al
rcl $1, %cl
rclq %cl, parm(%r13)
rclq $4, alpha


ror %cl, %bx
ror $2, %al
rorb %cl, cmd_word
rorl $2, port_stat

rcr %cl, %bl
rcr $10, %bx
rcr %cl, array(%r14)
rcrq $24, (%r12)

and %al, %bl
and flag_word, %rcx
and %al, ascii(%rdi)
and $0xf0, %cl
andq $3, beta

test %si, %di
test end_cnt, %rax
testw $0xCC4, (%r15)
testq $1, retcode

or %dl, %al
or prtid(%rdi), %r14
or %cl, flag_byte
or $1, %cx
orq $0xcf, car(%rbx)

xor %rbx, %r10
xor mask_byte, %dl
xor %rdx, alpha(%rsi)
xor $0xc2, %rsi
xorq $0xff, retcode

movsxd	%eax, %r15

movsxd	var, %r10

proc:

scasb (%rdi)

bsf %rcx, %rax
bsf var, %ax

call proc

call strcpy
call *%rbx
call *table(%rsi)

jmp .L1
jmp *%rbx
jmp *switch(%rsi)

ret
ret $4

enter	$4, $3
enter	$0, $3

setg %al
setg res

in $0xfa, %al
in %dx, %ax

out %ax, $0x44
out %eax, %dx
