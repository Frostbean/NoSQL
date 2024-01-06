#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// doubly linked list
typedef struct node {
    char *value;
    struct node *left;
    struct node *right;
} node;

// typedef struct dList {
//     node *leftMost;
//     node *rightMost;
// } dList;

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

void setKey(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aObj->key = (char *)malloc(len + 1);
    strncpy(aObj->key,buffer+'\0',len);
}

void setValue(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aNode->value) {
        free(aNode->value);
    }
    aNode->value = (char *)malloc(len + 1);
    strncpy(aNode->value,buffer+'\0',len);
}

node *createNode() {
    node *aNode = malloc(sizeof(node));
    aNode->value = NULL;
    aNode->left = NULL;
    aNode->right = NULL;
    return aNode;
}

void lpush(node **leftMost, const char *buffer) {
    node *newNode = createNode();
    if (*leftMost == NULL) {
        *leftMost = createNode();
    }
    newNode->right = *leftMost;
    (*leftMost)->left = newNode;
    *leftMost = newNode;
    setValue(*leftMost, buffer);
}

void rpush(node **rightMost, const char *buffer) {
    node *newNode = createNode();
    newNode->left = *rightMost;
    (*rightMost)->right = newNode;
    *rightMost = newNode;
    setValue(*rightMost, buffer);
}

void lpop(node **leftMost, char **rValue) {
    node *delNode = *leftMost;
    *leftMost = (*leftMost)->right;
    (*leftMost)->left = NULL;
    size_t len = strlen(delNode->value);
    *rValue = (char *)realloc(*rValue, sizeof(len + 1));
    strncpy(*rValue,delNode->value,len);
    printf("%s \n", *rValue);
    free(delNode);
}

void rpop(node **rightMost, char **rValue) {
    node *delNode = *rightMost;
    *rightMost = (*rightMost)->left;
    (*rightMost)->right = NULL;
    size_t len = strlen(delNode->value);
    *rValue = (char *)realloc(*rValue, sizeof(len + 1));
    strncpy(*rValue,delNode->value,len);
    printf("%s \n", *rValue);
    free(delNode);
}

dbObj *createObj() {
    dbObj *aObj = malloc(sizeof(dbObj));
    aObj->key = NULL;
    aObj->value = NULL;
    aObj->next = NULL;
    aObj->type = -1;
}

dbObj *createList() {
    dbObj *aObj = createObj();
    node *aNode = createNode();
    aObj->list.leftMost = aNode;
    aObj->list.rightMost = aNode;
    aObj->type = 1;
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

void DBllen(const dbObj *const aObj) {
    printf("Length: %d\n", llen(aObj));
}

void DBlrange(const dbObj *const aObj , int lowBound, int highBound) {
    const node *cur = aObj->list.leftMost;
    int count = 0;     // number of found node
    int pos = 0;       // current position
    int len = llen(aObj);
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

int main() {
    char *returnBuffer = (char *)malloc(0);

    // node *nodeA = createNode();
    // setValue(nodeA, "hello");
    // lpush(&nodeA, "12345");
    // lpop(&nodeA, &returnBuffer);
    // printf("%s \n", returnBuffer);
    // printf("%s \n", nodeA->value);

    dbObj *aObj = createList();
    setKey(aObj, "111");
    printf("%s\n", aObj->key);
    setValue(aObj->list.leftMost, "1");
    printf("%s\n",aObj->list.leftMost->value);
    lpush(&(aObj->list.leftMost), "2");
    printf("%s\n",aObj->list.leftMost->right->value);
    lpush(&(aObj->list.leftMost), "3");
    lpush(&(aObj->list.leftMost), "4");

    DBllen(aObj);
    DBlrange(aObj, -3, -2);

    return 0;
}
