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
sd x10, 16(fp)
sd x11, 24(fp)
ld x5, 16(fp)
mv a0, x5
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_0: .string " "
.align 4
.text
la x6, _CONSTANT_0
mv a0, x6
call _write_str
## Codegen: write() call Stmt ##
ld x7, 24(fp)
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
## Codegen: Assign Stmt ##
ld x29, 16(fp)
mv x9, x29
## Codegen: Assign Stmt ##
ld x30, 16(fp)
mv x18, x30
## Codegen: Assign Stmt ##
ld x31, 24(fp)
mv x19, x31
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
add x5, x0, x0
add x5, x5, x9
slli x5, x5, 2
la x6, _GLOBAL_a
add x6, x6, x5
lw x6, 0(x6)
ble x17, x6, _SKIP_2
la ra, _BOOL_SHORT_0
jr ra
_SKIP_2:
blt x18, x13, _SKIP_3
la ra, _BOOL_SHORT_0
jr ra
_SKIP_3:
addi x7, x0, 1
la ra, _BOOL_EXIT_0
jr ra
_BOOL_SHORT_0:
mv x7, x0
_BOOL_EXIT_0:
bnez x7, _SKIP_4
la ra, _WHILE_EXIT_1
jr ra
_SKIP_4:
## Codegen: Block ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_2: .word 1
.align 2
.text
la x28, _CONSTANT_2
lw x28, 0(x28)
addw x29, x18, x28
mv x18, x29
la ra, _WHILE_LABEL_1
jr ra
_WHILE_EXIT_1:
## Codegen: While Stmt ##
_WHILE_LABEL_2:
add x30, x0, x0
add x30, x30, x19
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
lw x31, 0(x31)
add x5, x0, x0
add x5, x5, x9
slli x5, x5, 2
la x6, _GLOBAL_a
add x6, x6, x5
lw x6, 0(x6)
bgt x31, x6, _SKIP_5
la ra, _BOOL_SHORT_1
jr ra
_SKIP_5:
bge x19, x12, _SKIP_6
la ra, _BOOL_SHORT_1
jr ra
_SKIP_6:
addi x7, x0, 1
la ra, _BOOL_EXIT_1
jr ra
_BOOL_SHORT_1:
mv x7, x0
_BOOL_EXIT_1:
bnez x7, _SKIP_7
la ra, _WHILE_EXIT_2
jr ra
_SKIP_7:
## Codegen: Block ##
## Codegen: Assign Stmt ##
.data
_CONSTANT_3: .word 1
.align 2
.text
la x28, _CONSTANT_3
lw x28, 0(x28)
subw x29, x19, x28
mv x19, x29
la ra, _WHILE_LABEL_2
jr ra
_WHILE_EXIT_2:
## Codegen: If Stmt ##
slt x30, x18, x19
bnez x30, _SKIP_8
la ra, _IF_EXIT_1
jr ra
_SKIP_8:
## Codegen: Block ##
## Codegen: Assign Stmt ##
add x5, x0, x0
add x5, x5, x18
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
lw x31, 0(x31)
mv x20, x31
## Codegen: Assign Stmt ##
add x6, x0, x0
add x6, x6, x19
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
lw x7, 0(x7)
add x28, x0, x0
add x28, x28, x18
slli x28, x28, 2
la x29, _GLOBAL_a
add x29, x29, x28
sw x7, 0(x29)
## Codegen: Assign Stmt ##
add x30, x0, x0
add x30, x30, x19
slli x30, x30, 2
la x5, _GLOBAL_a
add x5, x5, x30
sw x20, 0(x5)
_IF_EXIT_1:
la ra, _WHILE_LABEL_0
jr ra
_WHILE_EXIT_0:
## Codegen: Assign Stmt ##
add x31, x0, x0
add x31, x31, x9
slli x31, x31, 2
la x6, _GLOBAL_a
add x6, x6, x31
lw x6, 0(x6)
mv x20, x6
## Codegen: Assign Stmt ##
add x28, x0, x0
add x28, x28, x19
slli x28, x28, 2
la x7, _GLOBAL_a
add x7, x7, x28
lw x7, 0(x7)
add x29, x0, x0
add x29, x29, x9
slli x29, x29, 2
la x30, _GLOBAL_a
add x30, x30, x29
sw x7, 0(x30)
## Codegen: Assign Stmt ##
add x5, x0, x0
add x5, x5, x19
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x20, 0(x31)
## Codegen: Normal Function Call Stmt ##
sd x12, 16(fp)
sd x13, 24(fp)
sd x14, 24(fp)
sd x15, 24(fp)
sd x16, 24(fp)
sd x17, 16(fp)
ld x6, 16(fp)
.data
_CONSTANT_4: .word 1
.align 2
.text
la x28, _CONSTANT_4
lw x28, 0(x28)
subw x29, x19, x28
li ra, 16
add sp, sp, ra
mv x10, x6
mv x11, x29
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: Normal Function Call Stmt ##
sd x6, 16(fp)
sd x29, 16(fp)
.data
_CONSTANT_5: .word 1
.align 2
.text
la x7, _CONSTANT_5
lw x7, 0(x7)
addw x30, x19, x7
ld x5, 24(fp)
li ra, 16
add sp, sp, ra
mv x10, x30
mv x11, x5
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
_CONSTANT_6: .word 2
.align 2
.text
la x5, _CONSTANT_6
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_7: .word 0
.align 2
.text
la x7, _CONSTANT_7
lw x7, 0(x7)
add x6, x6, x7
slli x6, x6, 2
la x28, _GLOBAL_a
add x28, x28, x6
sw x5, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_8: .word 10
.align 2
.text
la x29, _CONSTANT_8
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_9: .word 1
.align 2
.text
la x31, _CONSTANT_9
lw x31, 0(x31)
add x30, x30, x31
slli x30, x30, 2
la x10, _GLOBAL_a
add x10, x10, x30
sw x29, 0(x10)
## Codegen: Assign Stmt ##
.data
_CONSTANT_10: .word 3
.align 2
.text
la x11, _CONSTANT_10
lw x11, 0(x11)
add x12, x0, x0
.data
_CONSTANT_11: .word 2
.align 2
.text
la x13, _CONSTANT_11
lw x13, 0(x13)
add x12, x12, x13
slli x12, x12, 2
la x14, _GLOBAL_a
add x14, x14, x12
sw x11, 0(x14)
## Codegen: Assign Stmt ##
.data
_CONSTANT_12: .word 8
.align 2
.text
la x15, _CONSTANT_12
lw x15, 0(x15)
add x16, x0, x0
.data
_CONSTANT_13: .word 3
.align 2
.text
la x17, _CONSTANT_13
lw x17, 0(x17)
add x16, x16, x17
slli x16, x16, 2
la x7, _GLOBAL_a
add x7, x7, x16
sw x15, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_14: .word 1
.align 2
.text
la x6, _CONSTANT_14
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_15: .word 4
.align 2
.text
la x28, _CONSTANT_15
lw x28, 0(x28)
add x5, x5, x28
slli x5, x5, 2
la x31, _GLOBAL_a
add x31, x31, x5
sw x6, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_16: .word 9
.align 2
.text
la x30, _CONSTANT_16
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_17: .word 5
.align 2
.text
la x7, _CONSTANT_17
lw x7, 0(x7)
add x29, x29, x7
slli x29, x29, 2
la x28, _GLOBAL_a
add x28, x28, x29
sw x30, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_18: .word 4
.align 2
.text
la x5, _CONSTANT_18
lw x5, 0(x5)
add x6, x0, x0
.data
_CONSTANT_19: .word 6
.align 2
.text
la x31, _CONSTANT_19
lw x31, 0(x31)
add x6, x6, x31
slli x6, x6, 2
la x7, _GLOBAL_a
add x7, x7, x6
sw x5, 0(x7)
## Codegen: Assign Stmt ##
.data
_CONSTANT_20: .word 7
.align 2
.text
la x29, _CONSTANT_20
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_21: .word 7
.align 2
.text
la x28, _CONSTANT_21
lw x28, 0(x28)
add x30, x30, x28
slli x30, x30, 2
la x31, _GLOBAL_a
add x31, x31, x30
sw x29, 0(x31)
## Codegen: Assign Stmt ##
.data
_CONSTANT_22: .word 6
.align 2
.text
la x6, _CONSTANT_22
lw x6, 0(x6)
add x5, x0, x0
.data
_CONSTANT_23: .word 8
.align 2
.text
la x7, _CONSTANT_23
lw x7, 0(x7)
add x5, x5, x7
slli x5, x5, 2
la x28, _GLOBAL_a
add x28, x28, x5
sw x6, 0(x28)
## Codegen: Assign Stmt ##
.data
_CONSTANT_24: .word 5
.align 2
.text
la x30, _CONSTANT_24
lw x30, 0(x30)
add x29, x0, x0
.data
_CONSTANT_25: .word 9
.align 2
.text
la x31, _CONSTANT_25
lw x31, 0(x31)
add x29, x29, x31
slli x29, x29, 2
la x7, _GLOBAL_a
add x7, x7, x29
sw x30, 0(x7)
## Codegen: Normal Function Call Stmt ##
sd x10, -20(fp)
sd x11, -20(fp)
sd x12, -28(fp)
sd x13, -12(fp)
sd x14, -12(fp)
sd x15, -12(fp)
sd x16, -20(fp)
sd x17, -28(fp)
.data
_CONSTANT_26: .word 0
.align 2
.text
la x5, _CONSTANT_26
lw x5, 0(x5)
.data
_CONSTANT_27: .word 9
.align 2
.text
la x6, _CONSTANT_27
lw x6, 0(x6)
li ra, 16
add sp, sp, ra
mv x10, x5
mv x11, x6
call _start_quicksort
li ra, -16
add sp, sp, ra
## Codegen: For Stmt ##
_FOR_LABEL_0:
## Codegen: Assign Stmt ##
.data
_CONSTANT_28: .word 0
.align 2
.text
la x28, _CONSTANT_28
lw x28, 0(x28)
mv x9, x28
_FOR_BODY_0:
.data
_CONSTANT_29: .word 10
.align 2
.text
la x31, _CONSTANT_29
lw x31, 0(x31)
slt x29, x9, x31
bnez x29, _SKIP_9
la ra, _FOR_EXIT_0
jr ra
_SKIP_9:
## Codegen: Block ##
## Codegen: write() call Stmt ##
sd x5, -28(fp)
sd x6, -12(fp)
add x30, x0, x0
add x30, x30, x9
slli x30, x30, 2
la x7, _GLOBAL_a
add x7, x7, x30
lw x7, 0(x7)
mv a0, x7
call _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_30: .string "\n"
.align 4
.text
la x28, _CONSTANT_30
mv a0, x28
call _write_str
## Codegen: Assign Stmt ##
.data
_CONSTANT_31: .word 1
.align 2
.text
la x31, _CONSTANT_31
lw x31, 0(x31)
addw x29, x9, x31
mv x9, x29
la ra, _FOR_BODY_0
jr ra
_FOR_EXIT_0:
## Codegen: Return Stmt ##
.data
_CONSTANT_32: .word 0
.align 2
.text
la x30, _CONSTANT_32
lw x30, 0(x30)
mv a0, x30
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
