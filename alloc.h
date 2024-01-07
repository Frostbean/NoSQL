#ifndef alloc_c
#define alloc_h

#include <stdlib.h>
#include <string.h>
#include "data.h"

void setKey(dbObj *aObj, const char *buffer);
void setValueString(dbObj *aObj, const char *buffer);
void setValueList(node *aNode, const char *buffer);

#endif
