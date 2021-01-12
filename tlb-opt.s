	.file	"tlb.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"#pages\t proc\t sum"
.LC2:
	.string	"%d\t %.6f\t %ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	.LC0(%rip), %rdi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	$1048576, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movl	$1, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	puts@PLT
	.p2align 4,,10
	.p2align 3
.L2:
	call	clock@PLT
	movq	%rax, %r13
	movl	%ebp, %eax
	cltd
	idivl	%ebx
	leal	-1(%rax), %r12d
	call	clock@PLT
	addq	$1, %r12
	pxor	%xmm0, %xmm0
	movl	%ebx, %edx
	imulq	%rbx, %r12
	subq	%r13, %rax
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	addq	$1, %rbx
	movl	$1, %eax
	divsd	.LC1(%rip), %xmm0
	movq	%r12, %rcx
	call	__printf_chk@PLT
	cmpq	$17, %rbx
	jne	.L2
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
