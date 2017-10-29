#include "AddAvl.h"

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
        (*rootPtr)->bf ++;
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
      }
  }

}
