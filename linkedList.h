#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

struct Node 
{
  int value;
  struct Node* next;
};

void clearMemory(struct Node* node);
void printList(struct Node* head);
void appendToList(struct Node* head, int value);
void pushToList(struct Node** node, int value);
int removeFirstItemFromList(struct Node** node);
int removeLastItemFromList(struct Node* node);
int removeFromList(struct Node** node, int valueToRemove);
void reverseLinkedList(struct Node** node);
int getListLength(struct Node* node);
struct Node* padZeros (struct Node* smallerNode, int difference);
struct Node* makeNode(int data);
struct Node* addTwoLinkedLists(struct Node* first, struct Node* second);
struct Node* subtractLinkedLists(struct Node* list1, struct Node* list2);
struct Node* subtractLinkedListHelper(struct Node* l1, struct Node* l2);
int multiplyTwoLists(struct Node* first, struct Node* second);
struct Node *divideList(struct Node *numerator, int denominator, int *remainder);

#endif
