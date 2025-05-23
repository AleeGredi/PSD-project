#include "datetime.h"

#include "utils.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct datetime {
    int minute;
    int hour;
    int day;
    int month;
    int year;
};

/*
    Builds temporary integer arrays of [day, month, year] for each datetime,
    then iterates from year down to day comparing corresponding elements to
    determine chronological order.

    parameters:
        datetime_one: pointer to the first datetime object.
        datetime_two: pointer to the second datetime object.

    pre-condition:
        datetime_one and datetime_two must be non-NULL and contain valid date fields.

    post-condition:
        Neither datetime object is modified.

    return:
        -1 if datetime_one is before datetime_two;
         0 if dates are equal;
         1 if datetime_one is after datetime_two.
*/
int compare_date(datetime_ptr datetime_one, datetime_ptr datetime_two) {
    // day - month - year
    int datetime_one_data[3] = {
        datetime_one->day,
        datetime_one->month,
        datetime_one->year
    };

    int datetime_two_data[3] = {
        datetime_two->day,
        datetime_two->month,
        datetime_two->year
    };

    int return_value = 0;
    for(int i = 2; i >= 0; i--) {
        if(datetime_one_data[i] > datetime_two_data[i]) {
            return_value = 1;
            break;
        }
        if(datetime_one_data[i] < datetime_two_data[i]) {
            return_value = -1;
            break;
        }
    }

    return return_value;
}


/*
    Constructs integer arrays [minute, hour] for each datetime, then iterates
    from hour down to minute comparing values to establish time ordering.

    parameters:
        datetime_one: pointer to the first datetime object.
        datetime_two: pointer to the second datetime object.

    pre-condition:
        datetime_one and datetime_two must be non-NULL and contain valid time fields.

    post-condition:
        Neither datetime object is modified.

    return:
        -1 if time in datetime_one is before datetime_two;
         0 if times are equal;
         1 if datetime_one is after datetime_two.
*/
int compare_time(datetime_ptr datetime_one, datetime_ptr datetime_two) {
    // minute - hour
    int datetime_one_data[2] = {
        datetime_one->minute,
        datetime_one->hour
    };

    int datetime_two_data[2] = {
        datetime_two->minute,
        datetime_two->hour
    };

    int return_value = 0;
    for(int i = 1; i >= 0; i--) {
        if(datetime_one_data[i] > datetime_two_data[i]) {
            return_value = 1;
            break;
        }
        if(datetime_one_data[i] < datetime_two_data[i]) {
            return_value = -1;
            break;
        }
    }

    return return_value;
}

/*
    First calls compare_date to compare the two datetimes’ dates; if they are
    equal (result 0), delegates to compare_time to compare times.

    parameters:
        datetime_one: pointer to the first datetime object.
        datetime_two: pointer to the second datetime object.

    pre-condition:
        datetime_one and datetime_two must be non-NULL and fully initialized.

    post-condition:
        Neither datetime object is modified.

    return:
        Result of compare_date if non-zero;
        otherwise result of compare_time.
*/
int compare_datetime(datetime_ptr datetime_one, datetime_ptr datetime_two) {
    int date_compare_result = compare_date(datetime_one, datetime_two);
    if (date_compare_result == 0) {
        return compare_time(datetime_one, datetime_two);
    }
    return date_compare_result;
}

/*
    Allocates a new datetime struct, retrieves the current system time,
    converts to local time, and populates each field (minute, hour, day,
    month, year) with proper adjustments (e.g., tm_mon + 1).

    parameters:
        None.

    pre-condition:
        Standard time functions (time, localtime) succeed.

    post-condition:
        A newly allocated datetime object contains the current local date and time.

    return:
        Pointer to the new datetime object, or exit if allocation fails.
*/
datetime_ptr get_datetime() {
    struct datetime* new_datetime = malloc(sizeof(struct datetime));
    CHECK_NULL(new_datetime);

    time_t current_time;
    struct tm *local_time;

    // Get the current time
    time(&current_time);

    // Convert to local time format
    local_time = localtime(&current_time);

    new_datetime->minute = local_time->tm_min + 1; // tm_min is 0-59
    new_datetime->hour   = local_time->tm_hour + 1; // tm_hour is 0-23
    new_datetime->day    = local_time->tm_mday;
    new_datetime->month  = local_time->tm_mon + 1;  // tm_mon is 0–11
    new_datetime->year   = local_time->tm_year + 1900; // tm_year is years since 1900

    return new_datetime;
}

/*
    Implementation allocates memory for a datetime struct, verifies
    the allocation succeeded, then assigns each struct member from
    the corresponding parameter.

    parameters:
        minute — minute value to store in the struct
        hour   — hour value to store in the struct
        day    — day value to store in the struct
        month  — month value to store in the struct
        year   — year value to store in the struct

    pre-condition:
        malloc must succeed in allocating sizeof(struct datetime) bytes.

    post-condition:
        The returned struct pointer has all fields set;
        upon allocation failure, the program exits (via CHECK_NULL).

    return:
        Pointer to the allocated and populated datetime struct.
*/
datetime_ptr create_datetime(int minute, int hour, int day, int month, int year) {
    struct datetime* new_datetime = malloc(sizeof(struct datetime));
    CHECK_NULL(new_datetime);

    new_datetime->minute = minute;
    new_datetime->hour = hour;
    new_datetime->day = day;
    new_datetime->month = month;
    new_datetime->year = year;

    return new_datetime;
}

/*
    Print the datetime object.

    parameters:
        datetime: pointer to the datetime object to print.
        file: file in which output the print function

    pre-condition:
        All parameters must be non-NULL and previously allocated.

    post-condition:
        Nothing.

    return:
        Nothing.
*/
void print_datetime(FILE* file, datetime_ptr datetime) {
    fprintf(file, "%d:%d %d/%d/%d", 
        datetime->minute,
        datetime->hour,
        datetime->day,
        datetime->month,
        datetime->year
    );
}

/*
    Frees the memory allocated for a datetime object.

    parameters:
        datetime: pointer to the datetime object to delete.

    pre-condition:
        datetime must be non-NULL and previously allocated by get_datetime().

    post-condition:
        The memory for the datetime object is released. The pointer becomes invalid.

    return:
        Nothing.
*/
void delete_datetime(datetime_ptr datetime) {
    free(datetime);
}