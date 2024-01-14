#ifndef set_c
#define set_h

#include <stdio.h>
#include <stdlib.h>
#include "link.h"

void zadd(dbObj *const aObj, const int score, const char *member);
int setCount(dbObj *aObj);
int zcount(dbObj *aObj, const int min, const int max);
void zrange(dbObj *aObj, int start, int stop);
void zrangebyscore(dbObj *aObj, const int min, const int max);
void zrank(dbObj *aObj, const char *const member);
void zrem(dbObj *aObj, const char *const member);
void zremrangebyscore(dbObj *aObj, const int min, const int max);
void zunionstore(dbObj *desObj, dbObj *souObj);
void pushSetNode(setNode **oldNode, const int score, const char *value);
void popSetNode(setNode **oldNode);
void insertAfterSetNode(setNode *prev, const int score, const char *value);
void delAfterSetNode(setNode *prev);
void freeSet(dbObj *delObj);

#endif
