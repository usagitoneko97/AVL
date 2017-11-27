#ifndef _IntegerNodeHELPER_H
#define _NODEHELPER_H

#include "Node.h"
#include "AvlInteger.h"

IntegerNode node2, node3, node4, node7;
IntegerNode node1, node5, node10, node15, node20, node25, node30, node35, node40, node23;
IntegerNode node45, node50, node55, node60, node70;

void initIntegerNodeData(void);
void initNode(IntegerNode *node, IntegerNode *left, IntegerNode *right, int balanceFactor);

#endif // _NODEHELPER_H
