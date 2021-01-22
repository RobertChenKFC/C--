.text
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_func:
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
la ra, _FRAME_SIZE_func
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: If Stmt ##
## Restoring 10 ##
## Restored to 10 ##
.data
_CONSTANT_0: .word 1
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
slt x6, x5, x10
bnez x6, _SKIP_0
la ra, _ELSE_LABEL_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: Return Stmt ##
## Restoring 10 ##
## Restored to 10 ##
## Restoring 11 ##
## Restored to 11 ##
mulw x7, x10, x11
.data
_CONSTANT_1: .word 3
.align 2
.text
la x28, _CONSTANT_1
lw x28, 0(x28)
subw x29, x7, x28
mv a0, x29
la ra, _FUNCTION_END_func
jr ra
la ra, _IF_EXIT_0
jr ra
_ELSE_LABEL_0:
## Codegen: Block ##
## Codegen: Return Stmt ##
## Restoring 13 ##
## Restored to 13 ##
## Restoring 12 ##
## Restored to 12 ##
.data
_CONSTANT_2: .word 2
.align 2
.text
la x30, _CONSTANT_2
lw x30, 0(x30)
subw x31, x12, x30
mulw x5, x13, x31
.data
_CONSTANT_3: .word 3
.align 2
.text
la x6, _CONSTANT_3
lw x6, 0(x6)
subw x7, x5, x6
mv a0, x7
la ra, _FUNCTION_END_func
jr ra
_IF_EXIT_0:
_FUNCTION_END_func:
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
_FRAME_SIZE_func: .word 16
.text
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
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
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: Variable Declaration - Local Variable Initialization ##
.data
_CONSTANT_4: .word 1
.align 2
.text
la x5, _CONSTANT_4
lw x5, 0(x5)
mv x9, x5
## Codegen: Variable Declaration - Local Variable Initialization ##
.data
_CONSTANT_5: .word 2
.align 2
.text
la x6, _CONSTANT_5
lw x6, 0(x6)
mv x18, x6
## Codegen: Local Variable Declaration ##
## Codegen: Variable Declaration - Local Variable Initialization ##
.data
_CONSTANT_6: .word 1
.align 2
.text
la x7, _CONSTANT_6
lw x7, 0(x7)
mv x19, x7
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
## Restoring 18 ##
## Restored to 18 ##
mulw x28, x9, x18
mv x20, x28
## Codegen: Assign Stmt ##
## Codegen: Normal Function Call Stmt ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_7: .word 1
.align 2
.text
la x29, _CONSTANT_7
lw x29, 0(x29)
subw x30, x9, x29
## Restoring 18 ##
## Restored to 18 ##
.data
_CONSTANT_8: .word 2
.align 2
.text
la x31, _CONSTANT_8
lw x31, 0(x31)
mulw x5, x18, x31
## Restoring 20 ##
## Restored to 20 ##
## Restoring 9 ##
## Restored to 9 ##
## Restoring 20 ##
## Restored to 20 ##
subw x6, x9, x20
li ra, 32
add sp, sp, ra
## saving int caller saved register ##
sd x30, -12(fp)
sd x5, -32(fp)
sd x6, -40(fp)
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
ld x7, -12(fp)
mv x10, x7
ld x28, -32(fp)
mv x11, x28
mv x12, x20
ld x29, -40(fp)
mv x13, x29
call _start_func
mv x31, a0
li ra, -32
add sp, sp, ra
## Restoring 19 ##
## Restored to 19 ##
mulw x30, x31, x19
## Restoring 19 ##
## Restored to 19 ##
mv x19, x30
## Codegen: write() call Stmt ##
## Restoring 19 ##
## Restored to 19 ##
## saving int caller saved register ##
sd x7, -12(fp)
sd x28, -32(fp)
sd x29, -40(fp)
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x19
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_9: .string "\n"
.align 4
.text
la x5, _CONSTANT_9
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Return Stmt ##
.data
_CONSTANT_10: .word 0
.align 2
.text
la x6, _CONSTANT_10
lw x6, 0(x6)
mv a0, x6
la ra, _FUNCTION_END_MAIN
jr ra
_FUNCTION_END_MAIN:
li t0, 40
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
_FRAME_SIZE_MAIN: .word 40
.text
