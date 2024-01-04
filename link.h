#ifndef link_c
#define link_h

#include <stdlib.h>

typedef struct NODE {
    char *key;
    char *value;
    struct NODE *next;
} node;

node *createNode();
void pushNode(node **oldNode);
void freeNode(node *const delNode);
void popNode(node **const oldNode);
void delAfterNode(node *const oldNode);

#endif