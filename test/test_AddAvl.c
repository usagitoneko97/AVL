#include "unity.h"
#include "AddAvl.h"
#include "NodeHelper.h"
#include "nodeVerifier.h"
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
  TEST_ASSERT_EQUAL_NODE(&node5, &node1 , &node10, 1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 2);

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
  TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, -1);
  //FIXME bf should be 0
  TEST_ASSERT_EQUAL_NODE(&node10, NULL , NULL, -2);
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
  TEST_ASSERT_EQUAL_NODE(&node5, NULL , NULL, 1);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL , NULL, -2);
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
  TEST_ASSERT_EQUAL_NODE(&node5, NULL , NULL, 2);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL , NULL, -1);
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
  TEST_ASSERT_EQUAL_NODE(&node10, NULL , NULL, 2);
  TEST_ASSERT_EQUAL_NODE(&node20, NULL , NULL, -1);
}
