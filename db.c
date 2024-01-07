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

// double pointer of value to return the value was got
void DBget(dbObj **db, const char *const key, char **value) {
    const dbObj *aObj = DBfind(db,key);
    if (aObj == NULL) {
        *value = realloc(*value, 1);
        *value = NULL;
        return;
    }
    if (aObj->type != 0) {
        printf("Invalid type");
        return;
    }
    size_t len = strlen(aObj->value);
    *value = (char *)realloc(*value, sizeof(len + 1));
    strncpy(*value,aObj->value,len);
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
    setValueString(aObj,value);
    printf("OK");
}

void DBdelete(dbObj **const db, const char *const key) {
    if (*db == NULL) {
        return;
    }
    if (!strcmp((*db)->key,key)) {
        if ((*db)->type == 0) {
            popObj(db);
        }
        else if ((*db)->type == 1) {
            // TODO
        }
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
    if (cur->type == 0) {
        delAfterObj(prev);
    }
    else if (cur->type == 1) {
        // TODO
    }
    return;
}
