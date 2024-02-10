#include <stdlib.h>
#include <stdio.h>
#include "calculator.h"

struct Node
{
  int value;
  struct Node* next;
};

char menu()
{
  char operation;
  printf("...Simple Terminal Calulator...\n");
  printf("Operations available are - \n");
  printf("Addition (+) | Subtraction (-) | Multiplication (*) | Division (/) \n");
  printf("What would you like to do : ");
  scanf("%c", &operation);
  return operation;
}

struct Node* makeNode(int data)
{
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->value = data;
  newNode->next = NULL;
  return newNode;
}

void printNode(struct Node* node)
{
  struct Node* current = node;

  while (current != NULL)
  {
    printf("%d", current->value);
    current = current->next;
  }
}

struct Node* getNumberFromUser()
{
  int digit;
  char exit;
  struct Node* number = makeNode(0);

  printf("Enter number, digit by digit(press '99' to end)): \n");

  do {
    scanf("%d", &digit);
    appendToNode(number, digit);
  }while(digit != 99);

  // Remove the first node value, 0 with the 
  // first value from user input
  removeLastItemFromList(number);
  removeFirstItemFromList(&number);
  printf("\n");
  return number;
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

void appendToNode(struct Node* node, int value)
{
  struct Node* current = node;
  while (current->next != NULL)
    current = current->next;

  // Add new variable
  current->next = (struct Node*)malloc(sizeof(struct Node*));
  current->next->value = value;
  current->next->next = NULL;
}

struct Node* addTwoNodes(struct Node* first, struct Node* second)
{
  // Initialize pointers for the result, temporary node, and previous node
  struct Node* resultNode = NULL;
  struct Node* tempNode;
  struct Node* previousNode = NULL;

  // Variables for carry-over and sum
  int carryOver = 0;
  int sum;

  // Iterate through the linked lists until both are exhausted
  while (first != NULL || second != NULL)
  {
    // Calculate the sum of current nodes and the carry-over
    sum = carryOver + (first ? first->value : 0) 
      + (second ? second->value : 0);

    // Update carry-over based on the sum
    carryOver = (sum >= 10) ? 1 : 0;
    
    // Update sum to be a single digit
    sum = sum % 10;

    // Create a new node with the calculated sum
    tempNode = makeNode(sum);

    // Connect the new node to the result list
    if (resultNode == NULL)
      resultNode = tempNode;
    else
      previousNode->next = tempNode;

    // Update the previous node to the current temporary node
    previousNode = tempNode;

    // Move to the next nodes in the input linked lists
    if (first)
      first = first->next;
    if (second)
      second = second->next;
  }

  // If there's a carry-over after the loop, add a new node to the result
  if (carryOver > 0)
    tempNode->next = makeNode(carryOver);

  // Return the result linked list
  return resultNode;
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

  // Now, current points to the second to last item in list
  removedValue = current->next->value;
  free(current->next);
  current->next = NULL;
  return removedValue;
}

// Static variable to track borrowing during subtraction
static int borrow;

// Function to subtract two linked lists (helper function)
struct Node* subtractLinkedListHelper(struct Node* l1, struct Node* l2)
{
  // Base case: If both linked lists are exhausted and no borrowing is needed, return NULL
  if (l1 == NULL && l2 == NULL && borrow == 0)
    return NULL;

  // Recursive call for the next nodes in both linked lists
  struct Node* previous = subtractLinkedListHelper(l1 ? l1->next : NULL, l2 ? l2->next : NULL);

  // Extract the current digits from the linked lists
  int d1 = l1->value;
  int d2 = l2->value;
  int sub = 0;

  // If there's a borrow from the previous subtraction, decrement d1 and reset the borrow flag
  if (borrow)
  {
    d1--;
    borrow = 0;
  }

  // If d1 is less than d2, set the borrow flag and adjust d1 by adding 10
  if (d1 < d2)
  {
    borrow = 1;
    d1 = d1 + 10;
  }

  // Calculate the result of subtraction
  sub = d1 - d2;

  // Create a new node with the result of subtraction
  struct Node* current = makeNode(sub);

  // Link the current node to the previously calculated result
  current->next = previous;

  // Return the current node, representing the result of the subtraction
  return current;
}

// Actual subtraction function
struct Node* subtractLinkedLists(struct Node* firstNode, struct Node* secondNode)
{
  // Base case: If both linked lists are empty, return NULL
  if (firstNode == NULL && secondNode == NULL)
    return NULL;

  // Calculate the lengths of the linked lists
  int lengthOfFirstNode = getListLength(firstNode);
  int lengthOfSecondNode = getListLength(secondNode);

  // Pointers to track the smaller and larger linked lists
  struct Node* smallerListNode = NULL;
  struct Node* largerListNode = NULL;
  struct Node* tempNode1 = firstNode;
  struct Node* tempNode2 = secondNode;

  // Determine the larger and smaller linked lists
  if (lengthOfFirstNode != lengthOfSecondNode)
  {
    largerListNode = (lengthOfFirstNode > lengthOfSecondNode) ? firstNode : secondNode;
    smallerListNode = (lengthOfFirstNode > lengthOfSecondNode) ? secondNode : firstNode;
    // Pad the smaller linked list with zeros to make lengths equal
    smallerListNode = padZeros(smallerListNode, abs(lengthOfFirstNode - lengthOfSecondNode));
  }
  else
  {
    // Compare individual digits until a difference is found
    while (firstNode && secondNode)
    {
      if (firstNode->value != secondNode->value)
      {
        // Determine the larger and smaller linked lists based on the first differing digit
        largerListNode = (firstNode->value > secondNode->value) ? tempNode1 : tempNode2;
        smallerListNode = (firstNode->value > secondNode->value) ? tempNode2 : tempNode1;
        break;
      }
      firstNode = firstNode->next;
      secondNode = secondNode->next;
    }
  }

  // Reset the borrow flag before performing subtraction
  borrow = 0;

  // Call the helper function to perform subtraction and return the result
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

void pushToList(struct Node** node, int value)
{
  struct Node* newNode;
  newNode = (struct Node*)malloc(sizeof(struct Node*));

  newNode->value = value;
  newNode->next = *node;
  *node = newNode;
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

struct Node* calculate(char operation, struct Node* firstNumber, struct Node* secondNumber)
{
  struct Node* result = makeNode(0);
  int numberResult;
  int remainder;
  int denominator;

  switch (operation)
  {
    case '+' :
      printNode(firstNumber);
      printf("\n + \n");
      printNode(secondNumber);
      printf("\n = \n");

      reverseLinkedList(&firstNumber);
      reverseLinkedList(&secondNumber);
      result = addTwoNodes(firstNumber, secondNumber);
      
      reverseLinkedList(&result);
      printNode(result);
      printf("\n");
      break;

    case '-' :
      printNode(firstNumber);
      printf("\n - \n");
      printNode(secondNumber);
      printf("\n = \n");

      result = subtractLinkedLists(firstNumber, secondNumber);
      
      printNode(result);
      printf("\n");
      break;

    case '*' :
      printNode(firstNumber);
      printf("\n * \n");
      printNode(secondNumber);
      printf("\n = \n");

      numberResult = multiplyTwoLists(firstNumber, secondNumber);
      
      printf("%d", numberResult);
      printf("\n");
      break;

    case '/' :
      printf("What's your denominator? Enter in full length (max : 5 digits): ");
      scanf("%d", &denominator);
      printNode(firstNumber);
      printf("\n / \n");
      printf("%d", denominator);
      printf("\n = \n");

      result = divideList(firstNumber, denominator, &remainder);
      
      reverseLinkedList(&result);
      printNode(result);
      printf("\n");
      break;

    default : printf("Invalid Operation\n");
  }
  return result;
}

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
