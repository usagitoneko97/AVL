#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>
typedef struct Node Node;
struct Node{
  Node *left;
  Node *right;
  int bf;
  int data;
};

typedef struct StrNode StrNode;
struct StrNode{
  StrNode *left;
  StrNode *right;
  char* data;
};

#endif // _NODE_H
