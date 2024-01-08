typedef struct hashNode {
    char *field;
    char *value;
    hashNode *next;
} hashNode;

typedef struct dbObj {
    char *key;
    union {
        char *value;    // type 0
        struct {
            node *leftMost;  // type 1, leftmost node of list
            node *rightMost; // type 1, rightmost node of list
        } list;
        struct {
            int size;
            hashNode **nodes;
        } hashMap;
    };
    struct dbObj *next;
    int type;
} dbObj;