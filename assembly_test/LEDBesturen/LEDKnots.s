.data


message1:	.asciz	"\n-------------------\nKnop:\t0x%x\nY:\t%d\nX:\t%d\n"
message2:	.asciz	"Number 2 \t0x%x\n"
ADDRESS:	.word	0x46
file:		.asciz 	"/dev/i2c-1"
O_RDWR:		.word 	0x02
I2C_SLAVE:	.word 	0x0703 
something:	.word	0xf2
fd:			.word	0
return:		.word 	0
return2:	.word	0
x:			.word	0
y:			.word	0
COLOR:		.word	0xF800
CLEAR:		.word	0x0000
array:		.skip	3
LEDArray: 	.skip 	193


.text


write:
	ldr r0, =fd
	ldr r0,	[r0]
	ldr r1, =LEDArray	@ array with led information
	mov r2, #193		@ size of the array
	mov r7, #4			@ system call write
	swi 0

	
	bx	lr

	
ledLoop:
			@ if
	ldr r6, =LEDArray
	
			@ i = (y * 24) + x
	mov r8, #24
	mla	r1, r8, r1, r0
	add r1, r6, r1		
	add r1, r1, #1
	mov r10, r1
	ldr	r2, =COLOR
	ldr r2, [r2]

	
	mov r5, #0
	mov r7, #0
cleanArray:
	
	cmp	r5, #193
	beq fillArray
	add r3, r1, r5
	str	r7, [r3]
	add r5,r5,#1
	b	Loop
	

fillArray:
	mov r1, r10
	mov	r8, r2, LSR #10
	and r8, #0x3e
	str r8, [r1]

	mov	r8, r2, LSR #5
	and r8, #0x3f
	str	r8, [r1, #+8]
	
	mov	r8, r2, LSL #1
	and r8, #0x3e
	str r8, [r1, #+16]

	

	push	{lr}
	bl write
	pop	{lr}


	bx lr
	


.global main

main:
	push	{lr}
	ldr r0, =file 	
	ldr r1, =O_RDWR
	ldr	r1, [r1]

	mov r7,	#5
	swi	0

	ldr r1, =fd
	str r0, [r1]

	
	ldr	r0, =fd
	ldr r0, [r0]
	ldr r1, =I2C_SLAVE	@ r1 = &I2C_SLAVE
	ldr	r1, [r1]		@ r1 = *r1
	ldr r2, =ADDRESS	@ r2 = &ADDRESS
	ldr	r2, [r2]		@ r2 = *r2

	
	mov r7, #0x36		@ system call ioctl
	swi	0
leds:
	

	ldr r1, =array	
	ldr r1, [r1]
	ldr r2, =x
	ldr	r2, [r2]
	ldr r3, =y
	ldr	r3, [r3]
	
	ldr	r0, =message1
	bl printf

@ if x < 0 && x >=8	
	ldr r0, =x
	ldr r0,	[r0]
	cmp r0, #0			
	blo end
	cmp r0, #8
	bhs end
other:					@ if y< 0 && y >= 8
	ldr r1, =y
	ldr r1,	[r1]
	cmp r1, #0
	blo	end
	cmp r1, #8
	bhs end
	
	
@	mov	r8, #0 
@	str r8, [r6]	
	

	bl	ledLoop

	

Loop:
	


	mov r4, #0xFF
	lsl r4, #19
1:
	subs	r4, r4, #1
	bne 1b

	ldr	r0, =fd
	ldr	r0, [r0]
	ldr r1, =something	@ array with led information
	mov r2, #1			@ size of the array
	mov r7, #4			@ system call write
	swi 0
	
	ldr r0, =fd
	ldr r0, [r0]
	ldr r1, =array	
	mov r2, #1
	mov	r7, #3
	swi	0

	ldr r1, =array
	ldr	r1, [r1]
	
	
	ldr r2, =x
	ldr r2, [r2]

	ldr	r3, =y
	ldr r3, [r3]

press:
	cmp r1, #0x8
	beq	end

yup:	
	cmp r1, #0x1
	bne xup
	
	ldr r5, =COLOR
	mov r7, #0x0000
	str	r7, [r5]
	bl ledLoop
	ldr r5, =COLOR
	mov r7, #0xf800
	str	r7, [r5]
	
	ldr r4, =y
	add r3, r3, #1
	str r3, [r4]
	beq	leds
	
xup:
	cmp r1, #0x2
	bne ydown
	
	ldr r4, =x
	add r2, r2, #1
	str r2, [r4]
	beq	leds
	

ydown:	
	cmp r1, #0x4
	bne xdown		
	ldr r4, =y
	sub r3, r3, #1
	str r3, [r4]
	beq	leds
			

xdown:
	cmp r1, #0x10
	bne endknots		
	ldr r4, =x
	sub r2, r2, #1
	str r2, [r4]
	beq	leds
	

endknots:

		
	b	Loop	


end:
	
	mov r7, #6
	swi 0
	
	pop	{lr}
	
	bx	lr



