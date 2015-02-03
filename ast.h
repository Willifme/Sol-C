#ifndef AST_H

#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

typedef enum AstNodeType {

  TYPE_INTEGER,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_BOOLEAN,
  TYPE_BINARYOPERATION,
  TYPE_FUNCDECLARATION,
  TYPE_BLOCK,
  TYPE_UNKNOWN

} AstNodeType;

typedef enum Types {

  STRING,
  INT,
  CHAR,
  BOOLEAN

} Types;

typedef enum BinaryOperationType {

  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

} BinaryOperationType;

typedef struct Node {

  union {

    struct Integer *integer;

 	struct Character *character;

 	struct String *string;

 	struct Boolean *boolean;

 	struct BinaryOperation *binOperation;

	struct FuncDeclaration *funcDecl;

	struct Block *block;

  };
 
  AstNodeType type;

} Node;

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


typedef struct FuncDeclaration {

	struct Node *block;

	struct Argument *arguments;

	const char *name;

	unsigned int arg_count;

} FuncDeclaration;

typedef struct Block {

	struct Node *expressions;

} Block;

typedef struct Argument {

	Types type;

	char *name;

} Argument;

Node *makeNode(void);

Node *makeInteger(int value);

Node *makeCharacter(char value);

Node *makeString(char *value);

Node *makeBoolean(bool value);

Node *makeBinaryOperation(Node *left, Node *right, BinaryOperationType type);

Node *makeFuncDeclarationWithArgs(const char *name, struct Argument *args, struct Node *block);

Node *makeFuncDeclaration(const char *name, struct Node *block);

Node *makeBlock(struct Node *expressions);

Argument *makeArgument(char *name, Types type);

void printNode(Node *node);

void deleteNode(Node *node);

const char *getBinaryOperationChar(BinaryOperationType type);

const char *getAstNodeTypeString(AstNodeType type);

void printNodeValue(Node *node);

#endif /* AST_H */
