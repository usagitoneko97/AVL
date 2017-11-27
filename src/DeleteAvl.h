#ifndef _DELETEAVL_H
#define _DELETEAVL_H

#include "Node.h"
Node *avlDeleteNearestLeft(Node **rootPtr, int *heightChangedStatus);
Node *avlDelete(Node **rootPtr, int data, int (*compare)(void *, Node *));
Node *_avlDelete(Node **rootPtr, void *data, int *heightChangedStatus, int (*compare)(void *, Node *));
Node *avlFindMin(Node *root);
Node *avlFindMax(Node *root);

#endif // _DELETEAVL_H
