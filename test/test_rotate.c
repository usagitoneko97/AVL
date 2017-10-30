#include "unity.h"
#include "rotate.h"
#include "Node.h"
#include "NodeHelper.h"
#include "NodeVerifier.h"

void setUp(void)
{
  initNodeData();
}

void tearDown(void)
{
}


/**
 *    Scenario : Node = -2
 *               child Node = -1
 *    Expected : Node = 0
 *               child Node = 0
 *
 *       30(-2)         10(0)
 *      /              /  \
 *    10(-1)  ---->   5   30(0)
 *   /
 *  5
 */
void test_rotateRight_m2_m1(void){
  initNode(&node30, &node10, NULL, -2);
  initNode(&node10, &node5, NULL, -1);
  initNode(&node5, NULL, NULL, 0);

  Node *root;
  root = rotateRight(&node30);

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
}
/**
 * Scenario : Node = -2
 *          : child Node = 0
 * expected : Node = 1
 *            child Node = -1
 *
 *       30(-2)         10(1)
 *      /              /  \
 *    10(0)   ---->   5   30
 *   / \                  /
 *  5  20               20
 */
void test_rotateRight_m2_m0(void)
{
    initNode(&node30, &node10, NULL, -2);
    initNode(&node10, &node5, &node20, 0);
    initNode(&node5, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);
    Node *root;
    root = rotateRight(&node30);
    TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node30, 1);
    TEST_ASSERT_EQUAL_NODE(&node30, &node20, NULL, -1);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);

}

/**
 * Scenario : Node = 2
 *          : child Node = 1
 * expected : Node = 0
 *            child Node = 0
 *     5                 10
 *      \               /  \
 *       10    --->    5   20
 *        \
 *         20
 */
void test_rotateLeft_p2_p1(void){
  initNode(&node5, NULL, &node10, 2);
  initNode(&node10, NULL,  &node20, 1);
  initNode(&node20, NULL, NULL, 0);

  rotateLeft(&node5);

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node20, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

/**
 * Scenario : Node = -2
 *          : child Node = 0
 * expected : Node = 1
 *            child Node = -1
 *       25(2)                   35
 *        \                     /  \
 *        35(0)         ----> 25   40
 *       / \                    \
 *      30  40                   30
 */
void test_rotateLeft_p2_p0(void){
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
 * Scenario : node = -2
 *            child Node = 1
 *            grandchild Node = 1
 * Expected :
 *     30(-2)                     15 (0)
 *    /     \                    /  \
 *   10(1)  50       ---->   10(-1) 30(0)
 *  / \                       /    /  \
 * 5  15(1)                 5    20   50
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
