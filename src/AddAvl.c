#include "AddAvl.h"
#include "rotate.h"
#include "Exception.h"
#include "CException.h"

int heightChanged;

/** 
 * @brief  add a value to the avl tree
 * @param  **rootPtr: pointer to the avl tree
 * @param  *nodeToAdd: node structure to add
 * @retval height change status of the avl tree after addition
 */
int _avlAdd(Node **rootPtr, Node *nodeToAdd){
  if(*(rootPtr) == NULL){
    nodeToAdd->left = NULL;
    nodeToAdd->right = NULL;
    nodeToAdd->balanceFactor = 0;
    *rootPtr = nodeToAdd;
    return CHANGED;
  }
  else{
    if(nodeToAdd->data > (*(rootPtr))->data){
      heightChanged = _avlAdd(&(*(rootPtr))->right, nodeToAdd);
      // (*rootPtr)->right = (*rootPtr);
      //calc balanceFactor
      // (*rootPtr)->balanceFactor ++;
      if(heightChanged == CHANGED){
        (*rootPtr)->balanceFactor ++;
        if((*rootPtr)->balanceFactor == 0){
          return NO_CHANGED;
        }
      }
      else {
        return NO_CHANGED;
      }
      //  (*rootPtr)->balanceFactor = calcbalanceFactor(*rootPtr);
      if ((*rootPtr)->balanceFactor != 2)
      {
        return CHANGED;
      }
      //change in structure of tree (decreasing level), will results in no change in the balanceFactor
      if(avlBalanceRightTree(rootPtr) == CHANGED){
        return NO_CHANGED;
      }
      else{
        return CHANGED;
      }
    }
    else if (nodeToAdd->data < (*(rootPtr))->data)
    {
      heightChanged = _avlAdd(&(*(rootPtr))->left, nodeToAdd);
      if(heightChanged == CHANGED){
        (*rootPtr)->balanceFactor --;
        if ((*rootPtr)->balanceFactor == 0)
        {
          return NO_CHANGED;
        }
      }
      else  
        return NO_CHANGED;
      if((*rootPtr)->balanceFactor != -2){
        return CHANGED;
      }
      //change in structure of tree (decreasing level), will results in no change in the balanceFactor
      if (avlBalanceLeftTree(rootPtr) == CHANGED)
      {
        return NO_CHANGED;
      }
      else
      {
        return CHANGED;
      }
    }
    else{
      Throw(createException("node to add is already exist in the avl tree", NODE_ADD_EXIST));
    }
  }
}

void avlAdd(Node **root, Node *nodeToAdd){
  _avlAdd(root, nodeToAdd);
}
