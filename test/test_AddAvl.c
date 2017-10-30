#include "unity.h"
#include "AddAvl.h"
#include "NodeHelper.h"
#include "NodeVerifier.h"
#include "rotate.h"
void setUp(void)
{
  initNodeData();
}

void tearDown(void)
{
}

/**
 *    NULL -->  node1
 */
void test_AddAvl_given_NULL_add_1Node(void)
{
  Node *root = NULL;
  addAvl(&root, &node5);

  TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
}

/**
 *    node1  ---->   node1
 *                      \
 *                      node5
 */
void test_AddAvl_given_node1_add_node5(void){
  initNode(&node1, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);

  Node *root = &node1;
  addAvl(&root, &node5);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, &node5, 1);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
}

/**
 *    node5  ---->   node5
 *                  /
 *                node1
 */
void test_AddAvl_given_node5_add_node1(void){
  initNode(&node1, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);

  Node *root = &node5;
  addAvl(&root, &node1);
  TEST_ASSERT_EQUAL_NODE(&node5, &node1, NULL, -1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
}

/**
 *    node1                  node1                     node5 (0)
 *        \         ----->     \            ---->      /    \
 *        node5                 node5               node1    node10
 *                               \
 *                               node10
 */
void test_AddAvl_given_node1_node5_add_node10(void){
  initNode(&node1, NULL, &node5, 1);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node10, NULL, NULL, 0);

  Node *root = &node1;
  addAvl(&root, &node10);
  TEST_ASSERT_EQUAL_NODE(&node5, &node1 , &node10, 0);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);

}

/**
 *        node10 (1)          node10 (-2)             node5(0)
 *        /          --->    /              -->      /    \
 *     node5               node5  (-1)            node1  node10
 *                         /
 *                        node1  (0)
 */
void test_AddAvl_given_node10_node5_add_node1(void){
  initNode(&node10, &node5, NULL, -1);

  initNode(&node5, NULL, NULL, 0);
  initNode(&node1, NULL, NULL, 0);

  Node *root = &node10;
  addAvl(&root, &node1);
  //FIXME bf should be 0
  TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 0);
  //FIXME bf should be 0
  TEST_ASSERT_EQUAL_NODE(&node10, NULL , NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL , NULL, 0);
}

/**
 *     node15               node15(-2)                node10
 *     /    (add node10)    /          (rotate LR)    /   \
 *   node5      --->       node5(1)       ---->   node5   node15
 *                             \
 *                             node10
 */
void test_addAvl_given_node15_node5_add_node10(void){
  initNode(&node15, &node5, NULL, -1);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node10, NULL, NULL, 0);

  Node *root = &node15;
  addAvl(&root, &node10);

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL , NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL , NULL, 0);
}

/**
 *     node5        (add node10)     node5      (rotate RL)   node10
 *         \           --->              \         --->       /    \
 *         node15                        node15            node5   node15
 *                                       /
 *                                     node10
 *
 *
 */
void test_addAvl_given_node5_node15_add_node10_expect_rotateRL(void){
  initNode(&node5, NULL, &node15, 1);
  initNode(&node15, NULL, NULL, 0);
  initNode(&node10, NULL, NULL, 0);

  Node *root = &node5;
  addAvl(&root, &node10);

  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL , NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL , NULL, 0);
}

/*
 *
 *      node5                           node5                     node5
 *     /     \                          /   \                     /    \
 *   node1   node10   (add node15 )  node1  node10 (rotate RL)  node1 node15
 *             \      --->                      \      --->           /   \
 *             node20                          node20             node10  node20
 *                                             /
 *                                           node15
 *
 */
void test_addAvl_given_above_expect_rotateRL(void){
  initNode(&node5, &node1, &node10, 1);
  initNode(&node10, NULL, &node20, 0);
  initNode(&node1, NULL, NULL, 0);
  initNode(&node20, NULL, NULL, 0);
  initNode(&node15, NULL, NULL, 0);

  Node *root = &node5;
  addAvl(&root, &node15);

  TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node15, 1);
  TEST_ASSERT_EQUAL_NODE(&node15, &node10 , &node20, 0);

  //TODO change bf after rotate
  TEST_ASSERT_EQUAL_NODE(&node1, NULL , NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, NULL , NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node20, NULL , NULL, 0);
}


//--------------------------------------------------------------------------
/**
 *    Scenario : Node = -2
 *               child Node = -1
 *    Expected : Node = 0
 *               child Node = 0
 *               heightChanged = true
 *
 *       30(-2)         10(0)
 *      /              /  \
 *    10(-1)  ---->   5   30(0)
 *   /
 *  5
 */
void test_avlBalanceLeftTree_given_30_10_5(void){
  initNode(&node30, &node10, NULL, -2);
  initNode(&node10, &node5, NULL, -1);
  initNode(&node5, NULL, NULL, 0);

  Node *root;
  root = (&node30);
  avlBalanceLeftTree(&root);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
}

/**
 * Scenario : Node = -2
 *          : child Node = 0
 * expected : Node = 1
 *            child Node = -1
 *            heightChanged = true
 *       30(-2)         10(1)
 *      /              /  \
 *    10(0)   ---->   5   30
 *   / \                  /
 *  5  20               20
 */
void test_avlBalanceLeftTree_given30_10_5_20(void)
{
    initNode(&node30, &node10, NULL, -2);
    initNode(&node10, &node5, &node20, 0);
    initNode(&node5, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);
    Node *root;
    root = &node30;
    avlBalanceLeftTree(&root);
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
void test_avBalanceRightTree_given_5_10_20(void){
  initNode(&node5, NULL, &node10, 2);
  initNode(&node10, NULL,  &node20, 1);
  initNode(&node20, NULL, NULL, 0);

  Node *root;
  root = &node5;
  avlBalanceRightTree(&root);

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
void test_avlBalanceRightTree_given_25_35_30_40(void){
  initNode(&node30, NULL, NULL, 0);
  initNode(&node40, NULL, NULL, 0);
  initNode(&node35, &node30, &node40, 0);
  initNode(&node25,NULL ,&node35, 2);

  Node *root;
  root = (&node25);
  avlBalanceRightTree(&root);

  TEST_ASSERT_EQUAL_NODE(&node35, &node25, &node40, -1);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, &node30, 1);
  TEST_ASSERT_EQUAL_NODE(&node40, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);

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
void test_avlBalanceLeftTree_given_above_expect_rotateLR_grandChild_1(void){
  initNode(&node30,&node10 ,&node50, -2);
  initNode(&node10, &node5, &node15, 1);
  initNode(&node15, NULL, &node20, 1);
  initNode(&node20, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node30;
  avlBalanceLeftTree(&root);
  TEST_ASSERT_EQUAL_NODE(&node15, &node10, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, NULL, -1);
  TEST_ASSERT_EQUAL_NODE(&node30, &node20, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}

/**
 *
 * Scenario : node = -2
 *            child Node = 1
 *            grandchild Node = 0
 * Expected :
 *     30(-2)                     20 (0)
 *    /     \                    /  \
 *   10(1)  50       ---->   10(0) 30(0)
 *  / \                     / \    /  \
 * 5  20(0)                5  15  25   50
 *   /  \
 *  15    25
 */
void test_avlBalanceLeftTree_given_above_expect_rotateLR_w_grandChild_0(void){
  initNode(&node30,&node10 ,&node50, -2);
  initNode(&node10, &node5, &node20, 1);
  initNode(&node20, &node15, &node25, 0);
  initNode(&node15, NULL, NULL, 0);
  initNode(&node25, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node30;
  avlBalanceLeftTree(&root);
  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, &node25, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}


/**
 *
 * Scenario : node = -2
 *            child Node = 1
 *            grandchild Node = -1
 * Expected :
 *     30(-2)                     20 (0)
 *    /     \                    /  \
 *   10(1)  50       ---->   10(0) 30(1)
 *  / \                     / \       \
 * 5  20(-1)               5  15      50
 *   /
 *  15
 */
void test_avlBalanceLeftTree_given_above_expect_rotateLR_w_grandChild_m1(void){
  initNode(&node30,&node10 ,&node50, -2);
  initNode(&node10, &node5, &node20, 1);
  initNode(&node20, &node15, NULL, -1);
  initNode(&node15, NULL, NULL, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node30;
  avlBalanceLeftTree(&root);
  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node30, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node30, NULL, &node50, 1);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}

/**
 * scenario : node = 2
 *            childNode = -1
 *            grandChild Node = -1
 *
 *          10(2)                          20(0)
 *        /   \                          /   \
 *       5    25(-1)          --->      10(0) 25(1)
 *            /    \                  /  \     \
 *          20(-1) 50                5  15    50
 *         /
 *        15
 */
void test_avlBalanceRightTree_given_above_expect_rotateRL_w_grandChild_m1(void){
  initNode(&node10, &node5 ,&node25, 2);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node25, &node20, &node50, -1);
  initNode(&node20, &node15, NULL, -1);
  initNode(&node15, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node10;
  avlBalanceRightTree(&root);

  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node25, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, &node50, 1);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}

/**
 * scenario : node = 2
 *            childNode = -1
 *            grandChild Node = -1
 *
 *          10(2)                          20(0)
 *        /   \                          /   \
 *       5    25(-1)          --->    10(-1) 25(0)
 *            /    \                  /      /  \
 *          20(1)  50                5      23  50
 *           \
 *           23
 */
void test_avlBalanceRightTree_given_above_expect_rotateRL_w_grandChild_1(void){
  initNode(&node10, &node5 ,&node25, 2);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node25, &node20, &node50, -1);
  initNode(&node20, NULL, &node23, 1);
  initNode(&node23, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node10;
  avlBalanceRightTree(&root);

  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node25, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, NULL, -1);
  TEST_ASSERT_EQUAL_NODE(&node25, &node23, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node23, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}

/**
 * scenario : node = 2
 *            childNode = -1
 *            grandChild Node = -1
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
  initNode(&node10, &node5 ,&node25, 2);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node25, &node20, &node50, -1);
  initNode(&node20, &node15, &node23, 0);
  initNode(&node23, NULL, NULL, 0);
  initNode(&node50, NULL, NULL, 0);

  Node *root;
  root = &node10;
  avlBalanceRightTree(&root);

  TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node25, 0);
  TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
  TEST_ASSERT_EQUAL_NODE(&node25, &node23, &node50, 0);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node23, NULL, NULL, 0);
  TEST_ASSERT_EQUAL_NODE(&node50, NULL, NULL, 0);
}
