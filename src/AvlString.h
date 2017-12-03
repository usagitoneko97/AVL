#ifndef _AVLSTRING_H
#define _AVLSTRING_H

#include "Node.h"
typedef struct StrNode StrNode;
struct StrNode
{
    StrNode *left;
    StrNode *right;
    int balanceFactor;
    char *data;
};

#define avlAddString(root, nodeToAdd)   _avlAdd((Node **)root, (Node*)nodeToAdd, compareStr)
int compareStr(Node *str1, Node *str2);
#endif // _AVLSTRING_H
