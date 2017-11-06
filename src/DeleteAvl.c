#include "DeleteAvl.h"
#include <stdio.h>
#include "rotate.h"

int avlDeleteLeaf(Node **rootPtr, int data){
    if((*rootPtr) == NULL)
        return NO_CHANGED;
    if((*rootPtr)->data == data){
        (*rootPtr) = NULL;
    }
    else if ((*rootPtr)->data > data){
        int heightChanged = avlDeleteLeaf(&(*(rootPtr))->right, data);
        if(heightChanged == CHANGED){
            (*rootPtr)->bf--;
            return avlBalanceLeftTree(rootPtr);
        }
        else{
            return NO_CHANGED;
        }
    }
    else{
        int heightChanged = avlDeleteLeaf(&(*(rootPtr))->left, data);
        if (heightChanged == CHANGED)
        {
            (*rootPtr)->bf++;
            return avlBalanceRightTree(rootPtr);
        }
        else
        {
            return NO_CHANGED;
        }
    }
}