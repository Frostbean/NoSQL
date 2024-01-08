#include "hash.h"

uint32_t getHash(const char *const key, int size) {
    uint32_t seed = 0;
    uint32_t hash = murmurhash(key, (uint32_t)strlen(key), seed);
    printf("murmurhash(%s) = 0d%u\n", key, hash % size);
    return hash % size;
}