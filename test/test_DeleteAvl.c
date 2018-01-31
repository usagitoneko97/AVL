#include "unity.h"
#include "DeleteAvl.h"
#include "NodeHelper.h"
#include "NodeVerifier.h"
#include "rotate.h"
#include "Node.h"
#include "AvlInteger.h"
#include "AddAvl.h"
#include "Exception.h"

IntegerNode node2, node3, node4, node7, node10Clone;
IntegerNode node1, node5, node10, node15, node20, node25, node30, node35, node40, node23;
IntegerNode node45, node50, node55, node60, node70;

Node node500, node600, node500, node600;
Node node1000, node2500, node4000, node5000, node5500;
StrNode nodeAli, nodeAbu, nodeBaba, nodeHgx, nodeJason;

void setUp(void)
{
    initIntegerNodeData();
}

void tearDown(void)
{
}

/**  
 *    NULL    --->    NULL
 */
void test_deleteLeaf_given_NULL(void){
    IntegerNode *root;
    root = NULL;

    Node *deletedNode = avlRemoveIntegerWithValue(&root, 0);
    TEST_ASSERT_NULL(deletedNode);
    TEST_ASSERT_NULL(root);
}

/** 
 *    10    delete node 15    10
 *   /         ---->          /
 *  5                        5
 */
void test_delete_remove_node_that_not_exists(void){
    initNode(&node10, &node5, NULL, -1);
    initNode(&node5, NULL, NULL, -1);
    IntegerNode *root;
    root = &node10;

    Node *deletedNode = avlRemoveIntegerWithValue(&root, 15);
    TEST_ASSERT_NULL(deletedNode);

}
/** 
 *       delete node10
 *  10      ---->         NULL
 */
void test_deleteLeaf_given_node10_expect_NULL(void)
{
    initNode(&node10, NULL, NULL, 0);
    IntegerNode *root;
    root = &node10;

    avlRemoveIntegerWithValue(&root, 10);
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
    IntegerNode *root;
    root = &node10;

    avlRemoveIntegerWithValue(&root, 5);
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
    IntegerNode *root;
    root = &node10;

    avlRemoveIntegerWithValue(&root, 15);
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
    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 15);
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
    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 1);
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
    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 10);
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
    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 10);
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
    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, &node5, &node15, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
}

/** 
 *    5    delete 1      5
 *   / \     -->         \ 
 *  1  10                10
 */
void test_deleteLeaf_balanceFactor_parent_no_change(void){
    initNode(&node5, &node1, &node10, 0);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node10, NULL, NULL, 0);

    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 1);
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, &node10, 1);
    // TEST_ASSERT_EQUAL(NO_CHANGED, heightChanged);
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
    IntegerNode *root;
    root = &node5;

    Node *deletedNode = avlRemoveIntegerWithValue(&root, 15);
    TEST_ASSERT_NOT_NULL(deletedNode);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 0);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
    // TEST_ASSERT_EQUAL(heightChanged, CHANGED);
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
    initNode(&node20, NULL, NULL, 0);
    initNode(&node1, NULL, NULL, 0);

    IntegerNode *root;
    root = &node5;

    Node *deletedNode = avlRemoveIntegerWithValue(&root, 15);
    TEST_ASSERT_NOT_NULL(deletedNode);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, &node20, 1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

/** 
 *    
 *         5                                 5 
 *       /  \                              /  \
 *      4    15      delete node 15       4   10 
 *     /    /  \          ---->          /   / \
 *    3   10  20                        3   7   20
 *       /
 *      7
 */
void test_deleteLeaf_given_deletedNode_left_right_Not_null_grandchild_notNULL_delete_15(void)
{
    initNode(&node5, &node4, &node15, 1);
    initNode(&node4, &node3, NULL, -1);
    initNode(&node15, &node10, &node20, -1);
    initNode(&node10, &node7, NULL, -1);

    initNode(&node3, NULL, NULL, 0);
    initNode(&node7, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);

    IntegerNode *root;
    root = &node5;

    avlRemoveIntegerWithValue(&root, 15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node4, &node10, 0);
    TEST_ASSERT_EQUAL_NODE(&node10, &node7, &node20, 0);
    TEST_ASSERT_EQUAL_NODE(&node3, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node7, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

/*
 *
 *         node3(1)                                       2  (2)                            5(0)
 *        /    \                                        /  \                              /   \
 *   node2(-1) node5(1)        remove node3            1   5 (1)    (rotate left)       2(0)  10(1)
 *    /       /     \             ----->                  / \            --->          / \     \
 * node1   node4   node10                                4   10                       1   4    20
 *                    \                                       \
 *                    node20                                  20 
 *                                                            
 *                                                          
 *
 */
void test_avlRemoveIntegerWithValue_3_expect_rotateAtParent(void)
{
    initNode(&node3, &node2, &node5, 1);
    initNode(&node2, &node1, NULL, -1);
    initNode(&node5, &node4, &node10, 1);
    initNode(&node10, NULL, &node20, 1);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);
    initNode(&node4, NULL, NULL, 0);

    initNode(&node15, NULL, NULL, 0);

    IntegerNode *root = &node3;
    avlRemoveIntegerWithValue(&root, 3);

    TEST_ASSERT_EQUAL_NODE(&node5, &node2, &node10, 0);
    TEST_ASSERT_EQUAL_NODE(&node2, &node1, &node4, 0);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, &node20, 1);

    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node4, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
}

/** 
 *     20 (-1)                     15 (0)
 *    /  \                       /  \
 *   5    35 (-1)  (delete 20)  5(0) 35(1) 
 *  / \    \            --->   / \    \
 * 1  15   40                 1   10  40
 *    /  
 *  10  
 */
void test_avlRemoveIntegerWithValue_replace_and_pass_grandChild_to_child(void){
    initNode(&node20, &node5, &node35, -1);
    initNode(&node5, &node1, &node15, 1);
    initNode(&node35, NULL, &node40, 1);
    initNode(&node15, &node10, NULL, -1);

    initNode(&node40, NULL, NULL, 0);
    initNode(&node1, NULL, NULL, 0);
    initNode(&node10, NULL, NULL, 0);

    IntegerNode *root = &node20;
    avlRemoveIntegerWithValue(&root, 20);

    TEST_ASSERT_EQUAL_NODE(&node15, &node5, &node35, 0);
    TEST_ASSERT_EQUAL_NODE(&node5, &node1, &node10, 0);
    TEST_ASSERT_EQUAL_NODE(&node35, NULL, &node40, 1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node40, NULL, NULL, 0);
}

/** 
 *           40                                 50
 *          /  \                               /  \
 *        30    60     remove node 40         35   60
 *         \   /  \       and rotateRL       / \    \
 *         35 50  70       ---->            30  45  70
 *            /
 *           45
 */
void test_avlRemoveIntegerWithValue_replace_and_rotate_rightLeft(void){
    initNode(&node40, &node30, &node60, 1);
    initNode(&node60, &node50, &node70, -1);
    initNode(&node30, NULL, &node35, 1);
    initNode(&node50, &node45, NULL, -1);
    initNode(&node35, NULL, NULL, 0);
    initNode(&node45, NULL, NULL, 0);
    initNode(&node70, NULL, NULL, 0);

    IntegerNode *root = &node40;
    avlRemoveIntegerWithValue(&root, 40);

    TEST_ASSERT_EQUAL_NODE(&node50, &node35, &node60, 0);
    TEST_ASSERT_EQUAL_NODE(&node35, &node30, &node45, 0);
    TEST_ASSERT_EQUAL_NODE(&node60, NULL, &node70, 1);
    TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node45, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node70, NULL, NULL, 0);
}

/** 
 *       50                                               40
 *      /  \              delete 50                      / \
 *     30  60    child rotate right before return      20  60
 *    /  \  \            --->                         / \   \
 *   20  40  70                                     10   30  70
 *  /
 * 10      
 */

void test_avlRemoveIntegerWithValue_replace_and_child_rotate_R(void)
{
    initNode(&node50, &node30, &node60, -1);
    initNode(&node30, &node20, &node40, -1);
    initNode(&node60, NULL, &node70, 1);
    initNode(&node20, &node10, NULL, -1);

    initNode(&node10, NULL, NULL, 0);
    initNode(&node40, NULL, NULL, 0);
    initNode(&node70, NULL, NULL, 0);
    
    IntegerNode *root = &node50;
    avlRemoveIntegerWithValue(&root, 50);

    TEST_ASSERT_EQUAL_NODE(&node40, &node20, &node60, 0);
    TEST_ASSERT_EQUAL_NODE(&node20, &node10, &node30, 0);
    TEST_ASSERT_EQUAL_NODE(&node60, NULL, &node70, 1);
    TEST_ASSERT_EQUAL_NODE(&node10, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node70, NULL, NULL, 0);
}

/** 
 *       50                                               40
 *      /  \              delete 50                      / \
 *     30  60    child rotate right before return      25  60
 *    /  \  \            --->                         / \   \
 *   20  40  70                                     20   30  70
 *    \
 *    25      
 */

void test_avlRemoveIntegerWithValue_replace_and_child_rotate_RL(void)
{
    initNode(&node50, &node30, &node60, -1);
    initNode(&node30, &node20, &node40, -1);
    initNode(&node60, NULL, &node70, 1);
    initNode(&node20, NULL, &node25, 1);

    initNode(&node25, NULL, NULL, 0);
    initNode(&node40, NULL, NULL, 0);
    initNode(&node70, NULL, NULL, 0);

    IntegerNode *root = &node50;
    avlRemoveIntegerWithValue(&root, 50);

    TEST_ASSERT_EQUAL_NODE(&node40, &node25, &node60, 0);
    TEST_ASSERT_EQUAL_NODE(&node25, &node20, &node30, 0);
    TEST_ASSERT_EQUAL_NODE(&node60, NULL, &node70, 1);
    TEST_ASSERT_EQUAL_NODE(&node20, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node30, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node70, NULL, NULL, 0);
}

/** 
 *       50                                               40
 *      /  \              delete 50                      / \
 *     30  60    child rotate right before return      20  60
 *    /  \  \                --->                     / \   \
 *   20  40  70                                     15   30  70
 *  / \                                                 /
 * 15  25                                              25  
 */

void test_avlRemoveIntegerWithValue_replace_and_child_rotate_R_rootPtr_balanceFactor_nochanged(void)
{
    initNode(&node50, &node30, &node60, -1);
    initNode(&node30, &node20, &node40, -1);
    initNode(&node60, NULL, &node70, 1);
    initNode(&node20, &node15, &node25, 0);

    initNode(&node15, NULL, NULL, 0);
    initNode(&node25, NULL, NULL, 0);
    initNode(&node40, NULL, NULL, 0);
    initNode(&node70, NULL, NULL, 0);

    IntegerNode *root = &node50;
    avlRemoveIntegerWithValue(&root, 50);

    TEST_ASSERT_EQUAL_NODE(&node40, &node20, &node60, -1);
    TEST_ASSERT_EQUAL_NODE(&node20, &node15, &node30, 1);
    TEST_ASSERT_EQUAL_NODE(&node60, NULL, &node70, 1);
    TEST_ASSERT_EQUAL_NODE(&node30, &node25, NULL, -1);

    TEST_ASSERT_EQUAL_NODE(&node15, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node25, NULL, NULL, 0);
    TEST_ASSERT_EQUAL_NODE(&node70, NULL, NULL, 0);
}

#define initTestNode(node, value)   _initTestNode((Node *)(node), value)
#define avlAddInteger_(root, node)  avlAddInteger((IntegerNode **)(root), (IntegerNode *)(node))



void _initTestNode(Node *node, uint32_t value) {
  node->data = (void *)(long long)value;
  node->balanceFactor = 0;
  node->left = NULL;
  node->right = NULL;
}

void test_avl_functional_test(void)
{
    IntegerNode *root = NULL;
    initNode(&node50, NULL, NULL, 0);
    initNode(&node30, NULL, NULL, 0);
    initNode(&node60, NULL, NULL, 0);
    initNode(&node20, NULL, NULL, 0);    
    initNode(&node15, NULL, NULL, 0); 
    /*initTestNode(&node50, 50);
    initTestNode(&node30, 30);
    initTestNode(&node60, 60);
    initTestNode(&node20, 20);
    initTestNode(&node15, 15);*/
    
    avlAddInteger(&root, &node50);
    avlAddInteger(&root, &node30);
    avlAddInteger(&root, &node60);
    avlAddInteger(&root, &node20);
    avlAddInteger(&root, &node15);

    printf("Start of my tests\n");
    
    avlRemoveIntegerWithValue(&root, 50);
    avlRemoveIntegerWithValue(&root, 30);
    avlRemoveIntegerWithValue(&root, 15);
    avlRemoveIntegerWithValue(&root, 20);
}

void test_avl_functional_test2(void)
{
    node1000.data = 1000;
    node2500.data = 2500;
    node4000.data = 4000;
    node5000.data = 5000;
    node5500.data = 5500;
    node500.data = 500;
    node600.data = 600;
    IntegerNode *root = NULL;
    initNode(&node1000, NULL, NULL, 0);
    initNode(&node2500, NULL, NULL, 0);
    initNode(&node4000, NULL, NULL, 0);
    initNode(&node5000, NULL, NULL, 0);    
    initNode(&node5500, NULL, NULL, 0); 
    initNode(&node500, NULL, NULL, 0);
    initNode(&node600, NULL, NULL, 0);
    /*    
    initTestNode(&node1000, 1000);
    initTestNode(&node2500, 2500);
    initTestNode(&node4000, 4000);
    initTestNode(&node5000, 5000);    
    initTestNode(&node5500, 5500);    
    initTestNode(&node500, 500);    
*/    
    avlAddInteger(&root, &node1000);
    avlAddInteger(&root, &node2500);
    avlAddInteger(&root, &node4000);
    avlAddInteger(&root, &node5000);
    avlAddInteger(&root, &node5500);
    avlAddInteger(&root, &node500);
    avlAddInteger(&root, &node600);

    /*    
    printf("Start of my tests\n");
    avlRemoveIntegerWithValue(&root, 5000);
    avlRemoveIntegerWithValue(&root, 3000);
    avlRemoveIntegerWithValue(&root, 1500);
    avlRemoveIntegerWithValue(&root, 2000);
*/
}

void xtest_test(void){
    node500.data = 500;
    printf("IntegerNode prev: %d", node500.data);
    IntegerNode *node500Test = (IntegerNode*)&node500;
    printf("IntegerNode : %d", node500Test->data);

    void *data = 500;
    int dataTest = (int)data;
    printf("data test is %d", dataTest);
}