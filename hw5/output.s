.text
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_n: .float 0
_GLOBAL_l: .float 0
_GLOBAL_r: .float 0
_GLOBAL_mid: .float 0
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_iter: .word 0
.text
_start_SquareRoot:
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
la ra, _FRAME_SIZE_SquareRoot
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_0: .word 0
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
la x6, _GLOBAL_l
fsw f5, 0(x6)
## Codegen: Assign Stmt ##
la x7, _GLOBAL_n
flw f0, 0(x7)
la x28, _GLOBAL_r
fsw f0, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_1: .word 0
.align 2
.text
la x29, _CONSTANT_1
lw x29, 0(x29)
la x30, _GLOBAL_iter
sw x29, 0(x30)
## Codegen: While Stmt ##
_WHILE_LABEL_0:
la x31, _GLOBAL_r
flw f1, 0(x31)
la x5, _GLOBAL_l
flw f2, 0(x5)
fsub.s f3, f1, f2
.data
_CONSTANT_2: .float 0.0001
.align 2
.text
la x6, _CONSTANT_2
flw f4, 0(x6)
flt.s x7, f4, f3
beqz x7, _BOOL_SHORT_0
la x28, _GLOBAL_iter
lw x28, 0(x28)
.data
_CONSTANT_3: .word 100
.align 2
.text
la x29, _CONSTANT_3
lw x29, 0(x29)
bge x28, x29, _BOOL_SHORT_0
addi x30, x0, 1
j _BOOL_EXIT_0
_BOOL_SHORT_0:
mv x30, x0
_BOOL_EXIT_0:
beqz x30, _WHILE_EXIT_0
## Codegen: Block ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_4: .string "iter "
.align 4
.text
la x31, _CONSTANT_4
mv a0, x31
jal _write_str
## Codegen: write() call Stmt ##
la x5, _GLOBAL_iter
lw x5, 0(x5)
mv a0, x5
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_5: .string ": "
.align 4
.text
la x6, _CONSTANT_5
mv a0, x6
jal _write_str
## Codegen: write() call Stmt ##
la x28, _GLOBAL_l
flw f5, 0(x28)
fmv.s fa0, f5
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_6: .string "\n"
.align 4
.text
la x29, _CONSTANT_6
mv a0, x29
jal _write_str
## Codegen: Assign Stmt ##
.data
_CONSTANT_7: .float 0.5
.align 2
.text
la x7, _CONSTANT_7
flw f6, 0(x7)
la x30, _GLOBAL_l
flw f7, 0(x30)
la x31, _GLOBAL_r
flw f28, 0(x31)
fadd.s f29, f7, f28
fmul.s f30, f6, f29
la x5, _GLOBAL_mid
fsw f30, 0(x5)
## Codegen: If Stmt ##
la x6, _GLOBAL_mid
flw f31, 0(x6)
la x28, _GLOBAL_mid
flw f0, 0(x28)
fmul.s f1, f31, f0
la x29, _GLOBAL_n
flw f2, 0(x29)
flt.s x7, f1, f2
beqz x7, _ELSE_LABEL_0
## Codegen: Assign Stmt ##
la x30, _GLOBAL_mid
flw f3, 0(x30)
la x31, _GLOBAL_l
fsw f3, 0(x31)
fmv.s f4, f31
j _IF_EXIT_0
_ELSE_LABEL_0:
## Codegen: Assign Stmt ##
la x5, _GLOBAL_mid
flw f5, 0(x5)
la x6, _GLOBAL_r
fsw f5, 0(x6)
fmv.s f7, f6
_IF_EXIT_0:
## Codegen: Assign Stmt ##
la x28, _GLOBAL_iter
lw x28, 0(x28)
.data
_CONSTANT_8: .word 1
.align 2
.text
la x29, _CONSTANT_8
lw x29, 0(x29)
addw x7, x28, x29
la x30, _GLOBAL_iter
sw x7, 0(x30)
j _WHILE_LABEL_0
_WHILE_EXIT_0:
## Codegen: write() call Stmt ##
fsw f4, -20(fp)
fsw f7, -24(fp)
.data
_CONSTANT_9: .string "iter "
.align 4
.text
la x31, _CONSTANT_9
mv a0, x31
jal _write_str
## Codegen: write() call Stmt ##
la x5, _GLOBAL_iter
lw x5, 0(x5)
mv a0, x5
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_10: .string ": "
.align 4
.text
la x6, _CONSTANT_10
mv a0, x6
jal _write_str
## Codegen: write() call Stmt ##
la x28, _GLOBAL_l
flw f28, 0(x28)
fmv.s fa0, f28
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_11: .string "\n"
.align 4
.text
la x29, _CONSTANT_11
mv a0, x29
jal _write_str
## Codegen: Return Stmt ##
la x7, _GLOBAL_l
flw f6, 0(x7)
fmv.s fa0, f6
j _FUNCTION_END_SquareRoot
_FUNCTION_END_SquareRoot:
li t0, 36
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
jr ra
.data
_FRAME_SIZE_SquareRoot: .word 36
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
## Codegen: Assign Stmt ##
.data
_CONSTANT_12: .word 1
.align 2
.text
la x5, _CONSTANT_12
lw x5, 0(x5)
la x6, _GLOBAL_n
fsw f5, 0(x6)
## Codegen: While Stmt ##
_WHILE_LABEL_1:
la x7, _GLOBAL_n
flw f0, 0(x7)
.data
_CONSTANT_13: .float 10
.align 2
.text
la x28, _CONSTANT_13
flw f1, 0(x28)
fle.s x29, f0, f1
beqz x29, _WHILE_EXIT_1
## Codegen: Block ##
## Codegen: write() call Stmt ##
## Codegen: Normal Function Call Stmt ##
jal _start_SquareRoot
fmv.s f2, fa0
fmv.s fa0, f2
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_14: .string "\n"
.align 4
.text
la x30, _CONSTANT_14
mv a0, x30
jal _write_str
## Codegen: Assign Stmt ##
la x31, _GLOBAL_n
flw f3, 0(x31)
.data
_CONSTANT_15: .float 1
.align 2
.text
la x5, _CONSTANT_15
flw f4, 0(x5)
fadd.s f5, f3, f4
la x6, _GLOBAL_n
fsw f5, 0(x6)
j _WHILE_LABEL_1
_WHILE_EXIT_1:
_FUNCTION_END_MAIN:
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
jr ra
.data
_FRAME_SIZE_MAIN: .word 24
.text
