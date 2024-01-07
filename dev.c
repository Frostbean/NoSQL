#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "link.h"

// return address of a single obj
dbObj *DBfind(dbObj **const db, const char *const key) {
    dbObj *aObj;
    if (*db == NULL) {
        return NULL;
    }
    aObj = *db;
    do {
        if (!strcmp(aObj->key,key)) {
            return aObj;
        }
        aObj = aObj->next;
    } while (aObj);
    return NULL;
}

void DBllen(dbObj **const db, const char *const key) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db, key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    printf("Length: %d\n", llen(aObj));
}

void DBlrange(dbObj **const db, const char *const key, int lowBound, int highBound) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    const node *cur = aObj->list.leftMost;
    int count = 0;     // number of found node
    int pos = 0;       // current position
    int len = llen(aObj);
    if (len == 0) {
        printf("(empty array)\n");
    }
    if (lowBound < 0) {
        lowBound = len + lowBound;
    }
    if (highBound < 0) {
        highBound = len + highBound;
    }
    while (cur != NULL && pos < lowBound) {
        pos++;
        cur = cur->right;
    }
    while (cur != NULL && pos <= highBound) {
        count++;
        pos++;
        printf("%d) %s\n", count, cur->value);
        cur = cur->right;
    }
}

void DBlpush(dbObj **db, const char *key, const char *value) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db , key);
    // if no corresponding key found
    if (aObj == NULL) {
        pushObj(db, 1);
        setKey(*db, key);
        setValueList((*db)->list.leftMost, value);
        printf("OK\n");
        return;
    }
    lpush(aObj, value);
    printf("OK\n");
}

void DBrpush(dbObj **db, const char *key, const char *value) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db , key);
    // if no corresponding key found
    if (aObj == NULL) {
        pushObj(db, 1);
        setKey(*db, key);
        setValueList((*db)->list.leftMost, value);
        printf("OK\n");
        return;
    }
    rpush(aObj, value);
}

void DBlpop(dbObj **db, const char *key, char **returnValue) {
    dbObj *aObj;
    if (*db == NULL) {
        printf("(nil)\n");
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    lpop(aObj, returnValue);
    printf("Pop done\n");
}

void DBrpop(dbObj **db, const char *key, char **returnValue) {
    dbObj *aObj;
    if (*db == NULL) {
        printf("(nil)\n");
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    rpop(aObj, returnValue);
    printf("Pop done\n");
}

void commandExecution(dbObj **db, const char **input_splited, char **returnValue) {
    if (!strcmp(*(input_splited), "set")) {
        printf("set\n");
    }
    else if (!strcmp(*(input_splited), "get")) {
        printf("get\n");
    }
    else if (!strcmp(*(input_splited), "del")) {
        printf("del\n");
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
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "rpop")) {
        if (*(input_splited+1) != NULL) {
            DBrpop(db, *(input_splited+1), returnValue);
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
    else {
        printf("Unknown Instruction\n");
    }
}

int main() {
    char *returnBuffer = (char *)malloc(0);
    dbObj *db = NULL;
    char input_buffer[100];
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

    dbObj *aObj = createList();
    db = aObj;
    setKey(aObj, "111");
    printf("dbkey: %s\n", db->key);
    setValueList(aObj->list.leftMost, "1");

    // first input
    readInput(input_buffer);
    removeEOL(input_buffer, strlen(input_buffer));
    splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    while (strcmp(input_buffer, "quit")) {
        // dumpInput(input_splited);

        commandExecution(&db, input_splited, &returnBuffer);

        readInput(input_buffer);
        removeEOL(input_buffer, strlen(input_buffer));
        splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);
    }

    return 0;
}
