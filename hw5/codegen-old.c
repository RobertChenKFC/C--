#include "codegen.h"
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* ========== global variables ========== */

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
    localVariableOffset -= size;
    arSize += size;
    VectorPushback(freeTmpOffsets, localVariableOffset);
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

  // local variable offset and AR size
  localVariableOffset = 0;
  arSize = 0;

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
      if (isFloat) {
        localVariableOffset -= 4;
        arSize += 4;
      } else {
        localVariableOffset -= 8;
        arSize += 8;
      }
      spillOffset = localVariableOffset;
      assert(savedRegisters);
      QueuePush(savedRegisters, spillRegister);
      assert(savedRegisterOffsets);
      QueuePush(savedRegisterOffsets, spillOffset);
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
  fprintf(outputFile, "ld ra, 8(fp)\n");
}

/* ========== register manager ========== */

/* ========== code generation ========== */

void CodegenProgramNode(AST_NODE *programNode) {
  // initialization is done here
  TmpOffsetInit();
  RegInit();
  outputFile = fopen("output.S", "w");

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
  fprintf(outputFile, "sd ra, 0(sp)\n");
  fprintf(outputFile, "sd fp, -8(sp)\n");
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
        CodegenExpr(dimNode);
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
void CodegenAssignStmt(AST_NODE *assignStmt) {}
void CodegenFunctionCallStmt(AST_NODE *functionCallStmt) {}
void CodegenFunctionDeclaration(AST_NODE *functionNode) {}
void CodegenVariableDeclaration(AST_NODE *variableNode) {}

