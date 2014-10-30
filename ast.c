#include "ast.h"
/*
int main(int argc, char *argv[]) {

  //Node *node = makeNode(makeBinaryOperation(makeIntegerExpression(1), makeIntegerExpression(1), PLUS));

//  Node *node = makeNode(makeBinaryOperation(makeBinaryOperation(makeIntegerExpression(1), makeIntegerExpression(2), PLUS), emakeBinaryOperation(makeIntegerExpression(3), makeIntegerExpression(4), TIMES), MINUS));

  Node *node = makeNode(makeStringExpression("Hello"));

  printNode(node);

  deleteNode(node);

  return 0;

}*/

Node *makeEmptyNode(void) {

  Node *node = malloc(sizeof(Node));

  node->expression = makeEmptyExpression();

  return node;

}

Node *makeNode(Expression *expression) {

  Node *node = malloc(sizeof(Node));

  if (expression)
    node->expression = expression;

  return node;

}

Expression *makeEmptyExpression(void) {

  Expression *newExpression = malloc(sizeof(Expression));

  newExpression->integer = NULL;

  newExpression->string = NULL;

  newExpression->boolean = NULL;
  
  newExpression->binaryOperation = NULL;

  return newExpression;

}

Expression *makeIntegerExpression(int value) {

  Expression *newInteger = makeEmptyExpression();

  newInteger->integer = malloc(sizeof(Integer));

  newInteger->integer->value = value;

  return newInteger;

}

Expression *makeStringExpression(char *value) {

  Expression *newString = makeEmptyExpression();

  newString->string = malloc(sizeof(String));

  newString->string->value = value;

  return newString;

}

Expression *makeBooleanExpression(bool value) {

  Expression *newBoolean = makeEmptyExpression();

  newBoolean->boolean = malloc(sizeof(Boolean));

  newBoolean->boolean->value = value;

  return newBoolean;
  
}

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationType type) {

  Expression *newBinaryOperation = makeEmptyExpression();

  newBinaryOperation->binaryOperation = malloc(sizeof(BinaryOperation));

  newBinaryOperation->binaryOperation->left = left;

  newBinaryOperation->binaryOperation->right = right;

  newBinaryOperation->binaryOperation->type = type;

  return newBinaryOperation;

}

void deleteNode(Node *node) {

  if (node->expression)
    deleteExpression(node->expression);

  free(node);

}

void deleteExpression(Expression *expression) {

  if (expression->integer)
    free(expression->integer);

  if (expression->string)
    free(expression->string);

  if (expression->boolean)
    free(expression->boolean);
  
  if (expression->binaryOperation) {

    if (expression->binaryOperation->left)
      deleteExpression(expression->binaryOperation->left);

    if (expression->binaryOperation->right)
      deleteExpression(expression->binaryOperation->right);

    // If the left and right are freed delete the struct all together

    free(expression->binaryOperation);

  }

  free(expression);

}

static int indentLevel = 0;

void printNode(Node *node) {

  if (node->expression) {

    printExpression(node->expression);

  }
}

void printExpression(Expression *expression) {

  // Reverse this

  for (int i = 0; i < indentLevel; i++) {

    printf("\t");

  }

  if (expression->integer) {

    // Hardcode for now
    printf("%d\n", expression->integer->value);

    indentLevel += 1;

  }

  if (expression->string) {

    // Hardcode for now
    printf("%s\n", expression->string->value);

  }

  if (expression->boolean) {

    // Hardcode for now, if the value is true print 'true' else false.
    printf("%s\n", expression->boolean->value ? "true" : "false");
    
  }

  /*
    if(getBinaryOperationTypeChar(expression->binaryOperation->type)) {

    printf("%c\n", getBinaryOperationTypeChar(expression->binaryOperation->type));


    }
  */
  if (expression->binaryOperation) {

    if (expression->binaryOperation->left)
      printExpression(expression->binaryOperation->left);

    if (expression->binaryOperation->right)
      printExpression(expression->binaryOperation->right);

  }

}

char getBinaryOperationTypeChar(BinaryOperationType type) {

  // I don't think the breaks are neccessary

  switch (type) {

    case PLUS:

      return '+';

      break;

    case MINUS:

      return '-';

      break;

    case TIMES:

      return '*';

      break;

    case DIVIDE:

      return '/';

      break;

    default:

      break;

  }

}
