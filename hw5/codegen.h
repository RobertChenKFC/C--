#ifndef CODEGEN_H
#define CODEGEN_H

#include "header.h"
#include <stdbool.h>

typedef struct {
  bool isFloat;
  bool isCallerSaved;
  int registerNumber;
} Reg;
/* call at function start */
/* me */ void RegInit();
/* me */ Reg RegGet(bool isFloat, bool isCallerSaved, int offset);
/* me */ void RegFree(Reg reg);
/* me */ Reg RegRestore(Reg oldReg);

/* Label convention */
// Constant: _CONSTANT_<constantCounter>
extern int constantCounter;
// Boolean:  _BOOL_SHORT_<booleanCounter>, _BOOL_EXIT_<booleanCounter>
extern int booleanCounter;
// While: _WHILE_LABEL_<whileCounter>, _WHILE_EXIT_<whileCounter>
extern int whileCounter;
// For: _FOR_LABEL_<forCounter>, _FOR_EXIT_<forCounter>
extern int forCounter;
// If: _ELSE_LABEL_<ifCounter>, _IF_EXIT_<ifCounter>
extern int ifCounter;
// Function: _FUNCTION_<functionName>
// Global variable: _GLOBAL_<variableName>
// AR size: _FRAME_SIZE_<functionName>

/* Variable offsets */
// local variable and temporary
extern int localVariableOffset;
// frame size
extern int arSize;

/* me */ void CodegenProgramNode(AST_NODE *programNode);
/* Declaration */
         void CodegenDeclarationNode(AST_NODE *declarationNode);
         void CodegenParameterDeclaration(AST_NODE *paramNode);
         void CodegenVariableDeclaration(AST_NODE *variableNode);
         void CodegenFunctionDeclaration(AST_NODE *functionNode);
/* me */ void CodegenFunctionPrologue(AST_NODE *functionNode);
/* me */ void CodegenFunctionEpilogue(AST_NODE *functionNode);
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
/* me */ void CodegenVariableRef(AST_NODE *varRef);
/* me */ void CodegenConstValue(AST_NODE *constValue);
/* me */ void CodegenExpr(AST_NODE *exprNode);

#endif // CODEGEN_H
