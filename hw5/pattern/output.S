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
_FUNCTION_main
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
la ra, _FRAME_SIZE_main
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
_CONSTANT_0: .word 1
.align 2
.text
la x5, _CONSTANT_0
lw x5, 0(x5)
la x6, _GLOBAL_g1
mv x6, x5
sd x6, -8(fp)
mv x7, x6
## Codegen: Assign Stmt ##
.data
_CONSTANT_1: .float 2.000000
.align 2
.text
la x28, _CONSTANT_1
flw f0, 0(x28
)la x29, _GLOBAL_g2
mv x1, x0
fsw f1, -20(fp)
fmv.s f2, f1
## Codegen: Assign Stmt ##
.data
_CONSTANT_2: .word 3
.align 2
.text
la x30, _CONSTANT_2
lw x30, 0(x30)
la x31, _GLOBAL_g3
mv x31, x30
sd x31, -24(fp)
mv x5, x31
## Codegen: Assign Stmt ##
.data
_CONSTANT_3: .float 4.000000
.align 2
.text
la x6, _CONSTANT_3
flw f3, 0(x6
)la x28, _GLOBAL_g4
mv x4, x3
fsw f4, -32(fp)
fmv.s f5, f4
## Codegen: Assign Stmt ##
.data
_CONSTANT_4: .word 5
.align 2
.text
la x29, _CONSTANT_4
lw x29, 0(x29)
add x30, x0, x0
.data
_CONSTANT_5: .word 0
.align 2
.text
la x31, _CONSTANT_5
lw x31, 0(x31)
add x30, x30, x31
slli x30, 3
la x6, _GLOBAL_g5
add x6, x6, x30
mv x6, x29
sd x6, -52(fp)
mv x28, x6
## Codegen: Assign Stmt ##
.data
_CONSTANT_6: .word 55
.align 2
.text
la x31, _CONSTANT_6
lw x31, 0(x31)
add x30, x0, x0
.data
_CONSTANT_7: .word 1
.align 2
.text
la x29, _CONSTANT_7
lw x29, 0(x29)
add x30, x30, x29
slli x30, 3
la x6, _GLOBAL_g5
add x6, x6, x30
mv x6, x31
sd x6, -68(fp)
mv x29, x6
## Codegen: Assign Stmt ##
.data
_CONSTANT_8: .float 6.000000
.align 2
.text
la x30, _CONSTANT_8
flw f6, 0(x30
)add x31, x0, x0
.data
_CONSTANT_9: .word 0
.align 2
.text
la x6, _CONSTANT_9
lw x6, 0(x6)
add x31, x31, x6
slli x31, 2
la x30, _GLOBAL_g6
add x30, x30, x31
mv x7, x6
fsw f7, -76(fp)
fmv.s f28, f7
## Codegen: Assign Stmt ##
.data
_CONSTANT_10: .float 66.000000
.align 2
.text
la x6, _CONSTANT_10
flw f29, 0(x6
)add x30, x0, x0
.data
_CONSTANT_11: .word 1
.align 2
.text
la x31, _CONSTANT_11
lw x31, 0(x31)
add x30, x30, x31
slli x30, 2
la x6, _GLOBAL_g6
add x6, x6, x30
mv x30, x29
fsw f30, -88(fp)
fmv.s f31, f30
## Codegen: Assign Stmt ##
.data
_CONSTANT_12: .word 7
.align 2
.text
la x31, _CONSTANT_12
lw x31, 0(x31)
add x6, x0, x0
.data
_CONSTANT_13: .word 0
.align 2
.text
la x30, _CONSTANT_13
lw x30, 0(x30)
add x6, x6, x30
slli x6, 3
la x30, _GLOBAL_g7
add x30, x30, x6
mv x30, x31
sd x30, -108(fp)
mv x6, x30
## Codegen: Assign Stmt ##
.data
_CONSTANT_14: .word 77
.align 2
.text
la x31, _CONSTANT_14
lw x31, 0(x31)
add x30, x0, x0
sd x7, 0(fp)
.data
_CONSTANT_15: .word 1
.align 2
.text
la x7, _CONSTANT_15
lw x7, 0(x7)
add x30, x30, x7
slli x30, 3
la x7, _GLOBAL_g7
add x7, x7, x30
mv x7, x31
sd x7, -124(fp)
mv x30, x7
## Codegen: Assign Stmt ##
.data
_CONSTANT_16: .float 8.000000
.align 2
.text
la x31, _CONSTANT_16
flw f0, 0(x31
)add x7, x0, x0
.data
_CONSTANT_17: .word 0
.align 2
.text
la x31, _CONSTANT_17
lw x31, 0(x31)
add x7, x7, x31
slli x7, 2
la x31, _GLOBAL_g8
add x31, x31, x7
mv x1, x0
fsw f1, -132(fp)
fmv.s f3, f1
## Codegen: Assign Stmt ##
.data
_CONSTANT_18: .float 88.000000
.align 2
.text
la x31, _CONSTANT_18
flw f4, 0(x31
)add x7, x0, x0
.data
_CONSTANT_19: .word 1
.align 2
.text
la x31, _CONSTANT_19
lw x31, 0(x31)
add x7, x7, x31
slli x7, 2
la x31, _GLOBAL_g8
add x31, x31, x7
mv x6, x4
fsw f6, -144(fp)
fmv.s f7, f6
## Codegen: Assign Stmt ##
.data
_CONSTANT_20: .word 9
.align 2
.text
la x31, _CONSTANT_20
lw x31, 0(x31)
add x7, x0, x0
sd x5, -8(fp)
.data
_CONSTANT_21: .word 0
.align 2
.text
la x5, _CONSTANT_21
lw x5, 0(x5)
add x7, x7, x5
slli x7, 3
la x5, _GLOBAL_g9
add x5, x5, x7
mv x5, x31
sd x5, -164(fp)
mv x7, x5
## Codegen: Assign Stmt ##
.data
_CONSTANT_22: .word 99
.align 2
.text
la x31, _CONSTANT_22
lw x31, 0(x31)
add x5, x0, x0
sd x28, -24(fp)
.data
_CONSTANT_23: .word 1
.align 2
.text
la x28, _CONSTANT_23
lw x28, 0(x28)
add x5, x5, x28
slli x5, 3
la x28, _GLOBAL_g9
add x28, x28, x5
mv x28, x31
sd x28, -180(fp)
mv x5, x28
## Codegen: Assign Stmt ##
.data
_CONSTANT_24: .float 10.000000
.align 2
.text
la x31, _CONSTANT_24
flw f29, 0(x31
)add x28, x0, x0
.data
_CONSTANT_25: .word 0
.align 2
.text
la x31, _CONSTANT_25
lw x31, 0(x31)
add x28, x28, x31
slli x28, 2
la x31, _GLOBAL_g10
add x31, x31, x28
mv x30, x29
fsw f30, -188(fp)
fmv.s f0, f30
## Codegen: Assign Stmt ##
.data
_CONSTANT_26: .float 100.000000
.align 2
.text
la x31, _CONSTANT_26
flw f1, 0(x31
)add x28, x0, x0
.data
_CONSTANT_27: .word 1
.align 2
.text
la x31, _CONSTANT_27
lw x31, 0(x31)
add x28, x28, x31
slli x28, 2
la x31, _GLOBAL_g10
add x31, x31, x28
mv x4, x1
fsw f4, -200(fp)
fmv.s f6, f4
## Codegen: Assign Stmt ##
.data
_CONSTANT_28: .word 1
.align 2
.text
la x31, _CONSTANT_28
lw x31, 0(x31)
mv x9, x31
sd x9, 0(fp)
mv x28, x9
## Codegen: Assign Stmt ##
.data
_CONSTANT_29: .float 2.000000
.align 2
.text
la x31, _CONSTANT_29
flw f29, 0(x31
)mv x8, x29
fsw f8, -8(fp)
fmv.s f30, f8
## Codegen: Assign Stmt ##
.data
_CONSTANT_30: .word 3
.align 2
.text
la x31, _CONSTANT_30
lw x31, 0(x31)
mv x18, x31
sd x18, -12(fp)
mv x31, x18
## Codegen: Assign Stmt ##
sd x29, -52(fp)
.data
_CONSTANT_31: .float 4.000000
.align 2
.text
la x29, _CONSTANT_31
flw f1, 0(x29
)mv x9, x1
fsw f9, -20(fp)
fmv.s f4, f9
## Codegen: Assign Stmt ##
.data
_CONSTANT_32: .word 5
.align 2
.text
la x29, _CONSTANT_32
lw x29, 0(x29)
sd x6, -68(fp)
add x6, x0, x0
sd x30, -108(fp)
.data
_CONSTANT_33: .word 0
.align 2
.text
la x30, _CONSTANT_33
lw x30, 0(x30)
add x6, x6, x30
slli x6, 3
addi x19, fp, -24
mv x30, x19
add x30, x30, x6
mv x30, x29
sd x30, -240(fp)
mv x6, x30
## Codegen: Assign Stmt ##
.data
_CONSTANT_34: .word 55
.align 2
.text
la x29, _CONSTANT_34
lw x29, 0(x29)
add x30, x0, x0
sd x7, -124(fp)
.data
_CONSTANT_35: .word 1
.align 2
.text
la x7, _CONSTANT_35
lw x7, 0(x7)
add x30, x30, x7
slli x30, 3
mv x7, x19
add x7, x7, x30
mv x7, x29
sd x7, -256(fp)
mv x30, x7
## Codegen: Assign Stmt ##
.data
_CONSTANT_36: .float 6.000000
.align 2
.text
la x29, _CONSTANT_36
flw f29, 0(x29
)add x7, x0, x0
.data
_CONSTANT_37: .word 0
.align 2
.text
la x29, _CONSTANT_37
lw x29, 0(x29)
add x7, x7, x29
slli x7, 2
addi x20, fp, -40
mv x29, x20
add x29, x29, x7
mv x1, x29
fsw f1, -268(fp)
fmv.s f29, f1
## Codegen: Assign Stmt ##
.data
_CONSTANT_38: .float 66.000000
.align 2
.text
la x29, _CONSTANT_38
flw f1, 0(x29
)add x7, x0, x0
.data
_CONSTANT_39: .word 1
.align 2
.text
la x29, _CONSTANT_39
lw x29, 0(x29)
add x7, x7, x29
slli x7, 2
fsw f2, -16(fp)
mv x29, x20
add x29, x29, x7
mv x2, x1
fsw f2, -280(fp)
fmv.s f1, f2
## Codegen: Assign Stmt ##
.data
_CONSTANT_40: .word 7
.align 2
.text
la x29, _CONSTANT_40
lw x29, 0(x29)
add x7, x0, x0
sd x5, -164(fp)
.data
_CONSTANT_41: .word 0
.align 2
.text
la x5, _CONSTANT_41
lw x5, 0(x5)
add x7, x7, x5
slli x7, 3
addi x21, fp, -48
mv x5, x21
add x5, x5, x7
mv x5, x29
sd x5, -300(fp)
mv x7, x5
## Codegen: Assign Stmt ##
.data
_CONSTANT_42: .word 77
.align 2
.text
la x29, _CONSTANT_42
lw x29, 0(x29)
add x5, x0, x0
sd x28, -180(fp)
.data
_CONSTANT_43: .word 1
.align 2
.text
la x28, _CONSTANT_43
lw x28, 0(x28)
add x5, x5, x28
slli x5, 3
mv x28, x21
add x28, x28, x5
mv x28, x29
sd x28, -316(fp)
mv x5, x28
## Codegen: Assign Stmt ##
.data
_CONSTANT_44: .float 8.000000
.align 2
.text
la x29, _CONSTANT_44
flw f2, 0(x29
)add x28, x0, x0
.data
_CONSTANT_45: .word 0
.align 2
.text
la x29, _CONSTANT_45
lw x29, 0(x29)
add x28, x28, x29
slli x28, 2
addi x22, fp, -64
fsw f5, -20(fp)
mv x29, x22
add x29, x29, x28
mv x5, x2
fsw f5, -324(fp)
fmv.s f2, f5
## Codegen: Assign Stmt ##
.data
_CONSTANT_46: .float 88.000000
.align 2
.text
la x29, _CONSTANT_46
flw f5, 0(x29
)add x28, x0, x0
.data
_CONSTANT_47: .word 1
.align 2
.text
la x29, _CONSTANT_47
lw x29, 0(x29)
add x28, x28, x29
slli x28, 2
fsw f28, -32(fp)
mv x29, x22
add x29, x29, x28
mv x28, x5
fsw f28, -336(fp)
fmv.s f5, f28
## Codegen: Assign Stmt ##
.data
_CONSTANT_48: .word 9
.align 2
.text
la x29, _CONSTANT_48
lw x29, 0(x29)
add x28, x0, x0
sd x31, -204(fp)
.data
_CONSTANT_49: .word 0
.align 2
.text
la x31, _CONSTANT_49
lw x31, 0(x31)
add x28, x28, x31
slli x28, 3
addi x23, fp, -72
mv x31, x23
add x31, x31, x28
mv x31, x29
sd x31, -356(fp)
mv x28, x31
## Codegen: Assign Stmt ##
.data
_CONSTANT_50: .word 99
.align 2
.text
la x29, _CONSTANT_50
lw x29, 0(x29)
add x31, x0, x0
sd x6, -216(fp)
.data
_CONSTANT_51: .word 1
.align 2
.text
la x6, _CONSTANT_51
lw x6, 0(x6)
add x31, x31, x6
slli x31, 3
mv x6, x23
add x6, x6, x31
mv x6, x29
sd x6, -372(fp)
mv x31, x6
## Codegen: Assign Stmt ##
.data
_CONSTANT_52: .float 10.000000
.align 2
.text
la x29, _CONSTANT_52
flw f28, 0(x29
)add x6, x0, x0
.data
_CONSTANT_53: .word 0
.align 2
.text
la x29, _CONSTANT_53
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
addi x24, fp, -88
fsw f31, -76(fp)
mv x29, x24
add x29, x29, x6
mv x31, x28
fsw f31, -380(fp)
fmv.s f28, f31
## Codegen: Assign Stmt ##
.data
_CONSTANT_54: .float 100.000000
.align 2
.text
la x29, _CONSTANT_54
flw f31, 0(x29
)add x6, x0, x0
.data
_CONSTANT_55: .word 1
.align 2
.text
la x29, _CONSTANT_55
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
fsw f3, -88(fp)
mv x29, x24
add x29, x29, x6
mv x3, x31
fsw f3, -392(fp)
fmv.s f31, f3
## Codegen: write() call Stmt ##
sd x30, -240(fp)
sd x7, -256(fp)
sd x5, -300(fp)
sd x28, -316(fp)
sd x31, -356(fp)
fsw f7, -132(fp)
fsw f0, -144(fp)
fsw f6, -188(fp)
fsw f30, -200(fp)
fsw f4, -212(fp)
fsw f29, -264(fp)
fsw f1, -268(fp)
fsw f2, -280(fp)
fsw f5, -324(fp)
fsw f28, -336(fp)
fsw f31, -380(fp)
la x29, _GLOBAL_g1
ld x29, 0(x29)
mv a0, x29
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_56: .string "\n"
.align 3
.text
la x3, _CONSTANT_56
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
la x6, _GLOBAL_g2
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_57: .string "\n"
.align 3
.text
la x3, _CONSTANT_57
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
la x29, _GLOBAL_g3
ld x29, 0(x29)
mv a0, x29
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_58: .string "\n"
.align 3
.text
la x3, _CONSTANT_58
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
la x6, _GLOBAL_g4
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_59: .string "\n"
.align 3
.text
la x3, _CONSTANT_59
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_60: .word 0
.align 2
.text
la x6, _CONSTANT_60
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g5
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_61: .string "\n"
.align 3
.text
la x3, _CONSTANT_61
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_62: .word 1
.align 2
.text
la x6, _CONSTANT_62
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g5
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_63: .string "\n"
.align 3
.text
la x3, _CONSTANT_63
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_64: .word 0
.align 2
.text
la x6, _CONSTANT_64
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
la x6, _GLOBAL_g6
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_65: .string "\n"
.align 3
.text
la x3, _CONSTANT_65
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_66: .word 1
.align 2
.text
la x29, _CONSTANT_66
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
la x29, _GLOBAL_g6
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_67: .string "\n"
.align 3
.text
la x3, _CONSTANT_67
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_68: .word 0
.align 2
.text
la x6, _CONSTANT_68
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g7
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_69: .string "\n"
.align 3
.text
la x3, _CONSTANT_69
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_70: .word 1
.align 2
.text
la x6, _CONSTANT_70
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g7
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_71: .string "\n"
.align 3
.text
la x3, _CONSTANT_71
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_72: .word 0
.align 2
.text
la x6, _CONSTANT_72
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
la x6, _GLOBAL_g8
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_73: .string "\n"
.align 3
.text
la x3, _CONSTANT_73
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_74: .word 1
.align 2
.text
la x29, _CONSTANT_74
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
la x29, _GLOBAL_g8
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_75: .string "\n"
.align 3
.text
la x3, _CONSTANT_75
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_76: .word 0
.align 2
.text
la x6, _CONSTANT_76
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g9
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_77: .string "\n"
.align 3
.text
la x3, _CONSTANT_77
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_78: .word 1
.align 2
.text
la x6, _CONSTANT_78
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
la x6, _GLOBAL_g9
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_79: .string "\n"
.align 3
.text
la x3, _CONSTANT_79
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_80: .word 0
.align 2
.text
la x6, _CONSTANT_80
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
la x6, _GLOBAL_g10
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_81: .string "\n"
.align 3
.text
la x3, _CONSTANT_81
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_82: .word 1
.align 2
.text
la x29, _CONSTANT_82
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
la x29, _GLOBAL_g10
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_83: .string "\n"
.align 3
.text
la x3, _CONSTANT_83
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
mv a0, x9
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_84: .string "\n"
.align 3
.text
la x3, _CONSTANT_84
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
mv a0, x8
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_85: .string "\n"
.align 3
.text
la x3, _CONSTANT_85
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
mv a0, x18
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_86: .string "\n"
.align 3
.text
la x3, _CONSTANT_86
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
mv a0, x9
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_87: .string "\n"
.align 3
.text
la x3, _CONSTANT_87
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_88: .word 0
.align 2
.text
la x6, _CONSTANT_88
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x19
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_89: .string "\n"
.align 3
.text
la x3, _CONSTANT_89
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_90: .word 1
.align 2
.text
la x6, _CONSTANT_90
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x19
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_91: .string "\n"
.align 3
.text
la x3, _CONSTANT_91
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_92: .word 0
.align 2
.text
la x6, _CONSTANT_92
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
mv x6, x20
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_93: .string "\n"
.align 3
.text
la x3, _CONSTANT_93
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_94: .word 1
.align 2
.text
la x29, _CONSTANT_94
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
mv x29, x20
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_95: .string "\n"
.align 3
.text
la x3, _CONSTANT_95
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_96: .word 0
.align 2
.text
la x6, _CONSTANT_96
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x21
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_97: .string "\n"
.align 3
.text
la x3, _CONSTANT_97
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_98: .word 1
.align 2
.text
la x6, _CONSTANT_98
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x21
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_99: .string "\n"
.align 3
.text
la x3, _CONSTANT_99
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_100: .word 0
.align 2
.text
la x6, _CONSTANT_100
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
mv x6, x22
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_101: .string "\n"
.align 3
.text
la x3, _CONSTANT_101
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_102: .word 1
.align 2
.text
la x29, _CONSTANT_102
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
mv x29, x22
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_103: .string "\n"
.align 3
.text
la x3, _CONSTANT_103
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_104: .word 0
.align 2
.text
la x6, _CONSTANT_104
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x23
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_105: .string "\n"
.align 3
.text
la x3, _CONSTANT_105
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_106: .word 1
.align 2
.text
la x6, _CONSTANT_106
lw x6, 0(x6)
add x29, x29, x6
slli x29, 3
mv x6, x23
add x6, x6, x29
ld x6, 0(x6)
mv a0, x6
jal _write_int
## Codegen: write() call Stmt ##
.data
_CONSTANT_107: .string "\n"
.align 3
.text
la x3, _CONSTANT_107
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x29, x0, x0
.data
_CONSTANT_108: .word 0
.align 2
.text
la x6, _CONSTANT_108
lw x6, 0(x6)
add x29, x29, x6
slli x29, 2
mv x6, x24
add x6, x6, x29
flw f3, 0(x6)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_109: .string "\n"
.align 3
.text
la x3, _CONSTANT_109
mv a0, x3
jal _write_str
## Codegen: write() call Stmt ##
add x6, x0, x0
.data
_CONSTANT_110: .word 1
.align 2
.text
la x29, _CONSTANT_110
lw x29, 0(x29)
add x6, x6, x29
slli x6, 2
mv x29, x24
add x29, x29, x6
flw f3, 0(x29)
mv a0, x3
jal _write_float
## Codegen: write() call Stmt ##
.data
_CONSTANT_111: .string "\n"
.align 3
.text
la x3, _CONSTANT_111
mv a0, x3
jal _write_str
## Codegen: Return Stmt ##
.data
_CONSTANT_112: .word 0
.align 2
.text
la x29, _CONSTANT_112
lw x29, 0(x29)
mv a0, x29
j _FUNCTION_END_int
_FUNCTION_END_main:
addi sp, sp, 940
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
addi sp, sp, 136
ld ra, 8(fp)
addi fp, sp, 8
ld fp, 0(fp)
jr ra
.data
_FRAME_SIZE_main: .word 940
.text
