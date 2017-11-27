#include "Node.h"

/** 
 * @brief  return 1 when node > data
 * @note   
 * @param  *node: node to compare
 * @param  *data: data to compare
 * @retval result
 */
int compareInt(Node *node1, Node *node2)
{
    IntegerNode *intNode1 = (IntegerNode *)node1;
    IntegerNode *intNode2 = (IntegerNode *)node2;
    if (intNode1->data > intNode2->data)
    {
        return 1;
    }
    else if (intNode1->data < intNode2->data)
    {
        return -1;
    }
    else{
        return 0;
    }
}

int compareIntwithVoidPtr(void *data1, Node *data2){
    int data1int = *((int*)data1);
    IntegerNode *intNode2 = (IntegerNode *)data2;
    if (data1int > intNode2->data)
    {
        return 1;
    }
    else if (data1int < intNode2->data)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}