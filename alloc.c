#include <string.h>
#include "link.h"

void setKey(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    aNode->key = (char *)malloc(len + 1);
    strncpy(aNode->key,buffer+'\0',len);
}

void setValue(node *aNode, const char *buffer) {
    size_t len;
    // what about sizeof
    len = strlen(buffer);
    if (aNode->value) {
        free(aNode->value);
    }
    aNode->value = (char *)malloc(len + 1);
    strncpy(aNode->value,buffer+'\0',len);
}
