#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#else

// How else can I handle a undefined macro? apart from part redefining it?
#define log_info(M, ...)

#endif

typedef enum AstNodeType {

  TYPE_INTEGER,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_BOOLEAN,
  TYPE_BINARYOPERATION,

} AstNodeType;

typedef enum BinaryOperationType {

  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

} BinaryOperationType;

typedef struct Node {

  struct Expression *expression;

  AstNodeType type;

} Node;

typedef struct Expression {

  struct Integer *integer;

  struct Character *character;

  struct String *string;

  struct Boolean *boolean;

  struct BinaryOperation *binOperation;

} Expression;

typedef struct Integer {

  int value;

} Integer;

typedef struct Character {

  char value;

} Character;

typedef struct String {

  char *value;

} String;

typedef struct Boolean {

  bool value;

} Boolean;

typedef struct BinaryOperation {

  struct Node *left, *right;

  BinaryOperationType binOperationType;

} BinaryOperation;

Node *makeNode(void);

Node *makeExpressionNode(Expression *expression);

Expression *makeExpression(void);

Node *makeInteger(int value);

Node *makeCharacter(char value);

Node *makeString(char *value);

Node *makeBoolean(bool value);

Node *makeBinaryOperation(Node *left, Node *right, BinaryOperationType type);

void printNode(Node *node);

void printExpression(Expression *expression);

void deleteNode(Node *node);

void deleteExpression(Expression *expression);

const char *getBinaryOperationChar(BinaryOperationType type);

const char *getAstNodeTypeString(AstNodeType type);
