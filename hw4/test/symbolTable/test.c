#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.h"

int main() {
  initializeSymbolTable();

  // 1. Check some default types before opening new scope
  SymbolTableEntry *entry = retrieveSymbol("int");
  assert(entry);
  assert(strcmp(entry->name, "int") == 0);
  assert(entry->attribute->attributeKind == TYPE_ATTRIBUTE);
  assert(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR);
  assert(entry->attribute->attr.typeDescriptor->properties.dataType == INT_TYPE);
  entry = retrieveSymbol("float");
  assert(entry);
  assert(strcmp(entry->name, "float") == 0);
  assert(entry->attribute->attributeKind == TYPE_ATTRIBUTE);
  assert(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR);
  assert(entry->attribute->attr.typeDescriptor->properties.dataType == FLOAT_TYPE);

  // 2. Open a scope and check some default types
  openScope();
  entry = retrieveSymbol("void");
  assert(entry);
  assert(strcmp(entry->name, "void") == 0);
  assert(entry->attribute->attributeKind == TYPE_ATTRIBUTE);
  assert(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR);
  assert(entry->attribute->attr.typeDescriptor->properties.dataType == VOID_TYPE);

  // 3. Enter a symbol which hides the default inserted symbol
  TypeDescriptor *typeDescriptor = malloc(sizeof(TypeDescriptor));
  typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
  typeDescriptor->properties.dataType = FLOAT_TYPE;
  SymbolAttribute *attribute = malloc(sizeof(SymbolAttribute));
  attribute->attributeKind = VARIABLE_ATTRIBUTE;
  attribute->attr.typeDescriptor = typeDescriptor;
  entry = enterSymbol("read", attribute);
  assert(entry);
  assert(strcmp(entry->name, "read") == 0);
  assert(entry->attribute == attribute);

  // 4. Enter a duplicate symbol
  typeDescriptor = malloc(sizeof(TypeDescriptor));
  typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
  typeDescriptor->properties.arrayProperties.dimension = 2;
  typeDescriptor->properties.arrayProperties.sizeInEachDimension[0] = 10;
  typeDescriptor->properties.arrayProperties.sizeInEachDimension[1] = 20;
  typeDescriptor->properties.arrayProperties.elementType = INT_TYPE;
  attribute = malloc(sizeof(SymbolAttribute));
  attribute->attributeKind = VARIABLE_ATTRIBUTE;
  attribute->attr.typeDescriptor = typeDescriptor;
  entry = enterSymbol("read", attribute);
  assert(!entry);
  free(typeDescriptor);
  free(attribute);

  // 5. Find a non-existing symbol
  entry = retrieveSymbol("hello");
  assert(!entry);

  // 6. Open several scopes and add new variables
  char varNames[26][4] = {0};
  for (int i = 0; i < 26; ++i) {
    if (i % 5 == 0) openScope();
    varNames[i][0] = 'a' + i;
    typeDescriptor = malloc(sizeof(TypeDescriptor));
    typeDescriptor->kind = SCALAR_TYPE_DESCRIPTOR;
    typeDescriptor->properties.dataType = INT_TYPE;
    attribute = malloc(sizeof(SymbolAttribute));
    attribute->attributeKind = VARIABLE_ATTRIBUTE;
    attribute->attr.typeDescriptor = typeDescriptor;
    entry = enterSymbol(varNames[i], attribute);
    assert(entry);
  }

  // 7. Check the added entries exists
  for (int i = 25; i >= 0; --i) {
    entry = retrieveSymbol(varNames[i]);
    assert(entry);
    if (i % 5 == 0) closeScope();
  }

  // 8. Check the removed entries don't exist
  for (int i = 0; i < 26; ++i) {
    entry = retrieveSymbol(varNames[i]);
    assert(!entry);
  }

  // 9. Check that closing a scope retains the original entry
  entry = retrieveSymbol("read");
  assert(entry);
  assert(entry->attribute->attributeKind == VARIABLE_ATTRIBUTE);
  assert(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR);
  assert(entry->attribute->attr.typeDescriptor->properties.dataType == FLOAT_TYPE);
  closeScope();
  entry = retrieveSymbol("read");
  assert(entry);
  assert(entry->attribute->attributeKind == FUNCTION_SIGNATURE);
  assert(!entry->attribute->attr.functionSignature->parameterList);
  assert(entry->attribute->attr.functionSignature->parametersCount == 0);
  assert(entry->attribute->attr.functionSignature->returnType == INT_TYPE);

  symbolTableEnd();
}

