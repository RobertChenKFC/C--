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
/* Function:        _FUNCTION_<functionName>,     _FUNCTION_END_<functionName>*/
/* Global variable: _GLOBAL_<variableName>                                    */
/* AR size:         _FRAME_SIZE_<functionName>                                */
/* =========== label convention ========== */

/* =========== variable offsets ========== */
/* local variable and temporary */
extern int localVariableOffset;
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
/* =========== code generation ========== */

#endif // CODEGEN_H
