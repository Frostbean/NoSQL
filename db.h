#ifndef db_c
#define db_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "hash.h"

#define streql !strcmp

// return a single node
dbObj *DBfind(dbObj **const db, const char *const key);
void DBset(dbObj **const db, const char *const key, const char *value);
// double pointer of value to return the value was got
void DBget(dbObj **db, const char *const key, char **value);
void DBdelete(dbObj **const db, const char *const key);
void DBllen(dbObj **const db, const char *const key);
void DBlrange(dbObj **const db, const char *const key, int lowBound, int highBound);
void DBlpush(dbObj **db, const char *key, const char *value);
void DBrpush(dbObj **db, const char *key, const char *value);
void DBlpop(dbObj **db, const char *key, char **returnValue);
void DBrpop(dbObj **db, const char *key, char **returnValue);
void DBhset(dbObj **db, const char *key, const char *field, const char *value);
void DBhget(dbObj **db, const char *key, const char *field, char **returnValue);
void DBhdel(dbObj **db, const char *key, const char *field);
void DBzadd(dbObj **db, const char *key, const int score, const char *value);
void DBzcard(dbObj **db, const char *key);
void DBzcount(dbObj **const db, const char *const key, int min, int max);

#endif
