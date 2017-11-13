#ifndef _DELETEAVL_H
#define _DELETEAVL_H

#include "Node.h"
Node *avlDelete(Node **rootPtr, int data);
Node *_avlDelete(Node **rootPtr, void *data, int *heightChangedStatus, int deleteFlag);
Node *avlFindMin(Node *root);
Node *avlFindMax(Node *root);

#endif // _DELETEAVL_H
