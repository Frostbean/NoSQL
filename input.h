#ifndef input_c
#define input_h

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FGETS_MAX_LENGTH 100
#define INPUT_MAX_WORDS 15

void removeEOL(char *str, size_t len);
void splitInput(const char **splited, char *str, const char *del, int limit);
void dumpInput(const char **str);
void readInput(char *input_buffer);
int isNumber(const char *str);

#endif
