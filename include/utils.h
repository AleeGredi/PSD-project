#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define CHECK_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        fprintf(stderr, "ERROR: %s is NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        exit(1); \
    } \
} while (0)

// date format dd/mm/aaaa

/*
    The compare_date function takes two date
    Return -1 if the first date is previous to the second
    Return 0 if the first date and the second are equals
    Return 1 if the first date is after the second
*/
int compare_date(const char* date_one, const char* date_two);

/*
    The compare_time function takes two time
    Return -1 if the first time is previous to the second
    Return 0 if the first time and the second are equals
    Return 1 if the first time is after the second
*/

// time format mm:hh
int compare_time(const char* time_one, const char* time_two);

#endif