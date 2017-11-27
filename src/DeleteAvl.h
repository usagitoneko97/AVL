#ifndef _DELETEAVL_H
#define _DELETEAVL_H

#include "Node.h"
Node *avlRemoveNearestLeft(Node **rootPtr, int *heightChangedStatus);
Node *avlRemove(Node **rootPtr, int data, int (*compare)(void *, Node *));
Node *_avlRemove(Node **rootPtr, void *data, int *heightChangedStatus, int (*compare)(void *, Node *));
Node *avlFindMin(Node *root);
Node *avlFindMax(Node *root);

#endif // _DELETEAVL_H
