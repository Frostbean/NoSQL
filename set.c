#include "set.h"

void zadd(dbObj *const aObj, const int score, const char *member) {
    setNode *cur = aObj->set;
    if (cur == NULL) {
        pushSetNode(&(aObj->set), score, member);
        return;
    }
    // find same member
    while (cur != NULL) {
        if (!strcmp(cur->member, member)) {
            cur->score = score;
            return;
        }
        cur = cur->next;
    }
    // no same member
    setNode *prev;
    cur = aObj->set;
    if (cur->score > score) {
        pushSetNode(&(aObj->set), score, member);
        return;
    }
    while (cur != NULL) {
        prev = cur;
        if (cur->score > score) {
            insertAfterSetNode(prev, score, member);
            return;
        }
        cur = cur->next;
    }
    insertAfterSetNode(prev, score, member);
    return;
}

int setCount(dbObj *aObj) {
    setNode *cur = aObj->set;
    int count = 0;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

int zcount(dbObj *aObj, const int min, const int max) {
    const setNode *cur = aObj->set;
    if (cur == NULL) {
        return -1;
    }
    int count = 0;
    while (cur != NULL) {
        if (cur->score < min) {
            cur = cur->next;
            continue;
        }
        if (cur->score > max) {
            break;
        }
        count += 1;
        cur = cur->next;
    }
    return count;
}

void zrange(dbObj *aObj, int start, int stop) {
    const setNode *cur = aObj->set;
    int count = 0;     // number of found node
    int pos = 0;       // current position
    int len = setCount(aObj);
    if (cur == NULL) {
        printf("(empty set)\n");
    }
    if (start < 0) {
        start = len + start;
    }
    if (stop < 0) {
        stop = len + stop;
    }
    while (cur != NULL && pos < start) {
        pos++;
        cur = cur->next;
    }
    while (cur != NULL && pos <= stop) {
        count++;
        pos++;
        printf("%d) %s\n", count, cur->member);
        cur = cur->next;
    }
}

void zrangebyscore(dbObj *aObj, const int min, const int max) {
    const setNode *cur = aObj->set;
    if (cur == NULL) {
        printf("(empty set)\n");
    }
    int count = 0;
    while (cur != NULL) {
        if (cur->score < min) {
            cur = cur->next;
            continue;
        }
        if (cur->score > max) {
            break;
        }
        count += 1;
        printf("%d) %s\n", count, cur->member);
        cur = cur->next;
    }
}

void zrank(dbObj *aObj, const char *const member) {
    int index = 0;
    const setNode *cur = aObj->set;
    while (cur != NULL) {
        if (!strcmp(cur->member, member)) {
            printf("(integer) %d\n", index);
            return;
        }
        index += 1;
        cur = cur->next;
    }
    printf("(nil)\n");
}

void zrem(dbObj *aObj, const char *const member) {
    setNode *cur = aObj->set;
    if (cur == NULL) {
        return;
    }
    if (!strcmp(cur->member, member)) {
        popSetNode(&(aObj->set));
        return;
    }
    setNode *prev;
    while (cur != NULL) {
        if (!strcmp(cur->member, member)) {
            delAfterSetNode(prev);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("No corresponding member.\n");
}

void zremrangebyscore(dbObj *aObj, const int min, const int max) {
    if (aObj->set == NULL) {
        printf("(empty set)\n");
        return;
    }
    while (aObj->set->score >= min && aObj->set->score <= max) {
        popSetNode(&(aObj->set));
        if (aObj->set == NULL) {
            return;
        }
    }
    if (aObj->set == NULL) {
        return;
    }
    setNode *prev = NULL;
    setNode *cur = aObj->set;
    while (cur != NULL) {
        if (cur->score >= min && cur->score <= max) {
            delAfterSetNode(prev);
            cur = prev->next;
            continue;
        }
        else if (cur->score > max) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("finished\n");
}

void pushSetNode(setNode **oldNode, const int score, const char *value) {
    setNode *newNode = createSetNode();
    if (*oldNode == NULL) {
        *oldNode = newNode;
        setValueSet(newNode, value);
        newNode->score = score;
        return;
    }
    newNode->next = *oldNode;
    setValueSet(newNode, value);
    newNode->score = score;
    *oldNode = newNode;
    return;
}

void insertAfterSetNode(setNode *prev, const int score, const char *value) {
    setNode *newNode = createSetNode();
    if (prev->next == NULL) {
        prev->next = newNode;
        setValueSet(newNode, value);
        newNode->score = score;
        return;
    }
    newNode->next = prev->next;
    prev->next = newNode;
    setValueSet(newNode, value);
    newNode->score = score;
    return;    
}

void popSetNode(setNode **oldNode) {
    setNode *delNode = *oldNode;
    if (*oldNode == NULL) {
        return;
    }
    *oldNode = (*oldNode)->next;
    freeSetNode(delNode);
    return;
}

void delAfterSetNode(setNode *prev) {
    setNode *delNode = prev->next;
    prev->next = prev->next->next;
    freeSetNode(delNode);
    return;
}
