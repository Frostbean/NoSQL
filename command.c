#include <stdio.h>
#include "command.h"

void commandExecution(dbObj **db, const char **input_splited, char **returnValue) {
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
            DBget(db, *(input_splited+1), returnValue);
            if (*returnValue != NULL) {
                printf("\"%s\"\n", *returnValue);
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
    else if (!strcmp(*(input_splited), "lpush")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBlpush(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "rpush")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBrpush(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "lpop")) {
        if (*(input_splited+1) != NULL) {
            DBlpop(db, *(input_splited+1), returnValue);
            if (*returnValue != NULL) {
                printf("\"%s\"\n", *returnValue);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "rpop")) {
        if (*(input_splited+1) != NULL) {
            DBrpop(db, *(input_splited+1), returnValue);
            if (*returnValue != NULL) {
                printf("\"%s\"\n", *returnValue);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "llen")) {
        if (*(input_splited+1) != NULL) {
            DBllen(db, *(input_splited+1));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "lrange")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL && *(input_splited+3) != NULL) {
            if (isNumber(*(input_splited+2)) && isNumber(*(input_splited+3))) {
                DBlrange(db, *(input_splited+1), atoi(*(input_splited+2)), atoi(*(input_splited+3)));
            }
            else {
                printf("Invalid number.\n");
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "hset")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL && *(input_splited+3) != NULL) {
            DBhset(db, *(input_splited+1), *(input_splited+2), *(input_splited+3));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "hget")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBhget(db, *(input_splited+1), *(input_splited+2), returnValue);
            if (*returnValue != NULL) {
                printf("\"%s\"\n", *returnValue);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "hdel")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBhdel(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "zadd")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL && *(input_splited+3) != NULL) {
            if (isNumber(*(input_splited+2))) {
                DBzadd(db, *(input_splited+1), atoi(*(input_splited+2)), *(input_splited+3));
            }
            else {
                printf("Score must be a number.\n");
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else {
        printf("Unknown Instruction\n");
    }
}