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

            //return the smallest value on the right
            //reattach the value to itself
            //perform avlDelete
            if((*rootPtr)->left == NULL){
                (*rootPtr)->bf --;
                (*rootPtr)->right->bf = (*rootPtr)->bf ++;

                (*rootPtr) = (*rootPtr)->right;
                // temp = avlFindMin((*rootPtr)->right);
                // int heightChanged = 
            }
            else if((*rootPtr)->right == NULL){
                (*rootPtr)->bf++;
                (*rootPtr)->left->bf = (*rootPtr)->bf;
                (*rootPtr) = (*rootPtr)->left;
            }
            else{
                // temp = avlFindMax((*rootPtr)->left);

                temp = _avlDelete(&(*(rootPtr))->left, data, heightChangedStatus, 1); //delete the data0
                if(*heightChangedStatus == CHANGED){
                    (*rootPtr)->bf ++;
                }
                temp->bf = (*rootPtr)->bf;
                temp->left = (*rootPtr)->left;
                temp->right = (*rootPtr)->right;
                (*rootPtr) = temp; //reattach the node that gets deleted
                if ((*rootPtr)->bf != 0)
                {
                    *heightChangedStatus = NO_CHANGED;
                    return NULL;
                }
                *heightChangedStatus = CHANGED;
            }
            *heightChangedStatus =  CHANGED;
            
        }
    }
    else if (data > (*rootPtr)->data){
        if((*rootPtr)->left == NULL && (*rootPtr)->left == NULL){
            if(deleteFlag == 1){
                //return Node to be replace at top
                *heightChangedStatus = CHANGED;
                temp = (*rootPtr);
                (*rootPtr) = NULL;
                return temp;
            }
        }
        temp = _avlDelete(&(*(rootPtr))->right, data, heightChangedStatus, 0);
        if (*heightChangedStatus == CHANGED)
        {
            (*rootPtr)->bf--;
            if((*rootPtr)->bf != 0 && (*rootPtr)->bf !=-2){
                *heightChangedStatus = NO_CHANGED;
            }
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
            if ((*rootPtr)->bf != 0 && (*rootPtr)->bf != 2)
            {
                *heightChangedStatus = NO_CHANGED;
            }
            *heightChangedStatus = avlBalanceRightTree(rootPtr);
        }
        else
        {
            *heightChangedStatus =  NO_CHANGED;
        }
        return temp;
    }
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