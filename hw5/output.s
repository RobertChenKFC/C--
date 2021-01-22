.text
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_a: .space 80
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_dfs:
sd ra, -8(sp)
sd fp, -16(sp)
addi fp, sp, -16
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
la ra, _FRAME_SIZE_dfs
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: If Stmt ##
## Codegen: Variable Ref ##
## Restoring 10 ##
## Restored to 10 ##
.data
_CONSTANT_0: .word 20
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
slt x6, x10, x5
seqz x6, x6
bnez x6, _SKIP_0
la ra, _IF_EXIT_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_dfs
jr ra
_IF_EXIT_0:
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string "visit "
.align 4
.text
la x7, _CONSTANT_1
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x7
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Codegen: Variable Ref ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
mv x28, x10
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x28
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_2: .string "\n"
.align 4
.text
la x29, _CONSTANT_2
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x29
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Normal Function Call Stmt ##
## Codegen: Variable Ref ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
.data
_CONSTANT_3: .word 2
.align 2
.text
la x30, _CONSTANT_3
lw x30, 0(x30)
mulw x31, x10, x30
.data
_CONSTANT_4: .word 1
.align 2
.text
la x5, _CONSTANT_4
lw x5, 0(x5)
addw x6, x31, x5
## move sp ##
li ra, 8
sub sp, sp, ra
## saving int caller saved register ##
sd x6, -152(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
ld x7, -152(fp)
mv x10, x7
call _start_dfs
## restore sp ##
li ra, 8
add sp, sp, ra
## Codegen: Normal Function Call Stmt ##
## Codegen: Variable Ref ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
.data
_CONSTANT_5: .word 2
.align 2
.text
la x28, _CONSTANT_5
lw x28, 0(x28)
mulw x29, x10, x28
.data
_CONSTANT_6: .word 2
.align 2
.text
la x30, _CONSTANT_6
lw x30, 0(x30)
addw x31, x29, x30
## move sp ##
li ra, 8
sub sp, sp, ra
## saving int caller saved register ##
sd x31, -144(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
ld x5, -144(fp)
mv x10, x5
call _start_dfs
## restore sp ##
li ra, 8
add sp, sp, ra
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_dfs
jr ra
_FUNCTION_END_dfs:
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
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_dfs: .word 16
.text
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_MAIN:
sd ra, -8(sp)
sd fp, -16(sp)
addi fp, sp, -16
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
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_7: .word 0
.align 2
.text
la x5, _CONSTANT_7
lw x5, 0(x5)
## Codegen: Variable Ref ##
## finish variable ref ##
## finish reg restore ##
mv x9, x5
_FOR_BODY_0:
## Codegen: Variable Ref ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_8: .word 20
.align 2
.text
la x6, _CONSTANT_8
lw x6, 0(x6)
slt x7, x9, x6
bnez x7, _SKIP_1
la ra, _FOR_EXIT_0
jr ra
_SKIP_1:
## Codegen: Block ##
## Codegen: Assign Stmt ##
## Codegen: Variable Ref ##
## Restoring 9 ##
## Restored to 9 ##
## Codegen: Variable Ref ##
add x28, x0, x0
## Codegen: Variable Ref ##
## Restoring 9 ##
## Restored to 9 ##
add x28, x28, x9
slli x28, x28, 2
la x29, _GLOBAL_a
add x29, x29, x28
## finish variable ref ##
## finish reg restore ##
sw x9, 0(x29)
## For increment ##
## Codegen: Assign Stmt ##
## Codegen: Variable Ref ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_9: .word 1
.align 2
.text
la x30, _CONSTANT_9
lw x30, 0(x30)
addw x31, x9, x30
## Codegen: Variable Ref ##
## Restoring 9 ##
## Restored to 9 ##
## finish variable ref ##
## finish reg restore ##
mv x9, x31
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: Normal Function Call Stmt ##
.data
_CONSTANT_10: .word 0
.align 2
.text
la x5, _CONSTANT_10
lw x5, 0(x5)
## move sp ##
li ra, 8
sub sp, sp, ra
## saving int caller saved register ##
sd x5, -156(fp)
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
ld x6, -156(fp)
mv x10, x6
call _start_dfs
## restore sp ##
li ra, 8
add sp, sp, ra
## Codegen: Return Stmt ##
.data
_CONSTANT_11: .word 0
.align 2
.text
la x7, _CONSTANT_11
lw x7, 0(x7)
mv a0, x7
la ra, _FUNCTION_END_MAIN
jr ra
_FUNCTION_END_MAIN:
li t0, 20
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
ld fp, 0(fp)
ret
.data
_FRAME_SIZE_MAIN: .word 20
.text
