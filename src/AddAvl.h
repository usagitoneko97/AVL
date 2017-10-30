#ifndef _ADDAVL_H
#define _ADDAVL_H
#include "Node.h"

#define CHANGED     1
#define NO_CHANGED  0
int addAvl(Node **root, Node *nodeToAdd);
int avlBalanceLeftTree(Node **rootPtr);
int avlBalanceRightTree(Node **rootPtr);


#endif // _ADDAVL_H
