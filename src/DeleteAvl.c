#include "DeleteAvl.h"
#include <stdio.h>
void avlDeleteLeaf(Node **rootPtr, int data){
    if((*rootPtr) == NULL)
        return;
    if((*rootPtr)->data == data){
        (*rootPtr) = NULL;
    }
}