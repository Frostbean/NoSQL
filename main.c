#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

int main() {
    // initial
    char *returnBuffer = (char *)malloc(0);
    dbObj *db = NULL;
    char input_buffer[100];
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

    // first input
    readInput(input_buffer);
    removeEOL(input_buffer, strlen(input_buffer));
    splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    while (strcmp(input_buffer, "quit")) {
        commandExecution(&db, input_splited, &returnBuffer);

        readInput(input_buffer);
        removeEOL(input_buffer, strlen(input_buffer));
        splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

        // dumpInput(input_splited);
    }

    // clear database
    while (db != NULL) {
        popObj(&db);
    }
    free(returnBuffer);

    return 0;
}