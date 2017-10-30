#include "AddAvl.h"
#include "rotate.h"

int heightChanged;
int addAvl(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    nodeToAdd->left = NULL;
    nodeToAdd->right = NULL;
    *rootPtr = nodeToAdd;
    return CHANGED;
  }
  else{
    if(nodeToAdd->data > (*(rootPtr))->data){
      heightChanged = addAvl(&(*(rootPtr))->right, nodeToAdd);
      // (*rootPtr)->right = (*rootPtr);
      //calc bf
      // (*rootPtr)->bf ++;
      if(heightChanged == CHANGED)
        (*rootPtr)->bf ++;
      //  (*rootPtr)->bf = calcBF(*rootPtr);
      return avlBalanceRightTree(rootPtr);
    }
    else{
      heightChanged = addAvl(&(*(rootPtr))->left, nodeToAdd);
      if(heightChanged == CHANGED)
        (*rootPtr)->bf --;
      return avlBalanceLeftTree(rootPtr);
    }
    // return (*rootPtr);
  }
}

int avlBalanceRightTree(Node **rootPtr){

  if((*rootPtr)->bf <= 1)
    return CHANGED;

  //need to balance here
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
  return NO_CHANGED;
}

int avlBalanceLeftTree(Node **rootPtr){
  if((*rootPtr)->bf >= -1)
    return CHANGED;
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
  return NO_CHANGED;
}
