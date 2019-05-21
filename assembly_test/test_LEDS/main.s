

.data

LEDArray: 	.skip 193

.text
.global main
.type	main,%function
main: 
	


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
	
	
				@ i = y * 24 + x
	mov r8, #24
	mla	r1, r8, r1, r0

	cmp	r3, #0

	mov	r7, r2, LSR #10
	and r7, #0x3e
	strb r7, [r5]

	mov	r7, r2, LSR #5
	and r7, #0x3f
	strb	r7, [r5, #+8]

	mov	r7, r2, LSL #1
	and r7, #0x3e
	strb r7, [r5, #+16]

	

	beq end
	
	mov r0, #3
	ldr r1, [r6]
	mov r2, #192	
	bl	i2cWrite

	

end:
	mov r0, #1
	bx	lr
	
case_true:				@ else
	mov r0, #0




.global i2cWrite
.type	i2cWrite,%function
i2cWrite:
	push	{r4,r5,r6,r7,r8,lr}
	mov		r6, r0	@ iHandle

	mov		r8, r1	@ ucAddr
	mov		r1, r0	@ iHandle
	mov 	r5, r3	@ iLen
	mov 	r7, r2	@ buf

	pop		{r4,r5,r6,r7,r8,lr}
	






