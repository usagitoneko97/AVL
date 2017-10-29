#ifndef _NODEHELPER_H
#define _NODEHELPER_H
#include "Node.h"

Node node1, node5, node10, node15, node20, node25, node30, node35, node40;
Node node45, node50, node55;

void initNodeData(void);
void initNode(Node *node, Node *left, Node *right, int bf);

#endif // _NODEHELPER_H
