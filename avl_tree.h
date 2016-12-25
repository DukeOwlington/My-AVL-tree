#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

Node *Insert(Node *node, int key);
Node *DeleteNode(Node *root, int key);
void DeleteTree(Node *root);
void Find(Node *root, int key);
void PrintInOrder(Node *root);
void PrintNode(Node *root);

#endif
