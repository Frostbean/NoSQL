#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "alloc.h"

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

void DBlrange(const dbObj *const aObj , int lowBound, int highBound) {
    const node *cur = aObj->list.leftMost;
    int count = 0;     // number of found node
    int pos = 0;       // current position
    int len = llen(aObj);
    if (len == 0) {
        printf("(empty array)");
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

void DBlpush(dbObj *aObj ,const char *buffer) {
    lpush(&(aObj->list.leftMost), buffer);
}

void DBrpush(dbObj *aObj ,const char *buffer) {
    rpush(&(aObj->list.rightMost), buffer);
}

void DBlpop(dbObj *aObj ,char **rValue) {
    lpop(&(aObj->list.leftMost), rValue);
}

void DBrpop(dbObj *aObj ,char **rValue) {
    rpop(&(aObj->list.rightMost), rValue);
}

void commandExecution(dbObj **db, const char **input_splited, char **value) {
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
        printf("lpush\n");
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            // DBset(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "rpush")) {
        printf("rpush\n");
    }
    else if (!strcmp(*(input_splited), "lpop")) {
        printf("lpop\n");
    }
    else if (!strcmp(*(input_splited), "rpop")) {
        printf("rpop\n");
    }
    else if (!strcmp(*(input_splited), "llen")) {
        printf("llen\n");
        if (*(input_splited+1) != NULL) {
            DBllen(db, *(input_splited+1));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (!strcmp(*(input_splited), "lrange")) {
        printf("lrange\n");
    }
    else {
        printf("Unknown Instruction\n");
    }
}

int main() {
    char *returnBuffer = (char *)malloc(0);
    dbObj *db = NULL;

    // node *nodeA = createNode();
    // setValue(nodeA, "hello");
    // lpush(&nodeA, "12345");
    // lpop(&nodeA, &returnBuffer);
    // printf("%s \n", returnBuffer);
    // printf("%s \n", nodeA->value);

    dbObj *aObj = createList();
    db = aObj;
    setKey(aObj, "111");
    printf("dbkey: %s\n", db->key);
    setValueList(aObj->list.leftMost, "1");
    DBlpush(aObj, "2");
    DBlpush(aObj, "3");
    DBlpush(aObj, "4");
    DBlpush(aObj, "5");
    DBrpush(aObj, "6");
    DBlpop(aObj, &returnBuffer);
    DBrpop(aObj, &returnBuffer);
    // lpop(&(aObj->list.leftMost), &returnBuffer);

    // DBllen(aObj);
    DBlrange(aObj, 0, 100);

    char input_buffer[100];
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

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
