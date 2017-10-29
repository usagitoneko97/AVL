#include "AddAvl.h"
#include "rotate.h"
void addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    *rootPtr = nodeToAdd;
    return;
  }
  if(nodeToAdd->data > (*(rootPtr))->data){
    // addAvl(&(*(rootPtr))->right, nodeToAdd);
    if((*rootPtr)->right == NULL){
      (*rootPtr)->right = nodeToAdd;
      (*rootPtr)->bf++;
    }
    else{
        addAvl(&(*(rootPtr))->right, nodeToAdd);
        (*rootPtr)->bf++;
        if((*rootPtr)->bf >=2){
          if((*rootPtr)->right->bf < 0){
            rotateRightLeft(*(rootPtr));
          }
          else{
            rotateLeft(*(rootPtr));
          }

        }

    }
  }
  else{
    if((*rootPtr)->left == NULL){
      (*rootPtr)->left = nodeToAdd;
      (*rootPtr)->bf--;
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
