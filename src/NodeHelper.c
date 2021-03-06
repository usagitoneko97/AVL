#include "NodeHelper.h"

void initStringNodeData(void)
{
  nodeAli.data = "Ali";
  nodeAbu.data = "Abu";
  nodeBaba.data = "Baba";
  nodeHgx.data = "Hgx";
  nodeJason.data = "Jason";
}

void initIntegerNodeData(void)
{
  node1.data = 1;
  node2.data = 2;
  node3.data = 3;
  node4.data = 4;
  node5.data = 5;
  node7.data = 7;
  node10.data = 10;
  node15.data = 15;
  node20.data = 20;
  node25.data = 25;
  node30.data = 30;
  node35.data = 35;
  node40.data = 40;
  node45.data = 45;
  node50.data = 50;
  node55.data = 55;
  node60.data = 60;
  node70.data = 70;
  node23.data = 23;
  node65.data = 65;
  node75.data = 75;
  node80.data = 80;
  node90.data = 90;
  node100.data = 100;
  node120.data = 120;
  node150.data = 150;
  node200.data = 200;
  node250.data = 250;
  
  node10Clone.data = 10;
}

void _initNode(Node *node, Node *left, Node *right, int balanceFactor)
{
  node->left = left;
  node->right = right;
  node->balanceFactor = balanceFactor;
}
