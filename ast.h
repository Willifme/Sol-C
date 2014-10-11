#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Types {

  INT,
	
  STRING,

  OPERATOR

} Types;

typedef enum BinaryOperationTypes {

  PLUS,

  MINUS,

  TIMES,

  DIVIDE
  
} BinaryOperationTypes;

typedef struct Number {

  int value;
  
} Number;

typedef struct String {

  const char *value;
  
} String;

typedef struct BinaryOperator {

  BinaryOperationTypes operator;

  struct Expression *left;

  struct Expression *right;
  
} BinaryOperator;

typedef struct Node {

  union {

    struct Expression *expression;
    
  };
  
} Node;

typedef struct Expression {

  struct Node *left;
	
  struct Node *right;

  Types type;

  union {

    Number number;

    String string;

    BinaryOperator binaryOperator;
    
  };
  
  
} Expression;

Node *makeNode(void);

Expression *makeInt(int value);

Expression *makeString(const char *value);

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationTypes  operatorValue);

void deleteNode(Node *node);

void printExpression(Expression *expression);

void deleteExpression(Expression *expression);

const char *getBinaryOperationString(BinaryOperationTypes operatorValue);
