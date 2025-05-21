#include "utils.h"
#include <stdlib.h>
#include <string.h>

char *str_dup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    CHECK_NULL(dup);
    memcpy(dup, s, len);
    return dup;
}

char *str_sep(char **stringp, const char *delim) {
    char *start = *stringp;
    if (!start) return NULL;
    char *p = strpbrk(start, delim);
    if (p) {
        *p = '\0';
        *stringp = p + 1;
    } else {
        *stringp = NULL;
    }
    return start;
}