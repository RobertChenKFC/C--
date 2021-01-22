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
mv x9, x10
## Codegen: Assign Stmt ##
ld x5, 16(fp)
mv x18, x5
## Codegen: Assign Stmt ##
mv x19, x11
## Codegen: write() call Stmt ##
.data
_CONSTANT_0: .string "Left:"
.align 4
.text
la x6, _CONSTANT_0
mv a0, x6
call _write_str
## Codegen: write() call Stmt ##
ld x7, 16(fp)
mv a0, x7
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_1: .string "\n"
.align 4
.text
la x28, _CONSTANT_1
mv a0, x28
call _write_str
## Codegen: write() call Stmt ##
.data
_CONSTANT_2: .string "Right:"
.align 4
.text
la x29, _CONSTANT_2
mv a0, x29
call _write_str
## Codegen: write() call Stmt ##
ld x30, 24(fp)
mv a0, x30
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_3: .string "\n"
.align 4
.text
la x31, _CONSTANT_3
mv a0, x31
call _write_str
## Codegen: If Stmt ##
ld x12, 16(fp)
ld x13, 24(fp)
slt x14, x12, x13
seqz x14, x14
bnez x14, _SKIP_0
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
slt x15, x18, x19
bnez x15, _SKIP_1
la ra, _WHILE_EXIT_0
jr ra
_SKIP_1:
## Codegen: Block ##
## Codegen: While Stmt ##
_WHILE_LABEL_1:
add x16, x0, x0
add x16, x16, x18
slli x16, x16, 2
la x17, _GLOBAL_a
add x17, x17, x16
lw x17, 0(x17)
add x10, x0, x0
add x10, x10, x9
slli x10, x10, 2
la x5, _GLOBAL_a
add x5, x5, x10
lw x5, 0(x5)
ble x17, x5, _SKIP_2
la ra, _BOOL_SHORT_0
jr ra
_SKIP_2:
ld x11, 24(fp)
blt x18, x11, _SKIP_3
la ra, _BOOL_SHORT_0
jr ra
_SKIP_3:
addi x6, x0, 1
la ra, _BOOL_EXIT_0
jr ra
_BOOL_SHORT_0:
mv x6, x0
_BOOL_EXIT_0:
bnez x6, _SKIP_4
la ra, _WHILE_EXIT_1
jr ra
_SKIP_4:
## Codegen: Block ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_4: .word 1
.align 2
.text
la x7, _CONSTANT_4
lw x7, 0(x7)
addw x28, x18, x7
mv x18, x28
la ra, _WHILE_LABEL_1
jr ra
_WHILE_EXIT_1:
## Codegen: While Stmt ##
_WHILE_LABEL_2:
add x29, x0, x0
add x29, x29, x19
slli x29, x29, 2
la x30, _GLOBAL_a
add x30, x30, x29
lw x30, 0(x30)
add x31, x0, x0
add x31, x31, x9
slli x31, x31, 2
la x12, _GLOBAL_a
add x12, x12, x31
lw x12, 0(x12)
bgt x30, x12, _SKIP_5
la ra, _BOOL_SHORT_1
jr ra
_SKIP_5:
ld x13, 16(fp)
bge x19, x13, _SKIP_6
la ra, _BOOL_SHORT_1
jr ra
_SKIP_6:
addi x14, x0, 1
la ra, _BOOL_EXIT_1
jr ra
_BOOL_SHORT_1:
mv x14, x0
_BOOL_EXIT_1:
bnez x14, _SKIP_7
la ra, _WHILE_EXIT_2
jr ra
_SKIP_7:
## Codegen: Block ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_5: .word 1
.align 2
.text
la x15, _CONSTANT_5
lw x15, 0(x15)
subw x16, x19, x15
mv x19, x16
la ra, _WHILE_LABEL_2
jr ra
_WHILE_EXIT_2:
## Codegen: If Stmt ##
slt x10, x18, x19
bnez x10, _SKIP_8
la ra, _IF_EXIT_1
jr ra
_SKIP_8:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x17, x0, x0
add x17, x17, x18
slli x17, x17, 2
la x5, _GLOBAL_a
add x5, x5, x17
lw x5, 0(x5)
mv x20, x5
## Codegen: Assign Stmt ##
add x11, x0, x0
add x11, x11, x19
slli x11, x11, 2
la x6, _GLOBAL_a
add x6, x6, x11
lw x6, 0(x6)
add x7, x0, x0
add x7, x7, x18
slli x7, x7, 2
la x28, _GLOBAL_a
add x28, x28, x7
sw x6, 0(x28)
## Codegen: Assign Stmt ##
add x29, x0, x0
add x29, x29, x19
slli x29, x29, 2
la x31, _GLOBAL_a
add x31, x31, x29
sw x20, 0(x31)
_IF_EXIT_1:
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
## Codegen: Assign Stmt ##
add x30, x0, x0
add x30, x30, x9
slli x30, x30, 2
la x12, _GLOBAL_a
add x12, x12, x30
lw x12, 0(x12)
mv x20, x12
## Codegen: Assign Stmt ##
add x13, x0, x0
add x13, x13, x19
slli x13, x13, 2
la x14, _GLOBAL_a
add x14, x14, x13
lw x14, 0(x14)
add x15, x0, x0
add x15, x15, x9
slli x15, x15, 2
la x16, _GLOBAL_a
add x16, x16, x15
sw x14, 0(x16)
## Codegen: Assign Stmt ##
add x10, x0, x0
add x10, x10, x19
slli x10, x10, 2
la x17, _GLOBAL_a
add x17, x17, x10
sw x20, 0(x17)
## Codegen: write() call Stmt ##
.data
_CONSTANT_6: .string "qsort("
.align 4
.text
la x5, _CONSTANT_6
mv a0, x5
call _write_str
## Codegen: write() call Stmt ##
ld x11, 16(fp)
mv a0, x11
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_7: .string ","
.align 4
.text
la x7, _CONSTANT_7
mv a0, x7
call _write_str
## Codegen: write() call Stmt ##
.data
_CONSTANT_8: .word 1
.align 2
.text
la x6, _CONSTANT_8
lw x6, 0(x6)
subw x28, x19, x6
mv a0, x28
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_9: .string ")\n"
.align 4
.text
la x29, _CONSTANT_9
mv a0, x29
call _write_str
## Codegen: Normal Function Call Stmt ##
ld x31, 16(fp)
.data
_CONSTANT_10: .word 1
.align 2
.text
la x30, _CONSTANT_10
lw x30, 0(x30)
subw x12, x19, x30
li ra, 16
add sp, sp, ra
mv x10, x31
mv x11, x12
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: write() call Stmt ##
sd x31, 16(fp)
sd x12, 16(fp)
.data
_CONSTANT_11: .string "qsort("
.align 4
.text
la x13, _CONSTANT_11
mv a0, x13
call _write_str
## Codegen: write() call Stmt ##
.data
_CONSTANT_12: .word 1
.align 2
.text
la x15, _CONSTANT_12
lw x15, 0(x15)
addw x14, x19, x15
mv a0, x14
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_13: .string ","
.align 4
.text
la x16, _CONSTANT_13
mv a0, x16
call _write_str
## Codegen: write() call Stmt ##
ld x10, 24(fp)
mv a0, x10
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_14: .string ")\n"
.align 4
.text
la x17, _CONSTANT_14
mv a0, x17
call _write_str
## Codegen: Normal Function Call Stmt ##
.data
_CONSTANT_15: .word 1
.align 2
.text
la x5, _CONSTANT_15
lw x5, 0(x5)
addw x11, x19, x5
ld x7, 24(fp)
li ra, 16
add sp, sp, ra
mv x10, x11
mv x11, x7
call _start_quicksort
li ra, -16
add sp, sp, ra
_FUNCTION_END_quicksort:
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
_FRAME_SIZE_quicksort: .word 16
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
_CONSTANT_16: .word 2
.align 2
.text
la x5, _CONSTANT_16
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_17: .word 0
.align 2
.text
la x7, _CONSTANT_17
lw x7, 0(x7)
add x6, x6, x7
slli x6, x6, 2
la x28, _GLOBAL_a
add x28, x28, x6
sw x5, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_18: .word 10
.align 2
.text
la x29, _CONSTANT_18
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_19: .word 1
.align 2
.text
la x31, _CONSTANT_19
lw x31, 0(x31)
add x30, x30, x31
slli x30, x30, 2
la x10, _GLOBAL_a
add x10, x10, x30
sw x29, 0(x10)
## Codegen: Assign Stmt ##
.data
_CONSTANT_20: .word 3
.align 2
.text
la x11, _CONSTANT_20
lw x11, 0(x11)
add x12, x0, x0
.data
_CONSTANT_21: .word 2
.align 2
.text
la x13, _CONSTANT_21
lw x13, 0(x13)
add x12, x12, x13
slli x12, x12, 2
la x14, _GLOBAL_a
add x14, x14, x12
sw x11, 0(x14)
## Codegen: Assign Stmt ##
.data
_CONSTANT_22: .word 8
.align 2
.text
la x15, _CONSTANT_22
lw x15, 0(x15)
add x16, x0, x0
.data
_CONSTANT_23: .word 3
.align 2
.text
la x17, _CONSTANT_23
lw x17, 0(x17)
add x16, x16, x17
slli x16, x16, 2
la x7, _GLOBAL_a
add x7, x7, x16
sw x15, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_24: .word 1
.align 2
.text
la x6, _CONSTANT_24
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_25: .word 4
.align 2
.text
la x28, _CONSTANT_25
lw x28, 0(x28)
add x5, x5, x28
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x6, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_26: .word 9
.align 2
.text
la x30, _CONSTANT_26
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_27: .word 5
.align 2
.text
la x10, _CONSTANT_27
lw x10, 0(x10)
add x29, x29, x10
slli x29, x29, 2
la x13, _GLOBAL_a
add x13, x13, x29
sw x30, 0(x13)
## Codegen: Assign Stmt ##
.data
_CONSTANT_28: .word 4
.align 2
.text
la x12, _CONSTANT_28
lw x12, 0(x12)
add x11, x0, x0
.data
_CONSTANT_29: .word 6
.align 2
.text
la x14, _CONSTANT_29
lw x14, 0(x14)
add x11, x11, x14
slli x11, x11, 2
la x17, _GLOBAL_a
add x17, x17, x11
sw x12, 0(x17)
## Codegen: Assign Stmt ##
.data
_CONSTANT_30: .word 7
.align 2
.text
la x16, _CONSTANT_30
lw x16, 0(x16)
add x15, x0, x0
.data
_CONSTANT_31: .word 7
.align 2
.text
la x7, _CONSTANT_31
lw x7, 0(x7)
add x15, x15, x7
slli x15, x15, 2
la x28, _GLOBAL_a
add x28, x28, x15
sw x16, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_32: .word 6
.align 2
.text
la x5, _CONSTANT_32
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_33: .word 8
.align 2
.text
la x31, _CONSTANT_33
lw x31, 0(x31)
add x6, x6, x31
slli x6, x6, 2
la x10, _GLOBAL_a
add x10, x10, x6
sw x5, 0(x10)
## Codegen: Assign Stmt ##
.data
_CONSTANT_34: .word 5
.align 2
.text
la x29, _CONSTANT_34
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_35: .word 9
.align 2
.text
la x13, _CONSTANT_35
lw x13, 0(x13)
add x30, x30, x13
slli x30, x30, 2
la x14, _GLOBAL_a
add x14, x14, x30
sw x29, 0(x14)
## Codegen: Normal Function Call Stmt ##
.data
_CONSTANT_36: .word 0
.align 2
.text
la x11, _CONSTANT_36
lw x11, 0(x11)
.data
_CONSTANT_37: .word 9
.align 2
.text
la x12, _CONSTANT_37
lw x12, 0(x12)
li ra, 16
add sp, sp, ra
mv x10, x11
mv x11, x12
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_38: .word 0
.align 2
.text
la x17, _CONSTANT_38
lw x17, 0(x17)
mv x9, x17
_FOR_BODY_0:
.data
_CONSTANT_39: .word 10
.align 2
.text
la x7, _CONSTANT_39
lw x7, 0(x7)
slt x15, x9, x7
bnez x15, _SKIP_9
la ra, _FOR_EXIT_0
jr ra
_SKIP_9:
## Codegen: Block ##
## Codegen: write() call Stmt ##
sd x11, -28(fp)
sd x12, -12(fp)
add x16, x0, x0
add x16, x16, x9
slli x16, x16, 2
la x28, _GLOBAL_a
add x28, x28, x16
lw x28, 0(x28)
mv a0, x28
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_40: .string "\n"
.align 4
.text
la x31, _CONSTANT_40
mv a0, x31
call _write_str
## Codegen: Assign Stmt ##
.data
_CONSTANT_41: .word 1
.align 2
.text
la x6, _CONSTANT_41
lw x6, 0(x6)
addw x5, x9, x6
mv x9, x5
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: Return Stmt ##
.data
_CONSTANT_42: .word 0
.align 2
.text
la x10, _CONSTANT_42
lw x10, 0(x10)
mv a0, x10
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
