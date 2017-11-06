#ifndef _DELETEAVL_H
#define _DELETEAVL_H

#include "Node.h"
int avlDelete(Node **rootPtr, int data);
Node *avlFindMin(Node *root);
Node *avlFindMax(Node *root);

#endif // _DELETEAVL_H
