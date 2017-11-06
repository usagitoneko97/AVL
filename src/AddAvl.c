#include "AddAvl.h"
#include "rotate.h"

int heightChanged;
int addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    nodeToAdd->left = NULL;
    nodeToAdd->right = NULL;
    nodeToAdd->bf = 0;
    *rootPtr = nodeToAdd;
    return CHANGED;
  }
  else{
    if(nodeToAdd->data > (*(rootPtr))->data){
      heightChanged = addAvl(&(*(rootPtr))->right, nodeToAdd);
      // (*rootPtr)->right = (*rootPtr);
      //calc bf
      // (*rootPtr)->bf ++;
      if(heightChanged == CHANGED){
        (*rootPtr)->bf ++;
        if((*rootPtr)->bf == 0){
          return NO_CHANGED;
        }
      }
      else {
        return NO_CHANGED;
      }
      //  (*rootPtr)->bf = calcBF(*rootPtr);
      return avlBalanceRightTree(rootPtr);
    }
    else{
      heightChanged = addAvl(&(*(rootPtr))->left, nodeToAdd);
      if(heightChanged == CHANGED){
        (*rootPtr)->bf --;
        if ((*rootPtr)->bf == 0)
        {
          return NO_CHANGED;
        }
      }
      else  
        return NO_CHANGED;
      return avlBalanceLeftTree(rootPtr);
    }
    // return (*rootPtr);
  }
}


