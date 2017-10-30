#ifndef _ADDAVL_H
#define _ADDAVL_H
#include "Node.h"

#define RIGHT   0
#define LEFT    1
Node *addAvl(Node **root, Node *nodeToAdd);
void avlBalanceLeftTree(Node **rootPtr);
void avlBalanceRightTree(Node **rootPtr);


#endif // _ADDAVL_H
