#ifndef FREQUENTATION_H
#define FREQUENTATION_H

#include <stdio.h>
#include <stdint.h>

typedef struct frequentation *frequentation_ptr;

/*
    Creates a new frequentation object.

    Parameters:
        course_id: the ID of the course.
        course_name: the name of the course (null-terminated string).
        times_booked: the number of times the course has been booked.

    Pre-conditions:
        course_name must not be NULL.

    Post-conditions:
        Allocates memory for a new frequentation and copies course_name.

    Returns:
        A pointer to the newly created frequentation object.
*/
frequentation_ptr create_frequentation(uint16_t course_id, char *course_name, uint16_t times_booked);

/*
    Saves the frequentation data to a file in CSV format.

    Parameters:
        file: file pointer to write to.
        element: void pointer to frequentation object.

    Returns:
        None.
*/
void save_frequentation_callback(FILE *file, void *element);

/*
    Frees the memory allocated for a frequentation, including its name.

    Parameters:
        element: void pointer to frequentation object.

    Returns:
        None.
*/
void delete_frequentation(void* element);

/*
    Gets the course ID from a frequentation.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        The course ID (uint16_t).
*/
uint16_t get_frequentation_id(frequentation_ptr frequentation);

/*
    Gets the course name from a frequentation.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        The course name string.
*/
char* get_frequentation_name(frequentation_ptr frequentation);

/*
    Gets the number of times booked from a frequentation.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        The times booked (uint16_t).
*/
uint16_t get_frequentation_times_booked(frequentation_ptr frequentation);

/*
    Sets the times booked count for a frequentation.

    Parameters:
        frequentation: pointer to frequentation.
        value: new times booked count.

    Returns:
        None.
*/
void set_frequentation_times_booked(frequentation_ptr frequentation, int value);

/*
    Prints a formatted representation of the frequentation to a file.

    Parameters:
        file: file pointer to print to.
        element: void pointer to frequentation.

    Returns:
        None.
*/
void print_frequentation_callback(FILE* file, void* element);

#endif