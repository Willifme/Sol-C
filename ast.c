#include "ast.h"

Node *makeNode(void) {

  Node *node = malloc(sizeof(Node));

  node->expression = NULL;

  return node;

}

Node *makeExpressionNode(Expression *expression) {

  Node *node = makeNode();

  node->expression = expression;

  return node;

}

Expression *makeExpression(void) {

  Expression *expression = malloc(sizeof(Expression));

  expression->integer = NULL;

  expression->character = NULL;

  expression->string = NULL;

  expression->boolean = NULL;

  expression->binOperation = NULL;

  return expression;

}

Node *makeInteger(int value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->integer = malloc(sizeof(Integer));

  node->expression->integer->value = value;

  node->type = TYPE_INTEGER;

  return node;

}

Node *makeCharacter(char value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->character = malloc(sizeof(Character));

  node->expression->character->value = value;

  node->type = TYPE_CHAR;

  return node;

}

Node *makeString(char *value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->string = malloc(sizeof(String));

  // GAHH pointers !*& - I am guessing with this

  node->expression->string->value = value;

  node->type = TYPE_STRING;

  return node;

}

Node *makeBoolean(bool value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->boolean = malloc(sizeof(Boolean));

  node->expression->boolean->value = value;

  node->type = TYPE_BOOLEAN;

  return node;

}

Node *makeBinaryOperation(Node *left, Node *right, BinaryOperationType type) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->binOperation = malloc(sizeof(BinaryOperation));

  node->expression->binOperation->left = left;

  node->expression->binOperation->right = right;

  node->expression->binOperation->binOperationType = type;

  node->type = TYPE_BINARYOPERATION;

  return node;

}

static unsigned int indent;

void printNode(Node *node) {

  for (unsigned int i = 0; i < indent; i++) {
   
    // For the second iteration to the fancy print else just print blank
    if (i == indent - 1)
      printf(" | - ");
    else
      printf("     ");

  }

  if (node->expression != NULL) {

    printf("%s ", getAstNodeTypeString(node->type));

    printExpression(node->expression);

  }
}

void printExpression(Expression *expression) {

  if (expression->binOperation != NULL) {

    printf("'%s'\n", getBinaryOperationChar(expression->binOperation->binOperationType));
    
    indent += 1;

    if (expression->binOperation->left != NULL)
      printNode(expression->binOperation->left);

    if (expression->binOperation->right != NULL)
      printNode(expression->binOperation->right);
     
  }
 
  if (expression->integer != NULL) 
    printf("'%d'\n", expression->integer->value);

  if (expression->character != NULL)
    printf("'%c'\n", expression->character->value);

  if (expression->string != NULL)
    printf("'%s'\n", expression->string->value);
  
  if (expression->boolean != NULL)
    // Boolean's cannot be printed in C directly
    printf("'%s'\n", expression->boolean->value ? "true" : "false");

}

void deleteNode(Node *node) {

  if (node->expression)
    deleteExpression(node->expression);

  free(node);

}

void deleteExpression(Expression *expression) {

  if (expression->integer)
    free(expression->integer);

  if (expression->character)
    free(expression->character);

  if (expression->string)
    free(expression->string); 

  if (expression->boolean)    
    free(expression->boolean);

  if (expression->binOperation) {

    if (expression->binOperation->left)
      deleteNode(expression->binOperation->left);

    if (expression->binOperation->right)
      deleteNode(expression->binOperation->right);

    free(expression->binOperation);

  }

  free(expression);

}

const char *getBinaryOperationChar(BinaryOperationType type) {

  // Are the breaks neccesary?

  switch (type) {

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

      return "Not found";

      break;

  }

  return "Not found";

}

const char *getAstNodeTypeString(AstNodeType type) {

  // Are the breaks necessary?
	
  switch (type) {

    case TYPE_INTEGER:

      return "IntegerExpression";

      break;

    case TYPE_CHAR:

      return "CharacterExpression";

      break;

    case TYPE_STRING:

      return "StringExpression";

      break;

    case TYPE_BOOLEAN:

      return "BooleanExpression";

      break;

    case TYPE_BINARYOPERATION:

      return "BinaryOperation";

      break;

    default:

      return "Not found";

      break;

  }

  return "Not found";

}
