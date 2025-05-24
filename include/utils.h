#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        fprintf(stderr, "ERROR: %s is NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        exit(1); \
    } \
} while (0)

char *str_dup(const char *s);

char *str_sep(char **stringp, const char *delim);

#endif