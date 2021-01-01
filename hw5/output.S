.text
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
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
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Variable Declaration ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: Assign Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: write() call Stmt ##
## Codegen: Return Stmt ##
ld ra, 8(fp)
addi fp, sp, 8
ld fp, 0(fp)
jr ra
.data
_FRAME_SIZE_main
: .word 0
.text
