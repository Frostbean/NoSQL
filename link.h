#ifndef link_c
#define link_h

#include <stdlib.h>
#include <string.h>

// doubly linked list
typedef struct node {
    char *value;
    struct node *left;
    struct node *right;
} node;

// type 0: string, type 1: list
typedef struct dbObj {
    char *key;
    union {
        char *value;    // type 0
        struct {
            node *leftMost;  // type 1, leftmost node of list
            node *rightMost; // type 1, rightmost node of list
        } list;
    };
    struct dbObj *next;
    int type;
} dbObj;

void setKey(dbObj *aObj, const char *buffer);
void setValueString(dbObj *aObj, const char *buffer);
void setValueList(node *aNode, const char *buffer);
dbObj *createObj();
node *createNode();
dbObj *createString();
dbObj *createList();
void pushObj(dbObj **oldObj, const int type);
void popObj(dbObj **const oldObj);
void delAfterObj(dbObj *const oldObj);
void freeString(dbObj *const delObj);
void freeList(dbObj *const delObj);
void lpush(dbObj *const aObj, const char *buffer);
void rpush(dbObj *const aObj, const char *buffer);
void lpop(dbObj *const aObj, char **rValue);
void rpop(dbObj *const aObj, char **rValue);
int llen(const dbObj *const aObj);

#endif