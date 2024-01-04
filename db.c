#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FGETS_MAX_LENGTH 100
#define INPUT_MAX_WORDS 5
#define streql !strcmp

typedef struct NODE {
    char *key;
    char *value;
    struct NODE *next;
} node;

// int streql(const char *str1, const char *str2) {
//     return !strcmp(str1, str2);
// }

void setKey(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aNode->key = (char *)malloc(len + 1);
    strncpy(aNode->key,buffer+'\0',len);
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

void DBdelete(node **const db, const char *const key) {
    if (*db == NULL) {
        return;
    }
    if (!strcmp((*db)->key,key)) {
        popNode(db);
        return;
    }
    node *prev = NULL;
    node *cur = *db;
    while (strcmp(cur->key, key) && cur != NULL) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        return;
    }
    delAfterNode(prev);
    return;
}

// return a single node
node *DBfind(node **const db, const char *const key) {
    node *aNode;
    if (*db == NULL) {
        return NULL;
    }
    aNode = *db;
    do {
        if (streql(aNode->key,key)) {
            return aNode;
        }
        aNode = aNode->next;
    } while (aNode);
    return NULL;
}

// double pointer of value to return the value was got
void DBget(node **db, const char *const key, char **value) {
    const node *aNode = DBfind(db,key);
    if (aNode == NULL) {
        *value = realloc(*value, 1);
        *value = NULL;
        return;
    }
    size_t len = strlen(aNode->value);
    *value = (char *)realloc(*value, sizeof(len + 1));
    strncpy(*value,aNode->value,len);
}

void DBset(node **const db, const char *const key, const char *value) {
    node *aNode;
    
    aNode = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aNode) {
        pushNode(db);
        aNode = *db;
        setKey(aNode,key);       
    }
    setValue(aNode,value);
}

void removeEOL(char *str, size_t len) {
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void splitInput(const char **splited, char *str, const char *del, int limit) {
    char *s = strtok(str, del);
    int count = 0;

    while(s != NULL && count < limit) {
        *splited++ = s;
        s = strtok(NULL, del);
        count++;
    }
}

void dumpInput(const char **str) {
    for (int i = 0; i < INPUT_MAX_WORDS; i++) {
        // printf("%p ", str+i);
        if (*(str+i) != NULL) {
            printf("%d %s\n", i, *(str+i));
        }
        else {
            printf("%d NULL\n", i);
        }
    }
}

void commandExecution(node **db, const char **input_splited, char **value) {
    if (streql(*(input_splited), "set")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            DBset(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (streql(*(input_splited), "get")) {
        if (*(input_splited+1) != NULL) {
            DBget(db, *(input_splited+1), value);
            if (*value == NULL) {
                // printf("No corresponding key.\n");
                printf("(nil)\n");
            }
            else {
                // printf("Value is \"%s\".\n", *value);
                printf("\"%s\"\n", *value);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (streql(*(input_splited), "del")) {
        if (*(input_splited+1) != NULL) {
            DBdelete(db, *(input_splited+1));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else {
        printf("Unknown Instruction\n");
    }
}

void readInput(char *input_buffer) {
    printf("> ");
    fgets(input_buffer, FGETS_MAX_LENGTH, stdin);
    // printf("The string is: %s", input_buffer);
}

int main() {
    // initial
    node *db;
    char *value = (char *)malloc(0);
    db = NULL;
    char input_buffer[100];
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

    // first input
    readInput(input_buffer);
    removeEOL(input_buffer, strlen(input_buffer));
    splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    while (strcmp(input_buffer, "quit")) {
        // dumpInput(input_splited);

        // db = commandExecution(db, input_splited, value);
        commandExecution(&db, input_splited, &value);

        readInput(input_buffer);
        removeEOL(input_buffer, strlen(input_buffer));
        splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);
    }

    // clear database
    while (db != NULL) {
        popNode(&db);
    }

    return 0;
}
