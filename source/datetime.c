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

int compare_date(datetime_ptr date_one, datetime_ptr date_two) {
    // day - month - year
    int date_one_data[3] = {
        date_one->day,
        date_one->month,
        date_one->year
    };

    int date_two_data[3] = {
        date_two->day,
        date_two->month,
        date_two->year
    };

    int return_value = 0;
    for(int i = 2; i >= 0; i--) {
        if(date_one_data[i] > date_two_data[i]) {
            return_value = 1;
        }
        if(date_one_data[i] < date_two_data[i]) {
            return_value = -1;
        }
    }

    return return_value;
}

int compare_time(datetime_ptr time_one, datetime_ptr time_two) {
    // minute - hour
    int time_one_data[2] = {
        time_one->minute,
        time_one->hour
    };

    int time_two_data[2] = {
        time_two->minute,
        time_two->hour
    };

    int return_value = -2;
    for(int i = 1; i >= 0; i--) {
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

    return return_value;
}

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

void delete_datetime(datetime_ptr datetime) {
    free(datetime);
}