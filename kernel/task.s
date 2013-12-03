	.file	"task.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.comm	aySchedSleepCounts,12,1
	.comm	aySchedIRQList,3,1
	.comm	ayTaskList,32,1
	.comm	ayCurrentTask,1,1
	.text
.global	AYTaskInitList
	.type	AYTaskInitList, @function
AYTaskInitList:
	push r28
	push r29
	push __zero_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
/* stack size = 3 */
.L__stack_usage = 3
	sts ayCurrentTask,__zero_reg__
	sts ayTaskList,__zero_reg__
	ldi r24,lo8(-1)
	ldi r25,lo8(8)
	sts ayTaskList+1+1,r25
	sts ayTaskList+1,r24
	ldi r24,lo8(gs(main))
	ldi r25,hi8(gs(main))
	sts ayTaskList+3+1,r25
	sts ayTaskList+3,r24
	ldi r24,lo8(3)
	sts ayTaskList+5,r24
	sts ayTaskList+6+1,__zero_reg__
	sts ayTaskList+6,__zero_reg__
	ldi r24,lo8(1)
	std Y+1,r24
	rjmp .L2
.L3:
	ldd r24,Y+1
	mov r24,r24
	ldi r25,0
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList))
	sbci r25,hi8(-(ayTaskList))
	ldi r18,lo8(-1)
	movw r30,r24
	st Z,r18
	ldd r24,Y+1
	mov r24,r24
	ldi r25,0
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	ldi r18,lo8(-1)
	movw r30,r24
	st Z,r18
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L2:
	ldd r24,Y+1
	cpi r24,lo8(4)
	brlo .L3
/* epilogue start */
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	AYTaskInitList, .-AYTaskInitList
.global	AYTaskCreate
	.type	AYTaskCreate, @function
AYTaskCreate:
	push r28
	push r29
	rcall .
	push __zero_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
/* stack size = 5 */
.L__stack_usage = 5
	std Y+3,r25
	std Y+2,r24
	ldi r24,lo8(1)
	std Y+1,r24
	rjmp .L5
.L8:
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList))
	sbci r25,hi8(-(ayTaskList))
	movw r30,r24
	ld r24,Z
	tst r24
	brlt .+2
	rjmp .L6
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList))
	sbci r25,hi8(-(ayTaskList))
	ldd r18,Y+1
	movw r30,r24
	st Z,r18
	ldd r24,Y+1
	mov r20,r24
	clr r21
	sbrc r20,7
	com r21
	ldd r24,Y+1
	mov r18,r24
	clr r19
	sbrc r18,7
	com r19
	ldi r24,0
	ldi r25,0
	sub r24,r18
	sbc r25,r19
	lsr r25
	mov r25,r24
	clr r24
	ror r25
	ror r24
	subi r24,1
	sbci r25,-9
	movw r18,r24
	movw r24,r20
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+1))
	sbci r25,hi8(-(ayTaskList+1))
	movw r30,r24
	std Z+1,r19
	st Z,r18
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+3))
	sbci r25,hi8(-(ayTaskList+3))
	ldd r18,Y+2
	ldd r19,Y+3
	movw r30,r24
	std Z+1,r19
	st Z,r18
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	movw r30,r24
	st Z,__zero_reg__
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+6))
	sbci r25,hi8(-(ayTaskList+6))
	movw r30,r24
	std Z+1,__zero_reg__
	st Z,__zero_reg__
	rjmp .L7
.L6:
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L5:
	ldd r24,Y+1
	cpi r24,lo8(4)
	brge .+2
	rjmp .L8
.L7:
	ldd r24,Y+1
	cpi r24,lo8(4)
	brne .L9
	ldi r24,lo8(-1)
	rjmp .L10
.L9:
	ldd r24,Y+1
.L10:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	AYTaskCreate, .-AYTaskCreate
.global	AYTaskEnd
	.type	AYTaskEnd, @function
AYTaskEnd:
	push r28
	push r29
	push __zero_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
/* stack size = 3 */
.L__stack_usage = 3
	std Y+1,r24
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList))
	sbci r25,hi8(-(ayTaskList))
	ldi r18,lo8(-1)
	movw r30,r24
	st Z,r18
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+1))
	sbci r25,hi8(-(ayTaskList+1))
	movw r30,r24
	std Z+1,__zero_reg__
	st Z,__zero_reg__
/* epilogue start */
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	AYTaskEnd, .-AYTaskEnd
	.section	.rodata
.LC0:
	.string	"C"
	.text
.global	AYTaskWait
	.type	AYTaskWait, @function
AYTaskWait:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call AYSerialString
	nop
.L13:
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	movw r30,r24
	ld r24,Z
	cpi r24,lo8(2)
	breq .L13
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	AYTaskWait, .-AYTaskWait
.global	AYTaskWaitMs
	.type	AYTaskWaitMs, @function
AYTaskWaitMs:
	push r28
	push r29
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	std Y+2,r25
	std Y+1,r24
/* #APP */
 ;  104 "task.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	lds r24,ayCurrentTask
	mov r18,r24
	clr r19
	sbrc r18,7
	com r19
	movw r24,r18
	lsl r24
	rol r25
	add r24,r18
	adc r25,r19
	subi r24,lo8(-(aySchedSleepCounts))
	sbci r25,hi8(-(aySchedSleepCounts))
	movw r30,r24
	ld r25,Z
	lds r24,ayCurrentTask
	cp r25,r24
	breq .L15
	lds r24,ayCurrentTask
	mov r18,r24
	clr r19
	sbrc r18,7
	com r19
	lds r20,ayCurrentTask
	movw r24,r18
	lsl r24
	rol r25
	add r24,r18
	adc r25,r19
	subi r24,lo8(-(aySchedSleepCounts))
	sbci r25,hi8(-(aySchedSleepCounts))
	movw r30,r24
	st Z,r20
	lds r24,ayCurrentTask
	mov r18,r24
	clr r19
	sbrc r18,7
	com r19
	movw r24,r18
	lsl r24
	rol r25
	add r24,r18
	adc r25,r19
	subi r24,lo8(-(aySchedSleepCounts+1))
	sbci r25,hi8(-(aySchedSleepCounts+1))
	ldd r18,Y+1
	ldd r19,Y+2
	movw r30,r24
	std Z+1,r19
	st Z,r18
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	ldi r18,lo8(2)
	movw r30,r24
	st Z,r18
.L15:
/* #APP */
 ;  114 "task.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	call AYTaskWait
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	AYTaskWaitMs, .-AYTaskWaitMs
.global	AYTaskWaitInt
	.type	AYTaskWaitInt, @function
AYTaskWaitInt:
	push r28
	push r29
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	std Y+2,r25
	std Y+1,r24
/* #APP */
 ;  121 "task.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldd r24,Y+1
	ldd r25,Y+2
	subi r24,lo8(-(aySchedIRQList))
	sbci r25,hi8(-(aySchedIRQList))
	movw r30,r24
	ld r24,Z
	tst r24
	brge .L17
	lds r18,ayCurrentTask
	ldd r24,Y+1
	ldd r25,Y+2
	subi r24,lo8(-(aySchedIRQList))
	sbci r25,hi8(-(aySchedIRQList))
	movw r30,r24
	st Z,r18
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	ldi r18,lo8(2)
	movw r30,r24
	st Z,r18
.L17:
/* #APP */
 ;  130 "task.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	call AYTaskWait
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	AYTaskWaitInt, .-AYTaskWaitInt
	.section	.rodata
.LC1:
	.string	"PC : "
.LC2:
	.string	"\n\r"
	.text
.global	__vector_14
	.type	__vector_14, @function
__vector_14:
	push r1
	push r0
	lds r0,95
	push r0
	clr __zero_reg__
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,6
	out __SP_H__,r29
	out __SP_L__,r28
/* prologue: Signal */
/* frame size = 6 */
/* stack size = 25 */
.L__stack_usage = 25
	call AYSchedUpdateCounts
	std Y+2,r24
	ldd r24,Y+2
	tst r24
	brlt .L19
	lds r24,ayCurrentTask
	ldd r25,Y+2
	cp r25,r24
	breq .L19
	ldd r24,Y+2
	std Y+1,r24
	rjmp .L20
.L19:
	lds r24,ayCurrentTask
	call AYSchedSelectTask
	std Y+1,r24
.L20:
	lds r24,ayCurrentTask
	ldd r25,Y+1
	cp r25,r24
	brne .+2
	rjmp .L18
/* #APP */
 ;  151 "task.c" 1
	in   r16, __SP_L__    
	in   r17, __SP_H__    
	
 ;  0 "" 2
/* #NOAPP */
	std Y+3,r16
	std Y+4,r17
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	ldd r18,Y+4
	mov r18,r18
	ldi r19,0
	mov r21,r18
	clr r20
	ldd r18,Y+3
	mov r18,r18
	ldi r19,0
	add r18,r20
	adc r19,r21
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+1))
	sbci r25,hi8(-(ayTaskList+1))
	movw r30,r24
	std Z+1,r19
	st Z,r18
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	movw r30,r24
	ld r24,Z
	cpi r24,lo8(3)
	brne .L22
	lds r24,ayCurrentTask
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	ldi r18,lo8(1)
	movw r30,r24
	st Z,r18
.L22:
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+1))
	sbci r25,hi8(-(ayTaskList+1))
	movw r30,r24
	ld r24,Z
	ldd r25,Z+1
	std Y+3,r24
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+1))
	sbci r25,hi8(-(ayTaskList+1))
	movw r30,r24
	ld r24,Z
	ldd r25,Z+1
	mov r24,r25
	clr r25
	std Y+4,r24
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	movw r30,r24
	ld r24,Z
	tst r24
	breq .+2
	rjmp .L23
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+3))
	sbci r25,hi8(-(ayTaskList+3))
	movw r30,r24
	ld r24,Z
	ldd r25,Z+1
	std Y+5,r24
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+3))
	sbci r25,hi8(-(ayTaskList+3))
	movw r30,r24
	ld r24,Z
	ldd r25,Z+1
	mov r24,r25
	clr r25
	std Y+6,r24
	ldi r24,lo8(.LC1)
	ldi r25,hi8(.LC1)
	call AYSerialString
	ldd r24,Y+6
	mov r24,r24
	ldi r25,0
	mov r19,r24
	clr r18
	ldd r24,Y+5
	mov r24,r24
	ldi r25,0
	add r24,r18
	adc r25,r19
	call AYSerialHex
	ldi r24,lo8(.LC2)
	ldi r25,hi8(.LC2)
	call AYSerialString
	ldd r24,Y+3
	ldd r25,Y+4
	ldd r18,Y+5
	ldd r19,Y+6
/* #APP */
 ;  174 "task.c" 1
	out    __SP_L__, r24   
	out    __SP_H__, r25   
	push   r18             
	push   r19             
	clr    r0             
	push   r0             
	push   r0             
	in     r0, __SREG__   
	push   r0             
	clr    r0             
	clr    r1             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	push   r0             
	
 ;  0 "" 2
/* #NOAPP */
	rjmp .L24
.L23:
	ldd r24,Y+3
	ldd r25,Y+4
/* #APP */
 ;  208 "task.c" 1
	out    __SP_L__, r24   
	out    __SP_H__, r25   
	
 ;  0 "" 2
/* #NOAPP */
.L24:
	ldd r24,Y+1
	sts ayCurrentTask,r24
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(ayTaskList+5))
	sbci r25,hi8(-(ayTaskList+5))
	ldi r18,lo8(3)
	movw r30,r24
	st Z,r18
.L18:
/* epilogue start */
	adiw r28,6
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r29
	pop r28
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	pop r0
	sts 95,r0
	pop r0
	pop r1
	reti
	.size	__vector_14, .-__vector_14
	.ident	"GCC: (GNU) 4.7.2"
.global __do_copy_data
.global __do_clear_bss
