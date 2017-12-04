#ifndef _AVLINTEGER_H
#define _AVLINTEGER_H

#include "Node.h"
#include "AddAvl.h"
typedef struct IntegerNode IntegerNode;
struct IntegerNode
{
    IntegerNode *left;
    IntegerNode *right;
    int balanceFactor;
    int data;
};

#define avlRemoveIntegerWithValue(root, data) avlRemove((Node **)root, data, compareIntwithVoidPtr)
int avlAddInteger(IntegerNode **root, IntegerNode *nodeToAdd);
int compareInt(Node *node1, Node *node2);
int compareIntwithVoidPtr(void *data1, Node *data2);
#endif // _AVLINTEGER_H
