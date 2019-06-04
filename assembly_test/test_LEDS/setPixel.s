

.data
LEDArray: 	.skip 	193


message1:	.asciz 	"Number:\t%x\n"


return:		.word 	0


file:		.asciz 	"/dev/i2c-1"


O_RDWR:		.word 	0x02


I2C_SLAVE:	.word 	0x0703 


ADDRESS:	.word	0x46

.text
.global main
.type	main,%function
main: 

	ldr r7, =return
	str lr, [r7]

	mov	r0, #3
	mov r1, #2

	mov r2, #0xF800
	mov r3, #1


	
		@ if r0 < 0 && r0 >=8	
	cmp r0, #0			
	blo end
	cmp r0, #8
	bhs end
other:					@ if r1 < 0 && r1 >= 8
	cmp r1, #0
	blo	end
	cmp r1, #8
	bhs end
	



case_different:			@ if
	ldr r6, =LEDArray
	
	
			@ i = (y * 24) + x
	mov r8, #24
	mla	r1, r8, r1, r0
	add r1, r6, r1		
	add r1, r1, #1

	
	cmp	r3, #0

	mov	r8, r2, LSR #10
	and r8, #0x3e
	str r8, [r1]
	

	mov	r8, r2, LSR #5
	and r8, #0x3f
	str	r8, [r1, #+8]
	
	mov	r8, r2, LSL #1
	and r8, #0x3e
	str r8, [r1, #+16]

		
	mov	r8, #0 
	str r8, [r6]	
	
	beq end

	
	
	ldr r0, =file		@ r0 = &file
	ldr r1, =O_RDWR		@ r1 = &O_RDWR	
	ldr	r1,	[r1]		@ r1= *r1
				
	mov r7, #5			@ system call for open
	swi 0
	
	mov r4, r0			@ put file descriptor in r0
	

	ldr r1, =I2C_SLAVE	@ r1 = &I2C_SLAVE
	ldr	r1, [r1]		@ r1 = *r1
	ldr r2, =ADDRESS	@ r2 = &ADDRESS
	ldr	r2, [r2]		@ r2 = *r2
		
	mov r7, #0x36		@ system call ioctl
	swi	0
	

	mov r0, r4			@ put fd in r0

	
	ldr r1, =LEDArray	@ array with led information
	mov r2, #193		@ size of the array
	mov r7, #4			@ system call write
	swi 0
	
	@mov r1, r0			@ printf for debugging
	@ldr r0, =message1
	@bl printf


	
		

end:
	mov r7 , #6			@ system call close
	swi	0
	mov r0, r3
	ldr r7, =return
	ldr lr, [r7]
	bx	lr
	
	





.global	printf


