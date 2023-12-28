#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void clearMemory(struct Node* node)
{
  struct Node* current = node;
  struct Node* nextNode = NULL;
  while (current != NULL)
  {
    nextNode = current->next;
    free(current);
    current = nextNode;
  }
}

struct Node* makeNode(int data)
{
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->value = data;
  newNode->next = NULL;
  return newNode;
}

void printList(struct Node* node)
{
  struct Node* current = node;

  while (current != NULL)
  {
    printf("%d->", current->value);
    current = current->next;
  }
  if (current == NULL)
    printf("END");
}

void appendToList(struct Node* node, int value)
{
  struct Node* current = node;
  while (current->next != NULL)
    current = current->next;

  // Add new variable
  current->next = (struct Node*)malloc(sizeof(struct Node*));
  current->next->value = value;
  current->next->next = NULL;
}

void pushToList(struct Node** node, int value)
{
  struct Node* newNode;
  newNode = (struct Node*)malloc(sizeof(struct Node*));

  newNode->value = value;
  newNode->next = *node;
  *node = newNode;
}

int removeFirstItemFromList(struct Node** node)
{
  int removedValue = -1;
  struct Node* nextNode = NULL;
  
  if (*node == NULL)
    return -1;

  nextNode = (*node)->next;
  removedValue = (*node)->value;
  free(*node);
  *node = nextNode;

  return removedValue;
}

int removeLastItemFromList(struct Node* node)
{
  int removedValue = 0;
  // If there is only one item in the list, remove item
  if (node->next == NULL)
  {
    removedValue = node->value;
    free(node);
    return removedValue;
  }

  // Get to the second to last node in the list
  struct Node* current = node;
  while (current->next->next != NULL)
    current = current->next;

  // Now current points to the second to last item in list
  removedValue = current->next->value;
  free(current->next);
  current->next = NULL;
  return removedValue;
}

int removeFromList(struct Node** node, int position)
{
  int removedValue = -1;
  struct Node* current = *node;
  struct Node* tempNode = NULL;

  if (position == 0)
    return removeFirstItemFromList(node);

  for (int i = 0; i < position-1; i++)
  {
    if (current->next == NULL)
      return -1;
    current = current->next;
  }

  if (current->next == NULL)
    return -1;
  
  tempNode = current->next;
  removedValue = tempNode->value;
  current->next = tempNode->next;
  free(tempNode);
  
  return removedValue;
}

void reverseLinkedList(struct Node** node)
{
  struct Node* previous = NULL;
  struct Node* current = *node;
  struct Node* next = NULL;
  
  while (current != NULL)
  {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  *node = previous;
}

struct Node* addTwoLinkedLists(struct Node* first, struct Node* second)
{
  struct Node* resultNode = NULL;
  struct Node* tempNode;
  struct Node* previousNode = NULL;
  int carryOver = 0;
  int sum;

  while (first != NULL || second != NULL)
  {
    sum = carryOver + (first ? first->value : 0)
      + (second ? second->value : 0);

    carryOver = (sum >= 10) ? 1 : 0;
    sum = sum % 10;
    tempNode = makeNode(sum);

    if (resultNode == NULL)
      resultNode = tempNode;
    else
      previousNode->next = tempNode;

    previousNode = tempNode;

    if (first)
      first = first->next;
    if (second)
      second = second->next;
  }

  if (carryOver > 0)
    tempNode->next = makeNode(carryOver);

  return resultNode;
}

int getListLength(struct Node* node)
{
  int size = 0;
  while (node != NULL)
  {
    node = node->next;
    size++;
  }
  return size;
}


struct Node* subtractTwoLinkedLists(struct Node* first, struct Node* second)
{
  struct Node* resultNode = NULL;
  struct Node* tempNode;
  struct Node* previousNode = NULL;
  int carryOver = 0;
  int sum;

  while (first != NULL || second != NULL)
  {
    sum = carryOver + (first ? first->value : 0)
      + (second ? second->value : 0);

    carryOver = (sum >= 10) ? 1 : 0;
    sum = sum % 10;
    tempNode = makeNode(sum);

    if (resultNode == NULL)
      resultNode = tempNode;
    else
      previousNode->next = tempNode;

    previousNode = tempNode;

    if (first)
      first = first->next;
    if (second)
      second = second->next;
  }

  if (carryOver > 0)
    tempNode->next = makeNode(carryOver);

  return resultNode;
}

