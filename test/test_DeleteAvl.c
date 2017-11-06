#include "unity.h"
#include "DeleteAvl.h"
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
 *      15
 *     /
 *    10
 *    /
 *   5
 */
void test_avlFindMin(void)
{
    initNode(&node15, &node10, NULL, 0);
    initNode(&node10, &node5, NULL, 0);
    initNode(&node5, NULL, NULL, 0);
    Node *root;
    root = &node15;

    Node *temp = avlFindMin(root);
    TEST_ASSERT_EQUAL_PTR(&node5, temp);
}

/*
 *
 *         node3(1)                                node3(1)                           node3(1)
 *        /    \                                   /    \                            /       \
 *   node2(-1) node5(1)                        node2   node5                      node2    node5
 *    /       /     \                           /      /   \                       /      /    \
 * node1   node4   node10   (add node15 )  node1    node4  node10 (rotate RL)  node1  node4   node15
 *                    \          --->                          \      --->                    /   \
 *                    node20                                  node20                      node10  node20
 *                                                            /
 *                                                          node15
 *
 */
void test_avlFindMin_given_above_expect_1(void)
{
    initNode(&node3, &node2, &node5, 1);
    initNode(&node2, &node1, NULL, -1);
    initNode(&node5, &node4, &node10, 1);
    initNode(&node10, NULL, &node20, 1);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);
    initNode(&node4, NULL, NULL, 0);

    initNode(&node15, NULL, NULL, 0);

    Node *root = &node3;
    Node *temp = avlFindMin(root);
    TEST_ASSERT_EQUAL_PTR(&node1, temp);
}
/**  
 *    NULL    --->    NULL
 */
void test_deleteLeaf_given_NULL(void){
    Node *root;
    root = NULL;

    avlDelete(&root, 0);
    TEST_ASSERT_NULL(root);
}   
/** 
 *       delete node10
 *  10      ---->         NULL
 */
void test_deleteLeaf_given_node10_expect_NULL(void)
{
    initNode(&node10, NULL, NULL, 0);
    Node *root;
    root = &node10;

    avlDelete(&root, 10);
    TEST_ASSERT_NULL(root);
}

/** 
 *    10    delete node 5    10
 *   /         ---->
 *  5
 */
void test_deleteLeaf_given_10_5_delete_5_expect_10(void){
    initNode(&node10, &node5, NULL, -1);
    initNode(&node5, NULL, NULL, -1);
    Node *root;
    root = &node10;
    
    avlDelete(&root, 5);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
}

/** 
 *    10    delete node 15    10
 *      \        ---->
 *      15
 */
void test_deleteLeaf_given_10_15_delete_15_expect_10(void)
{
    initNode(&node10, NULL, &node15, 1);
    Node *root;
    root = &node10;

    avlDelete(&root, 15);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
}

/** 
 *    
 *    5                          5
 *  /  \                      /    \
 * 1   10    delete node 15   1    10
 *      \        ---->
 *      15
 */
void test_deleteLeaf_given_10_15_delete_15_expect_10_with_1Parent(void)
{
    initNode(&node5, &node1, &node10, 1);
    initNode(&node10, NULL, &node15, 1);
    initNode(&node1, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 15);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 0);
}

/** 
 *    
 *    5                          5                            10
 *  /  \                          \                         /    \
 * 1   10    delete node 1        10     rotate left       5     15 
 *      \        ---->             \       ---->
 *      15                         15
 */
void test_deleteLeaf_given_5_1_10_15_delete_15_expect_rotateLeft(void)
{
    initNode(&node5, &node1, &node10, 1);
    initNode(&node10, NULL, &node15, 1);
    initNode(&node1, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
}

/** 
 *    
 *         5                          5                          3 
 *       /  \                        /                         /  \
 *      3   10    delete node 10    3     rotate right        1    5 
 *     /              ---->        /        ---->
 *    1                           1      
 */
void test_deleteLeaf_given_5_3_1_10_delete_10_expect_rotateRight(void)
{
    initNode(&node5, &node3, &node10, -1);
    initNode(&node3, &node1, NULL, -1);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node10, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 10);
    TEST_ASSERT_EQUAL_NODE(&node3, &node1, &node5, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
}

/** 
 *    
 *         5                          5                              3 
 *       /  \                        /                             /  \
 *      1   10    delete node 10    1     rotate Leftright        1    5 
 *      \               ---->        \         ---->
 *      3                            3      
 */
void test_deleteLeaf_given_5_3_1_10_delete_10_expect_rotateLeftRight(void)
{
    initNode(&node5, &node1, &node10, -1);
    initNode(&node1, NULL, &node3, 1);
    initNode(&node10, NULL, NULL, 0);
    initNode(&node3, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 10);
    TEST_ASSERT_EQUAL_NODE(&node3, &node1, &node5, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
}

/** 
 *    
 *         5                          5                              10 
 *       /  \                          \                            /  \
 *      1   15    delete node 1        15   rotate rightLeft       5   15 
 *         /           ---->           /      ---->
 *        10                          10     
 */
void test_deleteLeaf_given_5_3_1_10_delete_10_expect_rotateRightLeft(void)
{
    initNode(&node5, &node1, &node15, 1);
    initNode(&node15, &node10, NULL, -1);
    initNode(&node10, NULL, NULL, 0);
    initNode(&node1, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
}

/** 
 *    5    delete 1      5
 *   / \     -->         \ 
 *  1  10                10
 */
void test_deleteLeaf_bf_parent_no_change(void){
    initNode(&node5, &node1, &node10, 0);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node10, NULL, NULL, 0);

    Node *root;
    root = &node5;

    int heightChanged = avlDelete(&root, 1);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, &node10, 1);
    TEST_ASSERT_EQUAL(NO_CHANGED, heightChanged);
}

/** 
 *    
 *         5                             5 
 *       /  \                           /  \
 *      1   15    delete node 15       1   10 
 *         /           ---->       
 *        10                       
 */
void test_deleteNonLeaf_given_5_3_1_10_delete_15_expect_1_5_10(void)
{
    initNode(&node5, &node1, &node15, 1);
    initNode(&node15, &node10, NULL, -1);
    initNode(&node10, NULL, NULL, 0);
    initNode(&node1, NULL, NULL, 0);
    Node *root;
    root = &node5;

    avlDelete(&root, 15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 0);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
}

/** 
 *    
 *         5                               5 
 *       /  \                            /  \
 *      1   15     delete node 15       1   10 
 *         /  \          ---->               \
 *        10  20                             20
 */
void test_deleteLeaf_given_deletedNode_left_right_Not_null_delete_15(void)
{
    initNode(&node5, &node1, &node15, 1);
    initNode(&node15, &node10, &node20, 0);
    initNode(&node10, NULL, NULL, 0);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);

    Node *root;
    root = &node5;

    avlDelete(&root, 15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, &node20, 1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

