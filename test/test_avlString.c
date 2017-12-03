#include "unity.h"
#include "AddAvl.h"
#include "NodeHelper.h"
#include "NodeVerifier.h"
#include "rotate.h"
#include "Node.h"
#include "Exception.h"
#include "CException.h"
#include "AvlInteger.h"
#include "AvlString.h"

#define initNodeStr(node, left, right, bf)  initNode((Node*)node, (Node*)left, (Node*)right, bf)

CEXCEPTION_T ex;
void setUp(void)
{
  initStringNodeData();
}

void tearDown(void)
{
}

void test_avlString_cmp_ali_abu(void){

  Node *nodeAliNode = (Node*)&nodeAli;
  Node *nodeAbuNode = (Node*)&nodeAbu;
  TEST_ASSERT_EQUAL(1, compareStr(nodeAliNode, nodeAbuNode));

}

/**
       add Ali, Abu, Baba
*  NULL       --->                Ali
*                                /  \
*                              Abu  Baba
*/
void test_add_ali_abu_baba_to_NULL_expect_balancedTree(void){
  StrNode *root = NULL;
  Try{
    avlAddString(&root, &nodeAli);
    avlAddString(&root, &nodeAbu);
    avlAddString(&root, &nodeBaba);
  }Catch(ex){
    dumpException(ex);
  }

  TEST_ASSERT_EQUAL_NODE(&nodeAli, &nodeAbu, &nodeBaba, 0);
}
/**
       add Ali, Baba, hgx
*  NULL       --->             Ali                 Baba
*                               \    rotateLeft   /   \
*                              Baba    --->      Ali   Hgx
*                                 \
*                                  Hgx
*/
void test_add_ali_baba_hgx_to_NULL_expect_balancedTree(void){
  StrNode *root = NULL;
  Try{
    avlAddString(&root, &nodeAli);
    avlAddString(&root, &nodeBaba);
    avlAddString(&root, &nodeHgx);
  }Catch(ex){
    dumpException(ex);
  }

  TEST_ASSERT_EQUAL_NODE(&nodeBaba, &nodeAli, &nodeHgx, 0);
}
