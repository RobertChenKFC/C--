.text
## Codegen: Type Declaration ##
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_a: .space 80
## Codegen: Global Variable Declaration ##
.data
_GLOBAL_b: .space 240
.text
_FUNCTION_f
sd ra, 8(sp)
sd fp, 0(sp)
addi fp, sp, -8
addi sp, sp, -16
la ra, _FRAME_SIZE_f
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
ld ra, 8(fp)
addi fp, sp, 8
ld fp, 0(fp)
jr ra
.data
_FRAME_SIZE_f
: .word 0
.text
.text
_FUNCTION_main
sd ra, 8(sp)
sd fp, 0(sp)
addi fp, sp, -8
addi sp, sp, -16
la ra, _FRAME_SIZE_main
lw ra, 0(ra)
sub sp, sp, ra
## Codegen: Function Declaration ##
## Codegen: Block ##
## Codegen: Local Variable Declaration ##
## Codegen: Assign Stmt ##
ld ra, 8(fp)
addi fp, sp, 8
ld fp, 0(fp)
jr ra
.data
_FRAME_SIZE_main
: .word 8
.text
