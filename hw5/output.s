.text
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_a: .space 40
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_quicksort:
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
la ra, _FRAME_SIZE_quicksort
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: Assign Stmt ##
## Restoring 10 ##
## Restored to 10 ##
mv x9, x10
## Codegen: Assign Stmt ##
## Restoring 10 ##
## Restored to 10 ##
mv x18, x10
## Codegen: Assign Stmt ##
## Restoring 11 ##
## Restored to 11 ##
mv x19, x11
## Codegen: If Stmt ##
## Restoring 10 ##
## Restored to 10 ##
## Restoring 11 ##
## Restored to 11 ##
slt x5, x10, x11
seqz x5, x5
bnez x5, _SKIP_0
la ra, _IF_EXIT_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_quicksort
jr ra
_IF_EXIT_0:
## Codegen: While Stmt ##
_WHILE_LABEL_0:
## Restoring 18 ##
## Restored to 18 ##
## Restoring 19 ##
## Restored to 19 ##
slt x6, x18, x19
bnez x6, _SKIP_1
la ra, _WHILE_EXIT_0
jr ra
_SKIP_1:
## Codegen: Block ##
## Codegen: While Stmt ##
_WHILE_LABEL_1:
add x7, x0, x0
## Restoring 18 ##
## Restored to 18 ##
add x7, x7, x18
slli x7, x7, 2
la x28, _GLOBAL_a
add x28, x28, x7
lw x28, 0(x28)
add x29, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x29, x29, x9
slli x29, x29, 2
la x30, _GLOBAL_a
add x30, x30, x29
lw x30, 0(x30)
ble x28, x30, _SKIP_2
la ra, _BOOL_SHORT_0
jr ra
_SKIP_2:
## Restoring 18 ##
## Restored to 18 ##
## Restoring 11 ##
## Restored to 11 ##
blt x18, x11, _SKIP_3
la ra, _BOOL_SHORT_0
jr ra
_SKIP_3:
addi x31, x0, 1
la ra, _BOOL_EXIT_0
jr ra
_BOOL_SHORT_0:
mv x31, x0
_BOOL_EXIT_0:
bnez x31, _SKIP_4
la ra, _WHILE_EXIT_1
jr ra
_SKIP_4:
## Codegen: Block ##
## Codegen: Assign Stmt ##
## Restoring 18 ##
## Restored to 18 ##
.data
_CONSTANT_0: .word 1
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
addw x6, x18, x5
## Restoring 18 ##
## Restored to 18 ##
mv x18, x6
la ra, _WHILE_LABEL_1
jr ra
_WHILE_EXIT_1:
## Codegen: While Stmt ##
_WHILE_LABEL_2:
add x7, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x7, x7, x19
slli x7, x7, 2
la x29, _GLOBAL_a
add x29, x29, x7
lw x29, 0(x29)
add x28, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x28, x28, x9
slli x28, x28, 2
la x30, _GLOBAL_a
add x30, x30, x28
lw x30, 0(x30)
bgt x29, x30, _SKIP_5
la ra, _BOOL_SHORT_1
jr ra
_SKIP_5:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 10 ##
## Restored to 10 ##
bge x19, x10, _SKIP_6
la ra, _BOOL_SHORT_1
jr ra
_SKIP_6:
addi x31, x0, 1
la ra, _BOOL_EXIT_1
jr ra
_BOOL_SHORT_1:
mv x31, x0
_BOOL_EXIT_1:
bnez x31, _SKIP_7
la ra, _WHILE_EXIT_2
jr ra
_SKIP_7:
## Codegen: Block ##
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_1: .word 1
.align 2
.text
la x5, _CONSTANT_1
lw x5, 0(x5)
subw x6, x19, x5
## Restoring 19 ##
## Restored to 19 ##
mv x19, x6
la ra, _WHILE_LABEL_2
jr ra
_WHILE_EXIT_2:
## Codegen: If Stmt ##
## Restoring 18 ##
## Restored to 18 ##
## Restoring 19 ##
## Restored to 19 ##
slt x7, x18, x19
bnez x7, _SKIP_8
la ra, _IF_EXIT_1
jr ra
_SKIP_8:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x28, x0, x0
## Restoring 18 ##
## Restored to 18 ##
add x28, x28, x18
slli x28, x28, 2
la x29, _GLOBAL_a
add x29, x29, x28
lw x29, 0(x29)
mv x20, x29
## Codegen: Assign Stmt ##
add x30, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x30, x30, x19
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
lw x31, 0(x31)
add x5, x0, x0
## Restoring 18 ##
## Restored to 18 ##
add x5, x5, x18
slli x5, x5, 2
la x6, _GLOBAL_a
add x6, x6, x5
sw x31, 0(x6)
## Codegen: Assign Stmt ##
## Restoring 20 ##
## Restored to 20 ##
add x7, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x7, x7, x19
slli x7, x7, 2
la x28, _GLOBAL_a
add x28, x28, x7
sw x20, 0(x28)
_IF_EXIT_1:
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
## Codegen: Assign Stmt ##
add x29, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x29, x29, x9
slli x29, x29, 2
la x30, _GLOBAL_a
add x30, x30, x29
lw x30, 0(x30)
## Restoring 20 ##
## Restored to 20 ##
mv x20, x30
## Codegen: Assign Stmt ##
add x5, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x5, x5, x19
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
lw x31, 0(x31)
add x6, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x6, x6, x9
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
sw x31, 0(x7)
## Codegen: Assign Stmt ##
## Restoring 20 ##
## Restored to 20 ##
add x28, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x28, x28, x19
slli x28, x28, 2
la x29, _GLOBAL_a
add x29, x29, x28
sw x20, 0(x29)
## Codegen: Normal Function Call Stmt ##
## Restoring 10 ##
## Restored to 10 ##
## TmpOffset = -24 ##
mv x30, x10
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_2: .word 1
.align 2
.text
la x5, _CONSTANT_2
lw x5, 0(x5)
subw x6, x19, x5
li ra, 16
add sp, sp, ra
## saving int caller saved register ##
sd x30, -24(fp)
sd x6, -32(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
ld x31, -24(fp)
mv x10, x31
ld x7, -32(fp)
mv x11, x7
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: Normal Function Call Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_3: .word 1
.align 2
.text
la x28, _CONSTANT_3
lw x28, 0(x28)
addw x29, x19, x28
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
## TmpOffset = -24 ##
mv x5, x11
li ra, 16
add sp, sp, ra
## saving int caller saved register ##
sd x31, -24(fp)
sd x7, -32(fp)
sd x29, -32(fp)
sd x5, -24(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
ld x30, -32(fp)
mv x10, x30
ld x6, -24(fp)
mv x11, x6
call _start_quicksort
li ra, -16
add sp, sp, ra
_FUNCTION_END_quicksort:
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
_FRAME_SIZE_quicksort: .word 40
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
## Codegen: Assign Stmt ##
.data
_CONSTANT_4: .word 2
.align 2
.text
la x5, _CONSTANT_4
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_5: .word 0
.align 2
.text
la x7, _CONSTANT_5
lw x7, 0(x7)
add x6, x6, x7
slli x6, x6, 2
la x28, _GLOBAL_a
add x28, x28, x6
sw x5, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_6: .word 10
.align 2
.text
la x29, _CONSTANT_6
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_7: .word 1
.align 2
.text
la x31, _CONSTANT_7
lw x31, 0(x31)
add x30, x30, x31
slli x30, x30, 2
la x7, _GLOBAL_a
add x7, x7, x30
sw x29, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_8: .word 3
.align 2
.text
la x6, _CONSTANT_8
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_9: .word 2
.align 2
.text
la x28, _CONSTANT_9
lw x28, 0(x28)
add x5, x5, x28
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x6, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_10: .word 8
.align 2
.text
la x30, _CONSTANT_10
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_11: .word 3
.align 2
.text
la x7, _CONSTANT_11
lw x7, 0(x7)
add x29, x29, x7
slli x29, x29, 2
la x28, _GLOBAL_a
add x28, x28, x29
sw x30, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_12: .word 1
.align 2
.text
la x5, _CONSTANT_12
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_13: .word 4
.align 2
.text
la x31, _CONSTANT_13
lw x31, 0(x31)
add x6, x6, x31
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
sw x5, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_14: .word 9
.align 2
.text
la x29, _CONSTANT_14
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_15: .word 5
.align 2
.text
la x28, _CONSTANT_15
lw x28, 0(x28)
add x30, x30, x28
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
sw x29, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_16: .word 4
.align 2
.text
la x6, _CONSTANT_16
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_17: .word 6
.align 2
.text
la x7, _CONSTANT_17
lw x7, 0(x7)
add x5, x5, x7
slli x5, x5, 2
la x28, _GLOBAL_a
add x28, x28, x5
sw x6, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_18: .word 7
.align 2
.text
la x30, _CONSTANT_18
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_19: .word 7
.align 2
.text
la x31, _CONSTANT_19
lw x31, 0(x31)
add x29, x29, x31
slli x29, x29, 2
la x7, _GLOBAL_a
add x7, x7, x29
sw x30, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_20: .word 6
.align 2
.text
la x5, _CONSTANT_20
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_21: .word 8
.align 2
.text
la x28, _CONSTANT_21
lw x28, 0(x28)
add x6, x6, x28
slli x6, x6, 2
la x31, _GLOBAL_a
add x31, x31, x6
sw x5, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_22: .word 5
.align 2
.text
la x29, _CONSTANT_22
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_23: .word 9
.align 2
.text
la x7, _CONSTANT_23
lw x7, 0(x7)
add x30, x30, x7
slli x30, x30, 2
la x28, _GLOBAL_a
add x28, x28, x30
sw x29, 0(x28)
## Codegen: Normal Function Call Stmt ##
.data
_CONSTANT_24: .word 0
.align 2
.text
la x6, _CONSTANT_24
lw x6, 0(x6)
.data
_CONSTANT_25: .word 9
.align 2
.text
la x5, _CONSTANT_25
lw x5, 0(x5)
li ra, 16
add sp, sp, ra
## saving int caller saved register ##
sd x6, -28(fp)
sd x5, -12(fp)
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
ld x31, -28(fp)
mv x10, x31
ld x7, -12(fp)
mv x11, x7
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_26: .word 0
.align 2
.text
la x30, _CONSTANT_26
lw x30, 0(x30)
mv x9, x30
_FOR_BODY_0:
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_27: .word 10
.align 2
.text
la x29, _CONSTANT_27
lw x29, 0(x29)
slt x28, x9, x29
bnez x28, _SKIP_9
la ra, _FOR_EXIT_0
jr ra
_SKIP_9:
## Codegen: Block ##
## Codegen: write() call Stmt ##
add x6, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x6, x6, x9
slli x6, x6, 2
la x5, _GLOBAL_a
add x5, x5, x6
lw x5, 0(x5)
## saving int caller saved register ##
sd x31, -28(fp)
sd x7, -12(fp)
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_28: .string "\n"
.align 4
.text
la x30, _CONSTANT_28
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x30
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_29: .word 1
.align 2
.text
la x29, _CONSTANT_29
lw x29, 0(x29)
addw x28, x9, x29
## Restoring 9 ##
## Restored to 9 ##
mv x9, x28
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: Return Stmt ##
.data
_CONSTANT_30: .word 0
.align 2
.text
la x6, _CONSTANT_30
lw x6, 0(x6)
mv a0, x6
la ra, _FUNCTION_END_MAIN
jr ra
_FUNCTION_END_MAIN:
li t0, 28
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
_FRAME_SIZE_MAIN: .word 28
.text
