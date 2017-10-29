#include "unity.h"
#include "AddAvl.h"
#include "NodeHelper.h"
#include "nodeVerifier.h"
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
 *    node1                  node1                     node5
 *        \         ----->     \            ---->      /    \
 *        node5                 node5               node1    node10
 *                               \
 *                               node10
 */
void test_AddAvl_given_node1_node5_add_node10(void){
  initNode(&node1, NULL, &node5, 0);
  initNode(&node5, NULL, NULL, 0);
  initNode(&node10, NULL, NULL, 0);

  Node *root = &node1;
}
