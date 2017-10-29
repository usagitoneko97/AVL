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

/**
 *     1
 *      \
 *       5
 */
void test_nodeHeight_given_1(void){
  initNode(&node1, NULL, &node5, 1);
  initNode(&node5, NULL, NULL, 0);

  int height = nodeHeight(&node1);

  TEST_ASSERT_EQUAL(1, height);
}

/**
 *      1
 *       \
 *        5
 *         \
 *          10
 *           \
 *            20
 */
void test_nodeHeight_given_3(void){
  initNode(&node1, NULL, &node5, 3);
  initNode(&node5, NULL, &node10, 2);
  initNode(&node10, NULL, &node20, 1);
  initNode(&node20, NULL, NULL, 0);

  TEST_ASSERT_EQUAL(3, nodeHeight(&node1));
}

/**
 *         25
 *        /  \
 *       20   30
 *      /     \
 *     15     35
 *    /
 *  10
 */
void test_nodeHeight_given_above(void){
  initNode(&node25, &node20, &node30, -1);
  initNode(&node20, &node15, NULL, -2);
  initNode(&node15, &node10, NULL, 2);
  initNode(&node10, NULL, NULL, 1);

  initNode(&node30, NULL, &node35, 0);
  initNode(&node35, NULL, NULL, 3);

  TEST_ASSERT_EQUAL(3, nodeHeight(&node25));
}
