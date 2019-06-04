

.data
LEDArray: 	.skip 193

.balign 4
message1:	.asciz "Number:\t%d\n"

.balign 4
return:	.word 0

.balign 4
file:	.asciz "/dev/i2c-1"
.balign 4
flag:	.asciz "O_RDWR"
.balign 4
slave:	.asciz "I2C_SLAVE"

.text
.global main
.type	main,%function
main: 

	ldr r7, =return
	str lr, [r7]

	mov	r0, #0
	mov r1, #0

	mov r2, #0xFFFF
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
	
@ 	mov r1, r0
@	ldr r0, =message1
@	bl	printf


	
	beq end

	ldr r0, =file
	ldr r1, =flag
	mov r7, #5
	swi 0

	mov r4, r0

	mov r1, #0x706
	mov r2, #0x46
	bl	ioctl



	mov r0, r4			@ put fd in r0
	ldr r1, =LEDArray	@ array with led information
	mov r2, #193		@ 
	mov r7, #4
	swi 0

	
		

end:
	mov r0, r3
	ldr r7, =return
	ldr lr, [r7]
	bx	lr
	
	





.global	printf
.global ioctl

