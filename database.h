#ifndef DATABASE_H
#define DATABASE_H

#include "data.h"
#include "murmurhash.h"

#define INPUT_MAX_WORDS 15

void removeEOL(char *str, size_t len);
void splitInput(const char **splited, char *str, const char *del, int limit);
void dumpInput(const char **str);
void readInput(char *input_buffer);
void commandExecution(dbObj **db, const char **input_splited, char **returnValue);
void popObj(dbObj **const oldObj);

#endif
