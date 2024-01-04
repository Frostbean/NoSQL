#include <stdio.h>
#include <string.h>

#define FGETS_MAX_LENGTH 100
#define INPUT_MAX_WORDS 5

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
