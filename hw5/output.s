.text
.text
_start_f00:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f00
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
.data
_CONSTANT_0: .word 1
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
mv a0, x5
la ra, _FUNCTION_END_f00
jr ra
_FUNCTION_END_f00:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f00: .word 8
.text
.text
_start_f01:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f01
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f00
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f01
jr ra
_FUNCTION_END_f01:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f01: .word 8
.text
.text
_start_f02:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f02
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f01
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f02
jr ra
_FUNCTION_END_f02:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f02: .word 8
.text
.text
_start_f03:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f03
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f02
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f03
jr ra
_FUNCTION_END_f03:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f03: .word 8
.text
.text
_start_f04:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f04
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f03
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f04
jr ra
_FUNCTION_END_f04:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f04: .word 8
.text
.text
_start_f05:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f05
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f04
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f05
jr ra
_FUNCTION_END_f05:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f05: .word 8
.text
.text
_start_f06:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f06
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f05
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f06
jr ra
_FUNCTION_END_f06:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f06: .word 8
.text
.text
_start_f07:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f07
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f06
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f07
jr ra
_FUNCTION_END_f07:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f07: .word 8
.text
.text
_start_f08:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f08
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f07
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f08
jr ra
_FUNCTION_END_f08:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f08: .word 8
.text
.text
_start_f09:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f09
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f08
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f09
jr ra
_FUNCTION_END_f09:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f09: .word 8
.text
.text
_start_f10:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f10
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f09
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f10
jr ra
_FUNCTION_END_f10:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f10: .word 8
.text
.text
_start_f11:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f11
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f10
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f11
jr ra
_FUNCTION_END_f11:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f11: .word 8
.text
.text
_start_f12:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f12
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f11
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f12
jr ra
_FUNCTION_END_f12:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f12: .word 8
.text
.text
_start_f13:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f13
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f12
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f13
jr ra
_FUNCTION_END_f13:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f13: .word 8
.text
.text
_start_f14:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f14
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f13
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f14
jr ra
_FUNCTION_END_f14:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f14: .word 8
.text
.text
_start_f15:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f15
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f14
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f15
jr ra
_FUNCTION_END_f15:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f15: .word 8
.text
.text
_start_f16:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f16
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f15
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f16
jr ra
_FUNCTION_END_f16:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f16: .word 8
.text
.text
_start_f17:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f17
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f16
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f17
jr ra
_FUNCTION_END_f17:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f17: .word 8
.text
.text
_start_f18:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f18
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f17
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f18
jr ra
_FUNCTION_END_f18:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f18: .word 8
.text
.text
_start_f19:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f19
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f18
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f19
jr ra
_FUNCTION_END_f19:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f19: .word 8
.text
.text
_start_f20:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f20
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f19
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f20
jr ra
_FUNCTION_END_f20:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f20: .word 8
.text
.text
_start_f21:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f21
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f20
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f21
jr ra
_FUNCTION_END_f21:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f21: .word 8
.text
.text
_start_f22:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f22
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f21
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f22
jr ra
_FUNCTION_END_f22:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f22: .word 8
.text
.text
_start_f23:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f23
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f22
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f23
jr ra
_FUNCTION_END_f23:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f23: .word 8
.text
.text
_start_f24:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f24
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f23
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f24
jr ra
_FUNCTION_END_f24:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f24: .word 8
.text
.text
_start_f25:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f25
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f24
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f25
jr ra
_FUNCTION_END_f25:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f25: .word 8
.text
.text
_start_f26:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f26
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f25
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f26
jr ra
_FUNCTION_END_f26:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f26: .word 8
.text
.text
_start_f27:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f27
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f26
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f27
jr ra
_FUNCTION_END_f27:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f27: .word 8
.text
.text
_start_f28:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f28
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f27
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f28
jr ra
_FUNCTION_END_f28:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f28: .word 8
.text
.text
_start_f29:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f29
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f28
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f29
jr ra
_FUNCTION_END_f29:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f29: .word 8
.text
.text
_start_f30:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f30
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f29
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f30
jr ra
_FUNCTION_END_f30:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f30: .word 8
.text
.text
_start_f31:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f31
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f30
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f31
jr ra
_FUNCTION_END_f31:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f31: .word 8
.text
.text
_start_f32:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f32
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f31
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f32
jr ra
_FUNCTION_END_f32:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f32: .word 8
.text
.text
_start_f33:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f33
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f32
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f33
jr ra
_FUNCTION_END_f33:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f33: .word 8
.text
.text
_start_f34:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f34
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f33
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f34
jr ra
_FUNCTION_END_f34:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f34: .word 8
.text
.text
_start_f35:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f35
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f34
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f35
jr ra
_FUNCTION_END_f35:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f35: .word 8
.text
.text
_start_f36:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f36
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f35
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f36
jr ra
_FUNCTION_END_f36:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f36: .word 8
.text
.text
_start_f37:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f37
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f36
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f37
jr ra
_FUNCTION_END_f37:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f37: .word 8
.text
.text
_start_f38:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f38
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f37
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f38
jr ra
_FUNCTION_END_f38:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f38: .word 8
.text
.text
_start_f39:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_f39
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Return Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f38
mv x5, a0
mv a0, x5
la ra, _FUNCTION_END_f39
jr ra
_FUNCTION_END_f39:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_f39: .word 8
.text
.text
_start_Work:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_Work
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: Assign Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f00
mv x5, a0
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f01
mv x6, a0
ld x7, -16(fp)
addw x28, x7, x6
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f02
mv x29, a0
ld x30, -24(fp)
addw x31, x30, x29
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f03
mv x10, a0
ld x11, -16(fp)
addw x12, x11, x10
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f04
mv x13, a0
ld x14, -24(fp)
addw x15, x14, x13
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f05
mv x16, a0
ld x17, -16(fp)
addw x7, x17, x16
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f06
mv x6, a0
ld x30, -24(fp)
addw x29, x30, x6
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f07
mv x11, a0
ld x10, -16(fp)
addw x14, x10, x11
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f08
mv x13, a0
ld x17, -24(fp)
addw x16, x17, x13
## Codegen: Normal Function Call Stmt ##
sd x16, -16(fp)
call _start_f09
mv x30, a0
ld x6, -16(fp)
addw x10, x6, x30
## Codegen: Normal Function Call Stmt ##
sd x10, -24(fp)
call _start_f10
mv x11, a0
ld x17, -24(fp)
addw x13, x17, x11
## Codegen: Normal Function Call Stmt ##
sd x13, -16(fp)
call _start_f11
mv x6, a0
ld x30, -16(fp)
addw x17, x30, x6
## Codegen: Normal Function Call Stmt ##
sd x17, -24(fp)
call _start_f12
mv x11, a0
ld x30, -24(fp)
addw x6, x30, x11
## Codegen: Normal Function Call Stmt ##
sd x6, -16(fp)
call _start_f13
mv x30, a0
ld x11, -16(fp)
addw x11, x11, x30
## Codegen: Normal Function Call Stmt ##
sd x11, -24(fp)
call _start_f14
mv x30, a0
ld x5, -24(fp)
addw x5, x5, x30
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f15
mv x30, a0
ld x28, -16(fp)
addw x28, x28, x30
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f16
mv x30, a0
ld x31, -24(fp)
addw x31, x31, x30
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f17
mv x30, a0
ld x12, -16(fp)
addw x12, x12, x30
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f18
mv x30, a0
ld x15, -24(fp)
addw x15, x15, x30
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f19
mv x30, a0
ld x7, -16(fp)
addw x7, x7, x30
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f20
mv x30, a0
ld x29, -24(fp)
addw x29, x29, x30
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f21
mv x30, a0
ld x14, -16(fp)
addw x14, x14, x30
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f22
mv x30, a0
ld x16, -24(fp)
addw x16, x16, x30
## Codegen: Normal Function Call Stmt ##
sd x16, -16(fp)
call _start_f23
mv x30, a0
ld x10, -16(fp)
addw x10, x10, x30
## Codegen: Normal Function Call Stmt ##
sd x10, -24(fp)
call _start_f24
mv x30, a0
ld x13, -24(fp)
addw x13, x13, x30
## Codegen: Normal Function Call Stmt ##
sd x13, -16(fp)
call _start_f25
mv x30, a0
ld x17, -16(fp)
addw x17, x17, x30
## Codegen: Normal Function Call Stmt ##
sd x17, -24(fp)
call _start_f26
mv x30, a0
ld x6, -24(fp)
addw x6, x6, x30
## Codegen: Normal Function Call Stmt ##
sd x6, -16(fp)
call _start_f27
mv x30, a0
ld x11, -16(fp)
addw x11, x11, x30
## Codegen: Normal Function Call Stmt ##
sd x11, -24(fp)
call _start_f28
mv x30, a0
ld x5, -24(fp)
addw x5, x5, x30
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f29
mv x30, a0
ld x28, -16(fp)
addw x28, x28, x30
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f30
mv x30, a0
ld x31, -24(fp)
addw x31, x31, x30
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f31
mv x30, a0
ld x12, -16(fp)
addw x12, x12, x30
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f32
mv x30, a0
ld x15, -24(fp)
addw x15, x15, x30
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f33
mv x30, a0
ld x7, -16(fp)
addw x7, x7, x30
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f34
mv x30, a0
ld x29, -24(fp)
addw x29, x29, x30
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f35
mv x30, a0
ld x14, -16(fp)
addw x14, x14, x30
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f36
mv x30, a0
ld x16, -24(fp)
addw x16, x16, x30
## Codegen: Normal Function Call Stmt ##
sd x16, -16(fp)
call _start_f37
mv x30, a0
ld x10, -16(fp)
addw x10, x10, x30
## Codegen: Normal Function Call Stmt ##
sd x10, -24(fp)
call _start_f38
mv x30, a0
ld x13, -24(fp)
addw x13, x13, x30
## Codegen: Normal Function Call Stmt ##
sd x13, -16(fp)
call _start_f39
mv x30, a0
ld x17, -16(fp)
addw x17, x17, x30
mv x9, x17
## Codegen: Assign Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_f00
mv x30, a0
## Codegen: Normal Function Call Stmt ##
sd x30, -24(fp)
call _start_f01
mv x17, a0
ld x6, -24(fp)
mulw x6, x6, x17
## Codegen: Normal Function Call Stmt ##
sd x6, -16(fp)
call _start_f02
mv x17, a0
ld x11, -16(fp)
mulw x11, x11, x17
## Codegen: Normal Function Call Stmt ##
sd x11, -24(fp)
call _start_f03
mv x17, a0
ld x5, -24(fp)
mulw x5, x5, x17
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f04
mv x17, a0
ld x28, -16(fp)
mulw x28, x28, x17
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f05
mv x17, a0
ld x31, -24(fp)
mulw x31, x31, x17
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f06
mv x17, a0
ld x12, -16(fp)
mulw x12, x12, x17
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f07
mv x17, a0
ld x15, -24(fp)
mulw x15, x15, x17
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f08
mv x17, a0
ld x7, -16(fp)
mulw x7, x7, x17
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f09
mv x17, a0
ld x29, -24(fp)
mulw x29, x29, x17
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f10
mv x17, a0
ld x14, -16(fp)
mulw x14, x14, x17
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f11
mv x17, a0
ld x16, -24(fp)
mulw x16, x16, x17
## Codegen: Normal Function Call Stmt ##
sd x16, -16(fp)
call _start_f12
mv x17, a0
ld x10, -16(fp)
mulw x10, x10, x17
## Codegen: Normal Function Call Stmt ##
sd x10, -24(fp)
call _start_f13
mv x17, a0
ld x13, -24(fp)
mulw x13, x13, x17
## Codegen: Normal Function Call Stmt ##
sd x13, -16(fp)
call _start_f14
mv x17, a0
ld x30, -16(fp)
mulw x30, x30, x17
## Codegen: Normal Function Call Stmt ##
sd x30, -24(fp)
call _start_f15
mv x17, a0
ld x6, -24(fp)
mulw x6, x6, x17
## Codegen: Normal Function Call Stmt ##
sd x6, -16(fp)
call _start_f16
mv x17, a0
ld x11, -16(fp)
mulw x11, x11, x17
## Codegen: Normal Function Call Stmt ##
sd x11, -24(fp)
call _start_f17
mv x17, a0
ld x5, -24(fp)
mulw x5, x5, x17
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f18
mv x17, a0
ld x28, -16(fp)
mulw x28, x28, x17
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f19
mv x17, a0
ld x31, -24(fp)
mulw x31, x31, x17
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f20
mv x17, a0
ld x12, -16(fp)
mulw x12, x12, x17
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f21
mv x17, a0
ld x15, -24(fp)
mulw x15, x15, x17
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f22
mv x17, a0
ld x7, -16(fp)
mulw x7, x7, x17
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f23
mv x17, a0
ld x29, -24(fp)
mulw x29, x29, x17
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f24
mv x17, a0
ld x14, -16(fp)
mulw x14, x14, x17
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f25
mv x17, a0
ld x16, -24(fp)
mulw x16, x16, x17
## Codegen: Normal Function Call Stmt ##
sd x16, -16(fp)
call _start_f26
mv x17, a0
ld x10, -16(fp)
mulw x10, x10, x17
## Codegen: Normal Function Call Stmt ##
sd x10, -24(fp)
call _start_f27
mv x17, a0
ld x13, -24(fp)
mulw x13, x13, x17
## Codegen: Normal Function Call Stmt ##
sd x13, -16(fp)
call _start_f28
mv x17, a0
ld x30, -16(fp)
mulw x30, x30, x17
## Codegen: Normal Function Call Stmt ##
sd x30, -24(fp)
call _start_f29
mv x17, a0
ld x6, -24(fp)
mulw x6, x6, x17
## Codegen: Normal Function Call Stmt ##
sd x6, -16(fp)
call _start_f30
mv x17, a0
ld x11, -16(fp)
mulw x11, x11, x17
## Codegen: Normal Function Call Stmt ##
sd x11, -24(fp)
call _start_f31
mv x17, a0
ld x5, -24(fp)
mulw x5, x5, x17
## Codegen: Normal Function Call Stmt ##
sd x5, -16(fp)
call _start_f32
mv x17, a0
ld x28, -16(fp)
mulw x28, x28, x17
## Codegen: Normal Function Call Stmt ##
sd x28, -24(fp)
call _start_f33
mv x17, a0
ld x31, -24(fp)
mulw x31, x31, x17
## Codegen: Normal Function Call Stmt ##
sd x31, -16(fp)
call _start_f34
mv x17, a0
ld x12, -16(fp)
mulw x12, x12, x17
## Codegen: Normal Function Call Stmt ##
sd x12, -24(fp)
call _start_f35
mv x17, a0
ld x15, -24(fp)
mulw x15, x15, x17
## Codegen: Normal Function Call Stmt ##
sd x15, -16(fp)
call _start_f36
mv x17, a0
ld x7, -16(fp)
mulw x7, x7, x17
## Codegen: Normal Function Call Stmt ##
sd x7, -24(fp)
call _start_f37
mv x17, a0
ld x29, -24(fp)
mulw x29, x29, x17
## Codegen: Normal Function Call Stmt ##
sd x29, -16(fp)
call _start_f38
mv x17, a0
ld x14, -16(fp)
mulw x14, x14, x17
## Codegen: Normal Function Call Stmt ##
sd x14, -24(fp)
call _start_f39
mv x17, a0
ld x16, -24(fp)
mulw x16, x16, x17
mv x18, x16
## Codegen: Return Stmt ##
addw x17, x9, x18
mv a0, x17
la ra, _FUNCTION_END_Work
jr ra
_FUNCTION_END_Work:
li t0, 24
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_Work: .word 24
.text
.text
_start_MAIN:
sd ra, 0(sp)
sd fp, -8(sp)
addi fp, sp, -8
addi sp, sp, -16
addi sp, sp, -136
sd x9, 0(sp)
sd x18, 8(sp)
sd x19, 16(sp)
sd x20, 24(sp)
sd x21, 32(sp)
sd x22, 40(sp)
sd x23, 48(sp)
sd x24, 56(sp)
sd x25, 64(sp)
sd x26, 72(sp)
sd x27, 80(sp)
fsw f8, 88(sp)
fsw f9, 92(sp)
fsw f18, 96(sp)
fsw f19, 100(sp)
fsw f20, 104(sp)
fsw f21, 108(sp)
fsw f22, 112(sp)
fsw f23, 116(sp)
fsw f24, 120(sp)
fsw f25, 124(sp)
fsw f26, 128(sp)
fsw f27, 132(sp)
la ra, _FRAME_SIZE_MAIN
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: write() call Stmt ##
## Codegen: Normal Function Call Stmt ##
call _start_Work
mv x5, a0
mv a0, x5
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string "\n"
.align 4
.text
la x6, _CONSTANT_1
mv a0, x6
call _write_str
_FUNCTION_END_MAIN:
li t0, 8
add sp, sp, t0
ld x9, 0(sp)
ld x18, 8(sp)
ld x19, 16(sp)
ld x20, 24(sp)
ld x21, 32(sp)
ld x22, 40(sp)
ld x23, 48(sp)
ld x24, 56(sp)
ld x25, 64(sp)
ld x26, 72(sp)
ld x27, 80(sp)
flw f8, 88(sp)
flw f9, 92(sp)
flw f18, 96(sp)
flw f19, 100(sp)
flw f20, 104(sp)
flw f21, 108(sp)
flw f22, 112(sp)
flw f23, 116(sp)
flw f24, 120(sp)
flw f25, 124(sp)
flw f26, 128(sp)
flw f27, 132(sp)
addi sp, sp, 152
ld ra, 8(fp)
addi fp, sp, -8
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_MAIN: .word 8
.text
