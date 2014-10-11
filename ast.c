#include "ast.h"

Node *makeNode(void) {

  Node *newNode = (Node *)malloc(sizeof(Node));
	
  return newNode;

}

Expression *makeInt(int value) {

  Expression *newInt = (Expression *)malloc(sizeof(Expression));
  /*
    newInt->left = makeNode();

    newInt->right = NULL;
  */
  newInt->number.value = value;
	
  newInt->type = INT;

  return newInt;

}

Expression *makeString(const char *value) {

  Expression *newString = (Expression *)malloc(sizeof(Expression));
	
  newString->string.value = value;
	
  newString->type = STRING;
	
  return newString;

}

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationTypes operatorValue) {

  Expression *newBinaryOperator = (Expression *)malloc(sizeof(Expression));

  newBinaryOperator->binaryOperator.left = left;

  newBinaryOperator->binaryOperator.right = right;
  
  newBinaryOperator->binaryOperator.operator = operatorValue;

  newBinaryOperator->type = OPERATOR;

  return newBinaryOperator;
  
}

void deleteNode(Node *node) {

  free(node);

}

void printExpression(Expression *expression) {

  const char *operator;
    
  if (expression->binaryOperator.left != NULL)
    printExpression(expression->binaryOperator.left);
    
  if (expression->binaryOperator.right != NULL)
    printExpression(expression->binaryOperator.right);


  switch (expression->type) {
	
  case INT:
		
    // if (expression->number.value ) {
		
    printf("Int: %d\n", expression->number.value);

    //    }

    break;
			
  case STRING:
		
    // if (expression->string.value) {
		
    printf("String: %s\n", expression->string.value);
			
    //   }
			
    break;

  case OPERATOR:

    // printf("Operator: %s\n", operator);

    break;
			
  default:
		
    printf("Type not found\n");
			
    break;
	
  }
  
}

void deleteExpression(Expression *expression) {

  if (expression->left != NULL) {

    deleteNode(expression->left);

  }

  if (expression->right != NULL) {

    deleteNode(expression->right);

  }

  if (expression->binaryOperator.left != NULL) {

    deleteExpression(expression->binaryOperator.left);
    
  }

  if (expression->binaryOperator.right != NULL) {

    deleteExpression(expression->binaryOperator.right);
    
  }
  
  free(expression);
  
}

int main() {

  Expression *main = makeBinaryOperation(makeInt(1), makeInt(1), PLUS);

  //  Expression *main = makeInt(1);
  
  printExpression(main);
	
  deleteExpression(main);

  return 0;
  
}


