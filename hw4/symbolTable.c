#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// This file is for reference only, you are not required to follow the
// implementation. //

int HASH(char *str) {
  int idx = 0;
  while (*str) {
    idx = idx << 1;
    idx += *str;
    str++;
  }
  return (idx & (HASH_TABLE_SIZE - 1));
}

SymbolTable symbolTable;

SymbolTableEntry *newSymbolTableEntry(int nestingLevel) {
  SymbolTableEntry *symbolTableEntry =
      (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
  symbolTableEntry->nextInHashChain = NULL;
  symbolTableEntry->prevInHashChain = NULL;
  symbolTableEntry->nextInSameLevel = NULL;
  symbolTableEntry->sameNameInOuterLevel = NULL;
  symbolTableEntry->attribute = NULL;
  symbolTableEntry->name = NULL;
  symbolTableEntry->nestingLevel = nestingLevel;
  return symbolTableEntry;
}

void removeFromHashTrain(int hashIndex, SymbolTableEntry *entry) {
  if (entry->prevInHashChain)
    entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
  else
    symbolTable.hashTable[hashIndex] = NULL;
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry *entry) {
  SymbolTableEntry *nextEntry = symbolTable.hashTable[hashIndex];
  entry->nextInHashChain = nextEntry;
  if (nextEntry)
    nextEntry->prevInHashChain = entry;
  symbolTable.hashTable[hashIndex] = entry;
}

void initializeSymbolTable() {
  memset(symbolTable.hashTable, 0, sizeof(symbolTable.hashTable));
  symbolTable.scopeDisplay = malloc(sizeof(SymbolTableEntry*));
  symbolTable.scopeDisplay[0] = NULL;
  symbolTable.currentLevel = 0;
  symbolTable.scopeDisplayElementCount = 1;

  // insert default types
  openScope();
  // int
  TypeDescriptor *typeDescriptor = malloc(sizeof(TypeDescriptor));
  typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
  typeDescriptor->properties.dataType = INT_TYPE;
  SymbolAttribute *symbolAttribute = malloc(sizeof(SymbolAttribute));
  symbolAttribute->attributeKind = TYPE_ATTRIBUTE;
  symbolAttribute->attr.typeDescriptor = typeDescriptor;
  enterSymbol(SYMBOL_TABLE_INT_NAME, symbolAttribute);
  // float
  typeDescriptor = malloc(sizeof(TypeDescriptor));
  typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
  typeDescriptor->properties.dataType = FLOAT_TYPE;
  symbolAttribute = malloc(sizeof(SymbolAttribute));
  symbolAttribute->attributeKind = TYPE_ATTRIBUTE;
  symbolAttribute->attr.typeDescriptor = typeDescriptor;
  enterSymbol(SYMBOL_TABLE_FLOAT_NAME, symbolAttribute);
  // void
  typeDescriptor = malloc(sizeof(TypeDescriptor));
  typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
  typeDescriptor->properties.dataType = VOID_TYPE;
  symbolAttribute = malloc(sizeof(SymbolAttribute));
  symbolAttribute->attributeKind = TYPE_ATTRIBUTE;
  symbolAttribute->attr.typeDescriptor = typeDescriptor;
  enterSymbol(SYMBOL_TABLE_VOID_NAME, symbolAttribute);
  // read
  FunctionSignature *functionSignature = malloc(sizeof(FunctionSignature));
  functionSignature->parametersCount = 0;
  // TODO: figure out what the comment in Parameter struct means
  functionSignature->parameterList = NULL;
  functionSignature->returnType = INT_TYPE;
  symbolAttribute = malloc(sizeof(SymbolAttribute));
  symbolAttribute->attributeKind = FUNCTION_SIGNATURE;
  symbolAttribute->attr.functionSignature = functionSignature;
  enterSymbol(SYMBOL_TABLE_SYS_LIB_READ, symbolAttribute);
  // read
  functionSignature = malloc(sizeof(FunctionSignature));
  functionSignature->parametersCount = 0;
  // TODO: figure out what the comment in Parameter struct means
  functionSignature->parameterList = NULL;
  functionSignature->returnType = FLOAT_TYPE;
  symbolAttribute = malloc(sizeof(SymbolAttribute));
  symbolAttribute->attributeKind = FUNCTION_SIGNATURE;
  symbolAttribute->attr.functionSignature = functionSignature;
  enterSymbol(SYMBOL_TABLE_SYS_LIB_FREAD, symbolAttribute);
}

void symbolTableEnd() {
  // TODO: not sure what this function should do, but this currently deletes
  // the symbolTable and all its entries
  while (symbolTable.currentLevel >= 0)
    closeScope();
  free(symbolTable.scopeDisplay);
}

SymbolTableEntry *retrieveSymbol(char *symbolName) {
  int hashIndex = HASH(symbolName);
  SymbolTableEntry *entry = symbolTable.hashTable[hashIndex];
  while (entry) {
    if (strcmp(symbolName, entry->name) == 0)
      return entry;
    entry = entry->nextInHashChain;
  }
  return NULL;
}

SymbolTableEntry *enterSymbol(char *symbolName, SymbolAttribute *attribute) {
  SymbolTableEntry *prevEntry = retrieveSymbol(symbolName);
  if (prevEntry && prevEntry->nestingLevel == symbolTable.currentLevel)
    return NULL;

  SymbolTableEntry *entry = malloc(sizeof(SymbolTableEntry));
  int hashIndex = HASH(symbolName);
  enterIntoHashTrain(hashIndex, entry);
  entry->nextInSameLevel = symbolTable.scopeDisplay[symbolTable.currentLevel];
  symbolTable.scopeDisplay[symbolTable.currentLevel] = entry;
  entry->sameNameInOuterLevel = prevEntry;
  if (prevEntry) {
    hashIndex = HASH(prevEntry->name);
    removeFromHashTrain(hashIndex, prevEntry);
  }

  entry->name = symbolName;
  entry->attribute = attribute;
  entry->nestingLevel = symbolTable.currentLevel;
  return entry;
}

void freeEntry(SymbolTableEntry *entry) {
  switch (entry->attribute->attributeKind) {
    case VARIABLE_ATTRIBUTE:
    case TYPE_ATTRIBUTE:
      free(entry->attribute->attr.typeDescriptor);
      break;
    case FUNCTION_SIGNATURE: {
      Parameter *param = entry->attribute->attr.functionSignature->parameterList;
      while (param) {
        Parameter *nextParam = param->next;
        free(param);
        param = param->next;
      }
      free(entry->attribute->attr.functionSignature);
      break;
    }
  }
  free(entry->attribute);
  free(entry);
}

// remove the symbol from the current scope
void removeSymbol(char *symbolName) {
  SymbolTableEntry *entry = retrieveSymbol(symbolName);
  int hashIndex = HASH(symbolName);
  removeFromHashTrain(hashIndex, entry);

  // TODO: should we free the entry here? or keep it?
  freeEntry(entry);
}

int declaredLocally(char *symbolName) {
  SymbolTableEntry *entry = retrieveSymbol(symbolName);
  return entry && entry->nestingLevel == symbolTable.currentLevel;
}

void openScope() {
  ++symbolTable.currentLevel;
  if (symbolTable.currentLevel >= symbolTable.scopeDisplayElementCount) {
    symbolTable.scopeDisplayElementCount *= 2;
    symbolTable.scopeDisplay = realloc(symbolTable.scopeDisplay,
      sizeof(SymbolTableEntry*) * symbolTable.scopeDisplayElementCount);
  }
  symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
}

void closeScope() {
  SymbolTableEntry *entry = symbolTable.scopeDisplay[symbolTable.currentLevel];
  while (entry) {
    int hashIndex = HASH(entry->name);
    removeFromHashTrain(hashIndex, entry);
    SymbolTableEntry *prevEntry = entry->sameNameInOuterLevel;
    if (prevEntry) {
      hashIndex = HASH(prevEntry->name);
      enterIntoHashTrain(hashIndex, prevEntry);
    }
    SymbolTableEntry *nextEntry = entry->nextInSameLevel;
    // TODO: should we free the entry here? or keep it?
    freeEntry(entry);
    entry = nextEntry;
  }
  --symbolTable.currentLevel;
}
