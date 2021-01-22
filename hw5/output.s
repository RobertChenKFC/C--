.text
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_a: .space 40
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_b: .space 40
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_c: .space 40
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_merge:
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
la ra, _FRAME_SIZE_merge
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_0: .string "left: "
.align 4
.text
la x5, _CONSTANT_0
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
sd x12, 32(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
mv x6, x10
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x6
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string ", mid: "
.align 4
.text
la x7, _CONSTANT_1
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x7
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
mv x28, x11
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x28
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_2: .string ", right: "
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
## Codegen: write() call Stmt ##
## Restoring 12 ##
ld x12, 32(fp)
## Restored to 12 ##
mv x30, x12
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x12, 32(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x30
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_3: .string "\n"
.align 4
.text
la x31, _CONSTANT_3
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x31
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Assign Stmt ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
subw x5, x11, x10
.data
_CONSTANT_4: .word 1
.align 2
.text
la x6, _CONSTANT_4
lw x6, 0(x6)
addw x7, x5, x6
mv x9, x7
## Codegen: Assign Stmt ##
## Restoring 12 ##
ld x12, 32(fp)
## Restored to 12 ##
## Restoring 11 ##
## Restored to 11 ##
.data
_CONSTANT_5: .word 1
.align 2
.text
la x28, _CONSTANT_5
lw x28, 0(x28)
addw x29, x11, x28
subw x30, x12, x29
.data
_CONSTANT_6: .word 1
.align 2
.text
la x31, _CONSTANT_6
lw x31, 0(x31)
addw x5, x30, x31
mv x18, x5
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_7: .word 0
.align 2
.text
la x6, _CONSTANT_7
lw x6, 0(x6)
mv x19, x6
_FOR_BODY_0:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 9 ##
## Restored to 9 ##
slt x7, x19, x9
bnez x7, _SKIP_0
la ra, _FOR_EXIT_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x28, x0, x0
## Restoring 10 ##
## Restored to 10 ##
## Restoring 19 ##
## Restored to 19 ##
addw x29, x10, x19
add x28, x28, x29
slli x28, x28, 2
la x30, _GLOBAL_a
add x30, x30, x28
lw x30, 0(x30)
add x31, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x31, x31, x19
slli x31, x31, 2
la x5, _GLOBAL_b
add x5, x5, x31
sw x30, 0(x5)
## For increment ##
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_8: .word 1
.align 2
.text
la x6, _CONSTANT_8
lw x6, 0(x6)
addw x7, x19, x6
## Restoring 19 ##
## Restored to 19 ##
mv x19, x7
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: For Stmt ##
_FOR_LABEL_1:
## Codegen: Assign Stmt ##
.data
_CONSTANT_9: .word 0
.align 2
.text
la x29, _CONSTANT_9
lw x29, 0(x29)
## Restoring 19 ##
## Restored to 19 ##
mv x19, x29
_FOR_BODY_1:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 18 ##
## Restored to 18 ##
slt x28, x19, x18
bnez x28, _SKIP_1
la ra, _FOR_EXIT_1
jr ra
_SKIP_1:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x31, x0, x0
## Restoring 11 ##
## Restored to 11 ##
.data
_CONSTANT_10: .word 1
.align 2
.text
la x30, _CONSTANT_10
lw x30, 0(x30)
addw x5, x11, x30
## Restoring 19 ##
## Restored to 19 ##
addw x6, x5, x19
add x31, x31, x6
slli x31, x31, 2
la x7, _GLOBAL_a
add x7, x7, x31
lw x7, 0(x7)
add x29, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x29, x29, x19
slli x29, x29, 2
la x28, _GLOBAL_c
add x28, x28, x29
sw x7, 0(x28)
## For increment ##
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_11: .word 1
.align 2
.text
la x30, _CONSTANT_11
lw x30, 0(x30)
addw x5, x19, x30
## Restoring 19 ##
## Restored to 19 ##
mv x19, x5
la ra, _FOR_BODY_1
jr ra
_FOR_EXIT_1:
## Codegen: Assign Stmt ##
.data
_CONSTANT_12: .word 0
.align 2
.text
la x6, _CONSTANT_12
lw x6, 0(x6)
## Restoring 19 ##
## Restored to 19 ##
mv x19, x6
## Codegen: Assign Stmt ##
.data
_CONSTANT_13: .word 0
.align 2
.text
la x31, _CONSTANT_13
lw x31, 0(x31)
mv x20, x31
## Codegen: Assign Stmt ##
## Restoring 10 ##
## Restored to 10 ##
mv x21, x10
## Codegen: While Stmt ##
_WHILE_LABEL_0:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 9 ##
## Restored to 9 ##
blt x19, x9, _SKIP_2
la ra, _BOOL_SHORT_0
jr ra
_SKIP_2:
## Restoring 20 ##
## Restored to 20 ##
## Restoring 18 ##
## Restored to 18 ##
blt x20, x18, _SKIP_3
la ra, _BOOL_SHORT_0
jr ra
_SKIP_3:
addi x29, x0, 1
la ra, _BOOL_EXIT_0
jr ra
_BOOL_SHORT_0:
mv x29, x0
_BOOL_EXIT_0:
bnez x29, _SKIP_4
la ra, _WHILE_EXIT_0
jr ra
_SKIP_4:
## Codegen: Block ##
## Codegen: If Stmt ##
add x7, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x7, x7, x19
slli x7, x7, 2
la x28, _GLOBAL_b
add x28, x28, x7
lw x28, 0(x28)
add x30, x0, x0
## Restoring 20 ##
## Restored to 20 ##
add x30, x30, x20
slli x30, x30, 2
la x5, _GLOBAL_c
add x5, x5, x30
lw x5, 0(x5)
slt x6, x5, x28
seqz x6, x6
bnez x6, _SKIP_5
la ra, _ELSE_LABEL_0
jr ra
_SKIP_5:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x31, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x31, x31, x19
slli x31, x31, 2
la x29, _GLOBAL_b
add x29, x29, x31
lw x29, 0(x29)
add x7, x0, x0
## Restoring 21 ##
## Restored to 21 ##
add x7, x7, x21
slli x7, x7, 2
la x30, _GLOBAL_a
add x30, x30, x7
sw x29, 0(x30)
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_14: .word 1
.align 2
.text
la x28, _CONSTANT_14
lw x28, 0(x28)
addw x5, x19, x28
## Restoring 19 ##
## Restored to 19 ##
mv x19, x5
la ra, _IF_EXIT_0
jr ra
_ELSE_LABEL_0:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x6, x0, x0
## Restoring 20 ##
## Restored to 20 ##
add x6, x6, x20
slli x6, x6, 2
la x31, _GLOBAL_c
add x31, x31, x6
lw x31, 0(x31)
add x7, x0, x0
## Restoring 21 ##
## Restored to 21 ##
add x7, x7, x21
slli x7, x7, 2
la x29, _GLOBAL_a
add x29, x29, x7
sw x31, 0(x29)
## Codegen: Assign Stmt ##
## Restoring 20 ##
## Restored to 20 ##
.data
_CONSTANT_15: .word 1
.align 2
.text
la x30, _CONSTANT_15
lw x30, 0(x30)
addw x28, x20, x30
## Restoring 20 ##
## Restored to 20 ##
mv x20, x28
_IF_EXIT_0:
## Codegen: Assign Stmt ##
## Restoring 21 ##
## Restored to 21 ##
.data
_CONSTANT_16: .word 1
.align 2
.text
la x5, _CONSTANT_16
lw x5, 0(x5)
addw x6, x21, x5
## Restoring 21 ##
## Restored to 21 ##
mv x21, x6
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
## Codegen: While Stmt ##
_WHILE_LABEL_1:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 9 ##
## Restored to 9 ##
slt x7, x19, x9
bnez x7, _SKIP_6
la ra, _WHILE_EXIT_1
jr ra
_SKIP_6:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x31, x0, x0
## Restoring 19 ##
## Restored to 19 ##
add x31, x31, x19
slli x31, x31, 2
la x29, _GLOBAL_b
add x29, x29, x31
lw x29, 0(x29)
add x30, x0, x0
## Restoring 21 ##
## Restored to 21 ##
add x30, x30, x21
slli x30, x30, 2
la x28, _GLOBAL_a
add x28, x28, x30
sw x29, 0(x28)
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_17: .word 1
.align 2
.text
la x5, _CONSTANT_17
lw x5, 0(x5)
addw x6, x19, x5
## Restoring 19 ##
## Restored to 19 ##
mv x19, x6
## Codegen: Assign Stmt ##
## Restoring 21 ##
## Restored to 21 ##
.data
_CONSTANT_18: .word 1
.align 2
.text
la x7, _CONSTANT_18
lw x7, 0(x7)
addw x31, x21, x7
## Restoring 21 ##
## Restored to 21 ##
mv x21, x31
la ra, _WHILE_LABEL_1
jr ra
_WHILE_EXIT_1:
## Codegen: While Stmt ##
_WHILE_LABEL_2:
## Restoring 20 ##
## Restored to 20 ##
## Restoring 18 ##
## Restored to 18 ##
slt x30, x20, x18
bnez x30, _SKIP_7
la ra, _WHILE_EXIT_2
jr ra
_SKIP_7:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x29, x0, x0
## Restoring 20 ##
## Restored to 20 ##
add x29, x29, x20
slli x29, x29, 2
la x28, _GLOBAL_c
add x28, x28, x29
lw x28, 0(x28)
add x5, x0, x0
## Restoring 21 ##
## Restored to 21 ##
add x5, x5, x21
slli x5, x5, 2
la x6, _GLOBAL_a
add x6, x6, x5
sw x28, 0(x6)
## Codegen: Assign Stmt ##
## Restoring 20 ##
## Restored to 20 ##
.data
_CONSTANT_19: .word 1
.align 2
.text
la x7, _CONSTANT_19
lw x7, 0(x7)
addw x31, x20, x7
## Restoring 20 ##
## Restored to 20 ##
mv x20, x31
## Codegen: Assign Stmt ##
## Restoring 21 ##
## Restored to 21 ##
.data
_CONSTANT_20: .word 1
.align 2
.text
la x30, _CONSTANT_20
lw x30, 0(x30)
addw x29, x21, x30
## Restoring 21 ##
## Restored to 21 ##
mv x21, x29
la ra, _WHILE_LABEL_2
jr ra
_WHILE_EXIT_2:
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_merge
jr ra
_FUNCTION_END_merge:
li t0, 44
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
_FRAME_SIZE_merge: .word 44
.text
## Codegen: Function Declaration ##
## Codegen: Parameter List Declaration ##
.text
_start_mergesort:
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
la ra, _FRAME_SIZE_mergesort
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Body Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: Local Variable Declaration ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_21: .string "left: "
.align 4
.text
la x5, _CONSTANT_21
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
mv x6, x10
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x6
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_22: .string ", right: "
.align 4
.text
la x7, _CONSTANT_22
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x7
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
mv x28, x11
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x28
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_23: .string "\n"
.align 4
.text
la x29, _CONSTANT_23
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x29
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Assign Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
addw x30, x10, x11
.data
_CONSTANT_24: .word 2
.align 2
.text
la x31, _CONSTANT_24
lw x31, 0(x31)
divw x5, x30, x31
mv x9, x5
## Codegen: If Stmt ##
## Restoring 10 ##
## Restored to 10 ##
## Restoring 11 ##
## Restored to 11 ##
slt x6, x10, x11
seqz x6, x6
bnez x6, _SKIP_8
la ra, _IF_EXIT_1
jr ra
_SKIP_8:
## Codegen: Block ##
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_mergesort
jr ra
_IF_EXIT_1:
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
mv x18, x9
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
mv x19, x9
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
mv x20, x9
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
mv x21, x9
## Codegen: If Stmt ##
## Restoring 9 ##
## Restored to 9 ##
## Restoring 18 ##
## Restored to 18 ##
beq x9, x18, _SKIP_9
la ra, _BOOL_SHORT_1
jr ra
_SKIP_9:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 19 ##
## Restored to 19 ##
beq x9, x19, _SKIP_10
la ra, _BOOL_SHORT_1
jr ra
_SKIP_10:
la ra, _BOOL_EXIT_3
jr ra
_BOOL_SHORT_3:
la ra, _BOOL_SHORT_1
jr ra
_BOOL_EXIT_3:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 20 ##
## Restored to 20 ##
beq x9, x20, _SKIP_11
la ra, _BOOL_SHORT_1
jr ra
_SKIP_11:
la ra, _BOOL_EXIT_2
jr ra
_BOOL_SHORT_2:
la ra, _BOOL_SHORT_1
jr ra
_BOOL_EXIT_2:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 21 ##
## Restored to 21 ##
beq x9, x21, _SKIP_12
la ra, _BOOL_SHORT_1
jr ra
_SKIP_12:
mv x7, x0
la ra, _BOOL_EXIT_1
jr ra
_BOOL_SHORT_1:
addi x7, x0, 1
_BOOL_EXIT_1:
bnez x7, _SKIP_13
la ra, _IF_EXIT_2
jr ra
_SKIP_13:
## Codegen: Block ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_25: .string "FAIL1! Mid = "
.align 4
.text
la x28, _CONSTANT_25
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
mv a0, x28
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 9 ##
## Restored to 9 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x9
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_26: .string ", test1 = "
.align 4
.text
la x29, _CONSTANT_26
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x29
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 18 ##
## Restored to 18 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x18
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_27: .string ", test2 = "
.align 4
.text
la x30, _CONSTANT_27
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x30
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 19 ##
## Restored to 19 ##
## saving int caller saved register ##
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
_CONSTANT_28: .string ", test3 = "
.align 4
.text
la x31, _CONSTANT_28
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x31
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 20 ##
## Restored to 20 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x20
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_29: .string ", test4 = "
.align 4
.text
la x5, _CONSTANT_29
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 21 ##
## Restored to 21 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x21
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_30: .string "\n"
.align 4
.text
la x6, _CONSTANT_30
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x6
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_mergesort
jr ra
_IF_EXIT_2:
## Codegen: Normal Function Call Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
## TmpOffset = -36 ##
mv x7, x10
## Restoring 9 ##
## Restored to 9 ##
li ra, 16
add sp, sp, ra
## saving int caller saved register ##
sd x7, -36(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
ld x28, -36(fp)
mv x10, x28
mv x11, x9
call _start_mergesort
li ra, -16
add sp, sp, ra
## Codegen: If Stmt ##
## Restoring 9 ##
## Restored to 9 ##
## Restoring 18 ##
## Restored to 18 ##
beq x9, x18, _SKIP_14
la ra, _BOOL_SHORT_4
jr ra
_SKIP_14:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 19 ##
## Restored to 19 ##
beq x9, x19, _SKIP_15
la ra, _BOOL_SHORT_4
jr ra
_SKIP_15:
la ra, _BOOL_EXIT_6
jr ra
_BOOL_SHORT_6:
la ra, _BOOL_SHORT_4
jr ra
_BOOL_EXIT_6:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 20 ##
## Restored to 20 ##
beq x9, x20, _SKIP_16
la ra, _BOOL_SHORT_4
jr ra
_SKIP_16:
la ra, _BOOL_EXIT_5
jr ra
_BOOL_SHORT_5:
la ra, _BOOL_SHORT_4
jr ra
_BOOL_EXIT_5:
## Restoring 9 ##
## Restored to 9 ##
## Restoring 21 ##
## Restored to 21 ##
beq x9, x21, _SKIP_17
la ra, _BOOL_SHORT_4
jr ra
_SKIP_17:
mv x29, x0
la ra, _BOOL_EXIT_4
jr ra
_BOOL_SHORT_4:
addi x29, x0, 1
_BOOL_EXIT_4:
bnez x29, _SKIP_18
la ra, _IF_EXIT_3
jr ra
_SKIP_18:
## Codegen: Block ##
## Codegen: write() call Stmt ##
.data
_CONSTANT_31: .string "FAIL2! Mid = "
.align 4
.text
la x30, _CONSTANT_31
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x30
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 9 ##
## Restored to 9 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x9
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_32: .string ", test1 = "
.align 4
.text
la x31, _CONSTANT_32
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x31
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 18 ##
## Restored to 18 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x18
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_33: .string ", test2 = "
.align 4
.text
la x5, _CONSTANT_33
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x5
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 19 ##
## Restored to 19 ##
## saving int caller saved register ##
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
_CONSTANT_34: .string ", test3 = "
.align 4
.text
la x6, _CONSTANT_34
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x6
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 20 ##
## Restored to 20 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x20
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_35: .string ", test4 = "
.align 4
.text
la x28, _CONSTANT_35
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x28
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: write() call Stmt ##
## Restoring 21 ##
## Restored to 21 ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x21
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_36: .string "\n"
.align 4
.text
la x29, _CONSTANT_36
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x29
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_mergesort
jr ra
_IF_EXIT_3:
## Codegen: Normal Function Call Stmt ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_37: .word 1
.align 2
.text
la x30, _CONSTANT_37
lw x30, 0(x30)
addw x31, x9, x30
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
## TmpOffset = -28 ##
mv x5, x11
li ra, 16
add sp, sp, ra
## saving int caller saved register ##
sd x31, -36(fp)
sd x5, -28(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
ld x6, -36(fp)
mv x10, x6
ld x28, -28(fp)
mv x11, x28
call _start_mergesort
li ra, -16
add sp, sp, ra
## Codegen: Normal Function Call Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
## TmpOffset = -28 ##
mv x29, x10
## Restoring 9 ##
## Restored to 9 ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
## TmpOffset = -36 ##
mv x30, x11
li ra, 24
add sp, sp, ra
## saving int caller saved register ##
sd x29, -28(fp)
sd x30, -36(fp)
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
ld x6, -28(fp)
mv x10, x6
mv x11, x9
ld x28, -36(fp)
mv x12, x28
call _start_merge
li ra, -24
add sp, sp, ra
_FUNCTION_END_mergesort:
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
ret
.data
_FRAME_SIZE_mergesort: .word 36
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
_CONSTANT_38: .word 2
.align 2
.text
la x5, _CONSTANT_38
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_39: .word 0
.align 2
.text
la x7, _CONSTANT_39
lw x7, 0(x7)
add x6, x6, x7
slli x6, x6, 2
la x28, _GLOBAL_a
add x28, x28, x6
sw x5, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_40: .word 10
.align 2
.text
la x29, _CONSTANT_40
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_41: .word 1
.align 2
.text
la x31, _CONSTANT_41
lw x31, 0(x31)
add x30, x30, x31
slli x30, x30, 2
la x7, _GLOBAL_a
add x7, x7, x30
sw x29, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_42: .word 3
.align 2
.text
la x6, _CONSTANT_42
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_43: .word 2
.align 2
.text
la x28, _CONSTANT_43
lw x28, 0(x28)
add x5, x5, x28
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x6, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_44: .word 8
.align 2
.text
la x30, _CONSTANT_44
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_45: .word 3
.align 2
.text
la x7, _CONSTANT_45
lw x7, 0(x7)
add x29, x29, x7
slli x29, x29, 2
la x28, _GLOBAL_a
add x28, x28, x29
sw x30, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_46: .word 1
.align 2
.text
la x5, _CONSTANT_46
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_47: .word 4
.align 2
.text
la x31, _CONSTANT_47
lw x31, 0(x31)
add x6, x6, x31
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
sw x5, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_48: .word 9
.align 2
.text
la x29, _CONSTANT_48
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_49: .word 5
.align 2
.text
la x28, _CONSTANT_49
lw x28, 0(x28)
add x30, x30, x28
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
sw x29, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_50: .word 4
.align 2
.text
la x6, _CONSTANT_50
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_51: .word 6
.align 2
.text
la x7, _CONSTANT_51
lw x7, 0(x7)
add x5, x5, x7
slli x5, x5, 2
la x28, _GLOBAL_a
add x28, x28, x5
sw x6, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_52: .word 7
.align 2
.text
la x30, _CONSTANT_52
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_53: .word 7
.align 2
.text
la x31, _CONSTANT_53
lw x31, 0(x31)
add x29, x29, x31
slli x29, x29, 2
la x7, _GLOBAL_a
add x7, x7, x29
sw x30, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_54: .word 6
.align 2
.text
la x5, _CONSTANT_54
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_55: .word 8
.align 2
.text
la x28, _CONSTANT_55
lw x28, 0(x28)
add x6, x6, x28
slli x6, x6, 2
la x31, _GLOBAL_a
add x31, x31, x6
sw x5, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_56: .word 5
.align 2
.text
la x29, _CONSTANT_56
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_57: .word 9
.align 2
.text
la x7, _CONSTANT_57
lw x7, 0(x7)
add x30, x30, x7
slli x30, x30, 2
la x28, _GLOBAL_a
add x28, x28, x30
sw x29, 0(x28)
## Codegen: Normal Function Call Stmt ##
.data
_CONSTANT_58: .word 0
.align 2
.text
la x6, _CONSTANT_58
lw x6, 0(x6)
.data
_CONSTANT_59: .word 9
.align 2
.text
la x5, _CONSTANT_59
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
call _start_mergesort
li ra, -16
add sp, sp, ra
## Codegen: For Stmt ##
_FOR_LABEL_2:
## Codegen: Assign Stmt ##
.data
_CONSTANT_60: .word 0
.align 2
.text
la x30, _CONSTANT_60
lw x30, 0(x30)
mv x9, x30
_FOR_BODY_2:
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_61: .word 10
.align 2
.text
la x29, _CONSTANT_61
lw x29, 0(x29)
slt x28, x9, x29
bnez x28, _SKIP_19
la ra, _FOR_EXIT_2
jr ra
_SKIP_19:
## Codegen: Block ##
## Codegen: write() call Stmt ##
add x31, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x31, x31, x9
slli x31, x31, 2
la x7, _GLOBAL_a
add x7, x7, x31
lw x7, 0(x7)
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x7
addi sp, sp, -8
call _write_int
addi sp, sp, 8
## Codegen: write() call Stmt ##
.data
_CONSTANT_62: .string "\n"
.align 4
.text
la x30, _CONSTANT_62
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
mv a0, x30
addi sp, sp, -8
call _write_str
addi sp, sp, 8
## For increment ##
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_63: .word 1
.align 2
.text
la x29, _CONSTANT_63
lw x29, 0(x29)
addw x28, x9, x29
## Restoring 9 ##
## Restored to 9 ##
mv x9, x28
la ra, _FOR_BODY_2
jr ra
_FOR_EXIT_2:
## Codegen: Return Stmt ##
.data
_CONSTANT_64: .word 0
.align 2
.text
la x31, _CONSTANT_64
lw x31, 0(x31)
mv a0, x31
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
