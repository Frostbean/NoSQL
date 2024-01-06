#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "db.h"

void DBdelete(node **const db, const char *const key) {
    if (*db == NULL) {
        return;
    }
    if (!strcmp((*db)->key,key)) {
        popNode(db);
        return;
    }
    node *prev = NULL;
    node *cur = *db;
    while (strcmp(cur->key, key) && cur != NULL) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        return;
    }
    delAfterNode(prev);
    return;
}

// return a single node
node *DBfind(node **const db, const char *const key) {
    node *aNode;
    if (*db == NULL) {
        return NULL;
    }
    aNode = *db;
    do {
        if (streql(aNode->key,key)) {
            return aNode;
        }
        aNode = aNode->next;
    } while (aNode);
    return NULL;
}

// double pointer of value to return the value was got
void DBget(node **db, const char *const key, char **value) {
    const node *aNode = DBfind(db,key);
    if (aNode == NULL) {
        *value = realloc(*value, 1);
        *value = NULL;
        return;
    }
    size_t len = strlen(aNode->value);
    *value = (char *)realloc(*value, sizeof(len + 1));
    strncpy(*value,aNode->value,len);
}

void DBset(node **const db, const char *const key, const char *value) {
    node *aNode;
    
    aNode = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aNode) {
        pushNode(db);
        aNode = *db;
        setKey(aNode,key);       
    }
    setValue(aNode,value);
    printf("OK");
}
