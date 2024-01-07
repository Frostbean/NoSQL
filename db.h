#ifndef db_c
#define db_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"

#define streql !strcmp

// return a single node
dbObj *DBfind(dbObj **const db, const char *const key);
// double pointer of value to return the value was got
void DBget(dbObj **db, const char *const key, char **value);
void DBset(dbObj **const db, const char *const key, const char *value);
void DBdelete(dbObj **const db, const char *const key);

#endif
