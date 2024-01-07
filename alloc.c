#include <string.h>
#include "link.h"

void setKey(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aObj->key = (char *)malloc(len + 1);
    strncpy(aObj->key,buffer+'\0',len);
}

void setValueString(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aObj->value) {
        free(aObj->value);
    }
    aObj->value = (char *)malloc(len + 1);
    strncpy(aObj->value,buffer+'\0',len);
}

void setValueList(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aNode->value) {
        free(aNode->value);
    }
    aNode->value = (char *)malloc(len + 1);
    strncpy(aNode->value,buffer+'\0',len);
}
