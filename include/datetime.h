#ifndef DATETIME_H
#define DATETIME_H

typedef struct datetime *datetime_ptr;

/*
    The compare_date function takes two date
    Return -1 if the first date is previous to the second
    Return 0 if the first date and the second are equals
    Return 1 if the first date is after the second
*/
int compare_date(datetime_ptr date_one, datetime_ptr date_two);

/*
    The compare_time function takes two time
    Return -1 if the first time is previous to the second
    Return 0 if the first time and the second are equals
    Return 1 if the first time is after the second
*/

int compare_time(datetime_ptr time_one, datetime_ptr time_two);

datetime_ptr get_datetime();

void delete_datetime(datetime_ptr datetime);

#endif