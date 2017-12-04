#include "AvlInteger.h"



int compareIntwithVoidPtr(void *data1, Node *data2)
{
    int *data1int = (int*)data1;
    IntegerNode *intNode2 = (IntegerNode *)data2;
    if (*data1int > intNode2->data)
    {
        return 1;
    }
    else if (*data1int < intNode2->data)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int avlAddInteger(IntegerNode **root, IntegerNode *nodeToAdd){
    Node *_nodeToAdd = (Node *)nodeToAdd;
    _nodeToAdd->data = &(nodeToAdd->data);
    _avlAdd((Node **)root, _nodeToAdd, compareIntwithVoidPtr);
}