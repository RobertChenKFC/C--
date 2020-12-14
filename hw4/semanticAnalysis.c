#include "header.h"
#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// This file is for reference only, you are not required to follow the
// implementation.
// You only need to check for errors stated in the hw4
// document.
int g_anyErrorOccur = 0;

// implement: 1, 3, 5, 7, 8, 9, 12, 13, 16, 20, 24, 25

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE *declarationNode);
void declareIdList(AST_NODE *typeNode,
                   SymbolAttributeKind isVariableOrTypeAttribute,
                   int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE *returnTypeNode);
// function prototype is changed
void processDeclDimList(AST_NODE *variableDeclDimList,
                        TypeDescriptor *typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE *typeNode);
void processBlockNode(AST_NODE *blockNode);
void processStmtNode(AST_NODE *stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE *assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE *whileNode);
void checkForStmt(AST_NODE *forNode);
void checkAssignmentStmt(AST_NODE *assignmentNode);
void checkIfStmt(AST_NODE *ifNode);
void checkWriteFunction(AST_NODE *functionCallNode);
void checkFunctionCall(AST_NODE *functionCallNode);
void processExprRelatedNode(AST_NODE *exprRelatedNode);
void checkParameterPassing(Parameter *formalParameter,
                           AST_NODE *actualParameter);
void checkReturnStmt(AST_NODE *returnNode);
void processExprNode(AST_NODE *exprNode);
void processVariableLValue(AST_NODE *idNode);
void processVariableRValue(AST_NODE *idNode);
void processConstValueNode(AST_NODE *constValueNode);
void getExprOrConstValue(AST_NODE *exprOrConstNode, int *iValue, float *fValue);
void evaluateExprValue(AST_NODE *exprNode);

/* ======= start of helper function declaration ======= */

#define NUL_DIM          -1
#define GRN              "\x1B[32m"
#define RST              "\x1B[0m"
#define MAX_ID_LEN       32
#define MAX_DIM_LEN      20
#define MAX_TYPE_STR_LEN (MAX_ID_LEN + MAX_ARRAY_DIMENSION * MAX_DIM_LEN)

typedef enum WarningMsgKind {
  FLOAT_TO_INT,
  ASSIGN_ARRAY_TO_SCALAR
} WarningMsgKind;

void getTypeString(TypeDescriptor *typeDescriptor, char *typeStr);
void printWarningMsg(AST_NODE *node, WarningMsgKind warningMsgType);

/* ======= end of helper function declaration ======= */

typedef enum ErrorMsgKind {
  SYMBOL_IS_NOT_TYPE,
  SYMBOL_REDECLARE,
  SYMBOL_UNDECLARED,
  NOT_FUNCTION_NAME,
  TRY_TO_INIT_ARRAY,
  EXCESSIVE_ARRAY_DIM_DECLARATION,
  RETURN_ARRAY,
  VOID_VARIABLE,
  TYPEDEF_VOID_ARRAY,
  PARAMETER_TYPE_UNMATCH,
  TOO_FEW_ARGUMENTS,
  TOO_MANY_ARGUMENTS,
  RETURN_TYPE_UNMATCH,
  INCOMPATIBLE_ARRAY_DIMENSION,
  NOT_ASSIGNABLE,
  NOT_ARRAY,
  IS_TYPE_NOT_VARIABLE,
  IS_FUNCTION_NOT_VARIABLE,
  STRING_OPERATION,
  ARRAY_SIZE_NOT_INT,
  ARRAY_SIZE_NEGATIVE,
  ARRAY_SUBSCRIPT_NOT_INT,
  PASS_ARRAY_TO_SCALAR,
  PASS_SCALAR_TO_ARRAY,
  // new error messages
  TYPEDEF_REDECLARE,
  NONCONST_GLOBAL_DECLARE,
  ASSIGN_STRING,
  INVALID_UNARY_EXPR,
  INVALID_BINARY_EXPR,
  INVALID_ASSIGNMENT
} ErrorMsgKind;

void printErrorMsgSpecial(AST_NODE *node1, char *name2,
                          ErrorMsgKind errorMsgKind) {
  g_anyErrorOccur = 1;
  printf("Error found in line %d\n", node1->linenumber);
  switch(errorMsgKind) {
    case TYPEDEF_REDECLARE: {
      // TODO: this is not ideal, maybe this should be implemented in another
      // function
      char *oldType = (char*)node1, *newType = name2;
      printf(GRN "typedef redefinition with different types ('%s' vs '%s')\n"
             RST, oldType, newType);
      break;
    } case INCOMPATIBLE_ARRAY_DIMENSION: {
      // TODO: this is not ideal, maybe this should be implemented in another
      // function
      char *lhsType = (char*)node1, *rhsType = name2;
      printf(GRN "incompatible pointer types passing '%s' to parameter of type "
             "'%s'\n" RST, rhsType, lhsType);
      break;
    } default: {
      printf("Unhandled case in void printErrorMsg(AST_NODE* node, "
             "ERROR_MSG_KIND* errorMsgKind)\n");
      break;
    }
  }
}

void printErrorMsg(AST_NODE *node, ErrorMsgKind errorMsgKind) {
  g_anyErrorOccur = 1;
  printf("Error found in line %d\n", node->linenumber);
  switch(errorMsgKind) {
    case SYMBOL_UNDECLARED: {
      printf(GRN "use of undeclared identifier '%s'\n" RST,
             node->semantic_value.identifierSemanticValue.identifierName);
      break;
    } case SYMBOL_REDECLARE: {
      printf(GRN "redefinition of '%s'\n" RST,
             node->semantic_value.identifierSemanticValue.identifierName);
      break;
    } case ARRAY_SIZE_NOT_INT: {
      printf(GRN "size of array has non integer type 'float'\n" RST);
      break;
    } case ARRAY_SIZE_NEGATIVE: {
      printf(GRN "'%s' declared as an array with a negative size\n" RST,
             node->semantic_value.identifierSemanticValue.identifierName);
      break;
    } case NONCONST_GLOBAL_DECLARE:
      printf(GRN "initializer element is not a compile-time constant\n" RST);
      break; {
    } case IS_FUNCTION_NOT_VARIABLE: {
      printf(GRN "non-object type '");
      SymbolTableEntry *entry =
          node->semantic_value.identifierSemanticValue.symbolTableEntry;
      FunctionSignature *functionSignature =
        entry->attribute->attr.functionSignature;
      switch (functionSignature->returnType) {
        case INT_TYPE:
          printf("int (");
          break;
        case FLOAT_TYPE:
          printf("float (");
          break;
        case VOID_TYPE:
          printf("void (");
          break;
        default:
          // this should not happen
          assert(0);
      }
      char typeStr[MAX_TYPE_STR_LEN];
      int separator = 0;
      for (Parameter *param = functionSignature->parameterList; param;
           param = param->next) {
        getTypeString(param->type, typeStr);
        if (separator) printf(", ");
        else separator = 1;
        printf("%s", typeStr);
      }
      printf(")' is not assignable\n" RST);
      break;
    } case NOT_ASSIGNABLE: {
      char typeStr[MAX_TYPE_STR_LEN];
      SymbolTableEntry *entry =
          node->semantic_value.identifierSemanticValue.symbolTableEntry;
      getTypeString(entry->attribute->attr.typeDescriptor, typeStr);
      printf(GRN "array type '%s' is not assignable\n" RST, typeStr);
      break;
    } case NOT_ARRAY: {
      printf(GRN "subscripted value is not an array, pointer, or vector\n" RST);
      break;
    } case NOT_FUNCTION_NAME: {
      char typeStr[MAX_TYPE_STR_LEN];
      getTypeString(node->semantic_value.identifierSemanticValue.
                    symbolTableEntry->attribute->attr.typeDescriptor, typeStr);
      printf(GRN "called object type '%s' is not a function or function "
             "pointer\n" RST, typeStr);
      break;
    } case TOO_MANY_ARGUMENTS:
      case TOO_FEW_ARGUMENTS:
      case PASS_ARRAY_TO_SCALAR:
      case PASS_SCALAR_TO_ARRAY: {
      printf(GRN "no matching function call for '%s'\n" RST,
             node->semantic_value.identifierSemanticValue.identifierName);
      break;
    } case INVALID_UNARY_EXPR: {
      // TODO: this error is not implemented completely since type information
      // isn't printed, but this error isn't mentioned in Assignment4 and it
      // requires some effort to get the type of the operand, so it is currently
      // skipped
      printf(GRN "invalid argument type to unary expression\n" RST);
      break;
    } case INVALID_BINARY_EXPR: {
      // TODO: this error is not implemented completely since type information
      // isn't printed, but this error isn't mentioned in Assignment4 and it
      // requires some effort to get the types of the operands, so it is
      // currently skipped
      printf(GRN "invalid operands to binary expression\n" RST);
      break;
    } case INVALID_ASSIGNMENT: {
      // TODO: this error is not implemented completely since type information
      // isn't printed, but this error isn't mentioned in Assignment4 and it
      // requires some effort to get the type of the operand, so it is
      // currently skipped
      printf(GRN "assigning to incompatible type\n" RST);
      break;
    } default: {
      printf("Unhandled case in void printErrorMsg(AST_NODE* node, "
             "ERROR_MSG_KIND* errorMsgKind)\n");
      break;
    }
  }
}

void semanticAnalysis(AST_NODE *root) { processProgramNode(root); }

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2) {
  switch (dataType1) {
    case INT_TYPE:
      switch (dataType2) {
        case INT_TYPE:   return INT_TYPE;
        case FLOAT_TYPE: return FLOAT_TYPE;
        default:         return ERROR_TYPE;
      }
    case FLOAT_TYPE: return FLOAT_TYPE;
    default:         return ERROR_TYPE;
  }
}

void processProgramNode(AST_NODE *programNode) {
  for (AST_NODE *child = programNode->child; child;
       child = child->rightSibling) {
    switch (child->nodeType) {
      case VARIABLE_DECL_LIST_NODE:
        for (AST_NODE *declNode = child->child; declNode;
             declNode = declNode->rightSibling)
          processDeclarationNode(declNode);
        break;
      case DECLARATION_NODE:
        processDeclarationNode(child);
        break;
      default:
        // this should not happen
        assert(0);
        break;
    }
  }
}

void processDeclarationNode(AST_NODE *declarationNode) {}

void processTypeNode(AST_NODE *idNodeAsType) {}


void declareIdList(AST_NODE *declarationNode,
                   SymbolAttributeKind isVariableOrTypeAttribute,
                   int ignoreArrayFirstDimSize) {
  AST_NODE *typeNode = declarationNode->child;
  SymbolTableEntry *typeEntry = retrieveSymbol(
      typeNode->semantic_value.identifierSemanticValue.identifierName);
  if (!typeEntry) {
    printErrorMsg(typeNode, SYMBOL_UNDECLARED);
    return;
  }
  if (typeEntry->attribute->attributeKind != TYPE_ATTRIBUTE) {
    // TODO: error message is not yet implemented because it isn't mentioned in
    // Assignment4 and there doesn't seem to be a clang equivalent
    printErrorMsg(typeNode, SYMBOL_IS_NOT_TYPE);
    return;
  }
  TypeDescriptor *typeDescriptor = typeEntry->attribute->attr.typeDescriptor;

  switch (isVariableOrTypeAttribute) {
    case VARIABLE_ATTRIBUTE:
      for (AST_NODE *variableDeclDimList = typeNode->rightSibling;
           variableDeclDimList;
           variableDeclDimList = variableDeclDimList->rightSibling)
        processDeclDimList(variableDeclDimList,
                           typeEntry->attribute->attr.typeDescriptor,
                           ignoreArrayFirstDimSize);
      break;
    case TYPE_ATTRIBUTE:
      for (AST_NODE *typeDeclDimList = typeNode->rightSibling;
           typeDeclDimList;
           typeDeclDimList = typeDeclDimList->rightSibling) {
        IdentifierSemanticValue *id =
          &typeDeclDimList->semantic_value.identifierSemanticValue;

        TypeDescriptor *newTypeDescriptor = malloc(sizeof(TypeDescriptor));
        switch (id->kind) {
          case NORMAL_ID:
            // directly copy old type to new type
            newTypeDescriptor->kind = typeDescriptor->kind;
            switch (typeDescriptor->kind) {
              case SCALAR_TYPE_DESCRIPTOR:
                newTypeDescriptor->properties.dataType =
                  typeDescriptor->properties.dataType;
                break;
              case ARRAY_TYPE_DESCRIPTOR:
                newTypeDescriptor->properties.arrayProperties =
                  typeDescriptor->properties.arrayProperties;
            }
            break;
          case ARRAY_ID:
            // concatenate old type dimensions into new type
            newTypeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
            newTypeDescriptor->properties.arrayProperties.elementType =
              typeDescriptor->properties.arrayProperties.elementType;
            ArrayProperties *arrayProperties =
              &typeDescriptor->properties.arrayProperties;
            ArrayProperties *newArrayProperties =
              &newTypeDescriptor->properties.arrayProperties;
            int dimIndex = 0;
            for (AST_NODE *dimNode = typeDeclDimList->child; dimNode;
                 dimNode = dimNode->rightSibling) {
              int dimVal;
              getExprOrConstValue(dimNode, &dimVal, NULL);
              if (dimNode->dataType != INT_TYPE) {
                printErrorMsg(typeDeclDimList, ARRAY_SIZE_NOT_INT);
                free(newTypeDescriptor);
                break;
              } else if (dimVal < 0) {
                printErrorMsg(typeDeclDimList, ARRAY_SIZE_NEGATIVE);
                free(newTypeDescriptor);
                break;
              }
              newArrayProperties->sizeInEachDimension[dimIndex++] = dimVal;
            }
            for (int i = 0; arrayProperties->dimension; ++i)
              newArrayProperties->sizeInEachDimension[dimIndex++] =
                arrayProperties->sizeInEachDimension[i];
            newArrayProperties->dimension = dimIndex;
          default:
            // this should not happen
            assert(0);
        }
        SymbolAttribute *newSymbolAttribute =
              malloc(sizeof(SymbolAttribute));
        newSymbolAttribute->attributeKind = TYPE_ATTRIBUTE;
        newSymbolAttribute->attr.typeDescriptor = newTypeDescriptor;
        if (!(id->symbolTableEntry =
              enterSymbol(id->identifierName, newSymbolAttribute))) {
          char oldTypeStr[MAX_TYPE_STR_LEN], newTypeStr[MAX_TYPE_STR_LEN];
          getTypeString(typeDescriptor, oldTypeStr);
          getTypeString(newTypeDescriptor, newTypeStr);
          printErrorMsgSpecial((AST_NODE*)oldTypeStr, newTypeStr,
                               TYPEDEF_REDECLARE);
          free(newTypeDescriptor);
          free(newSymbolAttribute);
          break;
        }
      }
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void checkAssignOrExpr(AST_NODE *assignOrExprRelatedNode) {}

void checkWhileStmt(AST_NODE *whileNode) {}

void checkForStmt(AST_NODE *forNode) {
  AST_NODE *initNode = forNode->child;
  switch (initNode->nodeType) {
    case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
      for (AST_NODE *exprNode = initNode->child; exprNode;
           exprNode = exprNode->rightSibling)
        processExprNode(exprNode);
      break;
    case NUL_NODE:
      break;
    default:
      // this should not happen
      assert(0);
  }

  AST_NODE *condNode = initNode->rightSibling;
  switch (condNode->nodeType) {
    case NONEMPTY_RELOP_EXPR_LIST_NODE:
      for (AST_NODE *exprNode = condNode->child; exprNode;
           exprNode = exprNode->rightSibling)
        processExprNode(exprNode);
      break;
    case NUL_NODE:
      break;
    default:
      // this should not happen
      assert(0);
  }

  AST_NODE *incNode = condNode->rightSibling;
  switch (incNode->nodeType) {
    case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
      for (AST_NODE *exprNode = incNode->child; exprNode;
           exprNode = exprNode->rightSibling)
        processExprNode(exprNode);
      break;
    case NUL_NODE:
      break;
    default:
      // this should not happen
      assert(0);
  }

  AST_NODE *bodyNode = incNode->rightSibling;
  switch (bodyNode->nodeType) {
    case STMT_NODE:
      processStmtNode(bodyNode);
      break;
    case BLOCK_NODE:
      processBlockNode(bodyNode);
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void checkAssignmentStmt(AST_NODE *assignmentNode) {
  // TODO: recheck processDeclarationNode WITH_INIT_ID
  AST_NODE *lhs = assignmentNode->child, *rhs = lhs->rightSibling;
  processVariableLValue(lhs);
  if (lhs->dataType == INT_PTR_TYPE || lhs->dataType == FLOAT_PTR_TYPE) {
    printErrorMsg(lhs, NOT_ASSIGNABLE);
    return;
  } else if (lhs->dataType != INT_TYPE && lhs->dataType != FLOAT_TYPE) {
    printErrorMsg(lhs, INVALID_ASSIGNMENT);
    return;
  }
  switch (rhs->nodeType) {
    case IDENTIFIER_NODE:
      processVariableRValue(rhs);
      if ((rhs->dataType != INT_TYPE && rhs->dataType != FLOAT_TYPE &&
           rhs->dataType != INT_PTR_TYPE && rhs->dataType != FLOAT_PTR_TYPE) ||
          (rhs->dataType == INT_PTR_TYPE && lhs->dataType == FLOAT_TYPE) ||
          (rhs->dataType == FLOAT_PTR_TYPE && lhs->dataType == INT_TYPE)) {
        printErrorMsg(lhs, INVALID_ASSIGNMENT);
        return;
      } else if ((rhs->dataType == INT_PTR_TYPE && lhs->dataType == INT_TYPE) ||
          (rhs->dataType == FLOAT_PTR_TYPE && lhs->dataType == FLOAT_TYPE)) {
        printWarningMsg(lhs, ASSIGN_ARRAY_TO_SCALAR);
      } else if (lhs->dataType == INT_TYPE && rhs->dataType == FLOAT_TYPE) {
        printWarningMsg(lhs, FLOAT_TO_INT);
      }
      break;
    case CONST_VALUE_NODE:
      switch (rhs->semantic_value.const1->const_type) {
        case STRINGC:
          // TODO: error message is not yet implemented because it isn't
          // mentioned in Assignment4 and there doesn't seem to be a clang
          // equivalent
          printErrorMsg(lhs, ASSIGN_STRING);
          return;
        case FLOATC:
          if (lhs->dataType == INT_TYPE)
            printWarningMsg(lhs, FLOAT_TO_INT);
          break;
        case INTEGERC:
          break;
      }
      break;
    case EXPR_NODE:
      processExprNode(rhs);
      if (lhs->dataType == INT_TYPE && rhs->dataType == FLOAT_TYPE)
        printWarningMsg(lhs, FLOAT_TO_INT);
      break;
    default:
      // this should not happen
      assert(0);
  }
}

void checkIfStmt(AST_NODE *ifNode) {}

void checkWriteFunction(AST_NODE *functionCallNode) {}

void checkFunctionCall(AST_NODE *functionCallNode) {
  AST_NODE *functionNameNode = functionCallNode->child;
  IdentifierSemanticValue *functionNameId =
    &functionNameNode->semantic_value.identifierSemanticValue;
  if (strcmp(functionNameId->identifierName, "write") == 0) {
    checkWriteFunction(functionCallNode);
    return;
  }

  SymbolTableEntry *entry = retrieveSymbol(functionNameId->identifierName);
  functionNameId->symbolTableEntry = entry;
  if (!entry) {
    printErrorMsg(functionNameNode, SYMBOL_UNDECLARED);
    return;
  } else if (entry->attribute->attributeKind != FUNCTION_SIGNATURE) {
    printErrorMsg(functionNameNode, NOT_FUNCTION_NAME);
    return;
  }

  AST_NODE *exprNode;
  Parameter *param;
  for (exprNode = functionNameNode->rightSibling,
       param = entry->attribute->attr.functionSignature->parameterList;
       exprNode && param;
       exprNode = exprNode->rightSibling, param = param->next);
  if (exprNode) {
    printErrorMsg(functionNameNode, TOO_MANY_ARGUMENTS);
    return;
  } else if (param) {
    printErrorMsg(functionNameNode, TOO_FEW_ARGUMENTS);
    return;
  }

  for (exprNode = functionNameNode->rightSibling,
       param = entry->attribute->attr.functionSignature->parameterList;
       exprNode && param;
       exprNode = exprNode->rightSibling, param = param->next) {
    switch (param->type->kind) {
      // expected parameter is a scalar type
      case SCALAR_TYPE_DESCRIPTOR:
        switch (exprNode->nodeType) {
          // passed parameter is a variable (scalar or array type)
          case IDENTIFIER_NODE: {
            IdentifierSemanticValue *id =
              &exprNode->semantic_value.identifierSemanticValue;
            SymbolTableEntry *entry = retrieveSymbol(id->identifierName);
            id->symbolTableEntry = entry;
            if (!entry) {
              printErrorMsg(exprNode, SYMBOL_UNDECLARED);
              goto NEXT_PARAM;
            } else if (entry->attribute->attributeKind == TYPE_ATTRIBUTE) {
              printErrorMsg(exprNode, IS_TYPE_NOT_VARIABLE);
              goto NEXT_PARAM;
            } else if (entry->attribute->attributeKind == FUNCTION_SIGNATURE) {
              printErrorMsg(exprNode, IS_FUNCTION_NOT_VARIABLE);
              goto NEXT_PARAM;
            }
            int numDim = 0;
            for (AST_NODE *dim = exprNode->child; dim; dim = dim->rightSibling)
              ++numDim;
            TypeDescriptor *idType = entry->attribute->attr.typeDescriptor;
            switch (idType->kind) {
              // passed parameter is a scalar variable
              case SCALAR_TYPE_DESCRIPTOR: {
                if (numDim > 0) {
                  printErrorMsg(exprNode, NOT_ARRAY);
                  goto NEXT_PARAM;
                } else if (exprNode->dataType == FLOAT_TYPE &&
                           param->type->properties.dataType == INT_TYPE)
                  printWarningMsg(exprNode, FLOAT_TO_INT);
                break;
              }
              // passed parameter is an array variable
              case ARRAY_TYPE_DESCRIPTOR: {
                ArrayProperties *arrayProperties =
                  &idType->properties.arrayProperties;
                if (numDim > arrayProperties->dimension) {
                  printErrorMsg(exprNode, NOT_ARRAY);
                  goto NEXT_PARAM;
                } else if (numDim < arrayProperties->dimension) {
                  printErrorMsg(exprNode, PASS_ARRAY_TO_SCALAR);
                  goto NEXT_PARAM;
                } else if (param->type->properties.dataType == INT_TYPE &&
                           arrayProperties->elementType == FLOAT_TYPE)
                  printWarningMsg(exprNode, FLOAT_TO_INT);
                break;
              }
            }
            break;
          }
          // passed parameter is a constant value (definitely a scalar)
          case CONST_VALUE_NODE: {
            switch (exprNode->semantic_value.const1->const_type) {
              case STRINGC:
                printErrorMsg(exprNode, ASSIGN_STRING);
                goto NEXT_PARAM;
              case INTEGERC:
                break;
              case FLOATC:
                if (param->type->properties.dataType == INT_TYPE)
                  printWarningMsg(exprNode, FLOAT_TO_INT);
                break;
            }
            break;
          }
          // passed parameter is a expression (definitely a scalar)
          case EXPR_NODE: {
            processExprNode(exprNode);
            if (exprNode->dataType == FLOAT_TYPE &&
                param->type->properties.dataType == INT_TYPE)
              printWarningMsg(exprNode, FLOAT_TO_INT);
            break;
          } default: {
            // this should not happen
            break;
          }
        }
        break;
      // expected parameter is an array type
      case ARRAY_TYPE_DESCRIPTOR:
        switch (exprNode->nodeType) {
          // passed parameter is a variable (scalar or array type)
          case IDENTIFIER_NODE: {
            IdentifierSemanticValue *id =
              &exprNode->semantic_value.identifierSemanticValue;
            SymbolTableEntry *entry = retrieveSymbol(id->identifierName);
            id->symbolTableEntry = entry;
            if (!entry) {
              printErrorMsg(exprNode, SYMBOL_UNDECLARED);
              goto NEXT_PARAM;
            } else if (entry->attribute->attributeKind == TYPE_ATTRIBUTE) {
              printErrorMsg(exprNode, IS_TYPE_NOT_VARIABLE);
              goto NEXT_PARAM;
            } else if (entry->attribute->attributeKind == FUNCTION_SIGNATURE) {
              printErrorMsg(exprNode, IS_FUNCTION_NOT_VARIABLE);
              goto NEXT_PARAM;
            }
            TypeDescriptor *idType = entry->attribute->attr.typeDescriptor;
            int numDim = 0;
            for (AST_NODE *dim = exprNode->child; dim; dim = dim->rightSibling)
              ++numDim;
            switch (idType->kind) {
              // passed parameter is a scalar variable
              case SCALAR_TYPE_DESCRIPTOR: {
                if (numDim > 0) {
                  printErrorMsg(exprNode, NOT_ARRAY);
                  goto NEXT_PARAM;
                }
                printErrorMsg(exprNode, PASS_SCALAR_TO_ARRAY);
                goto NEXT_PARAM;
              }
              // passed parameter is an array variable
              case ARRAY_TYPE_DESCRIPTOR: {
                ArrayProperties *idArrayProperties =
                  &idType->properties.arrayProperties;
                ArrayProperties *paramArrayProperties =
                  &param->type->properties.arrayProperties;
                if (numDim > idArrayProperties->dimension) {
                  printErrorMsg(exprNode, NOT_ARRAY);
                  goto NEXT_PARAM;
                } else if (idArrayProperties->dimension - numDim !=
                           paramArrayProperties->dimension) {
                  printErrorMsg(exprNode, INCOMPATIBLE_ARRAY_DIMENSION);
                  goto NEXT_PARAM;
                }
                for (int i = idArrayProperties->dimension - numDim;
                     i < numDim; ++i) {
                  if (paramArrayProperties->sizeInEachDimension[i] != NUL_DIM &&
                      idArrayProperties->sizeInEachDimension[i] !=
                      paramArrayProperties->sizeInEachDimension[i]) {
                    printErrorMsg(exprNode, INCOMPATIBLE_ARRAY_DIMENSION);
                    goto NEXT_PARAM;
                  }
                }
                break;
              }
            }
            break;
          }
          // passed parameter is a constant value (definitely a scalar type)
          case CONST_VALUE_NODE:
          // passed parameter is an expression (definitely a scalar type)
          case EXPR_NODE: {
            printErrorMsg(exprNode, PASS_SCALAR_TO_ARRAY);
            goto NEXT_PARAM;
          } default: {
            // this should not happen
            assert(0);
          }
        }
        break;
    }
NEXT_PARAM: ;
  }
}

void checkParameterPassing(Parameter *formalParameter,
                           AST_NODE *actualParameter) {}

void processExprRelatedNode(AST_NODE *exprRelatedNode) {}

void getExprOrConstValue(AST_NODE *exprOrConstNode, int *iValue,
                         float *fValue) {
  switch (exprOrConstNode->nodeType) {
    case CONST_VALUE_NODE: {
      CON_Type *constant = exprOrConstNode->semantic_value.const1;
      switch (constant->const_type) {
        case INTEGERC:
          if (iValue) *iValue = constant->const_u.intval;
          break;
        case FLOATC:
          if (fValue) *fValue = constant->const_u.fval;
          break;
        default:
          break;
      }
      break;
    } case EXPR_NODE: {
      processExprNode(exprOrConstNode);
      EXPRSemanticValue *expr =
        &exprOrConstNode->semantic_value.exprSemanticValue;
      if (expr->isConstEval) {
        switch (exprOrConstNode->dataType) {
          case INT_TYPE:
            if (iValue) *iValue = expr->constEvalValue.iValue;
            break;
          case FLOAT_TYPE:
            if (fValue) *fValue = expr->constEvalValue.fValue;
            break;
          default:
            break;
        }
      }
      break;
    } default : {
      break;
    }
  }
}

void evaluateExprValue(AST_NODE *exprNode) {
  processExprNode(exprNode);
}

void processExprNode(AST_NODE *exprNode) {
  switch (exprNode->nodeType) {
    case IDENTIFIER_NODE: {
      processVariableRValue(exprNode);
      break;
    } case CONST_VALUE_NODE: {
      CON_Type *constant = exprNode->semantic_value.const1;
      switch (constant->const_type) {
        case STRINGC:
          exprNode->dataType = CONST_STRING_TYPE;
          break;
        case INTEGERC:
          exprNode->dataType = INT_TYPE;
          break;
        case FLOATC:
          exprNode->dataType = FLOAT_TYPE;
          break;
      }
      break;
    } case EXPR_NODE: {
      EXPRSemanticValue *expr = &exprNode->semantic_value.exprSemanticValue;
      switch (expr->kind) {
        case BINARY_OPERATION: {
          AST_NODE *leftOperandNode = exprNode->child,
                   *rightOperandNode = leftOperandNode->rightSibling;
          processExprNode(leftOperandNode);
          processExprNode(rightOperandNode);
          int leftOperandIVal, rightOperandIVal;
          float leftOperandFVal, rightOperandFVal;
          exprNode->dataType = getBiggerType(leftOperandNode->dataType,
                                             rightOperandNode->dataType);
          switch (leftOperandNode->nodeType) {
            // left operand is a variable, then the whole expression cannot be
            // constant
            case IDENTIFIER_NODE:
              expr->isConstEval = 0;
              break;
            // left operand is constant value, then it depends on the right
            // operand
            case CONST_VALUE_NODE:
              switch (leftOperandNode->semantic_value.const1->const_type) {
                case STRINGC:
                  break;
                case INTEGERC:
                  leftOperandIVal =
                    leftOperandNode->semantic_value.const1->const_u.intval;
                  break;
                case FLOATC:
                  leftOperandFVal =
                    leftOperandNode->semantic_value.const1->const_u.fval;
                  break;
              }
              switch (rightOperandNode->nodeType) {
                // right operand is a variable, then the whole expression is not
                // constant
                case IDENTIFIER_NODE:
                  expr->isConstEval = 0;
                  break;
                // right operand is a constant value, then the whole expression
                // is constant
                case CONST_VALUE_NODE:
                  expr->isConstEval = 1;
                  switch (rightOperandNode->semantic_value.const1->const_type) {
                    case STRINGC:
                      break;
                    case INTEGERC:
                      rightOperandIVal = rightOperandNode->semantic_value.
                                         const1->const_u.intval;
                      break;
                    case FLOATC:
                      rightOperandFVal = rightOperandNode->semantic_value.
                                         const1->const_u.fval;
                      break;
                  }
                  break;
                // right operand is an expression, then it depends on whether
                // the expression is a constant expression
                case EXPR_NODE:
                  expr->isConstEval = rightOperandNode->semantic_value.
                                      exprSemanticValue.isConstEval;
                  if (expr->isConstEval) {
                    switch (rightOperandNode->dataType) {
                      case INT_TYPE:
                        rightOperandIVal = rightOperandNode->semantic_value.
                          exprSemanticValue.constEvalValue.iValue;
                        break;
                      case FLOAT_TYPE:
                        rightOperandFVal = rightOperandNode->semantic_value.
                          exprSemanticValue.constEvalValue.fValue;
                        break;
                      default:
                        break;
                    }
                  }
                  break;
                default:
                  // this should not happen
                  assert(0);
              }
              break;
            // left operand is expression, then it depends on whether the left
            // expression is a constant expression
            case EXPR_NODE:
              if (leftOperandNode->semantic_value.exprSemanticValue.
                  isConstEval) {
                switch (leftOperandNode->dataType) {
                  case INT_TYPE:
                    leftOperandIVal = leftOperandNode->semantic_value.
                      exprSemanticValue.constEvalValue.iValue;
                    break;
                  case FLOAT_TYPE:
                    leftOperandFVal = leftOperandNode->semantic_value.
                      exprSemanticValue.constEvalValue.fValue;
                    break;
                  default:
                    break;
                }
                // left expression is constant, so it depends on whether the
                // right operand is constant
                switch (rightOperandNode->nodeType) {
                  // right operand is a variable, then the whole expression is
                  // not constant
                  case IDENTIFIER_NODE:
                    expr->isConstEval = 0;
                    break;
                  // right operand is a constant value, then the whole
                  // expression is not constant
                  case CONST_VALUE_NODE:
                    expr->isConstEval = 1;
                    switch (rightOperandNode->semantic_value.const1->
                            const_type) {
                      case STRINGC:
                        break;
                      case INTEGERC:
                        rightOperandIVal = rightOperandNode->semantic_value.
                                           const1->const_u.intval;
                        break;
                      case FLOATC:
                        rightOperandFVal = rightOperandNode->semantic_value.
                                           const1->const_u.fval;
                        break;
                    }
                    break;
                  // right operand is an expression, then it depends on whether
                  // the right expression is a constant expression
                  case EXPR_NODE:
                    expr->isConstEval = rightOperandNode->semantic_value.
                      exprSemanticValue.isConstEval;
                    if (expr->isConstEval) {
                      switch (rightOperandNode->dataType) {
                        case INT_TYPE:
                          rightOperandIVal = rightOperandNode->semantic_value.
                            exprSemanticValue.constEvalValue.iValue;
                          break;
                        case FLOAT_TYPE:
                          rightOperandFVal = rightOperandNode->semantic_value.
                            exprSemanticValue.constEvalValue.fValue;
                          break;
                        default:
                          break;
                      }
                    }
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
              } else {
                expr->isConstEval = 0;
              }
              break;
            default:
              // this should not happen
              assert(0);
          }
          if (exprNode->dataType == ERROR_TYPE) {
            printErrorMsg(exprNode, INVALID_BINARY_EXPR);
            return;
          }
          if (expr->isConstEval) {
            switch (leftOperandNode->dataType) {
              case INT_TYPE:
                switch (rightOperandNode->dataType) {
                  case INT_TYPE:
                    switch (expr->op.binaryOp) {
                      case BINARY_OP_ADD:
                        expr->constEvalValue.iValue = leftOperandIVal +
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_SUB:
                        expr->constEvalValue.iValue = leftOperandIVal -
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_MUL:
                        expr->constEvalValue.iValue = leftOperandIVal *
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_DIV:
                        expr->constEvalValue.iValue = leftOperandIVal /
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_EQ:
                        expr->constEvalValue.iValue = leftOperandIVal ==
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_GE:
                        expr->constEvalValue.iValue = leftOperandIVal >=
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_LE:
                        expr->constEvalValue.iValue = leftOperandIVal <=
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_NE:
                        expr->constEvalValue.iValue = leftOperandIVal !=
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_GT:
                        expr->constEvalValue.iValue = leftOperandIVal >
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_LT:
                        expr->constEvalValue.iValue = leftOperandIVal <
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_AND:
                        expr->constEvalValue.iValue = leftOperandIVal &&
                                                      rightOperandIVal;
                        break;
                      case BINARY_OP_OR:
                        expr->constEvalValue.iValue = leftOperandIVal ||
                                                      rightOperandIVal;
                        break;
                    }
                    break;
                  case FLOAT_TYPE:
                    switch (expr->op.binaryOp) {
                      case BINARY_OP_ADD:
                        expr->constEvalValue.fValue = (float)leftOperandIVal +
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_SUB:
                        expr->constEvalValue.fValue = (float)leftOperandIVal -
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_MUL:
                        expr->constEvalValue.fValue = (float)leftOperandIVal *
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_DIV:
                        expr->constEvalValue.fValue = (float)leftOperandIVal /
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_EQ:
                        expr->constEvalValue.fValue = (float)leftOperandIVal ==
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_GE:
                        expr->constEvalValue.fValue = (float)leftOperandIVal >=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_LE:
                        expr->constEvalValue.fValue = (float)leftOperandIVal <=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_NE:
                        expr->constEvalValue.fValue = (float)leftOperandIVal !=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_GT:
                        expr->constEvalValue.fValue = (float)leftOperandIVal >
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_LT:
                        expr->constEvalValue.fValue = (float)leftOperandIVal <
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_AND:
                        expr->constEvalValue.fValue = (float)leftOperandIVal &&
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_OR:
                        expr->constEvalValue.fValue = (float)leftOperandIVal ||
                                                      rightOperandFVal;
                        break;
                    }
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
                break;
              case FLOAT_TYPE:
                switch (rightOperandNode->dataType) {
                  case INT_TYPE:
                    switch (expr->op.binaryOp) {
                      case BINARY_OP_ADD:
                        expr->constEvalValue.fValue = leftOperandFVal +
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_SUB:
                        expr->constEvalValue.fValue = leftOperandFVal -
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_MUL:
                        expr->constEvalValue.fValue = leftOperandFVal *
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_DIV:
                        expr->constEvalValue.fValue = leftOperandFVal /
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_EQ:
                        expr->constEvalValue.fValue = leftOperandFVal ==
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_GE:
                        expr->constEvalValue.fValue = leftOperandFVal >=
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_LE:
                        expr->constEvalValue.fValue = leftOperandFVal <=
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_NE:
                        expr->constEvalValue.fValue = leftOperandFVal !=
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_GT:
                        expr->constEvalValue.fValue = leftOperandFVal >
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_LT:
                        expr->constEvalValue.fValue = leftOperandFVal <
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_AND:
                        expr->constEvalValue.fValue = leftOperandFVal &&
                                                      (float)rightOperandIVal;
                        break;
                      case BINARY_OP_OR:
                        expr->constEvalValue.fValue = leftOperandFVal ||
                                                      (float)rightOperandIVal;
                        break;
                    }
                    break;
                  case FLOAT_TYPE:
                    switch (expr->op.binaryOp) {
                      case BINARY_OP_ADD:
                        expr->constEvalValue.fValue = leftOperandFVal +
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_SUB:
                        expr->constEvalValue.fValue = leftOperandFVal -
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_MUL:
                        expr->constEvalValue.fValue = leftOperandFVal *
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_DIV:
                        expr->constEvalValue.fValue = leftOperandFVal /
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_EQ:
                        expr->constEvalValue.fValue = leftOperandFVal ==
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_GE:
                        expr->constEvalValue.fValue = leftOperandFVal >=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_LE:
                        expr->constEvalValue.fValue = leftOperandFVal <=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_NE:
                        expr->constEvalValue.fValue = leftOperandFVal !=
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_GT:
                        expr->constEvalValue.fValue = leftOperandFVal >
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_LT:
                        expr->constEvalValue.fValue = leftOperandFVal <
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_AND:
                        expr->constEvalValue.fValue = leftOperandFVal &&
                                                      rightOperandFVal;
                        break;
                      case BINARY_OP_OR:
                        expr->constEvalValue.fValue = leftOperandFVal ||
                                                      rightOperandFVal;
                        break;
                    }
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
          break;
        } case UNARY_OPERATION: {
          AST_NODE *operandNode = exprNode->child;
          processExprNode(operandNode);
          int operandIVal;
          float operandFVal;
          switch (operandNode->nodeType) {
            case IDENTIFIER_NODE:
              expr->isConstEval = 0;
              exprNode->dataType = operandNode->dataType;
              break;
            case CONST_VALUE_NODE:
              switch (operandNode->semantic_value.const1->const_type) {
                case STRINGC:
                  expr->isConstEval = 0;
                  exprNode->dataType = ERROR_TYPE;
                  break;
                case INTEGERC:
                  expr->isConstEval = 1;
                  operandIVal =
                    operandNode->semantic_value.const1->const_u.intval;
                  exprNode->dataType = INT_TYPE;
                  break;
                case FLOATC:
                  expr->isConstEval = 1;
                  operandFVal =
                    operandNode->semantic_value.const1->const_u.fval;
                  exprNode->dataType = FLOAT_TYPE;
                  break;
              }
              break;
            case EXPR_NODE:
              switch (operandNode->dataType) {
                case INT_TYPE:
                  if (operandNode->semantic_value.exprSemanticValue.
                      isConstEval) {
                    expr->isConstEval = 1;
                    operandIVal = operandNode->semantic_value.exprSemanticValue.
                                  constEvalValue.iValue;
                  } else {
                    expr->isConstEval = 0;
                  }
                  exprNode->dataType = INT_TYPE;
                  break;
                case FLOAT_TYPE:
                  if (expr->isConstEval) {
                    expr->isConstEval = 1;
                    operandFVal = operandNode->semantic_value.exprSemanticValue.
                                  constEvalValue.fValue;
                  } else {
                    expr->isConstEval = 0;
                  }
                  exprNode->dataType = FLOAT_TYPE;
                  break;
                default:
                  expr->isConstEval = 0;
                  exprNode->dataType = ERROR_TYPE;
              }
              break;
            default:
              // this should not happen
              assert(0);
          }
          if (exprNode->dataType == ERROR_TYPE) {
            printErrorMsg(exprNode, INVALID_UNARY_EXPR);
            return;
          }
          if (expr->isConstEval) {
            switch (expr->op.unaryOp) {
              case UNARY_OP_POSITIVE:
                switch (exprNode->dataType) {
                  case INT_TYPE:
                    expr->constEvalValue.iValue = operandIVal;
                    break;
                  case FLOAT_TYPE:
                    expr->constEvalValue.fValue = operandFVal;
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
                break;
              case UNARY_OP_NEGATIVE:
                switch (exprNode->dataType) {
                  case INT_TYPE:
                    expr->constEvalValue.iValue = -operandIVal;
                    break;
                  case FLOAT_TYPE:
                    expr->constEvalValue.fValue = -operandFVal;
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
                break;
              case UNARY_OP_LOGICAL_NEGATION:
                switch (exprNode->dataType) {
                  case INT_TYPE:
                    expr->constEvalValue.iValue = !operandIVal;
                    break;
                  case FLOAT_TYPE:
                    expr->constEvalValue.iValue = !operandFVal;
                    exprNode->dataType = INT_TYPE;
                    break;
                  default:
                    // this should not happen
                    assert(0);
                }
                break;
            }
          }
          break;
        }
      }
      break;
    } default: {
      // this should not happen
      assert(0);
    }
  }
}

void processVariableLValue(AST_NODE *idNode) {}

void processVariableRValue(AST_NODE *idNode) {}

void processConstValueNode(AST_NODE *constValueNode) {}

void checkReturnStmt(AST_NODE *returnNode) {}

void processBlockNode(AST_NODE *blockNode) {
  if (!(blockNode->parent->nodeType == DECLARATION_NODE &&
        blockNode->parent->semantic_value.declSemanticValue.kind ==
        FUNCTION_DECL))
    openScope();
  for (AST_NODE *child = blockNode->child; child; child = child->rightSibling) {
    switch (child->nodeType) {
      case VARIABLE_DECL_LIST_NODE:
        for (AST_NODE *declNode = child->child; declNode;
             declNode = declNode->rightSibling)
          processDeclarationNode(declNode);
        break;
      case STMT_LIST_NODE:
        for (AST_NODE *stmtNode = child->child; stmtNode;
             stmtNode = stmtNode->rightSibling)
          processStmtNode(stmtNode);
        break;
      default:
        // this should not happen
        assert(0);
    }
  }
  closeScope();
}

void processStmtNode(AST_NODE *stmtNode) {
  switch (stmtNode->semantic_value.stmtSemanticValue.kind) {
    case WHILE_STMT:
      checkWhileStmt(stmtNode);
      break;
    case FOR_STMT:
      checkForStmt(stmtNode);
      break;
    case ASSIGN_STMT:
      checkAssignmentStmt(stmtNode);
      break;
    case IF_STMT:
      checkIfStmt(stmtNode);
      break;
    case FUNCTION_CALL_STMT:
      checkFunctionCall(stmtNode);
      break;
    case RETURN_STMT:
      checkReturnStmt(stmtNode);
      break;
  }
}

void processGeneralNode(AST_NODE *node) {
  switch (node->nodeType) {
    case PROGRAM_NODE:
      processProgramNode(node);
      break;
    case DECLARATION_NODE:
      processDeclarationNode(node);
      break;
    case IDENTIFIER_NODE:
      // this should not happen; processGeneralNode cannot determine what to
      // do with just an identifier node
      assert(0);
    case PARAM_LIST_NODE:
      // this should be processed in declareFunction, but just in case
      // processGeneralNode is called instead, we still implement it; note that
      // opening scope isn't handled here
      for (AST_NODE *declNode = node->child; declNode;
           declNode = declNode->rightSibling)
        processDeclarationNode(declNode);
      break;
    case NUL_NODE:
      break;
    case BLOCK_NODE:
      processBlockNode(node);
      break;
    case VARIABLE_DECL_LIST_NODE:
      // this should be processed in processProgramNode or processBlockNode,
      // but just in case processGeneralNode is called instead, we still
      // implement it
      for (AST_NODE *declNode = node->child; declNode;
           declNode = declNode->rightSibling)
        processDeclarationNode(declNode);
      break;
    case STMT_LIST_NODE:
      // this should be processed in processBlockNode, but just in case
      // processGeneralNode is called instead, we still implement it
      for (AST_NODE *stmtNode = node->child; stmtNode;
           stmtNode = stmtNode->rightSibling)
        processStmtNode(stmtNode);
      break;
    case STMT_NODE:
      processStmtNode(node);
      break;
    case EXPR_NODE:
      processExprNode(node);
      break;
    case CONST_VALUE_NODE:
      processConstValueNode(node);
      break;
    case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
      for (AST_NODE *exprNode = node->child; exprNode;
           exprNode = exprNode->rightSibling)
        processExprNode(exprNode);
      break;
    case NONEMPTY_RELOP_EXPR_LIST_NODE:
      for (AST_NODE *exprNode = node->child; exprNode;
           exprNode = exprNode->rightSibling)
        processExprNode(exprNode);
      break;
  }
}

void processDeclDimList(AST_NODE *idNode,
                        TypeDescriptor *typeDescriptor,
                        int ignoreFirstDimSize) {
  IdentifierSemanticValue *id = &idNode->semantic_value.identifierSemanticValue;
  TypeDescriptor *newTypeDescriptor = malloc(sizeof(TypeDescriptor));
  AST_NODE *initIDNode = NULL;
  switch (id->kind) {
    case NORMAL_ID: {
      newTypeDescriptor->kind = typeDescriptor->kind;
      switch (typeDescriptor->kind) {
        case SCALAR_TYPE_DESCRIPTOR:
          newTypeDescriptor->properties.dataType =
            typeDescriptor->properties.dataType;
          break;
        case ARRAY_TYPE_DESCRIPTOR:
          newTypeDescriptor->properties.arrayProperties =
            typeDescriptor->properties.arrayProperties;
          break;
      }
      break;
    } case ARRAY_ID: {
      newTypeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
      ArrayProperties *newArrayProperties =
        &newTypeDescriptor->properties.arrayProperties;
      int dimIndex = 0;
      for (AST_NODE *dimNode = idNode->child; dimNode; dimNode = dimNode) {
        switch (dimNode->nodeType) {
          case EXPR_NODE:
          case CONST_VALUE_NODE: {
            int dimVal;
            getExprOrConstValue(dimNode, &dimVal, NULL);
            if (dimNode->dataType != INT_TYPE) {
              printErrorMsg(idNode, ARRAY_SIZE_NOT_INT);
              return;
            } else if (dimVal < 0) {
              printErrorMsg(idNode, ARRAY_SIZE_NEGATIVE);
              return;
            }
            newArrayProperties->sizeInEachDimension[dimIndex++] = dimVal;
            break;
          } case NUL_NODE: {
            newArrayProperties->sizeInEachDimension[dimIndex++] = NUL_DIM;
            break;
          } default: {
            // this should not happen
            assert(0);
          }
        }
      }
      switch (typeDescriptor->kind) {
        case SCALAR_TYPE_DESCRIPTOR: {
          break;
        } case ARRAY_TYPE_DESCRIPTOR: {
          ArrayProperties *arrayProperties =
            &typeDescriptor->properties.arrayProperties;
          for (int i = 0; i < arrayProperties->dimension; ++i)
            newArrayProperties->sizeInEachDimension[dimIndex++] =
              arrayProperties->sizeInEachDimension[i];
          break;
        }
      }
      newArrayProperties->dimension = dimIndex;
      break;
    } case WITH_INIT_ID: {
      newTypeDescriptor->kind = typeDescriptor->kind;
      switch (typeDescriptor->kind) {
        case SCALAR_TYPE_DESCRIPTOR:
          newTypeDescriptor->properties.dataType =
            typeDescriptor->properties.dataType;
          break;
        case ARRAY_TYPE_DESCRIPTOR:
          newTypeDescriptor->properties.arrayProperties =
            typeDescriptor->properties.arrayProperties;
          break;
      }
      AST_NODE *initExpr = idNode->child;
      getExprOrConstValue(initExpr, NULL, NULL);
      if (isGlobalScope() &&
          !initExpr->semantic_value.exprSemanticValue.isConstEval) {
        printErrorMsg(idNode, NONCONST_GLOBAL_DECLARE);
        break;
      }
      processVariableLValue(idNode);
      processVariableRValue(initExpr);
      DATA_TYPE lhsType = typeDescriptor->properties.dataType,
                rhsType = initExpr->dataType;
      if (lhsType == INT_PTR_TYPE || lhsType == FLOAT_PTR_TYPE) {
        printErrorMsg(idNode, NOT_ASSIGNABLE);
        return;
      } else if (lhsType != INT_TYPE && lhsType != FLOAT_TYPE) {
        printErrorMsg(idNode, INVALID_ASSIGNMENT);
        return;
      } else if ((rhsType != INT_TYPE && rhsType != FLOAT_TYPE &&
           rhsType != INT_PTR_TYPE && rhsType != FLOAT_PTR_TYPE) ||
          (rhsType == INT_PTR_TYPE && lhsType == FLOAT_TYPE) ||
          (rhsType == FLOAT_PTR_TYPE && lhsType == INT_TYPE)) {
        printErrorMsg(idNode, INVALID_ASSIGNMENT);
        return;
      } else if ((rhsType == INT_PTR_TYPE && lhsType == INT_TYPE) ||
                 (rhsType == FLOAT_PTR_TYPE && lhsType == FLOAT_TYPE)) {
        printWarningMsg(idNode, ASSIGN_ARRAY_TO_SCALAR);
      } else if (lhsType == INT_TYPE && rhsType == FLOAT_TYPE) {
        printWarningMsg(idNode, FLOAT_TO_INT);
      }
      break;
    }
  }
  SymbolAttribute *newSymbolAttribute = malloc(sizeof(SymbolAttribute));
  newSymbolAttribute->attributeKind = VARIABLE_ATTRIBUTE;
  newSymbolAttribute->attr.typeDescriptor = newTypeDescriptor;
  SymbolTableEntry *entry = enterSymbol(id->identifierName, newSymbolAttribute);
  if (!entry) {
    printErrorMsg(idNode, SYMBOL_REDECLARE);
    free(newTypeDescriptor);
    free(newSymbolAttribute);
  }
}

void declareFunction(AST_NODE *declarationNode) {}

/* ======= start of helper functions definitions ======= */

void getTypeString(TypeDescriptor *typeDescriptor, char *dimStr) {
  switch (typeDescriptor->kind) {
    case SCALAR_TYPE_DESCRIPTOR: {
      switch (typeDescriptor->properties.dataType) {
        case INT_TYPE:
          sprintf(dimStr, "int");
          break;
        case FLOAT_TYPE:
          sprintf(dimStr, "float");
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    } case ARRAY_TYPE_DESCRIPTOR: {
      ArrayProperties *arrayProperties =
        &typeDescriptor->properties.arrayProperties;
      switch (arrayProperties->elementType) {
        case INT_TYPE:
          dimStr += sprintf(dimStr, "int ");
          break;
        case FLOAT_TYPE:
          dimStr += sprintf(dimStr, "float ");
          break;
        default:
          // this should not happen
          assert(0);
      }
      for (int i = 0; i < arrayProperties->dimension; ++i) {
        if (arrayProperties->sizeInEachDimension[i] == NUL_DIM)
          dimStr += sprintf(dimStr, "[]");
        else
          dimStr += sprintf(dimStr, "[%d]",
                            arrayProperties->sizeInEachDimension[i]);
      }
      break;
    }
  }
}

void printWarningMsg(AST_NODE *node, WarningMsgKind warningMsgType) {
  printf("Warning found in line %d\n", node->linenumber);
  switch (warningMsgType) {
    case FLOAT_TO_INT:
      // TODO: this is not ideal; for instance, the following code
      //   typedef int INT;
      //   typedef float FLOAT;
      //   FLOAT i = 10;
      //   INT j = i;
      // should generate the warning:
      //   implicit conversion turns floating-point number into integer:
      //   'FLOAT' to 'INT'
      // but we generate the following warning instead:
      //   implicit conversion turns floating-point number into integer:
      //   'float' to 'int'
      printf(GRN "implicit conversion turns floating-point number into "
             "integer: 'float' to 'int" RST);
      break;
    case ASSIGN_ARRAY_TO_SCALAR:
      // TODO: this warning is not implemented completely since type information
      // isn't printed, but this warning isn't mentioned in Assignment4 and it
      // requires some effort to get the type of the operand, so it is
      // currently skipped
      printf(GRN "incompatible pointer to integer conversion\n" RST);
      break;
  }
}

/* ======= end of helper functions definitions ======= */

// This function can be ignored; it was implemented before realising that
// processVariableLValue and processVariableRValue are exactly what is needed.
// This function is kept here to clarify what has to be implemented in those
// two respective functions.
void checkLHSandRHS(AST_NODE *lhs, AST_NODE *rhs) {
  IdentifierSemanticValue *lhsId = &lhs->semantic_value.identifierSemanticValue;
  SymbolTableEntry *entry = lhsId->symbolTableEntry;
  if (!entry) {
    printErrorMsg(lhs, SYMBOL_UNDECLARED);
    return;
  } else if (entry->attribute->attributeKind == TYPE_ATTRIBUTE) {
    // TODO: error message is not yet implemented because it isn't mentioned in
    // Assignment4 and there doesn't seem to be a clang equivalent
    printErrorMsg(lhs, IS_TYPE_NOT_VARIABLE);
    return;
  } else if (entry->attribute->attributeKind == FUNCTION_SIGNATURE) {
    printErrorMsg(lhs, IS_FUNCTION_NOT_VARIABLE);
    return;
  }

  switch (lhsId->kind) {
    case NORMAL_ID:
      switch (rhs->nodeType) {
        case IDENTIFIER_NODE: {
          IdentifierSemanticValue *rhsId =
            &rhs->semantic_value.identifierSemanticValue;
          SymbolTableEntry *entry = rhsId->symbolTableEntry;
          if (!entry) {
            printErrorMsg(rhs, SYMBOL_UNDECLARED);
            return;
          } else if (entry->attribute->attributeKind == TYPE_ATTRIBUTE) {
            printErrorMsg(rhs, IS_TYPE_NOT_VARIABLE);
            return;
          } else if (entry->attribute->attributeKind == FUNCTION_SIGNATURE) {
            printErrorMsg(rhs, IS_FUNCTION_NOT_VARIABLE);
            break;
          }
          TypeDescriptor *rhsType = entry->attribute->attr.typeDescriptor;
          int numDim = 0;
          for (AST_NODE *dim = rhs->child; dim; dim = dim->rightSibling)
            ++numDim;
          switch (rhsType->kind) {
            case SCALAR_TYPE_DESCRIPTOR: {
              if (numDim > 0) {
                printErrorMsg(rhs, NOT_ARRAY);
                return;
              }
              break;
            } case ARRAY_TYPE_DESCRIPTOR: {
              ArrayProperties *arrayProperties =
                &rhsType->properties.arrayProperties;
              if (numDim > arrayProperties->dimension) {
                printErrorMsg(rhs, NOT_ARRAY);
                return;
              } else if (numDim < arrayProperties->dimension) {

              }
              break;
            }
          }
          break;
        } case CONST_VALUE_NODE:
          break;
        case EXPR_NODE:
          break;
        default:
          // this should not happen
          assert(0);
      }
      break;
    case ARRAY_ID:
      printErrorMsg(lhs, NOT_ASSIGNABLE);
      break;
    case WITH_INIT_ID:
      // this should not happen
      assert(0);
  }
}

