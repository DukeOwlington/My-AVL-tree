/*
 ============================================================================
 Name        : stringtools.h
 Author      : Maximov V.K.
 Version     : 0.1
 Description : Just some tools for working with C-strings
 ============================================================================
 */
#ifndef STRINGTOOLS_H_
#define STRINGTOOLS_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* lets you input as many characters as you want.
   If you'll reach out of given size, the string
   will increase in len_max value (length of string + len_max),
   and so on */
char *CreateString(unsigned int len_max);

// returns true if string is empty
bool isEmpty(char *passed_string);

#endif
