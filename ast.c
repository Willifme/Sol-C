#include "ast.h"

int main(void) {
   
  // Expression *integer = makeBinaryOperation(makeInteger(1), makeBinaryOperation(makeInteger(10), makeInteger(1), PLUS), PLUS);

  //Node *integer = makeInteger(1);

  //x  Node *integer = makeBinaryOperation(makeCharacter('a'), makeInteger(1), PLUS);

  /* Node *integer = makeBinaryOperation(makeInteger(1),  makeBinaryOperation(makeInteger(1), makeInteger(1), MINUS), PLUS); */

  //  Node *integer = makeBinaryOperation(makeInteger(1),  NULL, PLUS);

  Node *integer = makeBinaryOperation(makeInteger(1), makeBinaryOperation(makeInteger(2),
                                                                          makeInteger(3), MINUS), PLUS);
  
  printNode(integer);

  deleteNode(integer);

  printf(";\n");

  return 0;

}

Node *makeNode(void) {

  Node *node = malloc(sizeof(Node));

  log_info("Allocating Node");

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

  expression->binOperation = NULL;

  return expression;

}

Node *makeInteger(int value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->integer = malloc(sizeof(Integer));

  node->expression->integer->value = value;

  node->type = TYPE_INTEGER;

  log_info("Allocating %s", getAstNodeTypeString(node->type));

  return node;

}

Node *makeCharacter(char value) {

  Node *node = makeNode();

  node->expression = makeExpression();

  node->expression->character = malloc(sizeof(Character));

  node->expression->character->value = value;

  node->type = TYPE_CHAR;

  log_info("Allocating %s", getAstNodeTypeString(node->type));

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

  log_info("Allocating %s", getAstNodeTypeString(node->type));

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
}

void deleteNode(Node *node) {

  if (node->expression)
    deleteExpression(node->expression);

  free(node);

  log_info("Freed Node");

}

void deleteExpression(Expression *expression) {

  /* Note: The log_info's are 'hardcoded' because the way that the AST is designed I cannot find 
     a reasonible way of getting the type without passing a node as optional parameter which
     is more trouble than it's worth. */

  if (expression->integer) {

    free(expression->integer);

    log_info("Freed IntegerExpression");

  }

  if (expression->character) {

    free(expression->character);
		
    log_info("Freed CharacterExpression");

  }

  if (expression->binOperation) {

    if (expression->binOperation->left) {

      deleteNode(expression->binOperation->left);

      log_info("Freed right BinaryOperation");
			
    }

    if (expression->binOperation->right) {

      deleteNode(expression->binOperation->right);

      log_info("Freed left BinaryOperation");

    }

    free(expression->binOperation);

  }

  free(expression);

  log_info("Freed Expression");

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

    case TYPE_BINARYOPERATION:

      return "BinaryOperation";

      break;

    default:

      return "Not found";

      break;

  }

  return "Not found";

}
