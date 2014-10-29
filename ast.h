//
//  ast.h
//
//
//  Created by William Collier on 29/10/2014.
//
//

#ifndef _ast_h
#define _ast_h

#include <stdio.h>
#include <stdlib.h>

typedef enum BinaryOperationType {

  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

} BinaryOperationType;

typedef struct Node {

  struct Expression *expression;

} Node;

typedef struct Expression {

  struct Integer *integer;

  struct String *string;

  struct BinaryOperation *binaryOperation;

} Expression;

typedef struct Integer {

  int value;

} Integer;

typedef struct String {

  const char *value;

} String;

typedef struct BinaryOperation {

  Expression *left;

  Expression *right;

  BinaryOperationType type;

} BinaryOperation;

Node *makeEmptyNode(void);

Node *makeNode(Expression *expression);

Expression *makeEmptyExpression(void);

Expression *makeIntegerExpression(int value);

Expression *makeStringExpression(char *value);

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationType type);

void deleteNode(Node *node);

void deleteExpression(Expression *expression);

void printNode(Node *node);

void printExpression(Expression *expression);

char getBinaryOperationTypeChar(BinaryOperationType type);

#endif
