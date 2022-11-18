	.file	1 "ALee_Lab5_programme.c"

 # -G value = 8, Cpu = 3000, ISA = 1
 # GNU C version cygnus-2.7.2-970404 (mips-mips-ecoff) compiled by GNU C version cygnus-2.7.2-970404.
 # options passed:  -msoft-float
 # options enabled:  -fpeephole -ffunction-cse -fkeep-static-consts
 # -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -msoft-float
 # -meb -mcpu=3000

gcc2_compiled.:
__gnu_compiled_c:
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, extra= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	jal	__main							// Start of Main fucntion
	li	$2,9			# 0x00000009	// Load in value 9 to R2
	sw	$2,16($fp)						// Store in value from R2 to mem location 8
	li	$2,8			# 0x00000008	// Load in value 8 to R2
	sw	$2,20($fp)						// Store in value from R2 to mem location 20
	sw	$0,28($fp)						// 
	lw	$2,16($fp)
	lw	$3,20($fp)
	addu	$2,$2,$3
	sw	$2,24($fp)
	sw	$0,28($fp)
$L2:
	lw	$2,28($fp)
	slt	$3,$2,10
	bne	$3,$0,$L5
	j	$L3
$L5:
	lw	$2,24($fp)
	lw	$3,16($fp)
	addu	$2,$2,$3
	sw	$2,24($fp)
$L4:
	lw	$2,28($fp)
	addu	$3,$2,1
	sw	$3,28($fp)
	j	$L2				// End of main function
$L3:
$L1:
	move	$sp,$fp			# sp not trusted here
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addu	$sp,$sp,40
	j	$31
	.end	main
