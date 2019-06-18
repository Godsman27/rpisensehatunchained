
.data


message1:	.asciz	"Number:\t0x%x\n"
message2:	.asciz	"Number 2 \t0x%x\n"
ADDRESS:	.word	0x46
file:		.asciz 	"/dev/i2c-1"
O_RDWR:		.word 	0x02
I2C_SLAVE:	.word 	0x0703 
something:	.word	0xf2
fd:			.word	0
return:		.word 	0
array:		.skip	2



.text
.global main
.type 	main, %function

main:
	ldr r7, =return
	str lr, [r7]



	ldr r0, =file 	
	ldr r1, =O_RDWR
	ldr	r1, [r1]

	mov r7,	#5
	swi	0
	
	mov r4, r0
	
	mov r1, r0
	ldr r0, =message1
	bl	printf

	mov r0, r4
	ldr r1, =I2C_SLAVE	@ r1 = &I2C_SLAVE
	ldr	r1, [r1]		@ r1 = *r1
	ldr r2, =ADDRESS	@ r2 = &ADDRESS
	ldr	r2, [r2]		@ r2 = *r2

	
	mov r7, #0x36		@ system call ioctl
	swi	0
	

	

Loop:
	
	mov r0, #0xFF
	lsl r0, #20
1:
	subs	r0, r0, #1
	bne 1b

	mov r0, r4
	ldr r1, =something	@ array with led information
	mov r2, #1		@ size of the array
	mov r7, #4			@ system call write
	swi 0
	
	mov r0, r4
	ldr r1, =array	
	mov r2, #1
	mov	r7, #3
	
	swi	0

	ldr r1, =array
	ldr	r1, [r1]
	
	

	
	cmp r1, #0x8
	beq	end
	
	ldr r0, =message1
	bl	printf


	
	b	Loop	


end:
	mov r7, #6
	swi 0

	ldr r7, =return
	ldr lr, [r7]
	
	bx	lr








