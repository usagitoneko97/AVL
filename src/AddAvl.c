#include "AddAvl.h"
#include "rotate.h"
Node *addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    *rootPtr = nodeToAdd;
    return (*rootPtr);
  }
  else{
    if(nodeToAdd->data > (*(rootPtr))->data){
      (*rootPtr)->right = addAvl(&(*(rootPtr))->right, nodeToAdd);
      //calc bf
      (*rootPtr)->bf = calcBF(*rootPtr);
      if((*rootPtr)->bf > 1){
        if((*rootPtr)->right->bf < 0){
          //rotate right left
          (*rootPtr)->right = rotateRightLeft(*rootPtr);

        }
        //rotate left
        (*rootPtr)->right = rotateLeft(*rootPtr);
      }
    }
    else{
      (*rootPtr)->left = addAvl(&(*(rootPtr))->left, nodeToAdd);
      (*rootPtr)->bf = calcBF(*rootPtr);
      if((*rootPtr)->bf < -1){
        if((*rootPtr)->left->bf > 0){
          //rotate left right
          (*rootPtr)->left = rotateleftRight(*rootPtr);
        }
        //rotate right
        (*rootPtr)->left = rotateRight(*rootPtr);
      }
    }
  }
}
