#ifndef CODEGEN_H
#define CODEGEN_H

#include "header.h"
#include <stdbool.h>

/* =========== register manager ========== */
void RegInit();
void RegEnd();
void RegReset();
void RegClear();
Reg RegGet(bool isFloat, bool isCallerSaved, int offset);
void RegFree(Reg reg);
Reg RegRestore(Reg oldReg, int offset);
/* Note: the following is a new function for function argument registers */
/**
 * This function "RegGetParam" should be called when dealing with function
 * declarations. It should be called in the order of the function parameters
 * listed, and this function will return, in order, the function argument
 * registers.
 *
 * For instance, consider the following function declaration:
 *   void f(int p1, float p2, int p3, float p4) {}
 * Then, the following function calls should be made:
 *   <register for p1> = RegGetParam(false, <offset of p1>);
 *   <register for p2> = RegGetParam(true,  <offset of p2>);
 *   <register for p3> = RegGetParam(false, <offset of p3>);
 *   <register for p4> = RegGetParam(true,  <offset of p4>);
 * Note that for the parameters, the following argument registers are assigned:
 *   p1:  a0
 *   p2: fa0
 *   p3:  a1
 *   p4: fa1
 *
 * After a register is acquired via RegGetParam, it will not be obtainble
 * from subsequent RegGet or RegGetParam calls. The register acquired from
 * RegGetParam is a caller saved register, and should be handled with the same
 * care as normal caller saved registers (for instance, the register will be
 * spilled when encountering a function call, thus one must remember to call
 * RegRestore afterwards).
 *
 * This function should be called AFTER RegReset has been called.
 */
Reg RegGetParam(bool isFloat, int offset);
/* =========== register manager ========== */

/* =========== label convention ========== */
/* Constant:        _CONSTANT_<constantCounter>                               */
extern int constantCounter;
/* Boolean:         _BOOL_SHORT_<booleanCounter>, _BOOL_EXIT_<booleanCounter> */
extern int booleanCounter;
/* While:           _WHILE_LABEL_<whileCounter>,  _WHILE_EXIT_<whileCounter>  */
extern int whileCounter;
/* For:             _FOR_LABEL_<forCounter>,      _FOR_EXIT_<forCounter>      */
extern int forCounter;
/* If:              _ELSE_LABEL_<ifCounter>,      _IF_EXIT_<ifCounter>        */
extern int ifCounter;
/* Skip branch:     _SKIP_<skipCounter>                                       */
/* Note: this is added to support long branches                               */
extern int skipCounter;
/* Function:        _start_<functionName>,        _FUNCTION_END_<functionName>*/
/* Global variable: _GLOBAL_<variableName>                                    */
/* AR size:         _FRAME_SIZE_<functionName>                                */
/* =========== label convention ========== */

/* =========== variable offsets ========== */
/* frame size */
extern int arSize;
/* =========== variable offsets ========== */

/* =========== code generation ========== */
void CodegenProgramNode(AST_NODE *programNode);
/* Declaration */
void CodegenDeclarationNode(AST_NODE *declarationNode);
void CodegenParameterDeclaration(AST_NODE *paramNode);
void CodegenVariableDeclaration(AST_NODE *variableNode);
void CodegenFunctionDeclaration(AST_NODE *functionNode);
void CodegenFunctionPrologue(AST_NODE *functionNode);
void CodegenFunctionEpilogue(AST_NODE *functionNode);
/* Statement */
void CodegenBlockNode(AST_NODE *blockNode);
void CodegenStmtNode(AST_NODE *stmtNode);
void CodegenWhileStmt(AST_NODE *whileStmt);
void CodegenForStmt(AST_NODE *forStmt);
void CodegenAssignStmt(AST_NODE *assignStmt);
void CodegenIfStmt(AST_NODE *ifStmt);
void CodegenFunctionCallStmt(AST_NODE *functionCallStmt);
void CodegenReadFunction(AST_NODE *readFunctionCall);
void CodegenWriteFunction(AST_NODE *writeFunctionCall);
void CodegenReturnStmt(AST_NODE *returnStmt);
/* Expression */
void CodegenExprRelated(AST_NODE *exprRelated);
void CodegenVariableRef(AST_NODE *varRef, bool isLValue);
void CodegenConstValue(AST_NODE *constValue);
void CodegenExpr(AST_NODE *exprNode);
void CodegenUnaryBooleanExpr(AST_NODE *exprNode);
void CodegenUnaryArithmeticExpr(AST_NODE *exprNode);
void CodegenBinaryBooleanExpr(AST_NODE *exprNode);
void CodegenBinaryArithmeticExpr(AST_NODE *exprNode);
void CodegenShortCircuitArithmeticExpr(AST_NODE *exprNode);
/* Branches */
typedef enum {
  BEQZ,
  BNEZ,
  BEQ,
  BNE,
  BLT,
  BLE,
  BGT,
  BGE
} BranchInst;
void CodegenJumpLabel(const char *label);
void CodegenJumpLabelNo(const char *label, int labelNo);
void CodegenJumpLabelStr(const char *label, const char *str);
void CodegenBranchZero(BranchInst inst, int reg,
                       const char *label, int labelNo);
void CodegenBranch(BranchInst inst, int reg1, int reg2,
                   const char *label, int labelNo);
/* =========== code generation ========== */

#endif // CODEGEN_H
