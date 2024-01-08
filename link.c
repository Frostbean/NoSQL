#include <stdlib.h>
#include "link.h"

dbObj *createObj() {
    dbObj *aObj = malloc(sizeof(dbObj));
    aObj->key = NULL;
    aObj->value = NULL;
    aObj->next = NULL;
    aObj->type = -1;
    return aObj;
}

node *createNode() {
    node *aNode = malloc(sizeof(node));
    aNode->value = NULL;
    aNode->left = NULL;
    aNode->right = NULL;
    return aNode;
}

dbObj *createString() {
    dbObj *aObj = createObj();
    aObj->type = 0;
    return aObj;
}

dbObj *createList() {
    dbObj *aObj = createObj();
    node *aNode = createNode();
    aObj->list.leftMost = aNode;
    aObj->list.rightMost = aNode;
    aObj->type = 1;
    return aObj;
}

dbObj *createTable() {
    dbObj *aObj = createObj();
    aObj->hashMap.size = INITIAL_TABLE_SIZE;
    aObj->hashMap.nodes = (hashNode **)malloc(sizeof(hashNode *) * INITIAL_TABLE_SIZE);
    for (int i = 0; i < INITIAL_TABLE_SIZE; i++) {
        aObj->hashMap.nodes[i] = NULL;
    }
    aObj->type = 3;
    return aObj;
}

hashNode *createHashNode() {
    hashNode *aHash = (hashNode *)malloc(sizeof(hashNode));
    aHash->field = NULL;
    aHash->value = NULL;
    aHash->next = NULL;
    return aHash;
}

void extendTable() {

}

void shortenTable() {

}

void lpush(dbObj *const aObj, const char *buffer) {
    node *newNode = createNode();
    if (aObj->list.leftMost == NULL) {
        aObj->list.leftMost = createNode();
        aObj->list.rightMost = aObj->list.leftMost;
    }
    newNode->right = aObj->list.leftMost;
    aObj->list.leftMost->left = newNode;
    aObj->list.leftMost = newNode;
    setValueList(aObj->list.leftMost, buffer);
}

void rpush(dbObj *const aObj, const char *buffer) {
    node *newNode = createNode();
    if (aObj->list.rightMost == NULL) {
        aObj->list.leftMost = createNode();
        aObj->list.rightMost = aObj->list.leftMost;
    }
    newNode->left = aObj->list.rightMost;
    aObj->list.rightMost->right = newNode;
    aObj->list.rightMost = newNode;
    setValueList(aObj->list.rightMost, buffer);
}

void lpop(dbObj *const aObj, char **rValue) {
    node *delNode = aObj->list.leftMost;
    aObj->list.leftMost = aObj->list.leftMost->right;
    if ((aObj->list.leftMost != NULL)) {
        aObj->list.leftMost->left = NULL;
    }
    else {
        aObj->list.rightMost = NULL;
    }
    size_t len = strlen(delNode->value);
    *rValue = (char *)realloc(*rValue, sizeof(len + 1));
    strncpy(*rValue,delNode->value,len);
    free(delNode);
}

void rpop(dbObj *const aObj, char **rValue) {
    node *delNode = aObj->list.rightMost;
    aObj->list.rightMost = aObj->list.rightMost->left;
    if ((aObj->list.rightMost != NULL)) {
        aObj->list.rightMost->right = NULL;
    }
    else {
        aObj->list.leftMost = NULL;
    }
    size_t len = strlen(delNode->value);
    *rValue = (char *)realloc(*rValue, sizeof(len + 1));
    strncpy(*rValue,delNode->value,len);
    free(delNode);
}

int llen(const dbObj *const aObj) {
    const node *cur = aObj->list.leftMost;
    int count = 0;
    while (cur != NULL) {
        count++;
        cur = cur->right;
    }
    return count;
}

void pushObj(dbObj **oldObj, const int type) {
    dbObj *newObj;
    if (type == 0) {
        newObj = createString();
    }
    else if (type == 1) {
        newObj = createList();
    }
    else if (type == 3) {
        newObj = createTable();
    }
    else {
        return;
    }
    if (*oldObj == NULL) {
        // *oldNode = createNode();
        *oldObj = newObj;
    }
    else {
        newObj->next = *oldObj;
        *oldObj = newObj;
    }
}

void freeString(dbObj *const delObj) {
    free(delObj->key);
    free(delObj->value);
    free(delObj);
}

// void freeNode(dbObj *const delObj) {

// }

void freeList(dbObj *const delObj) {
    char *returnBuffer = (char *)malloc(0);
    free(delObj->key);
    while (delObj->list.leftMost != NULL) {
        lpop(delObj, &returnBuffer);
    }
    free(delObj);
}

void popObj(dbObj **const oldObj) {
    dbObj *delObj = *oldObj;
    if (*oldObj == NULL) {
        return;
    }
    // if ((*oldNode)->next == NULL) {
    //     *oldNode = NULL;
    //     freeNode(delNode);
    //     return;
    // }
    *oldObj = (*oldObj)->next;
    if (delObj->type == 0) {
        freeString(delObj);
    }
    else if (delObj->type == 1) {
        freeList(delObj);
    }
    return;
}

void delAfterObj(dbObj *const oldObj) {
    dbObj *delObj = oldObj->next;
    oldObj->next = oldObj->next->next;
    if (delObj->type == 0) {
        freeString(delObj);
    }
    else if (delObj->type == 1) {
        freeList(delObj);
    }
    return;
}

void hset(dbObj *aObj, const char *field, const char *value) {
    int pos = getHash(field, aObj->hashMap.size);
    hashNode *aHash = createHashNode();
    setHashNode(aHash, field, value);
    if ((aObj->hashMap.nodes)[pos] == NULL) {
        (aObj->hashMap.nodes)[pos] = aHash;
    }
    else {
        // hash collision
        (aObj->hashMap.nodes)[pos]->next = aHash;
    }
    return;
}