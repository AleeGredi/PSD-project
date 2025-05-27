#ifndef COURSE_H
#define COURSE_H

#include "datetime.h"
#include <stdint.h>
#include <stdio.h>

typedef struct course *course_ptr;

/*
    Creates a new course object with the specified parameters.

    Parameters:
        id: unique identifier for the course.
        name: name of the course (null-terminated string).
        datetime: pointer to the course's datetime.
        seats_total: total number of available seats.
        seats_booked: number of already booked seats.

    Pre-conditions:
        name must be a valid string.
        datetime must be a valid datetime_ptr.

    Post-conditions:
        A new course object is allocated and initialized.

    Returns:
        course_ptr: pointer to the newly created course object.
*/
course_ptr create_course(
    uint16_t id,
    char* name, 
    datetime_ptr datetime, 
    uint16_t seats_total,
    uint16_t seats_booked
);

/*
    Returns the ID of the course.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        uint16_t: course ID.
*/
uint16_t get_course_id(course_ptr course);

/*
    Compares two course pointers by their ID.

    Parameters:
        a: void pointer to first course.
        b: void pointer to second course.

    Returns:
        int: 1 if IDs match, 0 otherwise.
*/
int compare_course_id(void* a, void* b);

/*
    Returns the name of the course.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        char*: name of the course.
*/
char* get_course_name(course_ptr course);

/*
    Returns the datetime of the course.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        datetime_ptr: pointer to the datetime object.
*/
datetime_ptr get_course_datetime(course_ptr course);

/*
    Returns the total number of seats for the course.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        uint16_t: total seats.
*/
uint16_t get_course_seats_total(course_ptr course);

/*
    Returns the number of already booked seats.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        uint16_t: booked seats.
*/
uint16_t get_course_seats_booked(course_ptr course);

/*
    Sets the number of booked seats for the course.

    Parameters:
        course: pointer to the course.
        value: new booked seats count.

    Returns:
        None.
*/
void set_course_seats_booked(course_ptr course, int value);

/*
    Callback function to save course booking information to a file.

    Parameters:
        file: output file pointer.
        element: void pointer to a course.

    Returns:
        None.
*/
void save_booking_callback(FILE *file, void *element);

/*
    Prints detailed information about the course.

    Parameters:
        course: pointer to the course.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        None.
*/
void print_course(course_ptr course);

/*
    Callback function to print a course to stdout.

    Parameters:
        file: file pointer (ignored).
        element: void pointer to a course.

    Returns:
        None.
*/
void print_course_callback(FILE *file, void *element);

/*
    Callback function to print a course in CSV format to a file.

    Parameters:
        file: output file pointer.
        element: void pointer to a course.

    Returns:
        None.
*/
void print_course_file_callback(FILE *file, void *element);

/*
    Frees the memory allocated for the course, its name, and datetime.

    Parameters:
        course: pointer to the course to delete.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        None.
*/
void delete_course(course_ptr course);

#endif