#ifndef DATETIME_H
#define DATETIME_H

typedef struct datetime *datetime_ptr;

/*
    Compares two dates (year, month, day) to determine their chronological order.

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
int compare_date(datetime_ptr datetime_one, datetime_ptr datetime_two);

/*
    Compares two times (hour, minute, second) to determine their chronological order.

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
int compare_time(datetime_ptr datetime_one, datetime_ptr datetime_two);

/*
    Compares two datetime objects by date first, then time if dates are equal.

    parameters:
        datetime_one: pointer to the first datetime object.
        datetime_two: pointer to the second datetime object.

    pre-condition:
        datetime_one and datetime_two must be non-NULL and fully initialized.

    post-condition:
        Neither datetime object is modified.

    return:
        -1 if the datetime in datetime_one is earlier than in datetime_two;
         0 if both datetimes are equal;
         1 if the datetime in datetime_one is later than in datetime_two.
*/
int compare_datetime(datetime_ptr datetime_one, datetime_ptr datetime_two);

/*
    Allocates and initializes a new datetime object.

    parameters:
        None.

    pre-condition:
        Standard time functions (time, localtime) succeed.

    post-condition:
        A newly allocated datetime object contains the current local date and time.

    return:
        Pointer to the new datetime object, or exit if allocation fails.
*/
datetime_ptr get_datetime();

/*
    Frees all resources associated with a datetime object.

    parameters:
        datetime: pointer to the datetime object to delete.

    pre-condition:
        datetime must be non-NULL and previously allocated by get_datetime().

    post-condition:
        The memory for the datetime object is released. The pointer becomes invalid.

    return:
        Nothing.
*/
void delete_datetime(datetime_ptr datetime);

#endif