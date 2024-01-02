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

struct Node* padZeros (struct Node* smallerNode, int difference)
{
  // Base case
  if (smallerNode == NULL)
    return NULL;

  for (int i = 0; i < difference; ++i) 
  {
    struct Node* newNode = makeNode(0);
    newNode->next = smallerNode;
    smallerNode = newNode;
  }
  return smallerNode;
}

static int borrow;
struct Node* subtractLinkedListHelper(struct Node* l1, struct Node* l2)
{
if (l1 == NULL && l2 == NULL && borrow == 0)
        return NULL;
 
    struct Node* previous = subtractLinkedListHelper(
        l1 ? l1->next : NULL, l2 ? l2->next : NULL);
 
    int d1 = l1->value;
    int d2 = l2->value;
    int sub = 0;
 
    /* if you have given the value to next digit then
       reduce the d1 by 1 */
    if (borrow) {
        d1--;
        borrow = 0;
    }
 
    /* If d1 < d2, then borrow the number from previous
       digit. Add 10 to d1 and set borrow = true; */
    if (d1 < d2) {
        borrow = 1;
        d1 = d1 + 10;
    }
 
    /* subtract the digits */
    sub = d1 - d2;
 
    /* Create a Node with sub value */
    struct Node* current = makeNode(sub);
 
    /* Set the Next pointer as Previous */
    current->next = previous;
 
    return current;
}

struct Node* subtractLinkedLists(struct Node* firstNode, struct Node* secondNode)
{
  if (firstNode == NULL && secondNode == NULL)
    return NULL;

  int lengthOfFirstNode = getListLength(firstNode);
  int lengthOfSecondNode = getListLength(secondNode);
  struct Node* smallerListNode = NULL;
  struct Node* largerListNode = NULL;
  struct Node* tempNode1 = firstNode;
  struct Node* tempNode2 = secondNode;

  if (lengthOfFirstNode != lengthOfSecondNode)
  {
    largerListNode = (lengthOfFirstNode > lengthOfSecondNode) ? firstNode : secondNode;
    smallerListNode = (lengthOfFirstNode > lengthOfSecondNode) ? secondNode : firstNode;
    smallerListNode = padZeros(smallerListNode, abs(lengthOfFirstNode - lengthOfSecondNode));
  }
  else 
  {
    while (firstNode && secondNode)
    {
      if (firstNode->value != secondNode->value)
      {
        largerListNode = (firstNode->value > secondNode->value) ? tempNode1 : tempNode2;
        smallerListNode = (firstNode->value > secondNode->value) ? tempNode2 : tempNode1;
        break;
      }
      firstNode = firstNode->next;
      secondNode = secondNode->next;
    }
  }
  borrow = 0;
  return subtractLinkedListHelper(largerListNode, smallerListNode);
}

int multiplyTwoLists(struct Node *first, struct Node *second)
{
  // Assumes only one digit is in each node
  const int Mod = 1000000007;
  int number1 = 0;
  int number2 = 0;
  while (first || second)
  {
    if (first)
    {
      number1 = ((number1) * 10) % Mod + first->value;
      first = first->next;
    }

    if (second)
    {
      number2 = ((number2) * 10) % Mod + second->value;
      second = second->next;
    }
  }
  return ((number1 % Mod) * (number2 % Mod)) % Mod;
}

struct Node *divideList(struct Node *numerator, int denominator, int *remainder)
{
  if (denominator == 0)
  {
    printf("Error: Division by zero\n");
    exit(EXIT_FAILURE);
  }

struct Node *quotient = NULL;
  *remainder = 0;

  while (numerator != NULL)
  {
    int currentDigit = numerator->value + *remainder * 10;
    int quotientDigit = currentDigit / denominator;
    *remainder = currentDigit % denominator;

    if (!(quotient == NULL && quotientDigit == 0))
    {
      pushToList(&quotient, quotientDigit);
    }

    numerator = numerator->next;
  }

  return quotient;
}






