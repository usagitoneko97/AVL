#include "rotate.h"

/**
 *       25                      35
 *        \                     /  \
 *        35             ----> 25   40
 *       / \                    \
 *      30  40                   30
 */
Node *rotateLeft(Node *node){
  Node *root;
  root = node->right;
  if(root->left != NULL){
      node->right = node->right->left;
  }
  else{
    node->right = NULL;
  }
  root->left = node;
  return root;

}

/**
 *       30         10
 *      /          /  \
 *    10    ----> 5   30
 *   / \             /
 *  5  20          20
 */
Node *rotateRight(Node *node){
  Node *root;
  root = node->left;
  if(node->left->right != NULL){
    node->left = node->left->right;
  }
  else{
    node->left = NULL;
  }
    root->right = node;

  return root;
}

/**
 *
 *     30                      15
 *    /  \                    /  \
 *   10  50       ---->     10   30
 *  / \                    /    /  \
 * 5  15                  5    20   50
 *     \
 *     20
 */
Node *rotateleftRight(Node *node){
  Node *root, *temp;
  temp = rotateLeft(node->left);
  node->left = temp;
  root = rotateRight(node);
  return root;
}

//TODO test for this func
Node *rotateRightLeft(Node *node){
  Node *root, *temp;
  temp = rotateRight(node->right);
  node->right = temp;
  root = rotateLeft(node);
  return root;
}

int calcBF(Node *root){
  int leftHeight, rightHeight;
  if(root->left == NULL)
    leftHeight = -1;
  else
    leftHeight = nodeHeight(root->left);
  if(root->right == NULL){
    rightHeight = -1;
  }
  else
    rightHeight = nodeHeight(root->right);
  return (rightHeight-leftHeight);
}

int nodeHeight(Node *root){
  if(root == NULL){
    return -1;
  }
  if(nodeHeight(root->left) > nodeHeight(root->right)){
    return (1+nodeHeight(root->left));
  }
  else{
    return (1+nodeHeight(root->right));
  }
}
