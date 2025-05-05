#include "utils.h"

#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

static int convert_to_int(const char* s) {
    char* end;
    errno = 0;
    int val = (int)strtol(s, &end, 10);

    if (end == s) {
        // there are no digits
        fprintf(stderr, "ERROR: \"%s\" is not a number", s);
        exit(1);
    }
    if (*end != '\0') {
        // the string is not entirely read
        fprintf(stderr, "ERROR: \"%s\" not entirely read", s);
        exit(1);
    }
    if (errno == ERANGE) {
        // overflow or underflow occurred
        fprintf(stderr, "ERROR: \"%s\" is out of range", s);
        exit(1);
    }

    return val;
}

int compare_date(const char* date_one, const char* date_two) {
    // day - month - year
    int date_one_data[3] = {0};
    int date_two_data[3] = {0};

    char* date_one_copy = malloc(strlen(date_one) + 1);
    CHECK_NULL(date_one_copy);
    strcpy(date_one_copy, date_one);

    char* date_two_copy = malloc(strlen(date_two) + 1);
    CHECK_NULL(date_two_copy);
    strcpy(date_two_copy, date_two);
    
    int i = 0;
    char* substr;
    substr = strtok(date_one_copy, "/");
    do{
        date_one_data[i] = convert_to_int(substr);
        i++;
    }while((substr = strtok(NULL, "/")));
    
    i = 0;
    substr = strtok(date_two_copy, "/");
    do{
        date_two_data[i] = convert_to_int(substr);
        i++;
    }while((substr = strtok(NULL, "/")));

    int return_value = -2;
    for(i = 2; i >= 0; i--) {
        if(date_one_data[i] > date_two_data[i]) {
            return_value = 1;
        }
        if(date_one_data[i] < date_two_data[i]) {
            return_value = -1;
        }
        if((date_one_data[i] == date_two_data[i]) && i == 0) {
            return_value = 0;
        }
    }

    // clean up
    free(date_one_copy);
    free(date_two_copy);

    return return_value;
}

int compare_time(const char* time_one, const char* time_two) {
    // minute - hour
    int time_one_data[2] = {0};
    int time_two_data[2] = {0};

    char* time_one_copy = malloc(strlen(time_one) + 1);
    CHECK_NULL(time_one_copy);
    strcpy(time_one_copy, time_one);

    char* time_two_copy = malloc(strlen(time_two) + 1);
    CHECK_NULL(time_two_copy);
    strcpy(time_two_copy, time_two);
    
    int i = 0;
    char* substr;
    substr = strtok(time_one_copy, ":");
    do{
        time_one_data[i] = convert_to_int(substr);
        i++;
    }while((substr = strtok(NULL, ":")));
    
    i = 0;
    substr = strtok(time_two_copy, ":");
    do{
        time_two_data[i] = convert_to_int(substr);
        i++;
    }while((substr = strtok(NULL, ":")));

    int return_value = -2;
    for(i = 1; i >= 0; i--) {
        if(time_one_data[i] > time_two_data[i]) {
            return_value = 1;
        }
        if(time_one_data[i] < time_two_data[i]) {
            return_value = -1;
        }
        if((time_one_data[i] == time_two_data[i]) && i == 0) {
            return_value = 0;
        }
    }

    // clean up
    free(time_one_copy);
    free(time_two_copy);

    return return_value;
}