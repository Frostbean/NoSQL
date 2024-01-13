#ifndef data_c
#define data_h

#define INITIAL_TABLE_SIZE 100

// doubly linked list
typedef struct node {
    char *value;
    struct node *left;
    struct node *right;
} node;

typedef struct setNode {
    int score;
    char *value;
    struct setNode *next;
} setNode;

typedef struct hashNode {
    char *field;
    char *value;
    struct hashNode *next;
} hashNode;

// type 0: string, type 1: list, type 2: sorted set, type 3: hash
typedef struct dbObj {
    char *key;
    union {
        char *value;    // type 0
        struct {
            node *leftMost;  // type 1, leftmost node of list
            node *rightMost; // type 1, rightmost node of list
        } list;
        setNode *set;  // type 2
        struct {
            int size;
            int load;
            hashNode **nodes;
        } hashMap;      // type 3
    };
    struct dbObj *next;
    int type;
} dbObj;

#endif