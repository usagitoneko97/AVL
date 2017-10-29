#include "unity.h"
#include "rotate.h"
#include "Node.h"
#include "NodeHelper.h"

void setUp(void)
{
  initNodeData();
}

void tearDown(void)
{
}

/**
 *       30         10
 *      /          /  \
 *    10    ----> 5   30
 *   / \             /
 *  5  20          20
 */
void test_rotateRight(void)
{
    initNode(&node5, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);
    initNode(&node10, &node5, &node20, 0);
    initNode(&node30, &node10, NULL, 0);
    Node *root;
    root = rotateRight(&node30);
    TEST_ASSERT_EQUAL_PTR(&node10, root);
    TEST_ASSERT_EQUAL_PTR(&node5, root->left);
    TEST_ASSERT_EQUAL_PTR(&node30, root->right);
    TEST_ASSERT_EQUAL_PTR(&node20, node30.left);
    TEST_ASSERT_EQUAL_PTR(NULL, node20.right);
    TEST_ASSERT_EQUAL_PTR(NULL, node20.left);

    TEST_ASSERT_EQUAL_PTR(NULL, node5.right);
    TEST_ASSERT_EQUAL_PTR(NULL, node5.left);
}

/**
 *       25                      35
 *        \                     /  \
 *        35             ----> 25   40
 *       / \                    \
 *      30  40                   30
 */
void test_rotateLeft(void){
  initNode(&node30, NULL, NULL, 0);
  initNode(&node40, NULL, NULL, 0);
  initNode(&node35, &node30, &node40, 0);
  initNode(&node25,NULL ,&node35, 0);

  Node *root;
  root = rotateLeft(&node25);
  TEST_ASSERT_EQUAL_PTR(&node35, root);
  TEST_ASSERT_EQUAL_PTR(&node25, root->left);
  TEST_ASSERT_EQUAL_PTR(&node40, root->right);
  TEST_ASSERT_EQUAL_PTR(NULL, node25.left);
  TEST_ASSERT_EQUAL_PTR(&node30, node25.right);

  TEST_ASSERT_EQUAL_PTR(NULL, node30.right);
  TEST_ASSERT_EQUAL_PTR(NULL, node30.left);
  TEST_ASSERT_EQUAL_PTR(NULL, node40.right);
  TEST_ASSERT_EQUAL_PTR(NULL, node40.left);
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
void test_rotateLeftRight(void){
  initNode(&node20, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);
  initNode(&node15, NULL, &node20, 0);
  initNode(&node10, &node5, &node15, 0);
  initNode(&node30,&node10 ,&node50, 0);

  Node *root;
  root = rotateleftRight(&node30);
  TEST_ASSERT_EQUAL_PTR(&node15, root);
  TEST_ASSERT_EQUAL_PTR(&node10, root->left);
  TEST_ASSERT_EQUAL_PTR(&node30, root->right);
  TEST_ASSERT_EQUAL_PTR(&node20, node30.left);
  TEST_ASSERT_EQUAL_PTR(&node50, node30.right);
  TEST_ASSERT_EQUAL_PTR(&node5, node10.left);
  TEST_ASSERT_EQUAL_PTR(NULL, node10.right);

  TEST_ASSERT_EQUAL_PTR(NULL, node5.right);
  TEST_ASSERT_EQUAL_PTR(NULL, node5.left);
  TEST_ASSERT_EQUAL_PTR(NULL, node20.right);
  TEST_ASSERT_EQUAL_PTR(NULL, node20.left);
  TEST_ASSERT_EQUAL_PTR(NULL, node50.right);
  TEST_ASSERT_EQUAL_PTR(NULL, node50.left);
}
