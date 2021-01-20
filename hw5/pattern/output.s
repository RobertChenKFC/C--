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
## Codegen: Local Variable Declaration ##
## Codegen: Variable Declaration - Local Variable Initialization ##
.data
_CONSTANT_0: .float 1
.align 2
.text
la x5, _CONSTANT_0
flw f0, 0(x5)
fmv.s f8, f0
## Codegen: While Stmt ##
_WHILE_LABEL_0:
fclass.s x6, f8
andi x6, x6, 24
beqz x6, _SKIP_0
la ra, _WHILE_EXIT_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string "Hello world!\n"
.align 4
.text
la x7, _CONSTANT_1
mv a0, x7
call _write_str
## Codegen: Assign Stmt ##
.data
_CONSTANT_2: .float 0
.align 2
.text
la x28, _CONSTANT_2
flw f1, 0(x28)
fmv.s f8, f1
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
_FUNCTION_END_MAIN:
li t0, 16
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
_FRAME_SIZE_MAIN: .word 16
.text
