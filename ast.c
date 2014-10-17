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

  printf("Called\n");

  if (expression->left != NULL) {

    deleteNode(expression->left);

  }

  if (expression->right != NULL) {

    deleteNode(expression->right);

  }


  switch (expression->type) {
	
  case INT:

    break;
			
  case STRING:
			
    break;

  case OPERATOR:
    
    if (expression->binaryOperator.left != NULL) {

      deleteExpression(expression->binaryOperator.left);

    }

    if (expression->binaryOperator.right != NULL) {

      deleteExpression(expression->binaryOperator.right);

    }

    break;
			
  default:
		
    printf("Cannot delete expression\n");
			
    break;
	
  }

  free(expression);

}

const char *getBinaryOperationString(BinaryOperationTypes operatorValue) {

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

  // Are the breaks neccesary?

}
/*
int main() {

  //  Expression *main = makeBinaryOperation(makeInt(1), makeInt(1), PLUS);

  // Expression *main = makeInt(1);
  
  //   printExpression(main);
	
  // deleteExpression(main);

  repl();

  return 0;
  
}

void repl(void) {

  Expression *expression;

  while (1) {

    char *input= readline(">> ");

    add_history(input);

    if (!input) 
      return;

    expression = makeInt(1);

    printExpression(expression);

    deleteExpression(expression);

    free(input);

  }
  
}
*/
