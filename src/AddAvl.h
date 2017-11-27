#ifndef _avlAdd_H
#define _avlAdd_H

#include "Node.h"


int _avlAdd(Node **root, Node *nodeToAdd, Compare compare);
void avlAdd(Node **root, Node *NodeToAdd, Compare compare);
int avlBalanceLeftTree(Node **rootPtr);
int avlBalanceRightTree(Node **rootPtr);

#define avlAddInteger(root, nodeToAdd)  _avlAdd((Node **)root, (Node *)nodeToAdd, compareInt)
#define avlAddString(root, nodeToAdd)   _avlAdd(root, nodeToAdd, compareStr)

#endif // _avlAdd_H
