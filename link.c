#include <stdlib.h>
#include "link.h"

void setKey(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aObj->key = (char *)malloc(len + 1);
    strncpy(aObj->key,buffer+'\0',len);
}

void setValueString(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aObj->value) {
        free(aObj->value);
    }
    aObj->value = (char *)malloc(len + 1);
    strncpy(aObj->value,buffer+'\0',len);
}

void setValueList(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aNode->value) {
        free(aNode->value);
    }
    aNode->value = (char *)malloc(len + 1);
    strncpy(aNode->value,buffer+'\0',len);
}

dbObj *createObj() {
    dbObj *aObj = malloc(sizeof(dbObj));
    aObj->key = NULL;
    aObj->value = NULL;
    aObj->next = NULL;
    aObj->type = -1;
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
}

dbObj *createList() {
    dbObj *aObj = createObj();
    node *aNode = createNode();
    aObj->list.leftMost = aNode;
    aObj->list.rightMost = aNode;
    aObj->type = 1;
}

void lpush(node **const leftMost, const char *buffer) {
    node *newNode = createNode();
    if (*leftMost == NULL) {
        *leftMost = createNode();
    }
    newNode->right = *leftMost;
    (*leftMost)->left = newNode;
    *leftMost = newNode;
    setValueList(*leftMost, buffer);
}

void rpush(node **rightMost, const char *buffer) {
    node *newNode = createNode();
    newNode->left = *rightMost;
    (*rightMost)->right = newNode;
    *rightMost = newNode;
    setValueList(*rightMost, buffer);
}

void lpop(node **leftMost, char **rValue) {
    node *delNode = *leftMost;
    *leftMost = (*leftMost)->right;
    (*leftMost)->left = NULL;
    size_t len = strlen(delNode->value);
    *rValue = (char *)realloc(*rValue, sizeof(len + 1));
    strncpy(*rValue,delNode->value,len);
    free(delNode);
}

void rpop(node **rightMost, char **rValue) {
    node *delNode = *rightMost;
    *rightMost = (*rightMost)->left;
    (*rightMost)->right = NULL;
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
        lpop(&(delObj->list.leftMost), &returnBuffer);
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