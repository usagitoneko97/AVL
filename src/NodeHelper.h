#ifndef _NODEHELPER_H
#define _NODEHELPER_H

#include "Node.h"
#include "AvlInteger.h"
#include "AvlString.h"

extern IntegerNode node2, node3, node4, node7, node10Clone;
extern IntegerNode node1, node5, node10, node15, node20, node25, node30, node35, node40, node23;
extern IntegerNode node45, node50, node55, node60, node70;

extern StrNode nodeAli, nodeAbu, nodeBaba, nodeHgx, nodeJason;

extern Node node500, node600, node500, node600;
void initIntegerNodeData(void);
void initStringNodeData(void);
void _initNode(Node *node, Node *left, Node *right, int balanceFactor);

#define initNode(n, l, r, bf) _initNode((Node *)n, (Node *)l, (Node *)r, bf);

#endif // _NODEHELPER_H
