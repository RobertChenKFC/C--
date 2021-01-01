void CodegenDeclarationNode(AST_NODE *declarationNode) {
  switch (declarationNode->nodeType) {
    case FUNCTION_DECL:
      CodegenFunctionDeclaration(declarationNode);
      break;
    case FUNCTION_PARAMETER_DECL:
      CodegenParameterDeclaraion(declarationNode);
      break;
    case TYPE_DECL: // ??
      break;
    case VARIABLE_DECL:
      CodegenVariableDeclaration(declarationNode);
      break;
    default:
      assert(0);
  }
}
void CodegenParameterDeclaration(AST_NODE *paramNode) {}
void CodegenVariableDeclaration(AST_NODE *variableNode) {}
void CodegenFunctionDeclaration(AST_NODE *functionNode) {
  TmpOffsetReset();
  RegReset();

  arSize = 0;
  CodegenFunctionPrologue(functionNode);

  fprintf(outputFile, "## Here is Function ! ##\n");
  AST_NODE *paramListNode = functionNode->child->rightSibling->rightSibling;
  assert(paramListNode->nodeType == PARAM_LIST_NODE);
  for (AST_NODE *param = paramListNode->child; param; param = param->rightSibling) {
    assert(param->nodeType == FUNCTION_PARAMETER_DECL);
    CodegenDeclarationNode(param);  // FUNCTION_PARAMETER_DECL
  }
  CodegenDeclarationNode(paramListNode);
  
  AST_NODE *blockNode = paramListNode->rightSibling;
  assert(blockNode->nodeType == BLOCK_NODE);
  CodegenBlockNode(blockNode);
  
  CodegenFunctionEpilogue(functionNode);
}

void CodegenBlockNode(AST_NODE *blockNode) {}

void CodegenStmtNode(AST_NODE *stmtNode) {
  switch (stmtNode) {
    case WHILE_STMT:
      CodegenWhileStmt(stmtNode);
    case FOR_STMT:
      CodegenForStmt(stmtNode);
