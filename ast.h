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

  struct Node *left;

  struct Node *right;
  
} BinaryOperator;

typedef struct Node {

  struct Node *left;
	
  struct Node *right;

  Types type;

  union {

    Number number;

    String string;

    BinaryOperator binaryOperator;
    
  };
  
  //  int intValue;
	
  //const char *stringValue;

  //BinaryOperationTypes operatorValue;
  
} Node;

Node *makeNode(Node *left, Node *right);

Node *makeInt(int value);

Node *makeString(const char *value);

Node *makeBinaryOperator(Node *left, Node *right, BinaryOperationTypes  operatorValue);

void deleteNode(Node *node);

void printNode(Node *node);






