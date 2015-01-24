#include "ast.h"

Node *makeNode(void) {

  Node *node = malloc(sizeof(Node));

	node->type = TYPE_UNKNOWN;

  return node;

}

Node *makeInteger(int value) {

  Node *node = makeNode();

  node->integer = malloc(sizeof(Integer));

  node->integer->value = value;

  node->type = TYPE_INTEGER;

  return node;

}

Node *makeCharacter(char value) {

  Node *node = makeNode();

  node->character = malloc(sizeof(Character));

  node->character->value = value;

  node->type = TYPE_CHAR;

  return node;

}

Node *makeString(char *value) {

  Node *node = makeNode();

  node->string = malloc(sizeof(String));

  // GAHH pointers !*& - I am guessing with this

  node->string->value = value;

  node->type = TYPE_STRING;

  return node;

}

Node *makeBoolean(bool value) {

  Node *node = makeNode();

  node->boolean = malloc(sizeof(Boolean));

  node->boolean->value = value;

  node->type = TYPE_BOOLEAN;

  return node;

}

Node *makeBinaryOperation(Node *left, Node *right, BinaryOperationType type) {

  Node *node = makeNode();

  node->binOperation = malloc(sizeof(BinaryOperation));

  node->binOperation->left = left;

  node->binOperation->right = right;

  node->binOperation->binOperationType = type;

  node->type = TYPE_BINARYOPERATION;

  return node;

}

Node *makeFuncDeclaration(const char *name, struct Node *arguments, struct Node *block) {

	Node *node = makeNode();

	node->funcDecl = malloc(sizeof(FuncDeclaration));

	node->funcDecl->name = name;

	node->funcDecl->arguments = arguments;

	node->funcDecl->block = block;	

	node->type = TYPE_FUNCDECLARATION;

	for (int i = 0; i < sizeof(arguments); i++)
		node->funcDecl->arg_count += 1;

	return node;

}

Node *makeBlock(struct Node *expressions) {

	Node *node = makeNode();

	node->block = malloc(sizeof(Block));

	node->block->expressions = expressions;

	node->type = TYPE_BLOCK;

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

	printf("%s ", getAstNodeTypeString(node->type));

	// Are the breaks neccessary?

	switch (node->type) {
	
		case TYPE_INTEGER:

			printf("'%d'\n", node->integer->value);

			break;

		case TYPE_CHAR:

			printf("'%c'\n", node->character->value);

			break;

		case TYPE_STRING:

			printf("%s\n", node->string->value);

			break;

		case TYPE_BOOLEAN:

			// Boolean's cannot be printed in C directly
    		printf("'%s'\n", node->boolean->value ? "true" : "false");

			break;

		case TYPE_BINARYOPERATION:
			
			printf("'%s'\n", getBinaryOperationChar(node->binOperation->binOperationType));
    
    	indent += 1;

			if (node->binOperation->left) printNode(node->binOperation->left);

			if (node->binOperation->right) printNode(node->binOperation->right);

			indent -= 1;

			break;

		case TYPE_FUNCDECLARATION:

			printf("Name: '%s' Args: [", node->funcDecl->name);

			// This crap will be changed in the future
			printNodeValue(node->funcDecl->arguments);

			printf("%s", getAstNodeTypeString(node->funcDecl->arguments->type));

			// End the arguments brackets
			printf("]\n");

			indent += 1;

			if (node->funcDecl->block) printNode(node->funcDecl->block);

			indent -= 1;

			break;

		case TYPE_BLOCK:

	/*		for (int i = 0; i < sizeof(node->block->expressions); i++)*/
				printNode(node->block->expressions);

			break;

		case TYPE_UNKNOWN:

		default:

			log_error("Cannot print nothing or unknown\n");

			break;

	}

}

void deleteNode(Node *node) {

	// Are the breaks neccessary?

	switch (node->type) {
	
		case TYPE_INTEGER:

			free(node->integer);

			break;

		case TYPE_CHAR:

			free(node->character);

			break;

		case TYPE_STRING:

			free(node->string);

			break;

		case TYPE_BOOLEAN:

			free(node->boolean);

			break;

		case TYPE_BINARYOPERATION:

			if (node->binOperation->left) deleteNode(node->binOperation->left);

			if (node->binOperation->right) deleteNode(node->binOperation->right);

			free(node->binOperation);

			break;

		case TYPE_FUNCDECLARATION:

			if (node->funcDecl->block != NULL) free(node->funcDecl->block);

		//	for (int i = 0; i < sizeof(node->funcDecl->arguments); i++) 
			deleteNode(node->funcDecl->arguments);

			break;

		case TYPE_BLOCK:

		//	for (int i = 0; i < sizeof(node->block->expressions); i++)
			deleteNode(node->block->expressions);

			break;

		case TYPE_UNKNOWN:

		default:

			log_error("Cannot free nothing or unkown\n");

			break;

	}

  free(node);

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

		case TYPE_FUNCDECLARATION:

			return "FuncDeclaration";

			break;

		case TYPE_BLOCK:

			return "BlockExpression";

			break;

		case TYPE_UNKNOWN:

			return "UnknownNode";

    default:

      return "Not found";

      break;

  }

  return "Not found";

}

void printNodeValue(Node *node) {

	switch (node->type) {
	
		case TYPE_INTEGER:

			printf("'%d'", node->integer->value);

			break;

		case TYPE_CHAR:

			printf("'%c'", node->character->value);

			break;

		case TYPE_STRING:

 		  printf("%s", node->string->value);

			break;

		case TYPE_BOOLEAN:

			// Boolean's cannot be printed in C directly
	    sprintf("'%s", node->boolean->value ? "true" : "false");

			break;

		case TYPE_BINARYOPERATION:
			
			if (node->binOperation->left) printNodeValue(node->binOperation->left);

			if (node->binOperation->right) printNodeValue(node->binOperation->right);

			printf("'%s'", getBinaryOperationChar(node->binOperation->binOperationType));

			break;

		// Purposefully allow them to fall through

		case TYPE_FUNCDECLARATION:

		case TYPE_BLOCK:

		case TYPE_UNKNOWN:

		default:

			log_error("Some types do not have direct values\n");

	}
	
}
