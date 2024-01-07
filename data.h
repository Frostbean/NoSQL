#ifndef data_c
#define data_h

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

#endif