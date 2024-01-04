#ifndef command_c
#define command_h

#include <stdio.h>
#include "db.h"

#define streql !strcmp

void commandExecution(node **db, const char **input_splited, char **value) {
    if (streql(*(input_splited), "set")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBset(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (streql(*(input_splited), "get")) {
        if (*(input_splited+1) != NULL) {
            DBget(db, *(input_splited+1), value);
            if (*value == NULL) {
                // printf("No corresponding key.\n");
                printf("(nil)\n");
            }
            else {
                // printf("Value is \"%s\".\n", *value);
                printf("\"%s\"\n", *value);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (streql(*(input_splited), "del")) {
        if (*(input_splited+1) != NULL) {
            DBdelete(db, *(input_splited+1));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else {
        printf("Unknown Instruction\n");
    }
}

#endif
