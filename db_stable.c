#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FGETS_MAX_LENGTH 100
#define INPUT_MAX_WORDS 5

typedef struct NODE {
    char *key;
    char *value;
    struct NODE *next;
} node;

// char *setKey(char *key, char *buffer);
// char *setValue(char *key, char *buffer);

// char *setValue(char *buffer) {
//     size_t len;
//     char *value;
//     // what about sizeof
//     len = strlen(buffer);
//     // printf("%ld", len);
//     value = (char *)malloc(len + 1);
//     strncpy(value,buffer,len);
//     // printf("%ld", strlen(key));
//     return value;
// }

void setKey(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    // printf("%ld", len);
    aNode->key = (char *)malloc(len + 1);
    strncpy(aNode->key,buffer,len);
    // printf("%ld", strlen(key));
    // printf("%s",aNode->key);
}

void setValue(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    // printf("%ld", len);
    if (aNode->value) {
        free(aNode->value);
    }
    aNode->value = (char *)malloc(len + 1);
    strncpy(aNode->value,buffer,len);
    // printf("%ld", strlen(key));
}

node *createNode() {
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    newNode->key = NULL;
    newNode->value = NULL;
    return newNode;
}

node *pushNode(node *oldNode) {
    node *newNode = createNode();
    if (oldNode == NULL) {
        oldNode = newNode;
    }
    else {
        newNode->next = oldNode;
    }
    // newNode->next = oldNode;
    return newNode;
}

// fine
node *DBfind(node *const db, const char *const key) {
    node *aNode;
    aNode = db;
    if (aNode == NULL) {
        return NULL;
    }
    do {
        // printf("%d",strcmp(aNode->key,key));
        if (!strcmp(aNode->key,key)) {
            return aNode;
        }
        aNode = aNode->next;
    } while (aNode);
    return NULL;
}

// fine
// double pointer of value to return the value was got
void DBget(node *db, const char *key, char **value) {
    const node *aNode = DBfind(db,key);
    if (aNode == NULL) {
        printf("test 123\n");
        *value = realloc(*value, 1);
        *value = NULL;
        return;
    }
    size_t len = strlen(aNode->value);
    *value = (char *)realloc(*value, sizeof(len + 1));
    strncpy(*value,aNode->value,len);
    // printf("%s\n",*value);
}

// fine
node *DBset(node *const db, const char *key, const char *value) {
    node *aNode;
    // if key exist, trouble
    aNode = DBfind(db,key);
    if (aNode) {
        setValue(aNode,value);
    }
    // if key doesn't exist, create and set newNode
    aNode = pushNode(db);
    setKey(aNode,key);
    setValue(aNode,value);
    // important, hmm... C on linux doesn't do return check
    return aNode;
}

void removeEOL(char *str, size_t len) {
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// fine
void splitInput(const char **splited, char *str, const char *del, int limit) {
    char *s = strtok(str, del);
    int count = 0;

    while(s != NULL && count < limit) {
        *splited++ = s;
        s = strtok(NULL, del);
        count++;
    }
}

int streql(const char *str1, const char *str2) {
    return !strcmp(str1, str2);
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

node *commandExecution(node *db, const char **input_splited, char **value) {
    if (streql(*(input_splited), "set")) {
        if (*(input_splited+1) != NULL && *(input_splited+2) != NULL) {
            db = DBset(db, *(input_splited+1), *(input_splited+2));
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else if (streql(*(input_splited), "get")) {
        if (*(input_splited+1) != NULL) {
            DBget(db, *(input_splited+1), value);
            if (*value == NULL) {
                printf("No corresponding key.\n");
            }
            else {
                printf("Value is %s\n", *value);
            }
        }
        else {
            printf("Missing operand.\n");
        }
    }
    else {
        printf("Unknown Instruction\n");
    }
    return db;
}

void readInput(char *input_buffer) {
    printf("> ");
    fgets(input_buffer, FGETS_MAX_LENGTH, stdin);
    // printf("The string is: %s", input_buffer);
}

void startDB(node *db, char *input_buffer, char **value) {
    // initial
    const char *input_splited[INPUT_MAX_WORDS] = {NULL};

    readInput(input_buffer);
    removeEOL(input_buffer, strlen(input_buffer));
    splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    while (strcmp(input_buffer, "quit")) {
        // dumpInput(input_splited);

        db = commandExecution(db, input_splited, value);

        readInput(input_buffer);
        removeEOL(input_buffer, strlen(input_buffer));
        splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);
    }

    printf("Leaving...\n");
}

int main() {
    // initial
    node *db;
    char **value = (char **)malloc(0);
    db = NULL;
    char input_buffer[100];

    // user input

    startDB(db, input_buffer, value);

    // readInput(input_buffer);

    // removeEOL(input_buffer, strlen(input_buffer));

    // splitInput(input_splited, input_buffer, " ", INPUT_MAX_WORDS);

    // dumpInput(input_splited);

    // commandExecution(db, input_splited, value);

    // if (streql(input_splited[0], "set")) {
    //     printf("set...\n");
    //     if (input_splited[1] != NULL && input_splited[2] != NULL) {
    //         DBset(db, input_splited[1], input_splited[2]);
    //     }
    //     else {
    //         printf("Missing operand.\n");
    //     }
    // }
    // else if (streql(input_splited[0], "get")) {
    //     if (input_splited[1] != NULL) {
    //         DBget(db, input_splited[1], value);
    //         if (*value == NULL) {
    //             printf("No corresponding key.\n");
    //         }
    //         else {
    //             printf("Value is %s\n", *value);
    //         }
    //     }
    //     else {
    //         printf("Missing operand.\n");
    //     }
    // }
    // else {
    //     printf("Unknown Instruction\n");
    // }

    // user input end

    // test program

    // db = DBset(db,"abc","cde");
    // db = DBset(db,"cde","efg");
    // printf("%ld\n",sizeof(db));
    // printf("%s %s %p\n",db->key,db->value,db->next);
    // printf("%p\n",db);
    // printf("%p\n",DBfind(db,"cde"));
    // printf("%s %s %p \n",DBfind(db,"cde")->key,DBfind(db,"cde")->value,DBfind(db,"cde")->next);
    
    // DBget(db,"abc",&value);
    // printf("%s\n",value);

    // db = DBset(db,"abc","iii");

    // DBget(db,"abc",&value);
    // printf("%s\n",value);

    // test program end

    return 0;
}
