#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {

  struct Node *left;

  struct Node *right;

  char *token;

} Node;

Node *makeNode(Node *left, Node *right, char *token);

void printTree(Node *tree);
