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
#include <stdbool.h>

typedef enum BinaryOperationType {

  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

} BinaryOperationType;

typedef struct Node {

  struct Expression *expression;

  struct Statement *statement;

} Node;

typedef struct Statement {
	
	struct Func *func;
	
} Statement;

typedef struct Func {
	
	struct Expression *expression;
	
} Func;

typedef struct Expression {

  struct Integer *integer;

  struct String *string;

  struct Boolean *boolean;
  
  struct BinaryOperation *binaryOperation;

} Expression;

typedef struct Integer {

  int value;

} Integer;

typedef struct String {

  const char *value;

} String;

typedef struct Boolean {

  bool value;
  
} Boolean;

typedef struct BinaryOperation {

  Expression *left;

  Expression *right;

  BinaryOperationType type;

} BinaryOperation;

Node *makeEmptyNode(void);

Node *makeStatementNode(Statement *statement);

Statement *makeEmptyStatement(void);

Statement *makeFuncStatement(Expression *expression);

Node *makeExpressionNode(Expression *expression);

Expression *makeEmptyExpression(void);

Expression *makeIntegerExpression(int value);

Expression *makeStringExpression(char *value);

Expression *makeBooleanExpression(bool value);

Expression *makeBinaryOperation(Expression *left, Expression *right, BinaryOperationType type);

void deleteNode(Node *node);

void deleteStatement(Statement *statement);

void deleteExpression(Expression *expression);

void printNode(Node *node);

void printStatement(Statement *statement);

void printExpression(Expression *expression);

char getBinaryOperationTypeChar(BinaryOperationType type);

#endif
