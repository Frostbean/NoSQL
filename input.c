#include <stdio.h>
#include <string.h>
#include "input.h"

void removeEOL(char *str, size_t len) {
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void splitInput(const char **splited, char *str, const char *del, int limit) {
    char *s = strtok(str, del);
    int count = 0;

    while(s != NULL && count < limit) {
        *splited++ = s;
        s = strtok(NULL, del);
        count++;
    }
}

void dumpInput(const char **str) {
    for (int i = 0; i < INPUT_MAX_WORDS; i++) {
        // printf("%p ", str+i);
        if (*(str+i) != NULL) {
            printf("%d %s\n", i, *(str+i));
        }
        else {
            printf("%d NULL\n", i);
        }
    }
}

void readInput(char *input_buffer) {
    printf("> ");
    fgets(input_buffer, FGETS_MAX_LENGTH, stdin);
    // printf("The string is: %s", input_buffer);
}

int isNumber(const char *str) {
    if (*str == '\0') {
        return 0;
    }
    if (*str == '-') {
        str++;
    }
    if (*str == '\0') {
        return 0;
    }
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}
