#ifndef _AVLSTRING_H
#define _AVLSTRING_H

typedef struct StrNode StrNode;
struct StrNode
{
    StrNode *left;
    StrNode *right;
    int balanceFactor;
    char *data;
};

#endif // _AVLSTRING_H
