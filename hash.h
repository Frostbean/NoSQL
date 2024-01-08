#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "murmurhash.h"

uint32_t getHash(const char *const key, int size);

#endif