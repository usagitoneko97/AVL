#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>



typedef struct Node Node;
struct Node{
  Node *left;
  Node *right;
  int balanceFactor;
  void *data;
};

typedef struct IntegerNode IntegerNode;
struct IntegerNode
{
  IntegerNode *left;
  IntegerNode *right;
  int balanceFactor;
  int data;
};

typedef struct StrNode StrNode;
struct StrNode{
  StrNode *left;
  StrNode *right;
  int balanceFactor;
  char* data;
};
typedef int (*Compare)(Node *, Node *);
typedef int (*CompareWithVoidPtr)(void *, Node *);
#define CHANGED 1
#define NO_CHANGED 0

int compareInt(Node *node1, Node *node2);
int compareIntwithVoidPtr(void *data1, Node *data2);

#endif // _NODE_H
