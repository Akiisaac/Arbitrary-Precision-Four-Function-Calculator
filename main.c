#include <stdio.h>
#include "linkedList.h"

int main()
{
  // 3 5 1
  struct Node* node = makeNode(3);
  pushToList(&node, 9);
  printf("List one : ");
  printList(node);
  printf("\n");

  // 5 2 8
  struct Node* node2 = makeNode(5);
  printf("List two : ");
  pushToList(&node2, 2);
  pushToList(&node2, 8);
  printList(node2);
  printf("\n");
  
  struct Node* resultNode = NULL;
  resultNode = addTwoLinkedLists(node, node2);

  reverseLinkedList(&resultNode);
  printList(resultNode);
  printf("\n");

  clearMemory(node);
  clearMemory(node2);
  clearMemory(resultNode);

  return 0;
}

