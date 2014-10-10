#include "ast.h"

Node *makeNode(Node *left, Node *right) {

  Node *newNode = (Node *)malloc(sizeof(Node));
	
  newNode->left = left;
	
  newNode->right = right;
	
  return newNode;

}

Node *makeInt(int value) {

  printf("making int\n");
  
  Node *newInt = (Node *)malloc(sizeof(Node));

  newInt->number.value = value;
	
  newInt->type = INT;

  return newInt;

}

Node *makeString(const char *value) {

  Node *newString = (Node *)malloc(sizeof(Node));
	
  newString->string.value = value;
	
  newString->type = STRING;
	
  return newString;

}

Node *makeBinaryOperator(Node *left, Node *right, BinaryOperationTypes operatorValue) {

  Node *newBinaryOperator = (Node *)malloc(sizeof(Node));

  newBinaryOperator->binaryOperator.left = left;

  newBinaryOperator->binaryOperator.right = right;
  
  newBinaryOperator->binaryOperator.operator = operatorValue;

  newBinaryOperator->type = OPERATOR;

  return newBinaryOperator;
  
}

void deleteNode(Node *node) {

  if (node->left) {
		
    deleteNode(node->left);
		
  } 
	
  if (node->right) {
	
    deleteNode(node->right);
	
  }
	
  free(node);

}

void printNode(Node *node) {

  if (node->left) {
	
    printNode(node->left);
		
  }
	
  if (node->right) {
	
    printNode(node->right);
		
  }
        
  switch (node->type) {
	
  case INT:
		
    if (node->number.value ) {
		
      printf("Int: %d\n", node->number.value);

    }

    break;
			
  case STRING:
		
    if (node->string.value) {
		
      printf("String: %s\n", node->string.value);
			
    }
			
    break;

  case OPERATOR:

    if (node->binaryOperator.operator) {

      printf("Operator: %u\n", node->binaryOperator.operator);

    }

    break;
			
  default:
		
    printf("Type not found\n");
			
    break;
	
  }
	
}

int main() {

  // Node *main = makeBinaryOperator(makeInt(1), makeInt(1), PLUS);

  Node *main = makeInt(1);
  
  printNode(main);
	
  deleteNode(main);

  return 0;
  
}


