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
struct Node* makeNode(int data);
struct Node* addTwoLinkedLists(struct Node* first, struct Node* second);

#endif
