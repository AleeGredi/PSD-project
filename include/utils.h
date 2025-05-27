#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

/*
    Macro to check if a pointer is NULL.
    If NULL, prints an error message and terminates the program.

    Parameters:
        ptr: Pointer to check.

    Pre-condition:
        None.

    Post-condition:
        Program terminates if ptr is NULL.
*/
#define CHECK_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        fprintf(stderr, "ERROR: %s is NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

/*
    Allocates and returns a duplicate of the given string.

    Parameters:
        s: Pointer to the original null-terminated string.

    Pre-condition:
        s must be a valid null-terminated string and not NULL.

    Post-condition:
        Returns a pointer to a newly allocated copy of the string.

    Returns:
        Pointer to the duplicated string.
*/
char *str_dup(const char *s);

/*
    Splits the string at the first occurrence of any delimiter character.

    Parameters:
        stringp: Pointer to a char* pointer representing the string to tokenize.
        delim: String containing delimiter characters.

    Pre-condition:
        stringp and delim must not be NULL.
        *stringp must point to a valid null-terminated string or be NULL.

    Post-condition:
        Modifies the string by inserting a null terminator at the delimiter.
        Advances *stringp to the next token or NULL if no more tokens exist.

    Returns:
        Pointer to the token string.
*/
char *str_sep(char **stringp, const char *delim);

/*
    Swaps the values of two pointers.

    Parameters:
        pp1: Pointer to first pointer.
        pp2: Pointer to second pointer.

    Pre-condition:
        pp1 and pp2 must not be NULL.

    Post-condition:
        The values of *pp1 and *pp2 are exchanged.
*/
void ptr_swap(void **pp1, void **pp2);

#endif