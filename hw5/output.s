.text
## Codegen: Type Declaration ##
## Codegen: Type Declaration ##
## Codegen: Type Declaration ##
## Codegen: Type Declaration ##
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g1: .word
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g2: .float
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g3: .word
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g4: .float
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g5: .space 16
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g6: .space 8
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g7: .space 16
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g8: .space 8
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g9: .space 16
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_g10: .space 8
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
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_0: .float 2.000000
.align 2
.text
la x5, _CONSTANT_0
flw f0, 0(x5)
la x6, _GLOBAL_g2
fsw f0, 0(x1)
## Codegen: write() call Stmt ##
la x7, _GLOBAL_g1
ld x7, 0(x7)
mv a0, x7
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string "\n"
.align 4
.text
la x28, _CONSTANT_1
mv a0, x28
jal _write_str
## Codegen: write() call Stmt ##
la x29, _GLOBAL_g2
flw f2, 0(x29)
mv a0, x2
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_2: .string "\n"
.align 4
.text
la x30, _CONSTANT_2
mv a0, x30
jal _write_str
## Codegen: Return Stmt ##
.data
_CONSTANT_3: .word 0
.align 2
.text
la x31, _CONSTANT_3
lw x31, 0(x31)
mv a0, x31
j _FUNCTION_END_MAIN
_FUNCTION_END_MAIN:
addi sp, sp, 112
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
addi fp, sp, 8
ld fp, 0(fp)
jr ra
.data
_FRAME_SIZE_MAIN: .word 112
.text
