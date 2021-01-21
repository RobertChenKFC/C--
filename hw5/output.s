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
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_0: .string "left: "
.align 4
.text
la x5, _CONSTANT_0
mv a0, x5
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 10 ##
ld x10, 16(fp)
ld x10, 16(fp)
## Restored to 10 ##
mv a0, x10
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_1: .string ", Right: "
.align 4
.text
la x6, _CONSTANT_1
mv a0, x6
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 11 ##
ld x11, 24(fp)
ld x11, 24(fp)
## Restored to 11 ##
mv a0, x11
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_2: .string "\n"
.align 4
.text
la x7, _CONSTANT_2
mv a0, x7
call _write_str
## Codegen: Assign Stmt ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
mv x9, x10
## Codegen: Assign Stmt ##
## Restoring 10 ##
## Restored to 10 ##
mv x18, x10
## Codegen: Assign Stmt ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
mv x19, x11
## Codegen: If Stmt ##
## Restoring 10 ##
## Restored to 10 ##
## Restoring 11 ##
## Restored to 11 ##
slt x28, x10, x11
seqz x28, x28
bnez x28, _SKIP_0
la ra, _IF_EXIT_0
jr ra
_SKIP_0:
## Codegen: Block ##
## Codegen: Return Stmt ##
la ra, _FUNCTION_END_quicksort
jr ra
_IF_EXIT_0:
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_3: .string "left: "
.align 4
.text
la x29, _CONSTANT_3
mv a0, x29
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
mv a0, x10
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_4: .string ", Right: "
.align 4
.text
la x30, _CONSTANT_4
mv a0, x30
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 11 ##
ld x11, 24(fp)
## Restored to 11 ##
mv a0, x11
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x11, 24(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_5: .string "\n"
.align 4
.text
la x31, _CONSTANT_5
mv a0, x31
call _write_str
## Codegen: While Stmt ##
_WHILE_LABEL_0:
## Restoring 18 ##
## Restored to 18 ##
## Restoring 19 ##
## Restored to 19 ##
slt x5, x18, x19
bnez x5, _SKIP_1
la ra, _WHILE_EXIT_0
jr ra
_SKIP_1:
## Codegen: Block ##
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_6: .string ", j:"
.align 4
.text
la x6, _CONSTANT_6
mv a0, x6
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 19 ##
## Restored to 19 ##
mv a0, x19
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_7: .string "\n"
.align 4
.text
la x7, _CONSTANT_7
mv a0, x7
call _write_str
## Codegen: Assign Stmt ##
.data
_CONSTANT_8: .word 1
.align 2
.text
la x28, _CONSTANT_8
lw x28, 0(x28)
negw x29, x28
## Restoring 19 ##
## Restored to 19 ##
mv x19, x29
## Codegen: While Stmt ##
_WHILE_LABEL_1:
## Restoring 19 ##
## Restored to 19 ##
## Restoring 10 ##
ld x10, 16(fp)
## Restored to 10 ##
slt x30, x19, x10
seqz x30, x30
bnez x30, _SKIP_2
la ra, _WHILE_EXIT_1
jr ra
_SKIP_2:
## Codegen: Block ##
## Codegen: Assign Stmt ##
## Restoring 19 ##
## Restored to 19 ##
.data
_CONSTANT_9: .word 1
.align 2
.text
la x31, _CONSTANT_9
lw x31, 0(x31)
subw x5, x19, x31
## Restoring 19 ##
## Restored to 19 ##
mv x19, x5
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
sd x10, 16(fp)
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_10: .string " "
.align 4
.text
la x6, _CONSTANT_10
mv a0, x6
call _write_str
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
## Restoring 19 ##
## Restored to 19 ##
mv a0, x19
call _write_int
la ra, _WHILE_LABEL_1
jr ra
_WHILE_EXIT_1:
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
_FUNCTION_END_quicksort:
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
_FRAME_SIZE_quicksort: .word 24
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
_CONSTANT_11: .word 2
.align 2
.text
la x5, _CONSTANT_11
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_12: .word 0
.align 2
.text
la x7, _CONSTANT_12
lw x7, 0(x7)
add x6, x6, x7
slli x6, x6, 2
la x28, _GLOBAL_a
add x28, x28, x6
sw x5, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_13: .word 10
.align 2
.text
la x29, _CONSTANT_13
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_14: .word 1
.align 2
.text
la x31, _CONSTANT_14
lw x31, 0(x31)
add x30, x30, x31
slli x30, x30, 2
la x7, _GLOBAL_a
add x7, x7, x30
sw x29, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_15: .word 3
.align 2
.text
la x6, _CONSTANT_15
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_16: .word 2
.align 2
.text
la x28, _CONSTANT_16
lw x28, 0(x28)
add x5, x5, x28
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x6, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_17: .word 8
.align 2
.text
la x30, _CONSTANT_17
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_18: .word 3
.align 2
.text
la x7, _CONSTANT_18
lw x7, 0(x7)
add x29, x29, x7
slli x29, x29, 2
la x28, _GLOBAL_a
add x28, x28, x29
sw x30, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_19: .word 1
.align 2
.text
la x5, _CONSTANT_19
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_20: .word 4
.align 2
.text
la x31, _CONSTANT_20
lw x31, 0(x31)
add x6, x6, x31
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
sw x5, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_21: .word 9
.align 2
.text
la x29, _CONSTANT_21
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_22: .word 5
.align 2
.text
la x28, _CONSTANT_22
lw x28, 0(x28)
add x30, x30, x28
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
sw x29, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_23: .word 4
.align 2
.text
la x6, _CONSTANT_23
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_24: .word 6
.align 2
.text
la x7, _CONSTANT_24
lw x7, 0(x7)
add x5, x5, x7
slli x5, x5, 2
la x28, _GLOBAL_a
add x28, x28, x5
sw x6, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_25: .word 7
.align 2
.text
la x30, _CONSTANT_25
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_26: .word 7
.align 2
.text
la x31, _CONSTANT_26
lw x31, 0(x31)
add x29, x29, x31
slli x29, x29, 2
la x7, _GLOBAL_a
add x7, x7, x29
sw x30, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_27: .word 6
.align 2
.text
la x5, _CONSTANT_27
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_28: .word 8
.align 2
.text
la x28, _CONSTANT_28
lw x28, 0(x28)
add x6, x6, x28
slli x6, x6, 2
la x31, _GLOBAL_a
add x31, x31, x6
sw x5, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_29: .word 5
.align 2
.text
la x29, _CONSTANT_29
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_30: .word 9
.align 2
.text
la x7, _CONSTANT_30
lw x7, 0(x7)
add x30, x30, x7
slli x30, x30, 2
la x28, _GLOBAL_a
add x28, x28, x30
sw x29, 0(x28)
## Codegen: Normal Function Call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_31: .word 0
.align 2
.text
la x6, _CONSTANT_31
lw x6, 0(x6)
.data
_CONSTANT_32: .word 9
.align 2
.text
la x5, _CONSTANT_32
lw x5, 0(x5)
li ra, 16
add sp, sp, ra
mv x10, x6
mv x11, x5
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_33: .word 0
.align 2
.text
la x31, _CONSTANT_33
lw x31, 0(x31)
mv x9, x31
_FOR_BODY_0:
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_34: .word 10
.align 2
.text
la x7, _CONSTANT_34
lw x7, 0(x7)
slt x30, x9, x7
bnez x30, _SKIP_3
la ra, _FOR_EXIT_0
jr ra
_SKIP_3:
## Codegen: Block ##
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
add x29, x0, x0
## Restoring 9 ##
## Restored to 9 ##
add x29, x29, x9
slli x29, x29, 2
la x28, _GLOBAL_a
add x28, x28, x29
lw x28, 0(x28)
mv a0, x28
call _write_int
## Codegen: write() call Stmt ##
## saving int caller saved register ##
## saving float caller saved register ##
## saving int function argument register ##
## saving float function argument register ##
## end of RegClear ##
.data
_CONSTANT_35: .string "\n"
.align 4
.text
la x6, _CONSTANT_35
mv a0, x6
call _write_str
## Codegen: Assign Stmt ##
## Restoring 9 ##
## Restored to 9 ##
.data
_CONSTANT_36: .word 1
.align 2
.text
la x5, _CONSTANT_36
lw x5, 0(x5)
addw x31, x9, x5
## Restoring 9 ##
## Restored to 9 ##
mv x9, x31
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: Return Stmt ##
.data
_CONSTANT_37: .word 0
.align 2
.text
la x7, _CONSTANT_37
lw x7, 0(x7)
mv a0, x7
la ra, _FUNCTION_END_MAIN
jr ra
_FUNCTION_END_MAIN:
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
_FRAME_SIZE_MAIN: .word 36
.text
