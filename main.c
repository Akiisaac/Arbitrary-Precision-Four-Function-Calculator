#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main()
{
  // 3 5 1
  struct Node* node = makeNode(2);
  reverseLinkedList(&node);
  printf("List one : ");
  printList(node);
  printf("\n");

  // 5 2 8
  struct Node* node2 = makeNode(8);
  reverseLinkedList(&node2);
  printf("List two : ");
  printList(node2);
  printf("\n");
  int denominator = 2;
  int remainder;
  struct Node* result = divideList(node2, denominator, &remainder);
  reverseLinkedList(&node2);
  printf("\ndivided value : ");
  printList(result);
  printf("\n");
  
  clearMemory(node);
  clearMemory(node2);
  clearMemory(result);

  return 0;
}

