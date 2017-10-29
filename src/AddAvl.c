#include "AddAvl.h"
#include "rotate.h"
Node *addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    *rootPtr = nodeToAdd;
    return (*rootPtr);
  }
  if(nodeToAdd->data > (*(rootPtr))->data){
    // addAvl(&(*(rootPtr))->right, nodeToAdd);
    if((*rootPtr)->right == NULL){
      (*rootPtr)->right = nodeToAdd;
      (*rootPtr)->bf++;
      return (*rootPtr);
    }
    else{
        (*rootPtr)->right = addAvl(&(*(rootPtr))->right, nodeToAdd);
        (*rootPtr)->bf++;
        if((*rootPtr)->bf >=2){
          if((*rootPtr)->right->bf < 0){
            return rotateRightLeft(*(rootPtr));
          }
          else{
            return rotateLeft(*(rootPtr));
          }
        }

    }
  }
  else{
    if((*rootPtr)->left == NULL){
      (*rootPtr)->left = nodeToAdd;
      (*rootPtr)->bf--;
      return (*rootPtr);
    }
    else{
        addAvl(&(*(rootPtr))->left, nodeToAdd);
        (*rootPtr)->bf --;
        if((*rootPtr)->bf <=-2){
          if((*rootPtr)->left->bf >0){
            rotateleftRight(*(rootPtr));
          }
          else{
            rotateRight(*(rootPtr));
          }
        }
      }
  }

}
