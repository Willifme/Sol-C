#include "ast.h"

Node *makeNode(Node *left, Node *right, char *token) {

  // Malloc the Node
  Node *newNode = (Node *)malloc(sizeof(Node));

  char *newString = (char *)malloc(strlen(token)+1);

  strcpy(newString, token);

  newNode->left = left;

  newNode->right = right;

  newNode->token = newString;

  return newNode;

}

void printTree(Node *tree) {

  int i;

  if (tree->left || tree->right)
    printf("(");
    
  printf(" %s ", tree->token);

  if (tree->left)
    printTree(tree->left);
  
  if (tree->right)
    printTree(tree->right);

  if (tree->left || tree->right) 
    printf(")");

  printf("\n");

}
