#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

// return address of a single obj
dbObj *DBfind(dbObj **const db, const char *const key) {
    dbObj *aObj;
    if (*db == NULL) {
        return NULL;
    }
    aObj = *db;
    do {
        if (!strcmp(aObj->key,key)) {
            return aObj;
        }
        aObj = aObj->next;
    } while (aObj);
    return NULL;
}

void DBset(dbObj **const db, const char *const key, const char *value) {
    dbObj *aObj;
    
    aObj = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aObj) {
        pushObj(db, 0);
        aObj = *db;
        setKey(aObj,key);       
    }
    if (aObj->type != 0) {
        printf("Invalid type\n");
        return;
    }
    setValueString(aObj,value);
    printf("OK\n");
}

// double pointer of value to return the value was got
void DBget(dbObj **db, const char *const key, char **value) {
    const dbObj *aObj = DBfind(db,key);
    if (aObj == NULL) {
        *value = realloc(*value, 1);
        *value = NULL;
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 0) {
        *value = realloc(*value, 1);
        *value = NULL;
        printf("Invalid type\n");
        return;
    }
    size_t len = strlen(aObj->value);
    *value = (char *)realloc(*value, sizeof(len + 1));
    strncpy(*value,aObj->value,len);
}

void DBdelete(dbObj **const db, const char *const key) {
    if (*db == NULL) {
        return;
    }
    if (!strcmp((*db)->key,key)) {
        popObj(db);
        return;
    }
    dbObj *prev = NULL;
    dbObj *cur = *db;
    while (strcmp(cur->key, key) && cur != NULL) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        return;
    }
    delAfterObj(prev);
    return;
}

void DBllen(dbObj **const db, const char *const key) {
    dbObj *aObj;
    if (*db == NULL) {
        printf("(nil)\n");
        return;
    }
    aObj = DBfind(db, key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    printf("Length: %d\n", llen(aObj));
}

void DBlrange(dbObj **const db, const char *const key, int lowBound, int highBound) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    const node *cur = aObj->list.leftMost;
    int count = 0;     // number of found node
    int pos = 0;       // current position
    int len = llen(aObj);
    if (len == 0) {
        printf("(empty array)\n");
    }
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

void DBlpush(dbObj **db, const char *key, const char *value) {
    dbObj *aObj = DBfind(db , key);
    // if no corresponding key found
    if (aObj == NULL) {
        pushObj(db, 1);
        setKey(*db, key);
        setValueList((*db)->list.leftMost, value);
        printf("OK\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    lpush(aObj, value);
    printf("OK\n");
}

void DBrpush(dbObj **db, const char *key, const char *value) {
    dbObj *aObj;
    if (*db == NULL) {
        return;
    }
    aObj = DBfind(db , key);
    // if no corresponding key found
    if (aObj == NULL) {
        pushObj(db, 1);
        setKey(*db, key);
        setValueList((*db)->list.leftMost, value);
        printf("OK\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    rpush(aObj, value);
}

void DBlpop(dbObj **db, const char *key, char **returnValue) {
    dbObj *aObj;
    if (*db == NULL) {
        printf("(nil)\n");
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    lpop(aObj, returnValue);
    printf("Pop done\n");
}

void DBrpop(dbObj **db, const char *key, char **returnValue) {
    dbObj *aObj;
    if (*db == NULL) {
        printf("(nil)\n");
        return;
    }
    aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 1) {
        printf("Invalid type\n");
        return;
    }
    rpop(aObj, returnValue);
    printf("Pop done\n");
}
