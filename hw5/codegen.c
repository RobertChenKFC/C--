#include "codegen.h"
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* ========== global variables ========== */

int constantCounter = 0;
int booleanCounter = 0;
int whileCounter = 0;
int forCounter = 0;
int ifCounter = 0;
int skipCounter = 0;
int arSize = 0;
FILE *outputFile;

/* ========== global variables ========== */

/* ========== vector data structure ========== */

typedef struct {
  int *array;
  int capacity;
  int size;
} Vector;

#define VECTOR_INIT_CAPACITY 4
Vector *VectorAlloc() {
  Vector *vector = malloc(sizeof(Vector));
  vector->array = malloc(sizeof(int) * VECTOR_INIT_CAPACITY);
  vector->capacity = VECTOR_INIT_CAPACITY;
  vector->size = 0;
  return vector;
}

void VectorFree(Vector **pVector) {
  Vector *vector = *pVector;
  free(vector->array);
  free(vector);
  *pVector = NULL;
}

void VectorClear(Vector *vector) {
  vector->size = 0;
}

int VectorReadAt(Vector *vector, int idx) {
  return vector->array[idx];
}

void VectorWriteAt(Vector *vector, int idx, int elem) {
  vector->array[idx] = elem;
}

int VectorSize(Vector *vector) {
  return vector->size;
}

void VectorPushback(Vector *vector, int elem) {
  if (vector->size >= vector->capacity) {
    vector->capacity = vector->capacity * 2;
    vector->array = realloc(vector->array, sizeof(int) * vector->capacity);
  }
  vector->array[vector->size++] = elem;
}

int VectorPopback(Vector *vector) {
  return vector->array[--vector->size];
}

/* ========== vector data structure ========== */

/* ========== queue data structure ========== */

#define MAX_QUEUE_SIZE 64
typedef struct {
  int array[MAX_QUEUE_SIZE];
  int base;
  int top;
} Queue;

Queue *QueueAlloc() {
  Queue *queue = malloc(sizeof(Queue));
  queue->base = queue->top = 0;
  return queue;
}

void QueueFree(Queue **pQueue) {
  free(*pQueue);
  *pQueue = NULL;
}

void QueueClear(Queue *queue) {
  queue->base = queue->top = 0;
}

bool QueueEmpty(Queue *queue) {
  return queue->base == queue->top;
}

void QueuePush(Queue *queue, int elem) {
  queue->array[queue->top] = elem;
  queue->top = (queue->top + 1) % MAX_QUEUE_SIZE;
}

int QueuePop(Queue *queue) {
  int elem = queue->array[queue->base];
  queue->base = (queue->base + 1) % MAX_QUEUE_SIZE;
  return elem;
}

/* ========== queue data structure ========== */

/* ========== list data structure ========== */

#define MAX_LIST_SIZE 32
#define NUL_IDX       -1
typedef struct {
  int prev[MAX_LIST_SIZE];
  int next[MAX_LIST_SIZE];
  int head;
  int last;
} List;

List *ListAlloc() {
  List *list = malloc(sizeof(List));
  for (int i = 0; i < MAX_LIST_SIZE; ++i)
    list->prev[i] = list->next[i] = NUL_IDX;
  list->head = list->last = NUL_IDX;
  return list;
}

void ListFree(List **pList) {
  free(*pList);
  *pList = NULL;
}

bool ListEmpty(List *list) {
  return list->head == NUL_IDX;
}

void ListClear(List *list) {
  for (int i = 0; i < MAX_LIST_SIZE; ++i)
    list->prev[i] = list->next[i] = NUL_IDX;
  list->head = list->last = NUL_IDX;
}

int ListFront(List *list) {
  return list->head;
}

int ListNext(List *list, int elem) {
  return list->next[elem];
}

void ListPush(List *list, int elem) {
  assert(list->prev[elem] == NUL_IDX && list->next[elem] == NUL_IDX);
  if (list->last == NUL_IDX) {
    list->head = elem;
    list->prev[elem] = NUL_IDX;
  } else {
    list->prev[elem] = list->last;
    list->next[list->last] = elem;
  }
  list->next[elem] = NUL_IDX;
  list->last = elem;
}

void ListDelete(List *list, int elem) {
  assert(list->head != NUL_IDX);
  if (list->prev[elem] == NUL_IDX)
    list->head = list->next[elem];
  else
    list->next[list->prev[elem]] = list->next[elem];
  if (list->next[elem] == NUL_IDX)
    list->last = list->prev[elem];
  else
    list->prev[list->next[elem]] = list->prev[elem];
  list->prev[elem] = list->next[elem] = NUL_IDX;
}

int ListPop(List *list) {
  int elem = list->head;
  ListDelete(list, elem);
  return elem;
}

/* ========== list data structure ========== */

/* ========== temporary offset manager ========== */

Vector *freeIntTmpOffsets, *freeFloatTmpOffsets;
void TmpOffsetInit() {
  freeIntTmpOffsets = VectorAlloc();
  freeFloatTmpOffsets = VectorAlloc();
}

void TmpOffsetEnd() {
  VectorFree(&freeIntTmpOffsets);
  VectorFree(&freeFloatTmpOffsets);
}

/* TODO: remember to call this function every time a new function is declared */
void TmpOffsetReset() {
  VectorClear(freeIntTmpOffsets);
  VectorClear(freeFloatTmpOffsets);
}

int TmpOffsetGetImpl(Vector *freeTmpOffsets, int size) {
  if (VectorSize(freeTmpOffsets) == 0) {
    arSize += size;
    VectorPushback(freeTmpOffsets, -arSize);
  }
  return VectorPopback(freeTmpOffsets);
}

int TmpOffsetGet(bool isFloat) {
  if (isFloat)
    return TmpOffsetGetImpl(freeFloatTmpOffsets, 4);
  else
    return TmpOffsetGetImpl(freeIntTmpOffsets, 8);
}

void TmpOffsetFreeImpl(Vector *freeTmpOffsets, int tmpOffset) {
  // don't free an offset that corresponds to a parameter offset
  if (tmpOffset < 0) {
    for (int i = 0, size = VectorSize(freeTmpOffsets); i < size; ++i)
      assert(freeTmpOffsets->array[i] != tmpOffset);
    VectorPushback(freeTmpOffsets, tmpOffset);
  }
}

void TmpOffsetFree(bool isFloat, int tmpOffset) {
  if (isFloat)
    TmpOffsetFreeImpl(freeFloatTmpOffsets, tmpOffset);
  else
    TmpOffsetFreeImpl(freeIntTmpOffsets, tmpOffset);
}

/* ========== temporary offset manager ========== */

/* ========== register manager ========== */

#define RISCV_MAX_REG_NUM  32
#define NUL_OFFSET         8  // fp+8 is used to store return address, thus
                              // should not be a valid register spilling address
// integer caller saved registers
int intCallerSavedRegisters[] =
  { 5, 6, 7, 28, 29, 30, 31, NUL_REG };
List *freeIntCallerSavedRegisters, *usedIntCallerSavedRegisters;
int intCallerSavedRegisterOffsets[RISCV_MAX_REG_NUM];
// integer callee saved registers
int intCalleeSavedRegisters[] =
  { 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NUL_REG };
List *freeIntCalleeSavedRegisters, *usedIntCalleeSavedRegisters;
int intCalleeSavedRegisterOffsets[RISCV_MAX_REG_NUM];
// float caller saved registers
int floatCallerSavedRegisters[] =
  { 0, 1, 2, 3, 4, 5, 6, 7, 28, 29, 30, 31, NUL_REG };
List *freeFloatCallerSavedRegisters, *usedFloatCallerSavedRegisters;
int floatCallerSavedRegisterOffsets[RISCV_MAX_REG_NUM];
// float callee saved registers
int floatCalleeSavedRegisters[] =
  { 8, 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NUL_REG };
List *freeFloatCalleeSavedRegisters, *usedFloatCalleeSavedRegisters;
int floatCalleeSavedRegisterOffsets[RISCV_MAX_REG_NUM];
#define IS_ARG_REG(reg) ((reg) >= 10 && (reg) <= 17)
// integer function argument registers
int intFunctionArgumentRegisters[] =
  { 10, 11, 12, 13, 14, 15, 16, 17, NUL_REG };
int intFunctionArgumentRegisterOffsets[RISCV_MAX_REG_NUM];
int currentIntFunctionArgumentRegister;
// float function argument registers
int floatFunctionArgumentRegisters[] =
  { 10, 11, 12, 13, 14, 15, 16, 17, NUL_REG };
int floatFunctionArgumentRegisterOffsets[RISCV_MAX_REG_NUM];
int currentFloatFunctionArgumentRegister;

void RegInit() {
  // int caller saved registers
  freeIntCallerSavedRegisters = ListAlloc();
  usedIntCallerSavedRegisters = ListAlloc();
  // int callee saved registers
  freeIntCalleeSavedRegisters = ListAlloc();
  usedIntCalleeSavedRegisters = ListAlloc();
  // float caller saved registers
  freeFloatCallerSavedRegisters = ListAlloc();
  usedFloatCallerSavedRegisters = ListAlloc();
  // float callee saved registers
  freeFloatCalleeSavedRegisters = ListAlloc();
  usedFloatCalleeSavedRegisters = ListAlloc();
}

void RegEnd() {
  // int caller saved registers
  ListFree(&freeIntCallerSavedRegisters);
  ListFree(&usedIntCallerSavedRegisters);
  // int callee saved registers
  ListFree(&freeIntCalleeSavedRegisters);
  ListFree(&usedIntCalleeSavedRegisters);
  // float caller saved registers
  ListFree(&freeFloatCallerSavedRegisters);
  ListFree(&usedFloatCallerSavedRegisters);
  // float callee saved registers
  ListFree(&freeFloatCalleeSavedRegisters);
  ListFree(&usedFloatCalleeSavedRegisters);
}

/* TODO: remember to call this function every time a new function is declared */
void RegReset() {
  arSize = 0;

  // integer caller saved registers
  ListClear(freeIntCallerSavedRegisters);
  ListClear(usedIntCallerSavedRegisters);
  for (int i = 0; intCallerSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeIntCallerSavedRegisters, intCallerSavedRegisters[i]);

  // integer callee saved registers
  ListClear(freeIntCalleeSavedRegisters);
  ListClear(usedIntCalleeSavedRegisters);
  for (int i = 0; intCalleeSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeIntCalleeSavedRegisters, intCalleeSavedRegisters[i]);

  // float caller saved registers
  ListClear(freeFloatCallerSavedRegisters);
  ListClear(usedFloatCallerSavedRegisters);
  for (int i = 0; floatCallerSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeFloatCallerSavedRegisters, floatCallerSavedRegisters[i]);

  // float callee saved registers
  ListClear(freeFloatCalleeSavedRegisters);
  ListClear(usedFloatCalleeSavedRegisters);
  for (int i = 0; floatCalleeSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeFloatCalleeSavedRegisters, floatCalleeSavedRegisters[i]);

  // integer function argument registers
  currentIntFunctionArgumentRegister = 0;

  // float function argument registers
  currentFloatFunctionArgumentRegister = 0;
}

/* TODO: remember to call this function every time a function call is
 *       encountered */
void RegClear() {
  // int caller saved registers
  fprintf(outputFile, "## saving int caller saved register ##\n");
  for (int registerNumber = ListFront(usedIntCallerSavedRegisters);
       registerNumber != NUL_IDX;
       registerNumber = ListNext(usedIntCallerSavedRegisters, registerNumber)) {
    int offset = intCallerSavedRegisterOffsets[registerNumber];
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "sd x%d, %d(fp)\n", registerNumber, offset);
      intCallerSavedRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  // float caller saved registers
  fprintf(outputFile, "## saving float caller saved register ##\n");
  for (int registerNumber = ListFront(usedFloatCallerSavedRegisters);
       registerNumber != NUL_IDX;
       registerNumber = ListNext(usedFloatCallerSavedRegisters,
                                 registerNumber)) {
    int offset = floatCallerSavedRegisterOffsets[registerNumber];
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "fsw f%d, %d(fp)\n",
          registerNumber, floatCallerSavedRegisterOffsets[registerNumber]);
      floatCallerSavedRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  // int function argument registers
  fprintf(outputFile, "## saving int function argument register ##\n");
  for (int i = 0; i < currentIntFunctionArgumentRegister; ++i) {
    int registerNumber = intFunctionArgumentRegisters[i];
    int offset = intFunctionArgumentRegisterOffsets[registerNumber];
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "sd x%d, %d(fp)\n", registerNumber, offset);
      intFunctionArgumentRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  // float function argument registers
  fprintf(outputFile, "## saving float function argument register ##\n");
  for (int i = 0; i < currentFloatFunctionArgumentRegister; ++i) {
    int registerNumber = floatFunctionArgumentRegisters[i];
    int offset = floatFunctionArgumentRegisterOffsets[registerNumber];
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "fsw f%d, %d(fp)\n", registerNumber, offset);
      floatFunctionArgumentRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  fprintf(outputFile, "## end of RegClear ##\n");
}

int RegGetImpl(bool isFloat, bool isCallerSaved, int *registerOffsets,
               List *freeRegisters, List *usedRegisters, int offset) {
  if (ListEmpty(freeRegisters)) {
    // no more registers, need to spill
    int spillRegister = ListPop(usedRegisters);
    int spillOffset = registerOffsets[spillRegister];
    if (spillOffset != NUL_OFFSET) {
      // NUL_OFFSET is set by RegClear, which spills all caller saved registers
      // when a function call is encountered. Therefore, if NUL_OFFSET is
      // encountered, this means that the register has already been saved.
      if (isFloat)
        fprintf(outputFile, "fsw f%d, %d(fp)\n", spillRegister, spillOffset);
      else if (isCallerSaved)
        fprintf(outputFile, "sd x%d, %d(fp)\n", spillRegister, spillOffset);
      else
        fprintf(outputFile, "sw x%d, %d(fp)\n", spillRegister, spillOffset);
    }
    ListPush(freeRegisters, spillRegister);
  }
  int newRegister = ListPop(freeRegisters);
  ListPush(usedRegisters, newRegister);
  registerOffsets[newRegister] = offset;
  return newRegister;
}

Reg RegGet(bool isFloat, bool isCallerSaved, int offset) {
  Reg newRegister;
  newRegister.isFloat = isFloat;
  newRegister.isCallerSaved = isCallerSaved;
  if (isFloat) {
    if (isCallerSaved) {
      // float caller saved register
      newRegister.registerNumber = RegGetImpl(
          true, true, floatCallerSavedRegisterOffsets,
          freeFloatCallerSavedRegisters, usedFloatCallerSavedRegisters,
          offset);
    } else {
      // float callee saved register
      newRegister.registerNumber = RegGetImpl(
          true, false, floatCalleeSavedRegisterOffsets,
          freeFloatCalleeSavedRegisters, usedFloatCalleeSavedRegisters,
          offset);
    }
  } else {
    if (isCallerSaved) {
      // int caller saved register
      newRegister.registerNumber = RegGetImpl(
          false, true, intCallerSavedRegisterOffsets,
          freeIntCallerSavedRegisters, usedIntCallerSavedRegisters,
          offset);
    } else {
      // int caller saved register
      newRegister.registerNumber = RegGetImpl(
          false, false, intCalleeSavedRegisterOffsets,
          freeIntCalleeSavedRegisters, usedIntCalleeSavedRegisters,
          offset);
    }
  }
  return newRegister;
}

void RegFreeImpl(int registerNumber, int *registerOffsets,
                 List *freeRegisters, List *usedRegisters) {
  registerOffsets[registerNumber] = NUL_OFFSET;
  ListDelete(usedRegisters, registerNumber);
  ListPush(freeRegisters, registerNumber);
}

void RegFree(Reg reg) {
  if (reg.registerNumber == NUL_REG || IS_ARG_REG(reg.registerNumber))
    return;
  if (reg.isFloat) {
    if (reg.isCallerSaved) {
      // float caller saved registers
      RegFreeImpl(reg.registerNumber, floatCallerSavedRegisterOffsets,
                  freeFloatCallerSavedRegisters, usedFloatCallerSavedRegisters);
    } else {
      // float callee saved registers
      RegFreeImpl(reg.registerNumber, floatCalleeSavedRegisterOffsets,
                  freeFloatCalleeSavedRegisters, usedFloatCalleeSavedRegisters);
    }
  } else {
    if (reg.isCallerSaved) {
      // int caller saved registers
      RegFreeImpl(reg.registerNumber, intCallerSavedRegisterOffsets,
                  freeIntCallerSavedRegisters, usedIntCallerSavedRegisters);
    } else {
      // int callee saved registers
      RegFreeImpl(reg.registerNumber, intCalleeSavedRegisterOffsets,
                  freeIntCalleeSavedRegisters, usedIntCalleeSavedRegisters);
    }
  }
}

int RegRestoreImpl(int oldRegisterNumber, bool isFloat, bool isCallerSaved,
                   int *registerOffsets,
                   List *freeRegisters, List *usedRegisters,
                   int offset) {
  if (registerOffsets[oldRegisterNumber] == offset)
    return oldRegisterNumber;

  int newRegisterNumber;
  if (IS_ARG_REG(oldRegisterNumber)) {
    newRegisterNumber = oldRegisterNumber;
    registerOffsets[newRegisterNumber] = offset;
  } else {
    newRegisterNumber = RegGetImpl(isFloat, isCallerSaved, registerOffsets,
                                   freeRegisters, usedRegisters,
                                   offset);
  }

  if (isFloat)
    fprintf(outputFile, "flw f%d, %d(fp)\n", newRegisterNumber, offset);
  else if (isCallerSaved)
    fprintf(outputFile, "ld x%d, %d(fp)\n", newRegisterNumber, offset);
  else
    fprintf(outputFile, "lw x%d, %d(fp)\n", newRegisterNumber, offset);
  return newRegisterNumber;
}

Reg RegRestore(Reg oldReg, int offset) {
  Reg newReg = oldReg;
  if (oldReg.isFloat) {
    if (IS_ARG_REG(oldReg.registerNumber)) {
      // float function argument register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, true,
          floatFunctionArgumentRegisterOffsets, NULL, NULL, offset);
    } else if (oldReg.isCallerSaved) {
      // float caller saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, true,
          floatCallerSavedRegisterOffsets, freeFloatCallerSavedRegisters,
          usedFloatCallerSavedRegisters,
          offset);
    } else {
      // float callee saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, false,
          floatCalleeSavedRegisterOffsets, freeFloatCalleeSavedRegisters,
          usedFloatCalleeSavedRegisters, offset);
    }
  } else {
    if (IS_ARG_REG(oldReg.registerNumber)) {
      // int function argument register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, false, true,
          intFunctionArgumentRegisterOffsets, NULL, NULL, offset);
    } else if (oldReg.isCallerSaved) {
      // int caller saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, false, true,
          intCallerSavedRegisterOffsets, freeIntCallerSavedRegisters,
          usedIntCallerSavedRegisters,
          offset);
    } else {
      // int callee saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, false, false,
          intCalleeSavedRegisterOffsets, freeIntCalleeSavedRegisters,
          usedIntCalleeSavedRegisters,
          offset);
    }
  }
  return newReg;
}

Reg RegGetParamImpl(bool isFloat, int *functionArgumentRegisters,
                    int *currentFunctionArgumentRegister,
                    int *registerOffsets, int offset) {
  if (functionArgumentRegisters[*currentFunctionArgumentRegister] == NUL_REG) {
    Reg reg = {
      .registerNumber = NUL_REG
    };
    return reg;
  }
  Reg reg = {
    .isFloat = isFloat,
    .isCallerSaved = true,
    .registerNumber =
      functionArgumentRegisters[(*currentFunctionArgumentRegister)++]
  };
  registerOffsets[reg.registerNumber] = offset;
  return reg;
}

Reg RegGetParam(bool isFloat, int offset) {
  if (isFloat)
    return RegGetParamImpl(true, floatFunctionArgumentRegisters,
                           &currentFloatFunctionArgumentRegister,
                           floatFunctionArgumentRegisterOffsets, offset);
  else
    return RegGetParamImpl(false, intFunctionArgumentRegisters,
                           &currentIntFunctionArgumentRegister,
                           intFunctionArgumentRegisterOffsets, offset);
}

/* ========== register manager ========== */

/* ========== code generation ========== */

void CodegenProgramNode(AST_NODE *programNode) {
  // initialization is done here
  TmpOffsetInit();
  RegInit();
  outputFile = fopen("output.s", "w");
  //outputFile = stderr;

  fprintf(outputFile, ".text\n");
  for (AST_NODE *childNode = programNode->child; childNode;
       childNode = childNode->rightSibling) {
    switch (childNode->nodeType) {
      case VARIABLE_DECL_LIST_NODE:
        for (AST_NODE *variableNode = childNode->child; variableNode;
             variableNode = variableNode->rightSibling)
          CodegenVariableDeclaration(variableNode);
        break;
      case DECLARATION_NODE:
        assert(childNode->semantic_value.declSemanticValue.kind ==
               FUNCTION_DECL);
        CodegenFunctionDeclaration(childNode);
        break;
      default:
        // this should not happen
        assert(0);
    }
  }

  // cleanup is done here
  TmpOffsetEnd();
  RegEnd();
  fclose(outputFile);
}

void CodegenFunctionPrologue(AST_NODE *functionNode) {
  assert(functionNode->nodeType == DECLARATION_NODE &&
         functionNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL &&
         functionNode->child &&
         functionNode->child->rightSibling &&
         functionNode->child->rightSibling->nodeType == IDENTIFIER_NODE);
  char *functionName = functionNode->child->rightSibling->
    semantic_value.identifierSemanticValue.identifierName;
  fprintf(outputFile, ".text\n");
  fprintf(outputFile, "_start_%s:\n", functionName);
  fprintf(outputFile, "sd ra, 0(sp)\n");
  fprintf(outputFile, "sd fp, -8(sp)\n");
  fprintf(outputFile, "addi fp, sp, -8\n");
  fprintf(outputFile, "addi sp, sp, -16\n");

  fprintf(outputFile, "addi sp, sp, -136\n");
  int i;
  for (i = 0; intCalleeSavedRegisters[i] != NUL_REG; ++i)
    fprintf(outputFile, "sd x%d, %d(sp)\n",
        intCalleeSavedRegisters[i], i * 8);
  for (int j = 0; floatCalleeSavedRegisters[j] != NUL_REG; ++j) {
    fprintf(outputFile, "fsw f%d, %d(sp)\n",
        floatCalleeSavedRegisters[j], i * 8 + j * 4);
  }

  fprintf(outputFile, "la ra, _FRAME_SIZE_%s\n", functionName);
  fprintf(outputFile, "lw ra, 0(ra)\n");
  fprintf(outputFile, "sub sp, sp, ra\n");
}

void CodegenFunctionEpilogue(AST_NODE *functionNode) {
  assert(functionNode->nodeType == DECLARATION_NODE &&
         functionNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL &&
         functionNode->child &&
         functionNode->child->rightSibling &&
         functionNode->child->rightSibling->nodeType == IDENTIFIER_NODE);
  char *functionName = functionNode->child->rightSibling->
    semantic_value.identifierSemanticValue.identifierName;

  fprintf(outputFile, "_FUNCTION_END_%s:\n", functionName); // TODO: epilogue ?

  fprintf(outputFile, "li t0, %d\n", arSize);
  fprintf(outputFile, "add sp, sp, t0\n");
  int i;
  for (i = 0; intCalleeSavedRegisters[i] != NUL_REG; ++i)
    fprintf(outputFile, "ld x%d, %d(sp)\n",
        intCalleeSavedRegisters[i], i * 8);
  for (int j = 0; floatCalleeSavedRegisters[j] != NUL_REG; ++j) {
    fprintf(outputFile, "flw f%d, %d(sp)\n",
        floatCalleeSavedRegisters[j], i * 8 + j * 4);
  }
  fprintf(outputFile, "addi sp, sp, 152\n");

  fprintf(outputFile, "ld ra, 8(fp)\n");
  fprintf(outputFile, "addi fp, sp, -8\n");
  fprintf(outputFile, "ld fp, 0(fp)\n");
  fprintf(outputFile, "ret\n");
  fprintf(outputFile, ".data\n");
  // TODO: Is the newline character necessary?
  fprintf(outputFile, "_FRAME_SIZE_%s: .word %d\n", functionName, arSize);
  fprintf(outputFile, ".text\n");
}

void CodegenExprRelated(AST_NODE *exprRelated) {
  switch (exprRelated->nodeType) {
    case IDENTIFIER_NODE:
      CodegenVariableRef(exprRelated, false);
      break;
    case CONST_VALUE_NODE:
      CodegenConstValue(exprRelated);
      break;
    case STMT_NODE:
      switch (exprRelated->semantic_value.stmtSemanticValue.kind) {
        case FUNCTION_CALL_STMT:
          CodegenFunctionCallStmt(exprRelated);
          break;
        case ASSIGN_STMT:
          CodegenAssignStmt(exprRelated);
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    case EXPR_NODE:
      CodegenExpr(exprRelated);
      break;
    default:
      // this should not happen
      assert(0);
  }
}

#define NUL_LABEL -1

void CodegenVariableRef(AST_NODE *varRef, bool isLValue) {
  assert(varRef->nodeType == IDENTIFIER_NODE);

  varRef->isBooleanExpr = false;

  IdentifierSemanticValue *id = &varRef->semantic_value.identifierSemanticValue;
  SymbolTableEntry *entry = id->symbolTableEntry;
  assert(entry->attribute->attributeKind == VARIABLE_ATTRIBUTE);

  switch (id->kind) {
    case NORMAL_ID:
    case WITH_INIT_ID: {
      if (entry->nestingLevel == 0) {
        // variable is a global variable, should be temporarily assigned to
        // a caller saved register
        switch (varRef->dataType) {
          case INT_TYPE:
          case INT_PTR_TYPE:
          case FLOAT_PTR_TYPE: {
            varRef->offset = TmpOffsetGet(false);
            varRef->reg = RegGet(false, true, varRef->offset);
            fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                    varRef->reg.registerNumber, id->identifierName);
            if (!isLValue)
              fprintf(outputFile, "lw x%d, 0(x%d)\n",
                      varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
            if (isLValue) {
              varRef->offset = TmpOffsetGet(false);
              varRef->reg = RegGet(false, true, varRef->offset);
              fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                      varRef->reg.registerNumber, id->identifierName);
            } else {
              Reg addrReg = RegGet(false, true, NUL_OFFSET);
              varRef->offset = TmpOffsetGet(true);
              varRef->reg = RegGet(true, true, varRef->offset);
              fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                      addrReg.registerNumber, id->identifierName);
              fprintf(outputFile, "flw f%d, 0(x%d)\n",
                      varRef->reg.registerNumber, addrReg.registerNumber);
              RegFree(addrReg);
            }
            break;
          } default: {
            // this should not happen
            assert(0);
          }
        }
      } else {
        if (entry->reg.registerNumber == NUL_REG) {
          // variable is a local variable or parameter, and has not been
          // assigned to a register yet, should be assigned to a callee saved
          // register
          if (varRef->dataType == NONE_TYPE) {
            TypeDescriptor *typeDescriptor =
              entry->attribute->attr.typeDescriptor;
            switch (typeDescriptor->kind) {
              case SCALAR_TYPE_DESCRIPTOR:
                varRef->dataType = typeDescriptor->properties.dataType;
                break;
              case ARRAY_TYPE_DESCRIPTOR:
                switch (typeDescriptor->properties.arrayProperties.
                        elementType) {
                  case INT_TYPE:
                    varRef->dataType = INT_PTR_TYPE;
                    break;
                  case FLOAT_TYPE:
                    varRef->dataType = FLOAT_PTR_TYPE;
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
                break;
            }
          }
          switch (varRef->dataType) {
            case INT_TYPE:
            case INT_PTR_TYPE:
            case FLOAT_PTR_TYPE:
              entry->reg = RegGet(false, false, entry->offset);
              if (!isLValue)
                fprintf(outputFile, "lw x%d, %d(fp)\n",
                        entry->reg.registerNumber, entry->offset);
              break;
            case FLOAT_TYPE:
              entry->reg = RegGet(true, false, entry->offset);
              if (!isLValue)
                fprintf(outputFile, "flw f%d, %d(fp)\n",
                        entry->reg.registerNumber, entry->offset);
              break;
            default:
              // this should not happen
              fprintf(stderr, "dataType: %d\n", varRef->dataType);
              assert(0);
          }
        } else {
          // variable is a local variable or parameter, and has been assigned
          // to a register, then we restore the register

          fprintf(outputFile, "## Restoring %d ##\n", entry->reg.registerNumber);
          entry->reg = RegRestore(entry->reg, entry->offset);
          fprintf(outputFile, "## Restored to %d ##\n", entry->reg.registerNumber);
        }
        varRef->reg = entry->reg;
        varRef->offset = entry->offset;
      }
      break;
    } case ARRAY_ID: {
      // variable reference is an array element/slice, should only be
      // temporarily assigned to a caller saved register
      int vpOffset = TmpOffsetGet(false);
      Reg vpReg = RegGet(false, true, vpOffset);

      // calculate variable part
      fprintf(outputFile, "add x%d, x0, x0\n", vpReg.registerNumber);
      ArrayProperties *arrayProperties =
        &entry->attribute->attr.typeDescriptor->properties.arrayProperties;
      AST_NODE *dimNode = varRef->child;
      for (int i = 0; i < arrayProperties->dimension; ++i) {
        if (dimNode) {
          // if there is an index expression for this dimension, then add the
          // expression result to variable part; otherwise, no add is performed
          // (which is equivalent to adding 0)
          CodegenExprRelated(dimNode);
          vpReg = RegRestore(vpReg, vpOffset);
          fprintf(outputFile, "add x%d, x%d, x%d\n",
                  vpReg.registerNumber, vpReg.registerNumber,
                  dimNode->reg.registerNumber);
          if (dimNode->reg.isCallerSaved) {
            TmpOffsetFree(dimNode->reg.isFloat, dimNode->offset);
            RegFree(dimNode->reg);
          }
          dimNode = dimNode->rightSibling;
        }
        if (i < arrayProperties->dimension - 1) {
          Reg sizeReg = RegGet(false, true, NUL_OFFSET);
          RegFree(sizeReg);
          vpReg = RegRestore(vpReg, vpOffset);
          fprintf(outputFile, "li x%d, %d\n",
              sizeReg.registerNumber,
              arrayProperties->sizeInEachDimension[i + 1]);
          fprintf(outputFile, "mul x%d, x%d, x%d\n",
              vpReg.registerNumber, vpReg.registerNumber,
              sizeReg.registerNumber);
        }
      }
      fprintf(outputFile, "slli x%d, x%d, 2\n",
              vpReg.registerNumber, vpReg.registerNumber);

      // add base address to variable part and load
      if (entry->nestingLevel == 0) {
        // global variable
        switch (varRef->dataType) {
          case INT_TYPE:
          case INT_PTR_TYPE:
          case FLOAT_PTR_TYPE: {
            varRef->offset = TmpOffsetGet(false);
            varRef->reg = RegGet(false, true, varRef->offset);
            fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                varRef->reg.registerNumber, id->identifierName);
            fprintf(outputFile, "add x%d, x%d, x%d\n",
                varRef->reg.registerNumber, varRef->reg.registerNumber,
                vpReg.registerNumber);
            if (!isLValue)
              fprintf(outputFile, "lw x%d, 0(x%d)\n",
                  varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
            if (isLValue) {
              varRef->offset = TmpOffsetGet(false);
              varRef->reg = RegGet(false, true, varRef->offset);
              fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                      varRef->reg.registerNumber, id->identifierName);
              fprintf(outputFile, "add x%d, x%d, x%d\n",
                      varRef->reg.registerNumber, varRef->reg.registerNumber,
                      vpReg.registerNumber);
            } else {
              Reg baseReg = RegGet(false, true, NUL_OFFSET);
              varRef->offset = TmpOffsetGet(true);
              varRef->reg = RegGet(true, true, varRef->offset);
              fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                  baseReg.registerNumber, id->identifierName);
              fprintf(outputFile, "add x%d, x%d, x%d\n",
                  baseReg.registerNumber, baseReg.registerNumber,
                  vpReg.registerNumber);
              fprintf(outputFile, "flw f%d, 0(x%d)\n",
                  varRef->reg.registerNumber, baseReg.registerNumber);
              RegFree(baseReg);
            }
            break;
          } default: {
            // this should not happen
            assert(0);
          }
        }
      } else {
        // local variable
        if (entry->reg.registerNumber == NUL_REG) {
          // variable is a local variable or parameter, and has not been
          // assigned to a register yet, should be assigned to a callee saved
          // register
          entry->reg = RegGet(false, false, entry->offset);
          fprintf(outputFile, "li x%d, %d\n",
                  entry->reg.registerNumber, entry->offset);
          fprintf(outputFile, "add x%d, x%d, fp\n",
                  entry->reg.registerNumber, entry->reg.registerNumber);
        } else {
          // variable is a local variable or parameter, and has been assigned
          // to a register, then we restore the register
          entry->reg = RegRestore(entry->reg, entry->offset);
        }
        switch (varRef->dataType) {
          case INT_TYPE:
          case INT_PTR_TYPE:
          case FLOAT_PTR_TYPE: {
            varRef->offset = TmpOffsetGet(false);
            varRef->reg = RegGet(false, true, varRef->offset);
            fprintf(outputFile, "mv x%d, x%d\n",
                varRef->reg.registerNumber, entry->reg.registerNumber);
            fprintf(outputFile, "add x%d, x%d, x%d\n",
                varRef->reg.registerNumber, varRef->reg.registerNumber,
                vpReg.registerNumber);
            if (!isLValue)
              fprintf(outputFile, "lw x%d, 0(x%d)\n",
                  varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
            if (isLValue) {
              varRef->offset = TmpOffsetGet(false);
              varRef->reg = RegGet(false, true, varRef->offset);
              fprintf(outputFile, "add x%d, x%d, x%d\n",
                      varRef->reg.registerNumber, entry->reg.registerNumber,
                      vpReg.registerNumber);
            } else {
              Reg baseReg = RegGet(false, true, NUL_OFFSET);
              varRef->offset = TmpOffsetGet(true);
              varRef->reg = RegGet(true, true, varRef->offset);
              fprintf(outputFile, "mv x%d, x%d\n",
                  baseReg.registerNumber, entry->reg.registerNumber);
              fprintf(outputFile, "add x%d, x%d, x%d\n",
                  baseReg.registerNumber, baseReg.registerNumber,
                  vpReg.registerNumber);
              fprintf(outputFile, "flw f%d, 0(x%d)\n",
                  varRef->reg.registerNumber, baseReg.registerNumber);
              RegFree(baseReg);
            }
            break;
          } default: {
            // this should be happen
            assert(0);
          }
        }
      }
      RegFree(vpReg);
      TmpOffsetFree(false, vpOffset);
      break;
    }
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenConstValue(AST_NODE *constValue) {
  assert(constValue->nodeType == CONST_VALUE_NODE);

  constValue->isBooleanExpr = false;

  CON_Type *val = constValue->semantic_value.const1;
  int constantLabelNo = constantCounter++;
  switch (val->const_type) {
    case INTEGERC: {
      constValue->offset = TmpOffsetGet(false);
      constValue->reg = RegGet(false, true, constValue->offset);
      fprintf(outputFile, ".data\n");
      fprintf(outputFile, "_CONSTANT_%d: .word %d\n",
          constantLabelNo, val->const_u.intval);
      // TODO: verify that .align 2 (4 byte alignment) is correct; for some
      //       reason, the example code writes .align 3
      fprintf(outputFile, ".align 2\n");
      fprintf(outputFile, ".text\n");
      fprintf(outputFile, "la x%d, _CONSTANT_%d\n",
          constValue->reg.registerNumber, constantLabelNo);
      fprintf(outputFile, "lw x%d, 0(x%d)\n",
          constValue->reg.registerNumber, constValue->reg.registerNumber);
      break;
    } case FLOATC: {
      Reg addrReg = RegGet(false, true, NUL_OFFSET);
      constValue->offset = TmpOffsetGet(true);
      constValue->reg = RegGet(true, true, constValue->offset);
      fprintf(outputFile, ".data\n");
      // TODO: verify if using .float here is correct; apparently, there may be
      // some format issues
      fprintf(outputFile, "_CONSTANT_%d: .float %.9g\n",
          constantLabelNo, val->const_u.fval);
      // TODO: verify that .align 2 (4 byte alignment) is correct; for some
      //       reason, the example code writes .align 3
      fprintf(outputFile, ".align 2\n");
      fprintf(outputFile, ".text\n");
      fprintf(outputFile, "la x%d, _CONSTANT_%d\n",
          addrReg.registerNumber, constantLabelNo);
      fprintf(outputFile, "flw f%d, 0(x%d)\n",
          constValue->reg.registerNumber, addrReg.registerNumber);
      RegFree(addrReg);
      break;
    } case STRINGC: {
      constValue->offset = TmpOffsetGet(false);
      constValue->reg = RegGet(false, true, constValue->offset);
      fprintf(outputFile, ".data\n");
      fprintf(outputFile, "_CONSTANT_%d: .string %s\n",
          constantLabelNo, val->const_u.sc);
      // TODO: verify that .align 3 (8 byte alignment) is correct; for some
      //       reason, the example code writes .align 4
      fprintf(outputFile, ".align 4\n");
      fprintf(outputFile, ".text\n");
      fprintf(outputFile, "la x%d, _CONSTANT_%d\n",
          constValue->reg.registerNumber, constantLabelNo);
      break;
    }
  }
}

void CodegenExpr(AST_NODE *exprNode) {
  EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
  switch (expr->kind) {
    case UNARY_OPERATION:
      switch (expr->op.unaryOp) {
        case UNARY_OP_POSITIVE:
        case UNARY_OP_NEGATIVE:
          CodegenUnaryArithmeticExpr(exprNode);
          break;
        case UNARY_OP_LOGICAL_NEGATION:
          CodegenUnaryBooleanExpr(exprNode);
          break;
      }
      break;
    case BINARY_OPERATION:
      switch (expr->op.binaryOp) {
        case BINARY_OP_ADD:
        case BINARY_OP_SUB:
        case BINARY_OP_MUL:
        case BINARY_OP_DIV:
          CodegenBinaryArithmeticExpr(exprNode);
          break;
        case BINARY_OP_EQ:
        case BINARY_OP_NE:
        case BINARY_OP_GE:
        case BINARY_OP_LE:
        case BINARY_OP_GT:
        case BINARY_OP_LT:
        case BINARY_OP_AND:
        case BINARY_OP_OR:
          CodegenBinaryBooleanExpr(exprNode);
          break;
      }
      break;
  }
}

void CodegenUnaryBooleanExpr(AST_NODE *exprNode) {
  EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
  exprNode->isBooleanExpr = true;
  switch (expr->op.unaryOp) {
    case UNARY_OP_LOGICAL_NEGATION:
      assert(exprNode->child);
      if (exprNode->parentLabelNo != NUL_LABEL) {
        // parent is a short circuit expression, then child should short circuit
        // on opposite condition
        exprNode->child->parentLabelNo = exprNode->parentLabelNo;
        exprNode->child->shortOnFalse = !exprNode->shortOnFalse;
      }
      CodegenExprRelated(exprNode->child);
      if (exprNode->child->reg.isCallerSaved) {
        RegFree(exprNode->child->reg);
        TmpOffsetFree(exprNode->child->reg.isFloat,
                      exprNode->child->offset);
      }
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, so actually calculate
        // the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "seqz x%d, x%d\n",
            exprNode->reg.registerNumber, exprNode->child->reg.registerNumber);
      } else if (!exprNode->child->isBooleanExpr) {
        // parent is a short circuit expression and child doesn't short circuit,
        // then current level has to do the short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranchZero(BNEZ, exprNode->child->reg.registerNumber,
                            "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranchZero(BEQZ, exprNode->child->reg.registerNumber,
                            "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenUnaryArithmeticExpr(AST_NODE *exprNode) {
  EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
  exprNode->isBooleanExpr = false;
  switch (expr->op.unaryOp) {
    case UNARY_OP_POSITIVE:
      assert(exprNode->child);
      CodegenExprRelated(exprNode->child);
      exprNode->reg = exprNode->child->reg;
      break;
    case UNARY_OP_NEGATIVE:
      assert(exprNode->child);
      CodegenExprRelated(exprNode->child);
      if (exprNode->child->reg.isCallerSaved) {
        RegFree(exprNode->child->reg);
        TmpOffsetFree(exprNode->child->reg.isFloat,
                      exprNode->child->offset);
      }
      switch (exprNode->dataType) {
        case INT_TYPE:
          exprNode->offset = TmpOffsetGet(false);
          exprNode->reg = RegGet(false, true, exprNode->offset);
          fprintf(outputFile, "negw x%d, x%d\n",
              exprNode->reg.registerNumber,
              exprNode->child->reg.registerNumber);
          break;
        case FLOAT_TYPE:
          exprNode->offset = TmpOffsetGet(true);
          exprNode->reg = RegGet(true, true, exprNode->offset);
          fprintf(outputFile, "fneg.s f%d, f%d\n",
              exprNode->reg.registerNumber,
              exprNode->child->reg.registerNumber);
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenBinaryBooleanExpr(AST_NODE *exprNode) {
  EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
  exprNode->isBooleanExpr = true;
  AST_NODE *leftExprNode = exprNode->child;
  assert(leftExprNode);
  AST_NODE *rightExprNode = leftExprNode->rightSibling;
  assert(rightExprNode);

  int labelNo;
  switch (expr->op.binaryOp) {
    case BINARY_OP_AND:
      labelNo = booleanCounter++;
      if (exprNode->parentLabelNo != NUL_LABEL && exprNode->shortOnFalse)
        // current expression shorts on false, and parent expression shorts on
        // false, then child expression should short circuit to parent label
        leftExprNode->parentLabelNo = rightExprNode->parentLabelNo
                                    = exprNode->parentLabelNo;
      else
        // current expression shorts on false, and parent expression is either
        // not a short circuit expression, or it shorts on true, then child
        // expression should short circuit to current label
        leftExprNode->parentLabelNo = rightExprNode->parentLabelNo
                                    = labelNo;
      leftExprNode->shortOnFalse = rightExprNode->shortOnFalse = true;
      break;
    case BINARY_OP_OR:
      labelNo = booleanCounter++;
      if (exprNode->parentLabelNo == NUL_LABEL || exprNode->shortOnFalse)
        // current expression shorts on true, and parent expression is either
        // not a short circuit expression, or it shorts on false, then child
        // expression should short circuit to current label
        leftExprNode->parentLabelNo = rightExprNode->parentLabelNo
                                    = labelNo;
      else
        // current expression shorts on true, and parent expression shorts on
        // true, then child expression should short circuit to parent label
        leftExprNode->parentLabelNo = rightExprNode->parentLabelNo
                                    = exprNode->parentLabelNo;
      leftExprNode->shortOnFalse = false;
      break;
    default:
      // other expression do not require short circuit
      break;
  }

  CodegenExprRelated(leftExprNode);
  if (leftExprNode->parentLabelNo != NUL_LABEL &&
      !leftExprNode->isBooleanExpr)
    // current expression is a short circuit expression, but the child doesn't
    // short circuit, then we short circuit now
    CodegenShortCircuitArithmeticExpr(leftExprNode);

  CodegenExprRelated(rightExprNode);
  if (rightExprNode->parentLabelNo != NUL_LABEL &&
      !rightExprNode->isBooleanExpr)
    // current expression is a short circuit expression, but the child doesn't
    // short circuit, then we short circuit now
    CodegenShortCircuitArithmeticExpr(rightExprNode);

  if (expr->op.binaryOp != BINARY_OP_AND && expr->op.binaryOp != BINARY_OP_OR) {
    // only restore the left and right operand registers if it is needed, or
    // in other words, if the current expression is not a short circuit
    // expression
    leftExprNode->reg = RegRestore(leftExprNode->reg, leftExprNode->offset);
    rightExprNode->reg = RegRestore(rightExprNode->reg, rightExprNode->offset);
  }

  if (leftExprNode->reg.isCallerSaved) {
    RegFree(leftExprNode->reg);
    TmpOffsetFree(leftExprNode->reg.isFloat, leftExprNode->offset);
  }
  if (rightExprNode->reg.isCallerSaved) {
    RegFree(rightExprNode->reg);
    TmpOffsetFree(rightExprNode->reg.isFloat, rightExprNode->offset);
  }

  if ((leftExprNode->dataType == FLOAT_TYPE ||
       rightExprNode->dataType == FLOAT_TYPE) &&
      (expr->op.binaryOp != BINARY_OP_AND &&
       expr->op.binaryOp != BINARY_OP_OR)) {
    // implicit type conversion
    if (leftExprNode->dataType == INT_TYPE) {
      int intRegisterNumber = leftExprNode->reg.registerNumber;
      leftExprNode->reg = RegGet(true, true, NUL_OFFSET);
      fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
          leftExprNode->reg.registerNumber, intRegisterNumber);
      RegFree(leftExprNode->reg);
    }
    if (rightExprNode->dataType == INT_TYPE) {
      int intRegisterNumber = rightExprNode->reg.registerNumber;
      rightExprNode->reg = RegGet(true, true, NUL_OFFSET);
      fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
          rightExprNode->reg.registerNumber, intRegisterNumber);
      RegFree(rightExprNode->reg);
    }
  }

  exprNode->dataType = INT_TYPE;
  switch (expr->op.binaryOp) {
    case BINARY_OP_EQ:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "feq.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        // TODO: change this to maybe one instruction?
        fprintf(outputFile, "xor x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        fprintf(outputFile, "seqz x%d, x%d\n",
            exprNode->reg.registerNumber, exprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BNE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BEQ, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_NE:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        // TODO: change this to maybe one instruction?
        fprintf(outputFile, "feq.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        fprintf(outputFile, "seqz x%d, x%d\n",
            exprNode->reg.registerNumber,
            exprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        // TODO: change this to maybe one instruction?
        fprintf(outputFile, "xor x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        fprintf(outputFile, "snez x%d, x%d\n",
            exprNode->reg.registerNumber, exprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BEQ, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BNE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_GE:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "fle.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        // TODO: change this to maybe one instruction?
        fprintf(outputFile, "slt x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        fprintf(outputFile, "seqz x%d, x%d\n",
            exprNode->reg.registerNumber, exprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BLT, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BGE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_LE:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "fle.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->reg.registerNumber);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        // TODO: change this to maybe one instruction?
        fprintf(outputFile, "slt x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber);
        fprintf(outputFile, "seqz x%d, x%d\n",
            exprNode->reg.registerNumber, exprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BGT, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BLE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_GT:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "flt.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "slt x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BLE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BGT, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_LT:
      if (leftExprNode->reg.isFloat) {
        // left and right operands are float
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "flt.s x%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
        if (exprNode->parentLabelNo != NUL_LABEL) {
          // parent is short circuit expression, then generate short circuit
          // based on calculated value
          if (exprNode->shortOnFalse) {
            CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          } else {
            CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                              "_BOOL_SHORT_", exprNode->parentLabelNo);
          }
        }
      } else if (exprNode->parentLabelNo == NUL_LABEL) {
        // left and right operands are int, and parent is not a short circuit
        // expression, then actually calculate the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "slt x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber,
            rightExprNode->reg.registerNumber);
      } else {
        // left and right operands are int, and parent is a short circuit
        // expression, then directly compare and perform short circuit
        exprNode->reg.registerNumber = NUL_REG;
        if (exprNode->shortOnFalse) {
          CodegenBranch(BGE, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        } else {
          CodegenBranch(BLT, leftExprNode->reg.registerNumber,
                        rightExprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
        }
      }
      break;
    case BINARY_OP_AND:
      // fall through code, which corresponds to true
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "addi x%d, x0, 1\n", exprNode->reg.registerNumber);
        CodegenJumpLabelNo("_BOOL_EXIT_", labelNo);
      } else if (exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on false, then
        // exit the current boolean expression
        CodegenJumpLabelNo("_BOOL_EXIT_", labelNo);
      } else {
        // parent is a short circuit expression and it shorts on true, then
        // directly jump
        CodegenJumpLabelNo("_BOOL_SHORT_", exprNode->parentLabelNo);
      }
      // short circuit code, which corresponds to false
      fprintf(outputFile, "_BOOL_SHORT_%d:\n", labelNo);
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        fprintf(outputFile, "mv x%d, x0\n", exprNode->reg.registerNumber);
      } else if (exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on false, then
        // directly jump
        CodegenJumpLabelNo("_BOOL_SHORT_", exprNode->parentLabelNo);
      }
      fprintf(outputFile, "_BOOL_EXIT_%d:\n", labelNo);
      break;
    case BINARY_OP_OR:
      // fall through code, which corresponds to false
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "mv x%d, x0\n", exprNode->reg.registerNumber);
        CodegenJumpLabelNo("_BOOL_EXIT_", labelNo);
      } else if (exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on false, then
        // directly jump
        //fprintf(outputFile, "j _BOOL_SHORT_%d\n", exprNode->parentLabelNo);
        CodegenJumpLabelNo("_BOOL_SHORT_", exprNode->parentLabelNo);
      } else {
        // parent is a short circuit expression and it shorts on true, then
        // exit the current boolean expression
        CodegenJumpLabelNo("_BOOL_EXIT_", labelNo);
      }
      // short circuit code, which corresponds to true
      fprintf(outputFile, "_BOOL_SHORT_%d:\n", labelNo);
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        fprintf(outputFile, "addi x%d, x0, 1\n", exprNode->reg.registerNumber);
      } else if (!exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on true, then
        // directly jump
        CodegenJumpLabelNo("_BOOL_SHORT_", exprNode->parentLabelNo);
      }
      fprintf(outputFile, "_BOOL_EXIT_%d:\n", labelNo);
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenBinaryArithmeticExpr(AST_NODE *exprNode) {
  EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
  exprNode->isBooleanExpr = false;
  AST_NODE *leftExprNode = exprNode->child;
  assert(leftExprNode);
  AST_NODE *rightExprNode = leftExprNode->rightSibling;
  assert(rightExprNode);

  CodegenExprRelated(leftExprNode);
  CodegenExprRelated(rightExprNode);

  leftExprNode->reg = RegRestore(leftExprNode->reg, leftExprNode->offset);
  rightExprNode->reg = RegRestore(rightExprNode->reg, rightExprNode->offset);

  if (leftExprNode->reg.isCallerSaved) {
    RegFree(leftExprNode->reg);
    TmpOffsetFree(leftExprNode->reg.isFloat, leftExprNode->offset);
  }
  if (rightExprNode->reg.isCallerSaved) {
    RegFree(rightExprNode->reg);
    TmpOffsetFree(rightExprNode->reg.isFloat, rightExprNode->offset);
  }

  if (leftExprNode->dataType == FLOAT_TYPE ||
      rightExprNode->dataType == FLOAT_TYPE) {
    // implicit type conversion
    if (leftExprNode->dataType == INT_TYPE) {
      int intRegisterNumber = leftExprNode->reg.registerNumber;
      leftExprNode->reg = RegGet(true, true, NUL_OFFSET);
      fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
          leftExprNode->reg.registerNumber, intRegisterNumber);
      RegFree(leftExprNode->reg);
    }
    if (rightExprNode->dataType == INT_TYPE) {
      int intRegisterNumber = rightExprNode->reg.registerNumber;
      rightExprNode->reg = RegGet(true, true, NUL_OFFSET);
      fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
          rightExprNode->reg.registerNumber, intRegisterNumber);
      RegFree(rightExprNode->reg);
    }
  }

  exprNode->offset = TmpOffsetGet(leftExprNode->reg.isFloat);
  exprNode->reg = RegGet(leftExprNode->reg.isFloat, true, exprNode->offset);

  switch (expr->op.binaryOp) {
    case BINARY_OP_ADD:
      if (!leftExprNode->reg.isFloat)
        fprintf(outputFile, "addw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fadd.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_SUB:
      if (!leftExprNode->reg.isFloat)
        fprintf(outputFile, "subw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fsub.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_MUL:
      if (!leftExprNode->reg.isFloat)
        fprintf(outputFile, "mulw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fmul.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_DIV:
      if (!leftExprNode->reg.isFloat)
        fprintf(outputFile, "divw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fdiv.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenShortCircuitArithmeticExpr(AST_NODE *exprNode) {
  if (exprNode->reg.isFloat) {
    Reg condReg = RegGet(false, true, NUL_OFFSET);
    // TODO: change this to one instruction?
    fprintf(outputFile, "fclass.s x%d, f%d\n",
        condReg.registerNumber, exprNode->reg.registerNumber);
    // the fclass.s instruction sets bit 3/4 if the float value is -0/+0, thus
    // we use a bit mask 24 (11000 in binary) to check if either bit is set
    fprintf(outputFile, "andi x%d, x%d, 24\n",
        condReg.registerNumber, condReg.registerNumber);
    if (exprNode->shortOnFalse) {
      CodegenBranchZero(BNEZ, condReg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
    } else {
      CodegenBranchZero(BEQZ, condReg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
    }
    RegFree(condReg);
  } else {
    if (exprNode->shortOnFalse) {
      CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
    } else {
      CodegenBranchZero(BNEZ, exprNode->reg.registerNumber,
                        "_BOOL_SHORT_", exprNode->parentLabelNo);
    }
  }
}

/* ========== code generation ========== */

/* TODO: these are just placeholder functions, feel free to remove them */

void CodegenDeclarationNode(AST_NODE *declarationNode) {
  assert(declarationNode->nodeType == DECLARATION_NODE);
  DECL_KIND declKind = declarationNode->semantic_value.declSemanticValue.kind;
  switch (declKind) {
    case FUNCTION_DECL:
      CodegenFunctionDeclaration(declarationNode);
      break;
    case FUNCTION_PARAMETER_DECL: // should not appear here, codegen will generate full parameter list once
      assert(0);
    case TYPE_DECL: // have been handled in semantic check stage
      break;
    case VARIABLE_DECL:
      CodegenVariableDeclaration(declarationNode);
      break;
    default:
      assert(0);
  }
}

#define FP_DEFAULT_PARAM_OFFSET 16

void CodegenFunctionParameterList(AST_NODE *paramListNode) {
  assert(paramListNode->nodeType == PARAM_LIST_NODE);
  fprintf(outputFile, "## Codegen: Parameter List Declaration ##\n");
  int fp_offset = FP_DEFAULT_PARAM_OFFSET;
  for (AST_NODE *paramNode = paramListNode->child;
       paramNode;
       paramNode = paramNode->rightSibling) {
    AST_NODE *variableNode = paramNode->child->rightSibling;
    // TODO: need a lot modification
    // TODO: a[][2][3], first []
    SymbolTableEntry *variableEntry = variableNode->semantic_value.identifierSemanticValue.symbolTableEntry;
    TypeDescriptor *variableTD = variableEntry->attribute->attr.typeDescriptor;
    const int ptrSize = 8, intSize = 8, floatSize = 4;
    bool isIntType = false;
    int memSize = 0;
    switch (variableTD->kind) {
      case SCALAR_TYPE_DESCRIPTOR:
        switch (variableTD->properties.dataType) {
          case INT_TYPE:
            isIntType = true;
            memSize = intSize;
            break;
          case FLOAT_TYPE:
            isIntType = false;
            memSize = floatSize;
            break;
          default:
            // this should not happen
            assert(0);
        }
        break;
      case ARRAY_TYPE_DESCRIPTOR: {
        memSize = ptrSize;
        ArrayProperties variableAP = variableTD->properties.arrayProperties;
        switch (variableAP.elementType) {
          case INT_TYPE:
          case FLOAT_TYPE:
            isIntType = true;
            break;
          default:
            // this should not happen
            assert(0);
        }
        break;
      }
      default:
        // this should not happen
        assert(0);
    }
    // TODO: should i set both offset and param register ?
    variableEntry->reg = RegGetParam(!isIntType, fp_offset);
    variableEntry->offset = fp_offset;
    fp_offset += memSize;
  }
}

void CodegenVariableDeclaration(AST_NODE *variableNode) {
  DECL_KIND declKind = variableNode->semantic_value.declSemanticValue.kind;
  assert(declKind == VARIABLE_DECL
         || declKind == TYPE_DECL );
  if (declKind == TYPE_DECL) {  // Type Declaration from CodegenProgramNode()
    fprintf(outputFile, "## Codegen: Type Declaration ##\n");
    return;
  }
  // otherwise, do Variable Declaration
  AST_NODE *typeNode = variableNode->child;
  AST_NODE *firstVariable = variableNode->child->rightSibling;
  SymbolTableEntry *typeEntry = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry;
  SymbolTableEntry *entry = firstVariable->semantic_value.identifierSemanticValue.symbolTableEntry;
  if (entry->nestingLevel == 0) { // Global Variable
    fprintf(outputFile, "## Codegen: Global Variable Declaration ##\n");
    fprintf(outputFile, ".data\n");
    for (AST_NODE *singleVariable = firstVariable;
         singleVariable;
         singleVariable = singleVariable->rightSibling) {
      IDENTIFIER_KIND idKind = singleVariable->semantic_value.identifierSemanticValue.kind;
      SymbolTableEntry *singleVariableEntry = singleVariable->semantic_value.identifierSemanticValue.symbolTableEntry;
      TypeDescriptor *singleVariableTD = singleVariableEntry->attribute->attr.typeDescriptor;
      char *singleVariableName = singleVariable->semantic_value.identifierSemanticValue.identifierName;
      const int intSize = 4, floatSize = 4;
      int intValue = 0;
      float floatValue = 0;
      bool initValueIsIntType = true;
      int memSize = 0;
      switch (singleVariableTD->kind) {
        case SCALAR_TYPE_DESCRIPTOR: {
          memSize = 1;
          switch (idKind) {
            case NORMAL_ID: // no init value
              initValueIsIntType = true;  // by default
              intValue = 0;
              break;
            case WITH_INIT_ID: { // TODO: whether const init value?
              AST_NODE *initValueNode = singleVariable->child;
              switch (initValueNode->nodeType) {
                case EXPR_NODE: {
                  EXPRSemanticValue initExprSemanticValue = initValueNode->semantic_value.exprSemanticValue;
                  if (!initExprSemanticValue.isConstEval) {
                    fprintf(stderr, "codegen error: initializer element is a non-constant expression during Global Variable Declaration\n");
                    assert(0);
                  }
                  switch (initValueNode->dataType) {
                    case INT_TYPE:
                      initValueIsIntType = true;
                      intValue = initExprSemanticValue.constEvalValue.iValue;
                      break;
                    case FLOAT_TYPE:
                      initValueIsIntType = false;
                      floatValue = initExprSemanticValue.constEvalValue.fValue;
                      break;
                    default:
                      // this should not happen
                      fprintf(stderr, "codegen error: initializier element has invalid dataType during Global Variable Declaration\n");
                      assert(0);
                  }
                  break;
                }
                case CONST_VALUE_NODE: {
                  CON_Type *initValueConType = initValueNode->semantic_value.const1;
                  switch (initValueConType->const_type) {
                    case INTEGERC:
                      initValueIsIntType = true;
                      intValue = initValueConType->const_u.intval;
                      break;
                    case FLOATC:
                      initValueIsIntType = false;
                      floatValue = initValueConType->const_u.fval;
                      break;
                    case STRINGC:
                      fprintf(stderr, "codegen error: initializier element has invalid dataType during Global Variable Declaration\n");
                    default:
                      // this should not happen
                      fprintf(stderr, "codegen error initializier element has invalid dataType during Global Variable Declaration\n");
                      assert(0);
                  }
                  break;
                }
                case STMT_NODE:       // function call is not permitted here
                  fprintf(stderr, "codegen error: initializer element is a function call during Global Variable Declaration\n");
                case IDENTIFIER_NODE: // var_ref initialization is not permitted here
                  fprintf(stderr, "codegen error: initializer element is a variable reference during Global Variable Declaration\n");
                default:
                  // this should not happen
                  assert(0);
              }

              break;
            }
            case ARRAY_ID:
              fprintf(stderr, "codegen error: unexpected ARRAY_ID during Global Variable Declaration\n");
            default:
              // this should not happen
              assert(0);
          }
          switch (singleVariableTD->properties.dataType) {
            // TODO: implicit type conversion
            case INT_TYPE: {
              if (!initValueIsIntType) {
                intValue = (int)floatValue;
              }
              fprintf(outputFile, "_GLOBAL_%s: .word %d\n", singleVariableName, intValue);
              break;
            }
            case FLOAT_TYPE: {
              if (initValueIsIntType) {
                floatValue = (float)intValue;
              }
              fprintf(outputFile, "_GLOBAL_%s: .float %f\n", singleVariableName, floatValue);
              break;
            }
            default:
              // this should not happen
              assert(0);
          }
          break;
        }
        case ARRAY_TYPE_DESCRIPTOR: {
          memSize = 1;
          ArrayProperties singleVariableAP = singleVariableTD->properties.arrayProperties;
          for (int dim = 0; dim < singleVariableAP.dimension; dim++) {
            memSize *= singleVariableAP.sizeInEachDimension[dim];
          }
          switch (singleVariableAP.elementType) {
            case INT_TYPE:
              fprintf(outputFile, "_GLOBAL_%s: .space %d\n", singleVariableName, memSize * intSize);
              break;
            case FLOAT_TYPE:
              fprintf(outputFile, "_GLOBAL_%s: .space %d\n", singleVariableName, memSize * floatSize);
              break;
            default:
              // this should not happen
              assert(0);
          }
          break;
        }
        default:
          // this should not happen
          assert(0);
      }
    }
  }
  else {                          // Local Variable
    fprintf(outputFile, "## Codegen: Local Variable Declaration ##\n");
    for (AST_NODE *singleVariable = firstVariable;
         singleVariable;
         singleVariable = singleVariable->rightSibling) {
      IDENTIFIER_KIND idKind = singleVariable->semantic_value.identifierSemanticValue.kind;
      SymbolTableEntry *singleVariableEntry = singleVariable->semantic_value.identifierSemanticValue.symbolTableEntry;
      // modify new arSize
      TypeDescriptor *singleVariableTD = singleVariableEntry->attribute->attr.typeDescriptor;
      int intSize = 4, floatSize = 4;
      int memSize = 0;
      bool isIntType = false;
      switch (singleVariableTD->kind) {
        case SCALAR_TYPE_DESCRIPTOR:
          memSize = 1;
          switch (singleVariableTD->properties.dataType) {
            case INT_TYPE:
              isIntType = true;
              break;
            case FLOAT_TYPE:
              isIntType = false;
              break;
            default:
              // this should not happen
              assert(0);
          }
          break;
        case ARRAY_TYPE_DESCRIPTOR: {
          memSize = 1;
          ArrayProperties singleVariableAP = singleVariableTD->properties.arrayProperties;
          for (int dim = 0; dim < singleVariableAP.dimension; dim++) {
            memSize *= singleVariableAP.sizeInEachDimension[dim];
          }
          switch (singleVariableAP.elementType) {
            case INT_TYPE:
              isIntType = true;
              break;
            case FLOAT_TYPE:
              isIntType = false;
              break;
            default:
              // this should not happen
              assert(0);
          }
          break;
        }
        default:
          // this should not happen
          assert(0);
      }
      // set symbolTableEntry.offset
      arSize += memSize * (isIntType ? intSize : floatSize);
      singleVariableEntry->offset = -arSize;
      //fprintf(outputFile, "### allocate %d bytes, arSize: %d ###\n", memSize * intSize, arSize);
      
      // TODO: Variable Initialization
      if (idKind == WITH_INIT_ID) {
        CodegenLocalVariableInitAssignStmt(singleVariable);
      }
    }
  }
}

void CodegenLocalVariableInitAssignStmt(AST_NODE *variableNode) {
  // very similar to CodegenAssignStmt()
  fprintf(outputFile, "## Codegen: Variable Declaration - Local Variable Initialization ##\n");
  assert(variableNode->nodeType == IDENTIFIER_NODE);

  AST_NODE *exprNode = variableNode->child;
  CodegenExprRelated(exprNode);           // should be relop_expr
  CodegenVariableRef(variableNode, true); // should be var_ref (or simply ID, TODO: why?)
  exprNode->reg = RegRestore(exprNode->reg, exprNode->offset);
  SymbolTableEntry *entry = variableNode->semantic_value.identifierSemanticValue.symbolTableEntry;
  TypeDescriptor *entryTD = entry->attribute->attr.typeDescriptor;
  bool isFloatType = false;
  switch (entryTD->kind) {
    case SCALAR_TYPE_DESCRIPTOR: {
      switch (entryTD->properties.dataType) {
        case INT_TYPE:
          isFloatType = false;
          break;
        case FLOAT_TYPE:
          isFloatType = true;
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    case ARRAY_TYPE_DESCRIPTOR: {
      // TODO: what if first element is NUL?
      ArrayProperties arrayProp = entryTD->properties.arrayProperties;
      switch (arrayProp.elementType) {
        case INT_TYPE:
          isFloatType = false;
          break;
        case FLOAT_TYPE:
          isFloatType = true;
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    default:
      // this should not happen
      assert(0);
  }
  Reg exprReg;
  // TODO: implicit type conversion: float -> int ? check another mirror function also
  if (isFloatType && !exprNode->reg.isFloat) {      // int expr -> float var
    exprReg = RegGet(true, true, NUL_OFFSET);
    RegFree(exprReg);
    fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
            exprReg.registerNumber, exprNode->reg.registerNumber);
  } 
  else if (!isFloatType && exprNode->reg.isFloat) { // float expr -> int var
    exprReg = RegGet(false, true, NUL_OFFSET);
    RegFree(exprReg);
    fprintf(outputFile, "fcvt.w.s x%d, f%d, rtz\n",
            exprReg.registerNumber, exprNode->reg.registerNumber);
  }
  else {
    exprReg = exprNode->reg;
  }
  if (variableNode->reg.isCallerSaved) {
    if (!isFloatType) {
      fprintf(outputFile, "sw x%d, 0(x%d)\n", exprReg.registerNumber,
                                              variableNode->reg.registerNumber);
    }
    else {
      fprintf(outputFile, "fsw f%d, 0(x%d)\n", exprReg.registerNumber,
                                               variableNode->reg.registerNumber);
    }
  } else {
    if (!isFloatType) {
      fprintf(outputFile, "mv x%d, x%d\n", variableNode->reg.registerNumber,
                                           exprReg.registerNumber);
    }
    else {
      fprintf(outputFile, "fmv.s f%d, f%d\n", variableNode->reg.registerNumber,
                                              exprReg.registerNumber);
    }
  }
  // allocate a temporary (caller saved) register to assignStmt->reg
  // TODO: We don't need it here, right?
  /*
  if (assignStmt->parent->nodeType == STMT_NODE &&
      (assignStmt->parent->semantic_value.stmtSemanticValue.kind == IF_STMT ||
       assignStmt->parent->semantic_value.stmtSemanticValue.kind == WHILE_STMT ||
       assignStmt->parent->semantic_value.stmtSemanticValue.kind == FOR_STMT)) {
    assignStmt->offset = TmpOffsetGet(isFloatType);
    assignStmt->reg = RegGet(isFloatType, true, assignStmt->offset);
    if (!isFloatType) {
      fprintf(outputFile, "mv x%d, x%d\n", assignStmt->reg.registerNumber,
                                           variableNode->reg.registerNumber);
    }
    else {
      fprintf(outputFile, "fmv.s f%d, f%d\n", assignStmt->reg.registerNumber,
                                              variableNode->reg.registerNumber);
    }
  }
  */
  if (exprNode->reg.isCallerSaved) {
    TmpOffsetFree(exprNode->reg.isFloat,
                  exprNode->offset);
    RegFree(exprNode->reg);
  }
  if (variableNode->reg.isCallerSaved) {
    TmpOffsetFree(variableNode->reg.isFloat,
                  variableNode->offset);
    RegFree(variableNode->reg);
  }
}

void CodegenFunctionDeclaration(AST_NODE *functionNode) {
  assert(functionNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL);
  fprintf(outputFile, "## Codegen: Function Declaration ##\n");
  TmpOffsetReset();
  RegReset(); // arSize = 0

  // TODO: only need to set argument offset with respect to fp
  AST_NODE *paramListNode = functionNode->child->rightSibling->rightSibling;
  CodegenFunctionParameterList(paramListNode);

  CodegenFunctionPrologue(functionNode);

  fprintf(outputFile, "## Codegen: Function Body Declaration ##\n");

  AST_NODE *blockNode = paramListNode->rightSibling;
  CodegenBlockNode(blockNode);

  CodegenFunctionEpilogue(functionNode);
}

void CodegenBlockNode(AST_NODE *blockNode) {
  assert(blockNode->nodeType == BLOCK_NODE);
  fprintf(outputFile, "## Codegen: Block ##\n");
  for (AST_NODE *blockContent = blockNode->child;
       blockContent;
       blockContent = blockContent->rightSibling) {
    switch (blockContent->nodeType) {
      case VARIABLE_DECL_LIST_NODE: {
        for (AST_NODE *variableNode = blockContent->child;
             variableNode;
             variableNode = variableNode->rightSibling) {
          CodegenDeclarationNode(variableNode); // VARIABLE_DECL
        }
        break;
      }
      case STMT_LIST_NODE: {
        for (AST_NODE *stmtNode = blockContent->child;
            stmtNode;
            stmtNode = stmtNode->rightSibling) {
          CodegenStmtNode(stmtNode);
        }
        break;
      }
      default:
        // this should not happen
        assert(0);
    }
  }
}

void CodegenStmtNode(AST_NODE *stmtNode) {
  assert(   stmtNode->nodeType == STMT_NODE
         || stmtNode->nodeType == BLOCK_NODE
         || stmtNode->nodeType == NUL_NODE  );
  switch (stmtNode->nodeType) {
    case STMT_NODE: {
      STMT_KIND stmtKind = stmtNode->semantic_value.stmtSemanticValue.kind;
      switch (stmtKind) {
        case WHILE_STMT:
          CodegenWhileStmt(stmtNode);
          break;
        case FOR_STMT:
          CodegenForStmt(stmtNode);
          break;
        case ASSIGN_STMT:
          CodegenAssignStmt(stmtNode);
          break;
        case IF_STMT:
          CodegenIfStmt(stmtNode);
          break;
        case FUNCTION_CALL_STMT:
          CodegenFunctionCallStmt(stmtNode);
          break;
        case RETURN_STMT:
          CodegenReturnStmt(stmtNode);
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    case BLOCK_NODE:
      CodegenBlockNode(stmtNode);
      break;
    case NUL_NODE:
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void CodegenWhileStmt(AST_NODE *whileStmt) {
  assert(whileStmt->semantic_value.stmtSemanticValue.kind == WHILE_STMT);
  int labelNo = whileCounter++;
  fprintf(outputFile, "## Codegen: While Stmt ##\n");
  fprintf(outputFile, "_WHILE_LABEL_%d:\n", labelNo);
  AST_NODE *testNode = whileStmt->child;
  CodegenExprRelated(testNode); // TODO: what if testNode is assign_expr ? what if FLOAY_TYPE ?
  if (!testNode->reg.isFloat) { // INT_TYPE
    CodegenBranchZero(BEQZ, testNode->reg.registerNumber, "_WHILE_EXIT_", labelNo);
  }
  else {                        // FLOAT_TYPE
    int offset = TmpOffsetGet(false);
    Reg tmpReg = RegGet(false, true, offset); // note that we get a INT_TYPE temporary register
    fprintf(outputFile, "fclass.s x%d, f%d\n",
        tmpReg.registerNumber, testNode->reg.registerNumber);
    // the fclass.s instruction sets bit 3/4 if the float value is -0/+0, thus
    // we use a bit mask 24 (11000 in binary) to check if either bit is set
    fprintf(outputFile, "andi x%d, x%d, 24\n",
        tmpReg.registerNumber, tmpReg.registerNumber);
    CodegenBranchZero(BNEZ, tmpReg.registerNumber, "_WHILE_EXIT_", labelNo);
    RegFree(tmpReg);
    TmpOffsetFree(false, offset);
  }
  if (testNode->reg.isCallerSaved) {
    RegFree(testNode->reg);
    TmpOffsetFree(testNode->reg.isFloat, testNode->offset);
  }
  AST_NODE *stmtNode = testNode->rightSibling;
  CodegenStmtNode(stmtNode);
  CodegenJumpLabelNo("_WHILE_LABEL_", labelNo);
  fprintf(outputFile, "_WHILE_EXIT_%d:\n", labelNo);
}

void CodegenForStmt(AST_NODE *forStmt) {
  assert(forStmt->semantic_value.stmtSemanticValue.kind == FOR_STMT);
  int labelNo = forCounter++;
  fprintf(outputFile, "## Codegen: For Stmt ##\n");
  fprintf(outputFile, "_FOR_LABEL_%d:\n", labelNo);
  AST_NODE *forInitNode = forStmt->child;
  if (forInitNode->nodeType != NUL_NODE) {
    for (AST_NODE *exprNode = forInitNode->child;
         exprNode;
         exprNode = exprNode->rightSibling) {
      CodegenExprRelated(exprNode);
      if (exprNode->reg.isCallerSaved) {
        RegFree(exprNode->reg);
        TmpOffsetFree(exprNode->reg.isFloat, exprNode->offset);
      }
    }
  }

  fprintf(outputFile, "_FOR_BODY_%d:\n", labelNo);
  AST_NODE *forCondNode = forInitNode->rightSibling;
  if (forCondNode->nodeType != NUL_NODE) {
    // TODO: what if multiple condition statement ?
    for (AST_NODE *exprNode = forCondNode->child;
         exprNode;
         exprNode = exprNode->rightSibling) {
      CodegenExprRelated(exprNode);
      if (!exprNode->rightSibling) {  // real condition statement
        if (!exprNode->reg.isFloat) { // INT_TYPE
          CodegenBranchZero(BEQZ, exprNode->reg.registerNumber,
                            "_FOR_EXIT_", labelNo);
        }
        else {                        // FLOAT_TYPE
          int offset = TmpOffsetGet(false);
          Reg tmpReg = RegGet(false, true, offset);
          fprintf(outputFile, "fclass.s x%d, f%d\n",
              tmpReg.registerNumber, exprNode->reg.registerNumber);
          // the fclass.s instruction sets bit 3/4 if the float value is -0/+0, thus
          // we use a bit mask 24 (11000 in binary) to check if either bit is set
          fprintf(outputFile, "andi x%d, x%d, 24\n",
              tmpReg.registerNumber, tmpReg.registerNumber);
          CodegenBranchZero(BNEZ, tmpReg.registerNumber, "_FOR_EXIT_", labelNo);
          RegFree(tmpReg);
          TmpOffsetFree(false, offset);
        }
      }
      if (exprNode->reg.isCallerSaved) {
        RegFree(exprNode->reg);
        TmpOffsetFree(exprNode->reg.isFloat, exprNode->offset);
      }
    }
  }

  AST_NODE *forIncNode = forCondNode->rightSibling;
  AST_NODE *stmtNode = forIncNode->rightSibling;
  CodegenStmtNode(stmtNode);

  fprintf(outputFile, "## For increment ##\n");
  if (forIncNode->nodeType != NUL_NODE) {
    for (AST_NODE *exprNode = forIncNode->child;
         exprNode;
         exprNode = exprNode->rightSibling) {
      CodegenExprRelated(exprNode);
      if (exprNode->reg.isCallerSaved) {
        RegFree(exprNode->reg);
        TmpOffsetFree(exprNode->reg.isFloat, exprNode->offset);
      }
    }
  }
  CodegenJumpLabelNo("_FOR_BODY_", labelNo);
  fprintf(outputFile, "_FOR_EXIT_%d:\n", labelNo);
}

void CodegenAssignStmt(AST_NODE *assignStmt) {
  assert(assignStmt->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT);
  fprintf(outputFile, "## Codegen: Assign Stmt ##\n");
  AST_NODE *variableNode = assignStmt->child;
  AST_NODE *exprNode = variableNode->rightSibling;
  CodegenExprRelated(exprNode);           // should be relop_expr
  CodegenVariableRef(variableNode, true); // should be var_ref (or simply ID, TODO: why?)
  exprNode->reg = RegRestore(exprNode->reg, exprNode->offset);
  SymbolTableEntry *entry = variableNode->semantic_value.identifierSemanticValue.symbolTableEntry;
  TypeDescriptor *entryTD = entry->attribute->attr.typeDescriptor;
  bool isFloatType = false;
  switch (entryTD->kind) {
    case SCALAR_TYPE_DESCRIPTOR: {
      switch (entryTD->properties.dataType) {
        case INT_TYPE:
          isFloatType = false;
          break;
        case FLOAT_TYPE:
          isFloatType = true;
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    case ARRAY_TYPE_DESCRIPTOR: {
      // TODO: what if first element is NUL?
      ArrayProperties arrayProp = entryTD->properties.arrayProperties;
      switch (arrayProp.elementType) {
        case INT_TYPE:
          isFloatType = false;
          break;
        case FLOAT_TYPE:
          isFloatType = true;
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    default:
      // this should not happen
      assert(0);
  }
  Reg exprReg;
  // TODO: implicit type conversion: float -> int ? check another mirror function also
  if (isFloatType && !exprNode->reg.isFloat) {      // int expr -> float var
    exprReg = RegGet(true, true, NUL_OFFSET);
    RegFree(exprReg);
    fprintf(outputFile, "fcvt.s.w f%d, x%d\n",
            exprReg.registerNumber, exprNode->reg.registerNumber);
  } 
  else if (!isFloatType && exprNode->reg.isFloat) { // float expr -> int var
    exprReg = RegGet(false, true, NUL_OFFSET);
    RegFree(exprReg);
    fprintf(outputFile, "fcvt.w.s x%d, f%d, rtz\n",
            exprReg.registerNumber, exprNode->reg.registerNumber);
  }
  else {
    exprReg = exprNode->reg;
  }
  if (variableNode->reg.isCallerSaved) {
    if (!isFloatType) {
      fprintf(outputFile, "sw x%d, 0(x%d)\n", exprReg.registerNumber,
                                              variableNode->reg.registerNumber);
    }
    else {
      fprintf(outputFile, "fsw f%d, 0(x%d)\n", exprReg.registerNumber,
                                               variableNode->reg.registerNumber);
    }
  } else {
    if (!isFloatType) {
      fprintf(outputFile, "mv x%d, x%d\n", variableNode->reg.registerNumber,
                                           exprReg.registerNumber);
    }
    else {
      fprintf(outputFile, "fmv.s f%d, f%d\n", variableNode->reg.registerNumber,
                                              exprReg.registerNumber);
    }
  }
  // allocate a temporary (caller saved) register to assignStmt->reg
  if (assignStmt->parent->nodeType == STMT_NODE &&
      (assignStmt->parent->semantic_value.stmtSemanticValue.kind == IF_STMT ||
       assignStmt->parent->semantic_value.stmtSemanticValue.kind == WHILE_STMT ||
       assignStmt->parent->semantic_value.stmtSemanticValue.kind == FOR_STMT)) {
    assignStmt->offset = TmpOffsetGet(isFloatType);
    assignStmt->reg = RegGet(isFloatType, true, assignStmt->offset);
    if (!isFloatType) {
      fprintf(outputFile, "mv x%d, x%d\n", assignStmt->reg.registerNumber,
                                           variableNode->reg.registerNumber);
    }
    else {
      fprintf(outputFile, "fmv.s f%d, f%d\n", assignStmt->reg.registerNumber,
                                              variableNode->reg.registerNumber);
    }
  }
  if (exprNode->reg.isCallerSaved) {
    TmpOffsetFree(exprNode->reg.isFloat,
                  exprNode->offset);
    RegFree(exprNode->reg);
  }
  if (variableNode->reg.isCallerSaved) {
    TmpOffsetFree(variableNode->reg.isFloat,
                  variableNode->offset);
    RegFree(variableNode->reg);
  }
}

void CodegenIfStmt(AST_NODE *ifStmt) {
  assert(ifStmt->semantic_value.stmtSemanticValue.kind == IF_STMT);
  int labelNo = ifCounter++;
  fprintf(outputFile, "## Codegen: If Stmt ##\n");
  AST_NODE *testNode = ifStmt->child;
  CodegenExprRelated(testNode);
  AST_NODE *ifStmtNode = testNode->rightSibling;
  AST_NODE *elseStmtNode = ifStmtNode->rightSibling;
  if (!testNode->reg.isFloat) { // INT_TYPE
    if (elseStmtNode->nodeType != NUL_NODE) {
      CodegenBranchZero(BEQZ, testNode->reg.registerNumber,
                        "_ELSE_LABEL_", labelNo);
    } else {
      CodegenBranchZero(BEQZ, testNode->reg.registerNumber,
                        "_IF_EXIT_", labelNo);
    }
  }
  else {                        // FLOAT_TYPE
    int offset = TmpOffsetGet(false);
    Reg tmpReg = RegGet(false, true, offset);
    fprintf(outputFile, "fclass.s x%d, f%d\n",
        tmpReg.registerNumber, testNode->reg.registerNumber);
    // the fclass.s instruction sets bit 3/4 if the float value is -0/+0, thus
    // we use a bit mask 24 (11000 in binary) to check if either bit is set
    fprintf(outputFile, "andi x%d, x%d, 24\n",
        tmpReg.registerNumber, tmpReg.registerNumber);
    if (elseStmtNode->nodeType != NUL_NODE) {
      CodegenBranchZero(BNEZ, testNode->reg.registerNumber,
                        "_ELSE_LABEL_", labelNo);
    } else {
      CodegenBranchZero(BNEZ, testNode->reg.registerNumber,
                        "_IF_EXIT_", labelNo);
    }
    RegFree(tmpReg);
    TmpOffsetFree(false, offset);
  }
  if (testNode->reg.isCallerSaved) {
    RegFree(testNode->reg);
    TmpOffsetFree(testNode->reg.isFloat, testNode->offset);
  }
  CodegenStmtNode(ifStmtNode);
  if (elseStmtNode->nodeType != NUL_NODE) {
    CodegenJumpLabelNo("_IF_EXIT_", labelNo);
    fprintf(outputFile, "_ELSE_LABEL_%d:\n", labelNo);
    CodegenStmtNode(elseStmtNode);
  }
  fprintf(outputFile, "_IF_EXIT_%d:\n", labelNo);
}

void CodegenFunctionCallStmt(AST_NODE *functionCallStmt) {
  assert(functionCallStmt->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT);
  AST_NODE *functionId = functionCallStmt->child;
  char *functionName = functionId->semantic_value.identifierSemanticValue.identifierName;
  if (   !strcmp("read" , functionName)
      || !strcmp("fread", functionName)) {
    CodegenReadFunction(functionCallStmt);
    return;
  }
  else if (!strcmp("write", functionName)) {
    CodegenWriteFunction(functionCallStmt);
    return;
  }
  fprintf(outputFile, "## Codegen: Normal Function Call Stmt ##\n");

  // TODO: passing parameters here
  const int ptrSize = 8, intSize = 8, floatSize = 4;
  int sp_offset = 0;
  int memSize = 0;
  for (AST_NODE *paramNode = functionId->rightSibling->child;
       paramNode; paramNode = paramNode->rightSibling) {
    CodegenExprRelated(paramNode);
    if (IS_ARG_REG(paramNode->reg.registerNumber)) {
      int tmpOffset = TmpOffsetGet(paramNode->reg.isFloat);
      fprintf(outputFile, "## TmpOffset = %d ##\n", tmpOffset);
      Reg reg = RegGet(paramNode->reg.isFloat, true, tmpOffset);
      if (reg.isFloat)
        fprintf(outputFile, "fmv.s f%d, f%d\n",
                reg.registerNumber, paramNode->reg.registerNumber);
      else
        fprintf(outputFile, "mv x%d, x%d\n",
                reg.registerNumber, paramNode->reg.registerNumber);
      paramNode->offset = tmpOffset;
      paramNode->reg = reg;
    }
    switch (paramNode->dataType) {
      case INT_TYPE:
        memSize = intSize;
        break;
      case FLOAT_TYPE:
        memSize = floatSize;
        break;
      case INT_PTR_TYPE:
      case FLOAT_PTR_TYPE:
        memSize = ptrSize;
        break;
      default:
        // this should not happen
        assert(0);
    }
    sp_offset -= memSize;
  }

  fprintf(outputFile, "li ra, %d\n", -sp_offset);
  fprintf(outputFile, "add sp, sp, ra\n");
  RegClear();

  sp_offset = 0; // for spilled argument offset calculation
  int localCurrentIntFunctionArgumentRegister = 0;
  int localCurrentFloatFunctionArgumentRegister = 0;
  SymbolTableEntry *entry = functionId->semantic_value.identifierSemanticValue.symbolTableEntry;
  Parameter *paramList = entry->attribute->attr.functionSignature->parameterList;
  Parameter *paramEntry = paramList;
  for (AST_NODE *paramNode = functionId->rightSibling->child;
       paramNode;
       paramNode = paramNode->rightSibling,
       paramEntry = paramEntry->next) {
    Reg paramReg = RegRestore(paramNode->reg, paramNode->offset);
    int currentRegNumber;
    switch (paramEntry->type->kind) {
      case SCALAR_TYPE_DESCRIPTOR: {
        switch (paramEntry->type->properties.dataType) {
          case INT_TYPE: {
            currentRegNumber = intFunctionArgumentRegisters[localCurrentIntFunctionArgumentRegister];
            if (!paramReg.isFloat) {
              if (currentRegNumber == NUL_REG) {
                fprintf(outputFile, "sd x%d, %d(sp)\n", paramReg.registerNumber, sp_offset);
              }
              else {
                fprintf(outputFile, "mv x%d, x%d\n", currentRegNumber, paramReg.registerNumber);
                localCurrentIntFunctionArgumentRegister++;
              }
            }
            else {
              if (currentRegNumber == NUL_REG) {
                // float -> int, and then sd int
                Reg tmpReg = RegGet(false, true, NUL_OFFSET);
                RegFree(tmpReg);
                fprintf(outputFile, "fcvt.w.s x%d, f%d, rtz\n", tmpReg.registerNumber, paramReg.registerNumber);
                fprintf(outputFile, "sd x%d, %d(sp)\n", tmpReg.registerNumber, sp_offset);
              }
              else {
                fprintf(outputFile, "fcvt.w.s x%d, f%d, rtz\n", currentRegNumber, paramReg.registerNumber);
                localCurrentIntFunctionArgumentRegister++;
              }
            }
            sp_offset += intSize;
            break;
          }
          case FLOAT_TYPE: {
            currentRegNumber = floatFunctionArgumentRegisters[localCurrentFloatFunctionArgumentRegister];
            if (!paramReg.isFloat) {
              if (currentRegNumber == NUL_REG) {
                // int -> float, and then fsw float
                Reg tmpReg = RegGet(true, true, NUL_OFFSET);
                RegFree(tmpReg);
                fprintf(outputFile, "fcvt.s.w f%d, x%d\n", tmpReg.registerNumber, paramReg.registerNumber);
                fprintf(outputFile, "fsw f%d, %d(sp)\n", tmpReg.registerNumber, sp_offset);
              }
              else {
                fprintf(outputFile, "fcvt.s.w f%d, x%d\n", currentRegNumber, paramReg.registerNumber);
                localCurrentFloatFunctionArgumentRegister++;
              }
            }
            else {
              if (currentRegNumber == NUL_REG) {
                fprintf(outputFile, "fsw f%d, %d(sp)\n", paramReg.registerNumber, sp_offset);
              }
              else {
                fprintf(outputFile, "fmv.s f%d, f%d\n", currentRegNumber, paramReg.registerNumber);
                localCurrentFloatFunctionArgumentRegister++;
              }
            }
            sp_offset += floatSize;
            break;
          }
          default:
            // this should not happen
            assert(0);
        }
        break;
      }
      case ARRAY_TYPE_DESCRIPTOR: {
        switch (paramEntry->type->properties.arrayProperties.elementType) {
          case INT_TYPE:
          case FLOAT_TYPE:
            currentRegNumber = intFunctionArgumentRegisters[localCurrentIntFunctionArgumentRegister];
            // TODO: I assumed address must be an integer
            if (currentRegNumber == NUL_REG) {
              fprintf(outputFile, "sd x%d, %d(sp)\n", paramReg.registerNumber, sp_offset);
            }
            else {
              fprintf(outputFile, "mv x%d, x%d\n", currentRegNumber, paramReg.registerNumber);
              localCurrentIntFunctionArgumentRegister++;
            }
            sp_offset += ptrSize;
            break;
          default:
            // this should not happen
            assert(0);
        }
        break;
      }
      default:
        // this should not happen
        assert(0);
    }
    if (paramReg.isCallerSaved) {
      RegFree(paramReg);
      TmpOffsetFree(paramReg.isFloat, paramNode->offset);
    }
  }

  fprintf(outputFile, "call _start_%s\n", functionName);
  DATA_TYPE returnType = entry->attribute->attr.functionSignature->returnType;
  bool isFloatType = false;
  if (returnType != VOID_TYPE) {
    switch (returnType) {
      case INT_TYPE:
        functionCallStmt->offset = TmpOffsetGet(false);
        functionCallStmt->reg = RegGet(false, true, functionCallStmt->offset);
        fprintf(outputFile, "mv x%d, a0\n",
                functionCallStmt->reg.registerNumber);
        break;
      case FLOAT_TYPE:
        functionCallStmt->offset = TmpOffsetGet(false);
        functionCallStmt->reg = RegGet(true, true, functionCallStmt->offset);
        fprintf(outputFile, "fmv.s f%d, fa0\n",
                functionCallStmt->reg.registerNumber);
        break;
      default:
        // this should not happen
        break;
    }
  }
  fprintf(outputFile, "li ra, -%d\n", sp_offset);
  fprintf(outputFile, "add sp, sp, ra\n");
}

void CodegenReadFunction(AST_NODE *readFunctionCall) {
  fprintf(outputFile, "## Codegen: read() call Stmt ##\n");
  RegClear();
  AST_NODE *functionId = readFunctionCall->child;
  char *functionName = functionId->semantic_value.identifierSemanticValue.identifierName;
  if (!strcmp("read", functionName)) {        // return int
    fprintf(outputFile, "call _read_int\n");
    readFunctionCall->offset = TmpOffsetGet(false);
    readFunctionCall->reg = RegGet(false, true, readFunctionCall->offset);
    fprintf(outputFile, "mv x%d, a0\n",
            readFunctionCall->reg.registerNumber);
  }
  else if (!strcmp("fread", functionName)) {  // return float
    fprintf(outputFile, "call _read_float\n");
    readFunctionCall->offset = TmpOffsetGet(false);
    readFunctionCall->reg = RegGet(true, true, readFunctionCall->offset);
    fprintf(outputFile, "fmv.s f%d, fa0\n",
            readFunctionCall->reg.registerNumber);
  }
  else {
    // this should not happen
    assert(0);
  }
}

void CodegenWriteFunction(AST_NODE *writeFunctionCall) {
  fprintf(outputFile, "## Codegen: write() call Stmt ##\n");
  AST_NODE *onlyParamNode = writeFunctionCall->child->rightSibling->child;
  CodegenExprRelated(onlyParamNode);

  if (IS_ARG_REG(onlyParamNode->reg.registerNumber)) {
    int tmpOffset = TmpOffsetGet(onlyParamNode->reg.isFloat);
    Reg reg = RegGet(onlyParamNode->reg.isFloat, true, tmpOffset);
    if (reg.isFloat)
      fprintf(outputFile, "fmv.s f%d, f%d\n",
              reg.registerNumber, onlyParamNode->reg.registerNumber);
    else
      fprintf(outputFile, "mv x%d, x%d\n",
              reg.registerNumber, onlyParamNode->reg.registerNumber);
    onlyParamNode->offset = tmpOffset;
    onlyParamNode->reg = reg;
  }
  if (onlyParamNode->reg.isCallerSaved) {
    RegFree(onlyParamNode->reg);
    TmpOffsetFree(onlyParamNode->reg.isFloat,
                  onlyParamNode->offset);
  }
  RegClear();
  const char *typeStr;

  switch (onlyParamNode->nodeType) {
    case IDENTIFIER_NODE: { // var_ref
      SymbolTableEntry *entry = onlyParamNode->semantic_value.identifierSemanticValue.symbolTableEntry;
      TypeDescriptor *entryTD = entry->attribute->attr.typeDescriptor;
      bool isIntType = false;
      switch (entryTD->kind) {
        case SCALAR_TYPE_DESCRIPTOR:
          switch (entryTD->properties.dataType) {
            case INT_TYPE:
              isIntType = true;
              break;
            case FLOAT_TYPE:
              isIntType = false;
              break;
            default:
              // this should not happen
              assert(0);
          }
          break;
        case ARRAY_TYPE_DESCRIPTOR: {
          switch (entryTD->properties.arrayProperties.elementType) {
            case INT_TYPE:
              isIntType = true;
              break;
            case FLOAT_TYPE:
              isIntType = false;
              break;
            default:
              // this should not happen
              assert(0);
          }
          break;
        }
        default:
          // this should not happen
          assert(0);
      }
      if (isIntType)
        fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
      else
        fprintf(outputFile, "fmv.s fa0, f%d\n", onlyParamNode->reg.registerNumber);
      typeStr = isIntType ? "int" : "float";
      break;
    }
    case CONST_VALUE_NODE: {
      switch (onlyParamNode->semantic_value.const1->const_type) {
        case INTEGERC:
          fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "int";
          break;
        case FLOATC:
          fprintf(outputFile, "fmv.s fa0, f%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "float";
          break;
        case STRINGC:
          fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "str";
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    case STMT_NODE: { // FUNCTION_CALL_STMT
      SymbolTableEntry *entry = onlyParamNode->child->semantic_value.identifierSemanticValue.symbolTableEntry;
      DATA_TYPE returnType = entry->attribute->attr.functionSignature->returnType;
      switch (returnType) {
        case INT_TYPE:
          fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "int";
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "fmv.s fa0, f%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "float";
          break;
        case VOID_TYPE:
          assert(0 && "void value not ignored as it ought to be");
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    case EXPR_NODE: {
      switch (onlyParamNode->dataType) {
        case INT_TYPE:
          fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "int";
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "fmv.s fa0, f%d\n", onlyParamNode->reg.registerNumber);
          typeStr = "float";
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    }
    default:
      // this should not happen
      assert(0);
  }
  fprintf(outputFile, "addi sp, sp, -8\n");
  fprintf(outputFile, "call _write_%s\n", typeStr);
  fprintf(outputFile, "addi sp, sp, 8\n");
}

void CodegenReturnStmt(AST_NODE *returnStmt) {
  assert(returnStmt->semantic_value.stmtSemanticValue.kind == RETURN_STMT);
  fprintf(outputFile, "## Codegen: Return Stmt ##\n");
  // TODO: implicit type conversion ? done !
  AST_NODE *returnValueNode = returnStmt->child;
  AST_NODE *currentNode, *functionId;
  for (currentNode = returnStmt;
       currentNode->nodeType != DECLARATION_NODE
       && currentNode->semantic_value.declSemanticValue.kind != FUNCTION_DECL;
       currentNode = currentNode->parent);
  functionId = currentNode->child->rightSibling;
  char *functionName = functionId->semantic_value.identifierSemanticValue.identifierName;
  // SymbolTableEntry *functionEntry = functionId->semantic_value.identifierSemanticValue.symbolTableEntry;
  // TODO: TA didn't put symbolTableEntry into function id node !
  SymbolTableEntry *functionEntry = retrieveSymbol(functionName);
  FunctionSignature *funcSign = functionEntry->attribute->attr.functionSignature;
  if (returnValueNode->nodeType != NUL_NODE) {
    CodegenExprRelated(returnValueNode);
    if (!returnValueNode->reg.isFloat) {
      switch (funcSign->returnType) {
        case INT_TYPE:
          fprintf(outputFile, "mv a0, x%d\n", returnValueNode->reg.registerNumber);
          break;
        case FLOAT_TYPE:  // TODO: int -> float
          fprintf(outputFile, "fcvt.s.w fa0, x%d\n", returnValueNode->reg.registerNumber);
          break;
        default:
          // this should not happen
          assert(0);
      }
    }
    else {
      switch (funcSign->returnType) {
        case INT_TYPE:
          fprintf(outputFile, "fcvt.w.s a0, f%d, rtz\n", returnValueNode->reg.registerNumber);
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "fmv.s fa0, f%d\n", returnValueNode->reg.registerNumber);
          break;
        default:
          // this should not happen
          assert(0);
      }
    }
    if (returnValueNode->reg.isCallerSaved) {
      RegFree(returnValueNode->reg);
      TmpOffsetFree(returnValueNode->reg.isFloat,
                    returnValueNode->offset);
    }
  }
  CodegenJumpLabelStr("_FUNCTION_END_", functionName);
}

void CodegenJumpLabel(const char *label) {
  // ra register is used because it is the only register that can be used
  // at any time
  fprintf(outputFile, "la ra, %s\n", label);
  fprintf(outputFile, "jr ra\n");
}

void CodegenJumpLabelNo(const char *label, int labelNo) {
  // ra register is used because it is the only register that can be used
  // at any time
  fprintf(outputFile, "la ra, %s%d\n", label, labelNo);
  fprintf(outputFile, "jr ra\n");
}

void CodegenJumpLabelStr(const char *label, const char *str) {
  // ra register is used because it is the only register that can be used
  // at any time
  fprintf(outputFile, "la ra, %s%s\n", label, str);
  fprintf(outputFile, "jr ra\n");
}

void CodegenBranchZero(BranchInst inst, int reg,
                       const char *label, int labelNo) {
  const char *branch;
  switch (inst) {
    case BEQZ:
      branch = "bnez";
      break;
    case BNEZ:
      branch = "beqz";
      break;
    default:
      // this should not happen
      assert(0);
  }
  fprintf(outputFile, "%s x%d, _SKIP_%d\n", branch, reg, skipCounter);
  CodegenJumpLabelNo(label, labelNo);
  fprintf(outputFile, "_SKIP_%d:\n", skipCounter++);
}

void CodegenBranch(BranchInst inst, int reg1, int reg2,
                   const char *label, int labelNo) {
  const char *branch;
  switch (inst) {
    case BEQ:
      branch = "bne";
      break;
    case BNE:
      branch = "beq";
      break;
    case BLT:
      branch = "bge";
      break;
    case BLE:
      branch = "bgt";
      break;
    case BGT:
      branch = "ble";
      break;
    case BGE:
      branch = "blt";
      break;
    default:
      // this should not happen
      assert(0);
  }
  fprintf(outputFile, "%s x%d, x%d, _SKIP_%d\n", branch, reg1, reg2,
          skipCounter);
  CodegenJumpLabelNo(label, labelNo);
  fprintf(outputFile, "_SKIP_%d:\n", skipCounter++);
}
