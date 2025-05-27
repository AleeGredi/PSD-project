#include "utils.h"
#include <stdlib.h>
#include <string.h>

/*
    Duplicates the given string by allocating new memory and copying the contents.

    Parameters:
        s: Pointer to a null-terminated string to duplicate.

    Pre-condition:
        s must not be NULL.

    Post-condition:
        A new string is allocated and contains the same content as s.

    Returns:
        char*: Pointer to the duplicated string. Must be freed by the caller.
*/
char *str_dup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    CHECK_NULL(dup);
    memcpy(dup, s, len);
    return dup;
}

/*
    Extracts a token from a string based on a set of delimiter characters.
    Modifies the input string pointer to point to the next token.

    Parameters:
        stringp: Pointer to the current position in the string (char**).
        delim: A null-terminated string of delimiter characters.

    Pre-condition:
        *stringp must not be NULL.

    Post-condition:
        The string pointed to by *stringp is modified to isolate the token.

    Returns:
        char*: Pointer to the start of the extracted token, or NULL if no more tokens.
*/
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

/*
    Swaps the values of two void pointers.

    Parameters:
        pp1: Address of the first pointer.
        pp2: Address of the second pointer.

    Pre-condition:
        Both pp1 and pp2 must be valid pointers to pointers.

    Post-condition:
        The values of *pp1 and *pp2 are swapped.

    Returns:
        None.
*/
void ptr_swap(void **pp1, void **pp2) {
    void *tmp = *pp1;
    *pp1 = *pp2;
    *pp2 = tmp;
}