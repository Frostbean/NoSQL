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
    // printf("Pop done\n");
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
    // printf("Pop done\n");
}

void DBhset(dbObj **db, const char *key, const char *field, const char *value) {
    dbObj *aObj;
    
    aObj = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aObj) {
        pushObj(db, 3);
        aObj = *db;
        setKey(aObj,key);       
    }
    if (aObj->type != 3) {
        printf("Invalid type\n");
        return;
    }
    hset(aObj, field, value);
    printf("OK\n");
}

void DBhget(dbObj **db, const char *key, const char *field, char **returnValue) {
    const dbObj *aObj = DBfind(db,key);
    if (aObj == NULL) {
        *returnValue = realloc(*returnValue, 1);
        *returnValue = NULL;
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 3) {
        *returnValue = realloc(*returnValue, 1);
        *returnValue = NULL;
        printf("Invalid type\n");
        return;
    }

    int pos = getHash(field, aObj->hashMap.size);
    if ((aObj->hashMap.nodes)[pos] == NULL) {
        *returnValue = realloc(*returnValue, 1);
        *returnValue = NULL;
        printf("(nil)\n");
        return;
    }

    hashNode *cur = (aObj->hashMap.nodes)[pos];
    while (cur != NULL) {
        if (!strcmp(cur->field, field)) {
            size_t len = strlen(cur->value);
            *returnValue = (char *)realloc(*returnValue, sizeof(len + 1));
            strncpy(*returnValue,cur->value,len);
            return;
        }
        cur = cur->next;
    }
    if (cur == NULL) {
        *returnValue = realloc(*returnValue, 1);
        *returnValue = NULL;
        printf("(nil)\n");
        return;
    }
}

void DBhdel(dbObj **db, const char *key, const char *field) {
    dbObj *const aObj = DBfind(db,key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 3) {
        printf("Invalid type\n");
        return;
    }

    if (aObj->hashMap.load * 1.00 / aObj->hashMap.size < 0.01) {
        printf("Low Load Factor\n");
        shortenTable(aObj);
        return;
    }

    int pos = getHash(field, aObj->hashMap.size);
    if ((aObj->hashMap.nodes)[pos] == NULL) {
        printf("(nil)\n");
        return;
    }

    if (aObj->hashMap.load * 1.00 / aObj->hashMap.size < 0.01) {
        printf("Low Load Factor");
        return;
    }

    hashNode *prev = NULL;
    hashNode *cur = (aObj->hashMap.nodes)[pos];
    if (!strcmp(cur->field,field)) {
        popHashNode(aObj, pos);
        return;
    }
    while (strcmp(cur->field,field) && cur != NULL) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        return;
    }
    delAfterHashNode(prev);
    return;
}

void DBzadd(dbObj **db, const char *key, const int score, const char *value) {
    dbObj *aObj = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aObj) {
        pushObj(db, 2);
        aObj = *db;
        setKey(aObj,key);
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    zadd(aObj, score, value);
    printf("OK\n"); 
}

void DBzcard(dbObj **db, const char *key) {
    dbObj *aObj = DBfind(db,key);
    // if key doesn't exist, create and set newNode
    if (!aObj) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    printf("Set size: %d\n", setCount(aObj));    
}

void DBzcount(dbObj **const db, const char *const key, int min, int max) {
    dbObj *aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    const int count = zcount(aObj, min, max);
    if (count == -1) {
        printf("(empty set)\n");
        return;
    }
    printf("Count: %d\n", count);
}

void DBzrange(dbObj **const db, const char *const key, const int start, const int stop) {
    dbObj *aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    zrange(aObj, start, stop);
}

void DBzrangebyscore(dbObj **const db, const char *const key, const int min, const int max) {
    dbObj *aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    zrangebyscore(aObj, min, max);
}

void DBzrank(dbObj **const db, const char *const key, const char *const member) {
    dbObj *aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    zrank(aObj, member);
}

void DBzrem(dbObj **const db, const char *const key, const char *const member) {
    dbObj *aObj = DBfind(db , key);
    if (aObj == NULL) {
        printf("(nil)\n");
        return;
    }
    if (aObj->type != 2) {
        printf("Invalid type\n");
        return;
    }
    zrem(aObj, member);
}
