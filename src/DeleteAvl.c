#include "DeleteAvl.h"
#include <stdio.h>
#include "rotate.h"

int avlDelete(Node **rootPtr, int data){
    int min;
    Node *temp;
    if((*rootPtr) == NULL)
        return NO_CHANGED;
    if((*rootPtr)->data == data){
        if ((*rootPtr)->left == NULL && (*rootPtr)->right == NULL){
            (*rootPtr) = NULL;
            return CHANGED;
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
                temp = avlFindMax((*rootPtr)->left);
                // int heightChanged = avlDelete(rootPtr, temp->data); //delete the data
                avlDelete(rootPtr, temp->data); //delete the data

                temp->bf = (*rootPtr)->bf;
                temp->left = (*rootPtr)->left;
                temp->right = (*rootPtr)->right;
                (*rootPtr) = temp; //reattach the node that gets deleted
                if ((*rootPtr)->bf != 0)
                {
                    return NO_CHANGED;
                }
                return CHANGED;
            }
            return CHANGED;
            
        }
    }
    else if (data > (*rootPtr)->data){
        int heightChanged = avlDelete(&(*(rootPtr))->right, data);
        if(heightChanged == CHANGED){
            (*rootPtr)->bf--;
            if((*rootPtr)->bf != 0 && (*rootPtr)->bf !=-2){
                return NO_CHANGED;
            }
            return avlBalanceLeftTree(rootPtr);
        }
        else{
            return NO_CHANGED;
        }
    }
    else{
        int heightChanged = avlDelete(&(*(rootPtr))->left, data);
        if (heightChanged == CHANGED)
        {
            (*rootPtr)->bf++;
            if ((*rootPtr)->bf != 0 && (*rootPtr)->bf != 2)
            {
                return NO_CHANGED;
            }
            return avlBalanceRightTree(rootPtr);
        }
        else
        {
            return NO_CHANGED;
        }
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