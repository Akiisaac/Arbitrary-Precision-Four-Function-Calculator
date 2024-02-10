#ifndef CALCULATOR_H
#define CALCULATOR_H

struct Node;  
char menu();
struct Node* makeNode(int data);
void printNode(struct Node* node);
void appendToNode(struct Node* node, int value);
int removeFirstItemFromList(struct Node** node);
int removeLastItemFromList(struct Node* node);
void reverseLinkedList(struct Node** node);
struct Node* getNumberFromUser();
struct Node* addTwoNodes(struct Node* first, struct Node* second);
struct Node* calculate(char operation, struct Node* firstNumber, struct Node* secondNumber);
struct Node* subtractLinkedListHelper(struct Node* l1, struct Node* l2);
struct Node* subtractLinkedLists(struct Node* firstNode, struct Node* secondNode);
int getListLength(struct Node* node);
struct Node* padZeros (struct Node* smallerNode, int difference);
void clearMemory(struct Node* node);

#endif // CALCULATOR_H
