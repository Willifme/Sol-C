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
  
  node->statement = makeEmptyStatement();

  return node;

}

Node *makeStatementNode(Statement *statement) {

	Node *node = malloc(sizeof(Node));
	
	if(statement)
		node->statement = statement;
	
	return node;
	
}

Statement *makeEmptyStatement(void) {

	Statement *newStatement = malloc(sizeof(Statement));
	
	newStatement->func = NULL;
	
	return newStatement;
	
}

Statement *makeFuncStatement(Expression *expression) {

	Statement *newFunc = makeEmptyStatement();
	
	newFunc->func = malloc(sizeof(Func));
	
	newFunc->func->expression = expression;
	
	return newFunc;
		
}

Node *makeExpressionNode(Expression *expression) {

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

  if (node->statement)
	  deleteStatement(node->statement);

  free(node);

}


void deleteStatement(Statement *statement) {
	
	if (statement->func) {
		
		deleteExpression(statement->func->expression);
		
		free(statement->func);
	
	}
	
	free(statement);
	
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

    free(expression->binaryOperation);

  }

  free(expression);

}

void printNode(Node *node) {

  if (node->expression)
		printExpression(node->expression);

	if (node->statement)
		printStatement(node->statement);
  
}

void printStatement(Statement *statement) {
	
	if (statement->func)
		printExpression(statement->func->expression);
	
}

void printExpression(Expression *expression) {

  if (expression->integer) {

    // Hardcode for now
    printf("%d\n", expression->integer->value);

  }

  if (expression->string) {

    // Hardcode for now
    printf("%s\n", expression->string->value);

  }

  if (expression->boolean) {

    // Hardcode for now, if the value is true print 'true' else false.
    printf("%s\n", expression->boolean->value ? "true" : "false");

  }

  if (expression->binaryOperation) {

    if (expression->binaryOperation->left)
      printExpression(expression->binaryOperation->left);

    if(getBinaryOperationTypeChar(expression->binaryOperation->type)) {

      printf("%c\n", getBinaryOperationTypeChar(expression->binaryOperation->type));

    }

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
