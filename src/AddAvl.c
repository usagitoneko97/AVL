#include "AddAvl.h"
#include "rotate.h"
Node *addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    *rootPtr = nodeToAdd;
    return (*rootPtr);
  }
  else{
    if(nodeToAdd->data > (*(rootPtr))->data){
      // addAvl(&(*(rootPtr))->right, nodeToAdd);
      (*rootPtr)->right = addAvl(&(*(rootPtr))->right, nodeToAdd);
      (*rootPtr)->bf++;
      if(*(rootPtr)->bf > 1){
        if((*rootPtr)->right->bf < 0){
          //rotate right left
        }
        //rotate left
      }
    }
    else{
      (*rootPtr)->left = addAvl(&(*(rootPtr))->left, nodeToAdd);
      (*rootPtr)->bf--;
      if(*(rootPtr)->bf < -1){
        if((*rootPtr)->left->bf > 0){
          //rotate left right
        }
        //rotate right
      }
    }
  }


}
