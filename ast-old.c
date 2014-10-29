#include "ast.h"

Node *makeNode(void) {

  Node *newNode = (Node *)malloc(sizeof(Node));
	
  return newNode;

}

Expression *makeExpression(void) {

  Expression *newExpression = (Expression *)malloc(sizeof(Expression));

  return newExpression;

}

Expression *makeInt(int value) {

  Expression *newInt = (Expression *)malloc(sizeof(Expression));

  newInt->number.value = value;
	
  newInt->type = INT;

  newInt->left = makeNode();

  newInt->right = NULL;

  return newInt;

}

Expression *makeString(const char *value) {

  // Check if the first and last characters are " or ' - this is a workaround and the parser / lexer should fix this
  
  Expression *newString = (Expression *)malloc(sizeof(Expression));

  newString->string.value = value;
	
  newString->type = STRING;
	
  newString->left = makeNode();

  newString->right = NULL;

  return newString;

}

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationTypes operatorValue) {

  Expression *newBinaryOperator = (Expression *)malloc(sizeof(Expression));

  newBinaryOperator->binaryOperator.left = left;

  newBinaryOperator->binaryOperator.right = right;
  
  newBinaryOperator->binaryOperator.operator = operatorValue;

  newBinaryOperator->type = OPERATOR;

  newBinaryOperator->left = makeNode();

  newBinaryOperator->right = NULL;

  return newBinaryOperator;
  
}

void deleteNode(Node *node) {

  free(node);

}

void printExpression(Expression *expression) {

  const char *operator;
  
  switch (expression->type) {
	
  case INT:
		
    printf("Int: %d\n", expression->number.value);

    break;
			
  case STRING:
		
    printf("String: %s\n", expression->string.value);
			
    break;

  case OPERATOR:

    if (expression->binaryOperator.left != NULL)
      printExpression(expression->binaryOperator.left);
    
    if (expression->binaryOperator.right != NULL)
      printExpression(expression->binaryOperator.right);

    printf("Operator: %s\n", getBinaryOperationString(expression->binaryOperator.operator));

    break;
			
  default:
		
    printf("Type not found\n");
			
    break;
	
  }
  
}

void deleteExpression(Expression *expression) {

  if (expression->left != NULL) 
    deleteNode(expression->left);

  if (expression->right != NULL)
    deleteNode(expression->right);

  switch (expression->type) {
	
  case INT:

    break;
			
  case STRING:
			
    break;

  case OPERATOR:
    
    if (expression->binaryOperator.left != NULL) 
      deleteExpression(expression->binaryOperator.left);

    if (expression->binaryOperator.right != NULL)
      deleteExpression(expression->binaryOperator.right);

    break;
			
  default:
		
    printf("Cannot delete expression\n");
			
    break;
	
  }

  free(expression);

}

const char *getBinaryOperationString(BinaryOperationTypes operatorValue) {

   // Are the breaks neccesary?
  
  switch (operatorValue) {

  case PLUS:

    return "+";

    break;

  case MINUS:

    return "-";

    break;

  case TIMES:

    return "*";

    break;

  case DIVIDE:

    return "/";

    break;

  default:

    return "Binary operator type not found";

    break; 

  }

}
