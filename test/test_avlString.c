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
void setUp(void)
{
}

void tearDown(void)
{
}

void test_avlString_cmp_ali_abu(void){
  TEST_ASSERT_EQUAL(1, compareStr("Acu", "Abu"));
}
