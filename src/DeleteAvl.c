#include "DeleteAvl.h"
#include <stdio.h>
#include "rotate.h"


Node *avlDelete(Node **rootPtr, int data){
    int heightChangedTemp;
    _avlDelete(rootPtr, data, &heightChangedTemp, 0);
}

Node *_avlDelete(Node **rootPtr, int data, int *heightChangedStatus, int deleteFlag){
    int min;
    Node *temp;
    if((*rootPtr) == NULL)
        return NULL;
    if((*rootPtr)->data == data){
        if ((*rootPtr)->left == NULL && (*rootPtr)->right == NULL){
            *heightChangedStatus = CHANGED;
            (*rootPtr) = NULL;
            return NULL;
        }
        else{
            //has child
            //if left == NULL, directly move rootptr right up to replace
            if((*rootPtr)->left == NULL){
                (*rootPtr)->bf --;
                (*rootPtr)->right->bf = (*rootPtr)->bf ++;
                (*rootPtr) = (*rootPtr)->right;
				*heightChangedStatus =  CHANGED;
                // temp = avlFindMin((*rootPtr)->right);
                // int heightChanged = 
            }
            //if right == NULL, directly move rootptr left up to replace
            else if((*rootPtr)->right == NULL){
                (*rootPtr)->bf++;
                (*rootPtr)->left->bf = (*rootPtr)->bf;
                (*rootPtr) = (*rootPtr)->left;
				*heightChangedStatus =  CHANGED;
            }
            //when node that to be deleted has both child right and left
            else{
                //attempt to delete the nearest value to "data" by setting deleteFlag to 1
                temp = _avlDelete(&(*(rootPtr))->left, data, heightChangedStatus, 1); //delete the data0

                //case where nearest node that found is at left of rootptr, then the node 
                //that found should retain its left child instead of overwrite by rootptr right child
                if((*rootPtr)->left != NULL){
                    temp->left = (*rootPtr)->left;
                    temp->right = (*rootPtr)->right;
                }
                else{
                    temp->right = (*rootPtr)->right;
                }

                //modify balance factor by heightChangedStatus
                if(*heightChangedStatus == CHANGED){
                    (*rootPtr)->bf ++;
                }
                //replace bf of node that found to the original bf
                temp->bf = (*rootPtr)->bf;

                //reattach the node that gets deleted
                (*rootPtr) = temp; 
                
                //balance right tree if needed
                *heightChangedStatus = avlBalanceRightTree(rootPtr);

                //condition where deletion wont cause reduce in height
                if ((*rootPtr)->bf != 0)
                {
                    *heightChangedStatus = NO_CHANGED;
                    return NULL;
                }
            }
            return NULL;
        }
		return NULL;
    }
    else if (data > (*rootPtr)->data){
        if((*rootPtr)->right == NULL){
            //perform deletion when its not the leaf
            //reattach the rootPtr now to previous caller to attach to the parent
            if(deleteFlag == 1){
                //return Node to be replace at top
                *heightChangedStatus = CHANGED;
                temp = (*rootPtr);
                (*rootPtr) = NULL;
                return temp;
            }
        }
        temp = _avlDelete(&(*(rootPtr))->right, data, heightChangedStatus, deleteFlag);
        if(temp != NULL && temp->left != NULL){
            //pass grandchild to child before replacing at the parent
            (*rootPtr)->right = temp->left;
            temp->left = NULL;
        }
        if (*heightChangedStatus == CHANGED)
        {
            (*rootPtr)->bf--;
            *heightChangedStatus = avlBalanceLeftTree(rootPtr);
            
        }
        else{
            heightChangedStatus = NO_CHANGED;
        }
        return temp;
    }
    else{
        temp = _avlDelete(&(*(rootPtr))->left, data, heightChangedStatus, 0);
        if (*heightChangedStatus == CHANGED)
        {
            (*rootPtr)->bf++;
            *heightChangedStatus = avlBalanceRightTree(rootPtr);
        }
        else
        {
            *heightChangedStatus =  NO_CHANGED;
        }
        return temp;
    }
	return NULL;
}

Node *avlFindMin(Node *root){
    if(root->left == NULL)
        return root;
    return avlFindMin(root->left);
}

Node *avlFindMax(Node *root)
{
    if (root->right == NULL)
        return root;
    return avlFindMin(root->right);
}