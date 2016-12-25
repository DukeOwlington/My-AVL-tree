#include "stringtools.h"

char *CreateString(unsigned int len_max) {
  unsigned int current_size = 0;
  char *string = malloc(len_max);
  current_size = len_max;

  if (string != NULL) {
    int c = EOF;
    unsigned int i = 0;
    //accept user input until hit enter or end of file
    while ((c = getchar()) != '\n' && c != EOF) {
      string[i++] = (char) c;
      //if i reached maximize size then realloc size
      if (i == current_size) {
        current_size = i + len_max;
        string = realloc(string, current_size);
      }
    }
    string[i] = '\0';
  }
  return string;
}

bool isEmpty(char *string) {
  if (string[0] == '\0' || string == NULL)
    return true;
  else
    return false;
}
