#include "calculator.h"

int main()
{
  // Start menu
  char operation = menu();

  // Get the two operands from user
  struct Node* number_1 = getNumberFromUser();
  struct Node* number_2;
  
  if (operation != '/')
    number_2 = getNumberFromUser();
  // Calculate and output
  calculate(operation, number_1, number_2);

  clearMemory(number_1);
  clearMemory(number_2);

  return 0;
}
