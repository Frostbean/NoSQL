#include "alloc.h"

void setKey(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aObj->key = (char *)malloc(len + 1);
    strncpy(aObj->key,buffer+'\0',len+1);
}

void setValueString(dbObj *aObj, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aObj->value) {
        free(aObj->value);
    }
    aObj->value = (char *)malloc(len + 1);
    strncpy(aObj->value,buffer+'\0',len+1);
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

void setHashNode(hashNode *aHash, const char *field, const char *value) {
    size_t len;
    len = strlen(field);
    aHash->field = (char *)malloc(len + 1);
    strncpy(aHash->field,field+'\0',len+1);
    len = strlen(value);
    aHash->value = (char *)malloc(len + 1);
    strncpy(aHash->value,value+'\0',len+1);
}
