#ifndef _DELETEAVL_H
#define _DELETEAVL_H

#include "Node.h"
Node *avlRemoveNearestLeft(Node **rootPtr, int *heightChangedStatus);
Node *avlRemove(Node **rootPtr, int data, CompareWithVoidPtr compare);
Node *_avlRemove(Node **rootPtr, void *data, int *heightChangedStatus, CompareWithVoidPtr compare);

#define avlRemoveIntegerWithValue(root, data)   avlRemove((Node **)root, data, compareIntwithVoidPtr)
#endif // _DELETEAVL_H
