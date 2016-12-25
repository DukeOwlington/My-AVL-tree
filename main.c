#include "main.h"

// constant strings definitions
const static char * const menuChoice = "1: Insert node\n"
    "2: Delete node\n"
    "3: Find node\n"
    "4: Print tree in order\n"
    "5: Quit\n";

const static char * const incorrectMessage = "Incorrect choice";

enum MenuPoints {
  INSERT = 1,
  DELETE,
  FIND,
  PRINT_TREE,
  QUIT
};

// print menu points string
void PrintMenu(void) {
  puts(menuChoice);
}

int RequestNumber(char *purpouse) {
  int number = 0;
  int num_length = 10;
  int base = 10;
  printf("Enter the number you want to insert: ");
  char *string_number = CreateString(num_length);
  number = strtol(string_number, NULL, base);
  return number;
}

int main() {
  MenuPoints menu_point;
  Node *root = NULL;
  char *purpouse;
  int number = 0;
  while (menu_point != QUIT) {
    PrintMenu();
    scanf("%d", (int*) &menu_point);
    getchar();
    switch (menu_point) {
      case INSERT:
        purpouse = "Enter the number you want to insert: ";
        number = RequestNumber(purpouse);
        root = Insert(root, number);
        break;
      case DELETE:
        purpouse = "Enter the number you want to delete: ";
        number = RequestNumber(purpouse);
        root = DeleteNode(root, number);
        break;
      case FIND:
        purpouse = "Enter the number you want to find: ";
        number = RequestNumber(purpouse);
        Find(root, number);
        break;
      case PRINT_TREE:
        PrintInOrder(root);
        printf("\n");
        break;
      case QUIT:
        DeleteTree(root);
        break;
      default:
        puts(incorrectMessage);
        break;
    }
  }
  return EXIT_SUCCESS;
}
