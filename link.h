#ifndef link_c
#define link_h

#include <stdlib.h>
#include <string.h>
#include "alloc.h"

dbObj *createObj();
node *createNode();
dbObj *createString();
dbObj *createList();
hashNode *createHashNode();
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
void hset(dbObj *const aObj, const char *field, const char *value);
void popHashNode(const dbObj *aObj, const int pos);
void delAfterHashNode(hashNode *prevHash);
void extendTable(dbObj *const aObj);
void shortenTable(dbObj *const aObj);

#endif