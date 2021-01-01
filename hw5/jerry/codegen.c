#include "codegen.h"
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* ========== global variables ========== */

bool raSpilled = false;
int constantCounter = 0;
int booleanCounter = 0;
int whileCounter = 0;
int forCounter = 0;
int ifCounter = 0;
int localVariableOffset = 0;
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
    VectorPushback(freeTmpOffsets, localVariableOffset);
    localVariableOffset -= size;
    arSize += size;
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
  VectorPushback(freeTmpOffsets, tmpOffset);
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
#define PLACEHOLDER_OFFSET 0  // fp+0 is used to store old fp, thus should not
                              // be a valid register spilling address
#define NUL_OFFSET         8  // fp+8 is used to store return address, thus
                              // should not be a valid register spilling address
/*
 * TODO:
 * How do we manage registers for function arguments? The current implementation
 * doesn't allow them to be used as either caller saved or callee saved
 * registers.
 */
// integer caller saved registers
int intCallerSavedRegisters[] =
  { 5, 6, 7, 28, 29, 30, 31, NUL_REG };
List *freeIntCallerSavedRegisters, *usedIntCallerSavedRegisters;
int intCallerSavedRegisterOffsets[RISCV_MAX_REG_NUM];
// integer callee saved registers
int intCalleeSavedRegisters[] =
  { 9, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NUL_REG };
List *freeIntCalleeSavedRegisters, *usedIntCalleeSavedRegisters;
Queue *savedIntCalleeSavedRegisters, *savedIntCalleeSavedRegisterOffsets;
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
Queue *savedFloatCalleeSavedRegisters, *savedFloatCalleeSavedRegisterOffsets;
int floatCalleeSavedRegisterOffsets[RISCV_MAX_REG_NUM];

void RegInit() {
  // int caller saved registers
  freeIntCallerSavedRegisters = ListAlloc();
  usedIntCallerSavedRegisters = ListAlloc();
  // int callee saved registers
  freeIntCalleeSavedRegisters = ListAlloc();
  usedIntCalleeSavedRegisters = ListAlloc();
  savedIntCalleeSavedRegisters = QueueAlloc();
  savedIntCalleeSavedRegisterOffsets = QueueAlloc();
  // float caller saved registers
  freeFloatCallerSavedRegisters = ListAlloc();
  usedFloatCallerSavedRegisters = ListAlloc();
  // float callee saved registers
  freeFloatCalleeSavedRegisters = ListAlloc();
  usedFloatCalleeSavedRegisters = ListAlloc();
  savedFloatCalleeSavedRegisters = QueueAlloc();
  savedFloatCalleeSavedRegisterOffsets = QueueAlloc();
}

void RegEnd() {
  // int caller saved registers
  ListFree(&freeIntCallerSavedRegisters);
  ListFree(&usedIntCallerSavedRegisters);
  // int callee saved registers
  ListFree(&freeIntCalleeSavedRegisters);
  ListFree(&usedIntCalleeSavedRegisters);
  QueueFree(&savedIntCalleeSavedRegisters);
  QueueFree(&savedIntCalleeSavedRegisterOffsets);
  // float caller saved registers
  ListFree(&freeFloatCallerSavedRegisters);
  ListFree(&usedFloatCallerSavedRegisters);
  // float callee saved registers
  ListFree(&freeFloatCalleeSavedRegisters);
  ListFree(&usedFloatCalleeSavedRegisters);
  QueueFree(&savedFloatCalleeSavedRegisters);
  QueueFree(&savedFloatCalleeSavedRegisterOffsets);
}

/* TODO: remember to call this function every time a new function is declared */
void RegReset() {
  // The current implementation makes all caller saved registers free,
  // and make all callee saved registers used. If a callee saved register is
  // requested, then there will definitely be a spill, and the spill address
  // is dynamically assigned and recorded so that the function epilogue can
  // remember to restore it.

  // integer caller saved registers
  ListClear(freeIntCallerSavedRegisters);
  ListClear(usedIntCallerSavedRegisters);
  for (int i = 0; intCallerSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeIntCallerSavedRegisters, intCallerSavedRegisters[i]);

  // integer callee saved registers
  ListClear(freeIntCalleeSavedRegisters);
  ListClear(usedIntCalleeSavedRegisters);
  QueueClear(savedIntCalleeSavedRegisters);
  QueueClear(savedIntCalleeSavedRegisterOffsets);
  for (int i = 0; intCalleeSavedRegisters[i] != NUL_REG; ++i) {
    ListPush(usedIntCalleeSavedRegisters, intCalleeSavedRegisters[i]);
    intCalleeSavedRegisterOffsets[i] = PLACEHOLDER_OFFSET;
  }

  // float caller saved registers
  ListClear(freeFloatCallerSavedRegisters);
  ListClear(usedFloatCallerSavedRegisters);
  for (int i = 0; floatCallerSavedRegisters[i] != NUL_REG; ++i)
    ListPush(freeFloatCallerSavedRegisters, floatCallerSavedRegisters[i]);

  // float callee saved registers
  ListClear(freeFloatCalleeSavedRegisters);
  ListClear(usedFloatCalleeSavedRegisters);
  QueueClear(savedFloatCalleeSavedRegisters);
  QueueClear(savedFloatCalleeSavedRegisterOffsets);
  for (int i = 0; floatCalleeSavedRegisters[i] != NUL_REG; ++i) {
    ListPush(usedFloatCalleeSavedRegisters, floatCalleeSavedRegisters[i]);
    floatCalleeSavedRegisterOffsets[i] = PLACEHOLDER_OFFSET;
  }

  // return address register
  raSpilled = false;
}

/* TODO: remember to call this function every time a function call is
 *       encountered */
void RegClear() {
  // int caller saved registers
  for (int registerNumber = ListFront(usedIntCallerSavedRegisters);
       registerNumber != NUL_IDX;
       registerNumber = ListNext(usedIntCallerSavedRegisters, registerNumber)) {
    int offset = intCallerSavedRegisterOffsets[registerNumber];
    // placeholder offset should only be set by callee saved registers
    assert(offset != PLACEHOLDER_OFFSET);
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "sd x%d, %d(fp)\n", registerNumber, offset);
      intCallerSavedRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  // float caller saved registers
  for (int registerNumber = ListFront(usedFloatCallerSavedRegisters);
       registerNumber != NUL_IDX;
       registerNumber = ListNext(usedFloatCallerSavedRegisters,
                                 registerNumber)) {
    int offset = floatCallerSavedRegisterOffsets[registerNumber];
    // placeholder offset should only be set by callee saved registers
    assert(offset != PLACEHOLDER_OFFSET);
    if (offset != NUL_OFFSET) {
      fprintf(outputFile, "fsw f%d, %d(fp)\n",
          registerNumber, floatCallerSavedRegisterOffsets[registerNumber]);
      floatCallerSavedRegisterOffsets[registerNumber] = NUL_OFFSET;
    }
  }

  // return address register
  raSpilled = true;
}

int RegGetImpl(bool isFloat, int *registerOffsets,
               List *freeRegisters, List *usedRegisters,
               Queue *savedRegisters, Queue *savedRegisterOffsets, int offset) {
  if (ListEmpty(freeRegisters)) {
    // no more registers, need to spill
    int spillRegister = ListPop(usedRegisters);
    int spillOffset = registerOffsets[spillRegister];
    if (spillOffset == PLACEHOLDER_OFFSET) {
      // spilling a callee saved register for the first time, offset is recorded
      // for function epilogue to restore
      spillOffset = localVariableOffset;
      assert(savedRegisters);
      QueuePush(savedRegisters, spillRegister);
      assert(savedRegisterOffsets);
      QueuePush(savedRegisterOffsets, spillOffset);
      if (isFloat) {
        localVariableOffset -= 4;
        arSize += 4;
      } else {
        localVariableOffset -= 8;
        arSize += 8;
      }
    }
    if (spillOffset != NUL_OFFSET) {
      // NUL_OFFSET is set by RegClear, which spills all caller saved registers
      // when a function call is encountered. Therefore, if NUL_OFFSET is
      // encountered, this means that the register has already been saved.
      if (isFloat)
        fprintf(outputFile, "fsw f%d, %d(fp)\n", spillRegister, spillOffset);
      else
        fprintf(outputFile, "sd x%d, %d(fp)\n", spillRegister, spillOffset);
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
          true, floatCallerSavedRegisterOffsets,
          freeFloatCallerSavedRegisters, usedFloatCallerSavedRegisters,
          NULL, NULL,
          offset);
    } else {
      // float callee saved register
      newRegister.registerNumber = RegGetImpl(
          true, floatCalleeSavedRegisterOffsets,
          freeFloatCalleeSavedRegisters, usedFloatCalleeSavedRegisters,
          savedFloatCalleeSavedRegisters, savedFloatCalleeSavedRegisterOffsets,
          offset);
    }
  } else {
    if (isCallerSaved) {
      // int caller saved register
      newRegister.registerNumber = RegGetImpl(
          false, intCallerSavedRegisterOffsets,
          freeIntCallerSavedRegisters, usedIntCallerSavedRegisters,
          NULL, NULL,
          offset);
    } else {
      // int caller saved register
      newRegister.registerNumber = RegGetImpl(
          false, intCalleeSavedRegisterOffsets,
          freeIntCalleeSavedRegisters, usedIntCalleeSavedRegisters,
          savedIntCalleeSavedRegisters, savedIntCalleeSavedRegisterOffsets,
          offset);
    }
  }
  return newRegister;
}

void RegFreeImpl(int registerNumber,
                 List *freeRegisters, List *usedRegisters) {
  ListDelete(usedRegisters, registerNumber);
  ListPush(freeRegisters, registerNumber);
}

void RegFree(Reg reg) {
  if (reg.registerNumber == NUL_REG)
    return;
  if (reg.isFloat) {
    if (reg.isCallerSaved) {
      // float caller saved registers
      RegFreeImpl(reg.registerNumber,
                  freeFloatCallerSavedRegisters, usedFloatCallerSavedRegisters);
    } else {
      // float callee saved registers
      RegFreeImpl(reg.registerNumber,
                  freeFloatCalleeSavedRegisters, usedFloatCalleeSavedRegisters);
    }
  } else {
    if (reg.isCallerSaved) {
      // int caller saved registers
      RegFreeImpl(reg.registerNumber,
                  freeIntCallerSavedRegisters, usedIntCallerSavedRegisters);
    } else {
      // int callee saved registers
      RegFreeImpl(reg.registerNumber,
                  freeIntCalleeSavedRegisters, usedIntCalleeSavedRegisters);
    }
  }
}

int RegRestoreImpl(int oldRegisterNumber, bool isFloat, int *registerOffsets,
                   List *freeRegisters, List *usedRegisters,
                   Queue *savedRegisters, Queue *savedRegisterOffsets,
                   int offset) {
  if (registerOffsets[oldRegisterNumber] == offset)
    return oldRegisterNumber;
  int newRegisterNumber = RegGetImpl(isFloat, registerOffsets,
                                     freeRegisters, usedRegisters,
                                     savedRegisters, savedRegisterOffsets,
                                     offset);
  if (isFloat)
    fprintf(outputFile, "flw f%d, %d(fp)\n", newRegisterNumber, offset);
  else
    fprintf(outputFile, "ld x%d, %d(fp)\n", newRegisterNumber, offset);
  return newRegisterNumber;
}

Reg RegRestore(Reg oldReg, int offset) {
  Reg newReg = oldReg;
  if (oldReg.isFloat) {
    if (oldReg.isCallerSaved) {
      // float caller saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, floatCallerSavedRegisterOffsets,
          freeFloatCallerSavedRegisters, usedFloatCallerSavedRegisters,
          NULL, NULL,
          offset);
    } else {
      // float callee saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, floatCalleeSavedRegisterOffsets,
          freeFloatCalleeSavedRegisters, usedFloatCalleeSavedRegisters,
          savedFloatCalleeSavedRegisters, savedFloatCalleeSavedRegisterOffsets,
          offset);
    }
  } else {
    if (oldReg.isCallerSaved) {
      // int caller saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, intCallerSavedRegisterOffsets,
          freeIntCallerSavedRegisters, usedIntCallerSavedRegisters,
          NULL, NULL,
          offset);
    } else {
      // int callee saved register
      newReg.registerNumber = RegRestoreImpl(
          oldReg.registerNumber, true, intCalleeSavedRegisterOffsets,
          freeIntCalleeSavedRegisters, usedIntCalleeSavedRegisters,
          savedIntCalleeSavedRegisters, savedIntCalleeSavedRegisterOffsets,
          offset);
    }
  }
  return newReg;
}

void RegRestoreRA() {
  if (raSpilled) {
    fprintf(outputFile, "ld ra, 8(fp)\n");
    raSpilled = false;
  }
}

/* ========== register manager ========== */

/* ========== code generation ========== */

void CodegenProgramNode(AST_NODE *programNode) {
  // initialization is done here
  TmpOffsetInit();
  RegInit();
  outputFile = fopen("output.S", "w");
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
  fprintf(outputFile, "_FUNCTION_%s\n", functionName);
  fprintf(outputFile, "sd ra, 8(sp)\n");
  fprintf(outputFile, "sd fp, 0(sp)\n");
  fprintf(outputFile, "addi fp, sp, -8\n");
  fprintf(outputFile, "addi sp, sp, -16\n");
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

  // restore int callee saved registers
  while (!QueueEmpty(savedIntCalleeSavedRegisters)) {
    int registerNumber = QueuePop(savedIntCalleeSavedRegisters);
    assert(!QueueEmpty(savedIntCalleeSavedRegisterOffsets));
    int offset = QueuePop(savedIntCalleeSavedRegisterOffsets);
    fprintf(outputFile, "ld x%d, %d(fp)\n", registerNumber, offset);
  }

  // restore float callee saved registers
  while (!QueueEmpty(savedFloatCalleeSavedRegisters)) {
    int registerNumber = QueuePop(savedFloatCalleeSavedRegisters);
    assert(!QueueEmpty(savedFloatCalleeSavedRegisterOffsets));
    int offset = QueuePop(savedFloatCalleeSavedRegisterOffsets);
    fprintf(outputFile, "flw f%d, %d(fp)\n", registerNumber, offset);
  }

  fprintf(outputFile, "ld ra, 8(fp)\n");
  fprintf(outputFile, "addi fp, sp, 8\n");
  fprintf(outputFile, "ld fp, 0(fp)\n");
  fprintf(outputFile, "jr ra\n");
  fprintf(outputFile, ".data\n");
  // TODO: Is the newline character necessary?
  fprintf(outputFile, "_FRAME_SIZE_%s\n: .word %d\n", functionName, arSize);
  fprintf(outputFile, ".text\n");
}

void CodegenExprRelated(AST_NODE *exprRelated) {
  switch (exprRelated->nodeType) {
    case IDENTIFIER_NODE:
      CodegenVariableRef(exprRelated);
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

void CodegenVariableRef(AST_NODE *varRef) {
  assert(varRef->nodeType == IDENTIFIER_NODE);

  varRef->isBooleanExpr = false;

  IdentifierSemanticValue *id = &varRef->semantic_value.identifierSemanticValue;
  SymbolTableEntry *entry = id->symbolTableEntry;
  assert(entry->attribute->attributeKind == VARIABLE_ATTRIBUTE);

  switch (id->kind) {
    case NORMAL_ID: {
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
            fprintf(outputFile, "ld x%d, 0(x%d)\n",
                    varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
            Reg addrReg = RegGet(false, true, NUL_OFFSET);
            varRef->offset = TmpOffsetGet(true);
            varRef->reg = RegGet(true, true, varRef->offset);
            fprintf(outputFile, "la x%d, _GLOBAL_%s\n",
                    addrReg.registerNumber, id->identifierName);
            fprintf(outputFile, "flw f%d, 0(x%d)\n",
                    varRef->reg.registerNumber, addrReg.registerNumber);
            RegFree(addrReg);
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
          switch (varRef->dataType) {
            case INT_TYPE:
            case INT_PTR_TYPE:
            case FLOAT_PTR_TYPE:
              entry->reg = RegGet(false, false, entry->offset);
              fprintf(outputFile, "ld x%d, %d(fp)\n",
                      entry->reg.registerNumber, entry->offset);
              break;
            case FLOAT_TYPE:
              entry->reg = RegGet(true, false, entry->offset);
              fprintf(outputFile, "flw f%d, %d(fp\n)",
                      entry->reg.registerNumber, entry->offset);
              break;
            default:
              // this should not happen
              assert(0);
          }
        } else {
          // variable is a local variable or parameter, and has been assigned
          // to a register, then we restore the register
          entry->reg = RegRestore(entry->reg, entry->offset);
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
      int dimension = 1;
      for (AST_NODE *dimNode = varRef->child; dimNode;
           dimNode = dimNode->rightSibling) {
        CodegenExpr(dimNode); // TODO: ExprRelated ?
        vpReg = RegRestore(vpReg, vpOffset);
        fprintf(outputFile, "add x%d, x%d, x%d\n",
                vpReg.registerNumber, vpReg.registerNumber,
                dimNode->reg.registerNumber);
        if (dimension != arrayProperties->dimension) {
          fprintf(outputFile, "li x%d, %d\n",
              dimNode->reg.registerNumber,
              arrayProperties->sizeInEachDimension[dimension++]);
          fprintf(outputFile, "mul x%d, x%d, x%d\n",
              vpReg.registerNumber, vpReg.registerNumber,
              dimNode->reg.registerNumber);
        }
        RegFree(dimNode->reg);
      }
      switch (arrayProperties->elementType) {
        case INT_TYPE:
          fprintf(outputFile, "slli x%d, 3\n", vpReg.registerNumber);
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "slli x%d, 2\n", vpReg.registerNumber);
          break;
        default:
          // this should not happen
          assert(0);
      }

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
            fprintf(outputFile, "ld x%d, 0(x%d)\n",
                varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
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
          fprintf(outputFile, "addi x%d, fp, %d\n",
                  entry->reg.registerNumber, entry->offset);
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
            fprintf(outputFile, "ld x%d, 0(x%d)\n",
                varRef->reg.registerNumber, varRef->reg.registerNumber);
            break;
          } case FLOAT_TYPE: {
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
    } case WITH_INIT_ID: {
      // this should not happen
      assert(0);
    }
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
      fprintf(outputFile, "_CONSTANT_%d: .float %f\n",
          constantLabelNo, val->const_u.fval);
      // TODO: verify that .align 2 (4 byte alignment) is correct; for some
      //       reason, the example code writes .align 3
      fprintf(outputFile, ".align 2\n");
      fprintf(outputFile, ".text\n");
      fprintf(outputFile, "la x%d, _CONSTANT_%d\n",
          addrReg.registerNumber, constantLabelNo);
      fprintf(outputFile, "flw f%d, 0(x%d\n)",
          constValue->reg.registerNumber, addrReg.registerNumber);
      RegFree(addrReg);
      break;
    } case STRINGC: {
      constValue->offset = TmpOffsetGet(false);
      constValue->reg = RegGet(true, true, constValue->offset);
      fprintf(outputFile, ".data\n");
      fprintf(outputFile, "_CONSTANT_%d: .string %s\n",
          constantLabelNo, val->const_u.sc);
      // TODO: verify that .align 3 (8 byte alignment) is correct; for some
      //       reason, the example code writes .align 4
      fprintf(outputFile, ".align 3\n");
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
      CodegenExpr(exprNode->child);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
              exprNode->reg.registerNumber, exprNode->parentLabelNo);
        else
          fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
              exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
      exprNode->reg = exprNode->child->reg;
      break;
    case UNARY_OP_NEGATIVE:
      assert(exprNode->child);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "bne x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "beq x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "beq x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "bne x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "blt x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "bge x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "bgt x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "ble x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "ble x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "bgt x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
          if (exprNode->shortOnFalse)
            fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
          else
            fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
                exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
        if (exprNode->shortOnFalse)
          fprintf(outputFile, "bge x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
        else
          fprintf(outputFile, "blt x%d, x%d, _BOOL_SHORT_%d\n",
              leftExprNode->reg.registerNumber,
              rightExprNode->reg.registerNumber,
              exprNode->parentLabelNo);
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
        fprintf(outputFile, "j _BOOL_EXIT_%d\n", labelNo);
      } else if (!exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on true, then
        // directly jump
        fprintf(outputFile, "j _BOOL_SHORT_%d\n", exprNode->parentLabelNo);
      }
      // short circuit code, which corresponds to false
      fprintf(outputFile, "_BOOL_SHORT_%d:\n", labelNo);
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "mv x%d, x0\n", exprNode->reg.registerNumber);
      } else if (exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on false, then
        // directly jump
        fprintf(outputFile, "j _BOOL_SHORT_%d\n", exprNode->parentLabelNo);
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
        fprintf(outputFile, "j _BOOL_EXIT_%d\n", labelNo);
      } else if (exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on false, then
        // directly jump
        fprintf(outputFile, "j _BOOL_SHORT_%d\n", exprNode->parentLabelNo);
      }
      // short circuit code, which corresponds to true
      fprintf(outputFile, "_BOOL_SHORT_%d:\n", labelNo);
      if (exprNode->parentLabelNo == NUL_LABEL) {
        // parent is not a short circuit expression, then actually calculate
        // the arithemtic value
        exprNode->offset = TmpOffsetGet(false);
        exprNode->reg = RegGet(false, true, exprNode->offset);
        fprintf(outputFile, "addi x%d, x0, 1\n", exprNode->reg.registerNumber);
      } else if (!exprNode->shortOnFalse) {
        // parent is a short circuit expression and it shorts on true, then
        // directly jump
        fprintf(outputFile, "j _BOOL_SHORT_%d\n", exprNode->parentLabelNo);
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
      if (leftExprNode->reg.isFloat)
        fprintf(outputFile, "addw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fadd.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_SUB:
      if (leftExprNode->reg.isFloat)
        fprintf(outputFile, "subw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fsub.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_MUL:
      if (leftExprNode->reg.isFloat)
        fprintf(outputFile, "mulw x%d, x%d, x%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      else
        fprintf(outputFile, "fmul.s f%d, f%d, f%d\n",
            exprNode->reg.registerNumber,
            leftExprNode->reg.registerNumber, rightExprNode->reg.registerNumber);
      break;
    case BINARY_OP_DIV:
      if (leftExprNode->reg.isFloat)
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
    if (exprNode->shortOnFalse)
      fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
          condReg.registerNumber, exprNode->parentLabelNo);
    else
      fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
          condReg.registerNumber, exprNode->parentLabelNo);
    RegFree(condReg);
  } else {
    if (exprNode->shortOnFalse)
      fprintf(outputFile, "beqz x%d, _BOOL_SHORT_%d\n",
          exprNode->reg.registerNumber, exprNode->parentLabelNo);
    else
      fprintf(outputFile, "bnez x%d, _BOOL_SHORT_%d\n",
          exprNode->reg.registerNumber, exprNode->parentLabelNo);
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
    case FUNCTION_PARAMETER_DECL:
      CodegenParameterDeclaration(declarationNode);
      break;
    case TYPE_DECL: // have been handled in semantic check stage
      break;
    case VARIABLE_DECL:
      CodegenVariableDeclaration(declarationNode);
      break;
    default:
      assert(0);
  }
}

void CodegenParameterDeclaration(AST_NODE *paramNode) {
  assert(paramNode->semantic_value.declSemanticValue.kind == FUNCTION_PARAMETER_DECL);
  fprintf(outputFile, "## Codegen: Parameter Declaration ##\n");
  // would be covered in HW6
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
      int intSize = 8, floatSize = 4;
      int memSize = 0;
      switch (singleVariableTD->kind) {
        case SCALAR_TYPE_DESCRIPTOR:
          memSize = 1;
          switch (singleVariableTD->properties.dataType) {
            case INT_TYPE:
              fprintf(outputFile, "_GLOBAL_%s: .word\n", singleVariableName);
              break;
            case FLOAT_TYPE:
              fprintf(outputFile, "_GLOBAL_%s: .float\n", singleVariableName);
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
      // set symbolTableEntry.offset
      singleVariableEntry->offset = -arSize; // calculated from fp downto sp
      // modify new arSize
      TypeDescriptor *singleVariableTD = singleVariableEntry->attribute->attr.typeDescriptor;
      int intSize = 8, floatSize = 4;
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
      arSize += memSize * (isIntType ? intSize : floatSize);
      //fprintf(outputFile, "### allocate %d bytes, arSize: %d ###\n", memSize * intSize, arSize);
    }
  }
}

void CodegenFunctionDeclaration(AST_NODE *functionNode) {
  assert(functionNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL);
  TmpOffsetReset();
  RegReset();

  arSize = 0;
  CodegenFunctionPrologue(functionNode);

  fprintf(outputFile, "## Codegen: Function Declaration ##\n");
  AST_NODE *paramListNode = functionNode->child->rightSibling->rightSibling;
  assert(paramListNode->nodeType == PARAM_LIST_NODE);
  for (AST_NODE *param = paramListNode->child; param; param = param->rightSibling) {
    assert(param->nodeType == FUNCTION_PARAMETER_DECL);
    CodegenDeclarationNode(param);  // FUNCTION_PARAMETER_DECL
  }
  
  AST_NODE *blockNode = paramListNode->rightSibling;
  CodegenBlockNode(blockNode);
  
  AST_NODE *functionId = functionNode->child->rightSibling;
  char *functionName = functionId->semantic_value.identifierSemanticValue.identifierName;
  fprintf(outputFile, "_FUNCTION_END_%s:\n", functionName); // TODO: epilogue ?
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
  fprintf(outputFile, "## Codegen: While Stmt ##\n");
  fprintf(outputFile, "_WHILE_LABEL_%d:\n", whileCounter);
  AST_NODE *testNode = whileStmt->child;
  CodegenExprRelated(testNode); // TODO: what if testNode is assign_expr ? what if FLOAY_TYPE ?
  fprintf(outputFile, "beqz x%d, _WHILE_EXIT_%d\n", testNode->reg.registerNumber, whileCounter);
  RegFree(testNode->reg);
  if (testNode->reg.isCallerSaved) {
    TmpOffsetFree(testNode->reg.isFloat, testNode->offset);
  }
  AST_NODE *stmtNode = testNode->rightSibling;
  CodegenStmtNode(stmtNode);
  fprintf(outputFile, "j _WHILE_LABEL_%d\n", whileCounter);
  fprintf(outputFile, "_WHILE_EXIT_%d:\n", whileCounter);
  whileCounter++;
}

void CodegenForStmt(AST_NODE *forStmt) {
  assert(forStmt->semantic_value.stmtSemanticValue.kind == FOR_STMT);
  fprintf(outputFile, "## Codegen: For Stmt ##\n");
  fprintf(outputFile, "_FOR_LABEL_%d:\n", forCounter);
  AST_NODE *forInitNode = forStmt->child;
  if (forInitNode->nodeType != NUL_NODE) {
    for (AST_NODE *exprNode = forInitNode->child;
         exprNode;
         exprNode = exprNode->rightSibling) {
      CodegenExprRelated(exprNode); // should be ASSIGN_STMT
    }
  }
  fprintf(outputFile, "_FOR_BODY_%d:\n", forCounter);
  AST_NODE *forCondNode = forInitNode->rightSibling;
  if (forCondNode->nodeType != NUL_NODE) {
    // TODO: what if multiple condition statement ? 
  }
  AST_NODE *forIncNode = forCondNode->rightSibling;
  if (forIncNode->nodeType != NUL_NODE) {
    for (AST_NODE *exprNode = forIncNode->child;
         exprNode;
         exprNode = exprNode->rightSibling) {
      CodegenExprRelated(exprNode); // should be ASSIGN_STMT
    }
  }
  AST_NODE *stmtNode = forIncNode->rightSibling;
  CodegenStmtNode(stmtNode);
  fprintf(outputFile, "j _FOR_BODY_%d\n", forCounter);
  fprintf(outputFile, "_FOR_EXIT_%d:\n", forCounter);
  forCounter++;
}

void CodegenAssignStmt(AST_NODE *assignStmt) {
  assert(assignStmt->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT);
  fprintf(outputFile, "## Codegen: Assign Stmt ##\n");
  AST_NODE *variableNode = assignStmt->child;
  AST_NODE *exprNode = variableNode->rightSibling;
  CodegenExprRelated(variableNode); // should be var_ref (or simply ID, TODO: why?)
  CodegenExprRelated(exprNode);     // should be relop_expr
  fprintf(outputFile, "mv x%d, x%d\n", variableNode->reg.registerNumber,
                                       exprNode->reg.registerNumber);
  SymbolTableEntry *entry = variableNode->semantic_value.identifierSemanticValue.symbolTableEntry;
  TypeDescriptor *entryTD = entry->attribute->attr.typeDescriptor;
  /*
  switch (entryTD->kind) {
    case SCALAR_TYPE_DESCRIPTOR: {
      switch (entryTD->properties.dataType) {
        case INT_TYPE:
          fprintf(outputFile, "sd x%d, %d(fp)\n", variableNode->reg.registerNumber,
                                                  variableNode->offset);
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "fsw f%d, %d(fp)\n", variableNode->reg.registerNumber,
                                                   variableNode->offset);
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
      int elementOffset = 0;
      int currentArraySize = 1;
      for (int dim = arrayProp.dim; dim >= 0; dim--) {
         
      }
      switch (arrayProp.elementType) {
        case INT_TYPE: {
          break;
        }
        case FLOAT_TYPE: {
          break;
        }
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
  */
  RegFree(variableNode->reg);
  if (variableNode->reg.isCallerSaved) {
    TmpOffsetFree(variableNode->reg.isFloat,
                  variableNode->offset);
  }
  RegFree(exprNode->reg);
  if (exprNode->reg.isCallerSaved) {
    TmpOffsetFree(exprNode->reg.isFloat,
                  exprNode->offset);
  }
}

void CodegenIfStmt(AST_NODE *ifStmt) {
  assert(ifStmt->semantic_value.stmtSemanticValue.kind == IF_STMT);
  fprintf(outputFile, "## Codegen: If Stmt ##\n");
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
  RegClear();
  fprintf(outputFile, "jal _FUNCTION_%s\n", functionName);  
  SymbolTableEntry *entry = functionCallStmt->child->semantic_value.identifierSemanticValue.symbolTableEntry;
  DATA_TYPE returnType = entry->attribute->attr.functionSignature->returnType;
  bool isFloatType = false;
  switch (returnType) {
    case INT_TYPE:
      isFloatType = false;
      break;
    case FLOAT_TYPE:
      isFloatType = true;
      break;
    default:
      // this should not happen
      break;
  }
  functionCallStmt->offset = TmpOffsetGet(isFloatType); 
  functionCallStmt->reg = RegGet(isFloatType, true,
                                 functionCallStmt->offset);
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
    fprintf(outputFile, "mv x%d, a0\n", readFunctionCall->reg.registerNumber);
  }
  else if (!strcmp("fread", functionName)) {  // return float
    fprintf(outputFile, "call _read_float\n");
    readFunctionCall->offset = TmpOffsetGet(true);
    readFunctionCall->reg = RegGet(true, true, readFunctionCall->offset);
    fprintf(outputFile, "fmv.s x%d, fa0\n", readFunctionCall->reg.registerNumber);
  }
  else {
    // this should not happen
    assert(0);
  }
}

void CodegenWriteFunction(AST_NODE *writeFunctionCall) {
  fprintf(outputFile, "## Codegen: write() call Stmt ##\n");
  RegClear();
  AST_NODE *onlyParamNode = writeFunctionCall->child->rightSibling->child;
  CodegenExprRelated(onlyParamNode);
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
      fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
      fprintf(outputFile, "jal _write_%s\n", isIntType ? "int" : "float");
      break;
    }
    case CONST_VALUE_NODE: {
      fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
      switch (onlyParamNode->semantic_value.const1->const_type) {
        case INTEGERC:
          fprintf(outputFile, "jal _write_int\n");
          break;
        case FLOATC:
          fprintf(outputFile, "jal _write_float\n");
          break;
        case STRINGC:
          fprintf(outputFile, "jal _write_str\n");
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
      fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
      switch (returnType) {
        case INT_TYPE:
          fprintf(outputFile, "jal _write_int\n");
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "jal _write_float\n");
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
      fprintf(outputFile, "mv a0, x%d\n", onlyParamNode->reg.registerNumber);
      switch (onlyParamNode->dataType) {
        case INT_TYPE:
          fprintf(outputFile, "jal _write_int\n");
          break;
        case FLOAT_TYPE:
          fprintf(outputFile, "jal _write_float\n");
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
  RegFree(onlyParamNode->reg);
  if (onlyParamNode->reg.isCallerSaved) {
    TmpOffsetFree(onlyParamNode->reg.isFloat,
                  onlyParamNode->offset);
  }
}

void CodegenReturnStmt(AST_NODE *returnStmt) {
  assert(returnStmt->semantic_value.stmtSemanticValue.kind == RETURN_STMT);
  fprintf(outputFile, "## Codegen: Return Stmt ##\n");
  //fprintf(outputFile, "j _FUNCTION_END_%s\n");
}