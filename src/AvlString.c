#include "AvlString.h"
#include <string.h>

int compareStr(Node *str1, Node *str2){
  StrNode *strNode1 = (StrNode *)str1;
  StrNode *strNode2 = (StrNode *)str2;
  int result = strcmp(strNode1->data, strNode2->data);
  if(result > 0){
    return 1;
  }
  else if(result < 0){
    return -1;
  }
  else{
    return 0;
  }
}
