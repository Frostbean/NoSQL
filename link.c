#include <stdlib.h>

typedef struct NODE {
    char *key;
    char *value;
    struct NODE *next;
} node;

node *createNode() {
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    newNode->key = NULL;
    newNode->value = NULL;
    newNode->next = NULL;
    return newNode;
}

void pushNode(node **oldNode) {
    node *newNode = createNode();
    if (oldNode == NULL) {
        // *oldNode = newNode;
        *oldNode = createNode();
    }
    else {
        newNode->next = *oldNode;
        *oldNode = newNode;
    }
}

void freeNode(node *const delNode) {
    free(delNode->key);
    free(delNode->value);
    free(delNode);
}

void popNode(node **const oldNode) {
    node *delNode = *oldNode;
    if (oldNode == NULL) {
        return;
    }
    if ((*oldNode)->next == NULL) {
        *oldNode = NULL;
        freeNode(delNode);
        return;
    }
    *oldNode = (*oldNode)->next;
    freeNode(delNode);
    return;
}

void delAfterNode(node *const oldNode) {
    node *delNode = oldNode->next;
    oldNode->next = oldNode->next->next;
    freeNode(delNode);
    return;
}