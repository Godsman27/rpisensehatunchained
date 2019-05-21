

.data
LEDArray: 	.skip 193

.balign 4
message1:	.asciz "Number:\t%d\n"

.balign 4
return:	.word 0

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

	ldr r6, =LEDArray
	
	
		@ if r0 < 0 && r0 >=8	
	cmp r0, #0			
	blo case_true
	cmp r0, #8
	bhs case_true
other:					@ if r1 < 0 && r1 >= 8
	cmp r1, #0
	blo	case_true
	cmp r1, #8
	bhs case_true

	



case_different:			@ if
	
	
			@ i = (y * 24) + x
	mov r8, #24
	mla	r1, r8, r1, r0
	add r1, r6, r1		
	add r1, r1, #1

	


	cmp	r3, #0

	mov	r7, r2, LSR #10
	and r7, #0x3e
	str r7, [r1]
	

	mov	r7, r2, LSR #5
	and r7, #0x3f
	str	r7, [r1, #+8]
	
	mov	r7, r2, LSL #1
	and r7, #0x3e
	str r7, [r1, #+16]

		
	mov	r7, #1 
	str r7, [r6]	
	
	
	beq end

	mov r0, #3
	ldr r1, =LEDArray
	mov r2, #193	
	bl	write

	

end:
	mov r0, r3
	ldr r7, =return
	ldr lr, [r7]
	bx	lr
	
case_true:				@ else
	mov r0, r3
	ldr r7, =return
	ldr lr, [r7]	
	bx 	lr	





.global	printf


