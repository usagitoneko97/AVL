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
          return rotateRightLeft(*rootPtr);

        }
        else{
        //rotate left
          return rotateLeft(*rootPtr);
        }
      }
    }
    else{
      (*rootPtr)->left = addAvl(&(*(rootPtr))->left, nodeToAdd);
      (*rootPtr)->bf = calcBF(*rootPtr);
      if((*rootPtr)->bf < -1){
        if((*rootPtr)->left->bf > 0){
          //rotate left right
          return  rotateleftRight(*rootPtr);
        }
        else{
        //rotate right
          return  rotateRight(*rootPtr);
        }
      }
    }
    return (*rootPtr);
  }
}

void avlBalanceRightTree(Node **rootPtr){

  if((*rootPtr)->right->bf < 0){
    //rotate right left
    (*rootPtr) = rotateRightLeft(*rootPtr);
    switch ((*rootPtr)->bf) {
      case -1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = 0;
        (*rootPtr)->right->bf = 1;
        break;
      case 0:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = 0;
        (*rootPtr)->right->bf = 0;
        break;
      case 1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = -1;
        (*rootPtr)->right->bf = 0;
        break;
    }
  }
  else{
  //rotate left
    (*rootPtr) = rotateLeft(*rootPtr);
    switch ((*rootPtr)->bf) {
      case 1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = 0;
        break;
      case 0:
        (*rootPtr)->bf = -1;
        (*rootPtr)->left->bf = 1;
        break;
    }
  }
}

void avlBalanceLeftTree(Node **rootPtr){
  if((*rootPtr)->left->bf > 0){
    //rotate left right
    (*rootPtr) = rotateleftRight(*rootPtr);
    switch ((*rootPtr)->bf) {
      case 1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = -1;
        (*rootPtr)->right->bf = 0;
        break;
      case 0:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = 0;
        (*rootPtr)->right->bf = 0;
        break;
      case -1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->left->bf = 0;
        (*rootPtr)->right->bf = 1;
        break;
    }
  }
  else{
  //rotate right
    (*rootPtr) = rotateRight(*rootPtr);
    switch ((*rootPtr)->bf) {
      case -1:
        (*rootPtr)->bf = 0;
        (*rootPtr)->right->bf = 0;
        break;
      case 0:
        (*rootPtr)->bf = 1;
        (*rootPtr)->right->bf = -1;
        break;
    }
  }
}
