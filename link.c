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

dbObj *createTable(int size) {
    dbObj *aObj = createObj();
    aObj->hashMap.size = size;
    aObj->hashMap.nodes = (hashNode **)malloc(sizeof(hashNode *) * size);
    for (int i = 0; i < size; i++) {
        aObj->hashMap.nodes[i] = NULL;
    }
    aObj->type = 3;
    return aObj;
}

dbObj *createSet() {
    dbObj *aObj = createObj();
    aObj->set = NULL;
    aObj->type = 2;
    return aObj;
}

hashNode *createHashNode() {
    hashNode *aHash = (hashNode *)malloc(sizeof(hashNode));
    aHash->field = NULL;
    aHash->value = NULL;
    aHash->next = NULL;
    return aHash;
}

setNode *createSetNode() {
    setNode *aSet = (setNode *)malloc(sizeof(setNode));
    aSet->score = 0;
    aSet->member = NULL;
    aSet->next = NULL;
    return aSet;
}

void extendTable(dbObj *const aObj) {
    hashNode **oldMap = aObj->hashMap.nodes;
    int oldSize = aObj->hashMap.size;
    int newSize = 2 * oldSize;
    hashNode *cur;
    hashNode **newMap = malloc (sizeof(hashNode *) * newSize);
    hashNode *tmpHash = NULL;
    aObj->hashMap.size = newSize;
    aObj->hashMap.load = 0;
    for (int i = 0; i < oldSize; i++) {
        if (oldMap[i] != NULL) {
            tmpHash = createHashNode();
            setHashNode(tmpHash, oldMap[i]->field, oldMap[i]->value);

            cur = newMap[getHash(oldMap[i]->field, newSize)];
            while (cur != NULL && cur->next != NULL) {

            }
            if (cur == NULL) {
                newMap[getHash(oldMap[i]->field, newSize)] = tmpHash;
                aObj->hashMap.load += 1;
            }
            else if (cur->next == NULL) {
                cur->next = tmpHash;
            }
            free(oldMap[i]);
        }
    }
    aObj->hashMap.nodes = newMap;
    free(oldMap);
}

void shortenTable(dbObj *const aObj) {
    hashNode **oldMap = aObj->hashMap.nodes;
    int oldSize = aObj->hashMap.size;
    int newSize = oldSize / 2;
    hashNode *cur;
    hashNode **newMap = malloc (sizeof(hashNode *) * newSize);
    hashNode *tmpHash = NULL;
    aObj->hashMap.size = newSize;
    aObj->hashMap.load = 0;
    for (int i = 0; i < oldSize; i++) {
        if (oldMap[i] != NULL) {
            tmpHash = createHashNode();
            setHashNode(tmpHash, oldMap[i]->field, oldMap[i]->value);

            cur = newMap[getHash(oldMap[i]->field, newSize)];
            while (cur != NULL && cur->next != NULL) {

            }
            if (cur == NULL) {
                newMap[getHash(oldMap[i]->field, newSize)] = tmpHash;
                aObj->hashMap.load += 1;
            }
            else if (cur->next == NULL) {
                cur->next = tmpHash;
            }
            free(oldMap[i]);
        }
    }
    aObj->hashMap.nodes = newMap;
    free(oldMap);
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
    else if (type == 2) {
        newObj = createSet();
    }
    else if (type == 3) {
        newObj = createTable(INITIAL_TABLE_SIZE);
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

void freeHashNode(hashNode *delNode) {
    free(delNode->field);
    free(delNode->value);
    free(delNode);
}

void freeList(dbObj *const delObj) {
    char *returnBuffer = (char *)malloc(0);
    free(delObj->key);
    while (delObj->list.leftMost != NULL) {
        lpop(delObj, &returnBuffer);
    }
    free(returnBuffer);
    free(delObj);
}

void freeTable(dbObj *const delObj) {
    free(delObj->key);
    for (int i = 0; i < delObj->hashMap.size; i++) {
        if ((delObj->hashMap.nodes)[i] != NULL) {
            while((delObj->hashMap.nodes)[i] != NULL) {
                popHashNode(delObj, i);
            }
        }
    }
    free(delObj->hashMap.nodes);
    free(delObj);
}

void freeSetNode(setNode *aNode) {
    free(aNode->member);
    free(aNode);
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
    else if (delObj->type == 3) {
        freeTable(delObj);
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
    else if (delObj->type == 3) {
        freeTable(delObj);
    }
    return;
}

void hset(dbObj *const aObj, const char *field, const char *value) {
    if (aObj->hashMap.load * 1.00 / aObj->hashMap.size > 0.70) {
        printf("High Load Factor\n");
        extendTable(aObj);
        return;
    }

    int pos = getHash(field, aObj->hashMap.size);
    hashNode *const aHash = createHashNode();
    hashNode *prev;
    hashNode *cur = (aObj->hashMap.nodes)[pos];

    // empty field
    if (cur == NULL) {
        setHashNode(aHash, field, value);
        (aObj->hashMap.nodes)[pos] = aHash;
        aObj->hashMap.load += 1;
        return;
    }
    // hash collision
    while (cur != NULL) {
        prev = cur;
        // same field
        if (!strcmp(cur->field, field)) {
            // free(cur->value);
            // size_t len = strlen(value);
            // cur->value = (char *)malloc(len + 1);
            // strncpy(cur->value,value+'\0',len+1);
            return;
        }
        cur = cur->next;
    }
    // hash collision but no same field
    setHashNode(aHash, field, value);
    prev->next = aHash;
    return;
}

void popHashNode(const dbObj *aObj, const int pos) {
    hashNode *delHash = (aObj->hashMap.nodes)[pos];
    if (delHash == NULL) {
        return;
    }
    (aObj->hashMap.nodes)[pos] = (aObj->hashMap.nodes)[pos]->next;
    freeHashNode(delHash);
    return;
}

void delAfterHashNode(hashNode *prevHash) {
    hashNode *delHash = prevHash->next;
    prevHash->next = prevHash->next->next;
    freeHashNode(delHash);
    return;
}

void zadd(dbObj *const aObj, const int score, const char *member) {
    setNode *cur = aObj->set;
    if (cur == NULL) {
        pushSetNode(&(aObj->set), score, member);
        return;
    }
    // find same member
    while (cur != NULL) {
        if (!strcmp(cur->member, member)) {
            cur->score = score;
            return;
        }
        cur = cur->next;
    }
    // no same member
    setNode *prev;
    cur = aObj->set;
    while (cur != NULL) {
        prev = cur;
        if (cur->score > score) {
            insertAfterSetNode(prev, score, member);
            return;
        }
        cur = cur->next;
    }
    insertAfterSetNode(prev, score, member);
    return;
}

void pushSetNode(setNode **oldNode, const int score, const char *value) {
    setNode *newNode = createSetNode();
    if (*oldNode == NULL) {
        *oldNode = newNode;
        setValueSet(newNode, value);
        newNode->score = score;
        return;
    }
    newNode->next = *oldNode;
    setValueSet(newNode, value);
    newNode->score = score;
    *oldNode = newNode;
    return;
}

void insertAfterSetNode(setNode *prev, const int score, const char *value) {
    setNode *newNode = createSetNode();
    if (prev->next == NULL) {
        prev->next = newNode;
        setValueSet(newNode, value);
        newNode->score = score;
        return;
    }
    newNode->next = prev->next;
    prev->next = newNode;
    setValueSet(newNode, value);
    newNode->score = score;
    return;    
}

void delAfterSetNode(setNode *prev) {
    setNode *delNode = prev->next;
    prev->next = prev->next->next;
    freeSetNode(delNode);
    return;
}
