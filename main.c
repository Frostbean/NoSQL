#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "command.h"

int main() {
    // initial
    node *db;
    char *value = (char *)malloc(0);
    db = NULL;
    char input_buffer[100];
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

    // first input
    readInput(input_buffer);
    removeEOL(input_buffer, strlen(input_buffer));
    splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    while (strcmp(input_buffer, "quit")) {
        // dumpInput(input_splited);

        // db = commandExecution(db, input_splited, value);
        commandExecution(&db, input_splited, &value);

        readInput(input_buffer);
        removeEOL(input_buffer, strlen(input_buffer));
        splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);
    }

    // clear database
    while (db != NULL) {
        popNode(&db);
    }

    return 0;
}