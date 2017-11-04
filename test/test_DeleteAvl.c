#include "unity.h"
#include "DeleteAvl.h"
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
 *    NULL    --->    NULL
 */
void test_deleteLeaf_given_NULL(void){
    Node *root;
    root = NULL;

    avlDeleteLeaf(&root, 0);
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

    avlDeleteLeaf(&root, 10);
    TEST_ASSERT_NULL(root);
}



