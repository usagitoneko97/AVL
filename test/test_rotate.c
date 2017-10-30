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
// NOTE :balance factor will not changed since its not handle by rotation
//     func

/**
 *      func
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

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node30, -1);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, -2);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
}
/**
 * Scenario : Node = -2
 *          : child Node = 0
 * expected : normal rotation at pivot node30,
 *            node20 is transfered to left side of node30
 *
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
    TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node30, 0);
    TEST_ASSERT_EQUAL_NODE(&node30, &node20, NULL, -2);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);

}

/**
 * Scenario : Node = 2
 *          : child Node = 1
 * expected : normal rotation, no child get transfered
 *
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

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node20, 1);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 2);
  TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

/**
 * Scenario : Node = -2
 *          : child Node = 0
 * expected : normal rotation. node30 get transfered to right of node25
 *
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
  TEST_ASSERT_EQUAL_NODE(&node35, &node25, &node40, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node40, NULL, NULL, 0);
}

/**
 *
 * Scenario : node = -2
 *            child Node = 1
 *            grandchild Node = 1
 * Expected :
 *          left right rotation at pivot node30, node20 get transfered to left
 *          of node30
 *     45(-2)                     35 (0)
 *    /     \                    /    \
 *   25(1)  50       ---->   25(-1)   45(0)
 *  / \                       / \     /  \
 * 5  35(0)                 5   30   40   50
 *   /  \
 *  30  40
 */
void test_rotateLeftRight(void){
  initNode(&node45, &node25, &node50, 0);
  initNode(&node25, &node5, &node35, 0);
  initNode(&node35,&node30 ,&node40, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node30, NULL, NULL, 0);
  initNode(&node40, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = rotateleftRight(&node45);

  TEST_ASSERT_EQUAL_NODE(&node35, &node25, &node45, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, &node5, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node45, &node40, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node40, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}

/**
 * scenario : node = 2
 *            childNode = -1
 *            grandChild Node = -1
 * expected : rotate right left at pivot 10, node15 get transfered to right of node10,
 *            node23 get transfered tp left of node 25
 *
 *
 *          10(2)                          20(0)
 *        /   \                          /   \
 *       5    25(-1)          --->    10(0) 25(0)
 *            /    \                  / \     /  \
 *          20(0)  50                5  15   23  50
 *         / \
 *        15  23
 */
void test_avlBalanceRightTree_given_above_expect_rotateRL_w_grandChild_0(void){
  initNode(&node10, &node5 ,&node25, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node25, &node20, &node50, 0);
  initNode(&node20, &node15, &node23, 0);
  initNode(&node23, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  rotateRightLeft(&node10);

  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node25, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, &node23, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node23, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
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
