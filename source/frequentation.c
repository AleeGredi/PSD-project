#include "frequentation.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct frequentation {
    uint16_t course_id;
    char *course_name;
    uint16_t times_booked;
};

/*
    Creates a new frequentation object with specified values.
    Allocates and copies course_name.

    Parameters:
        course_id: ID of the course.
        course_name: name of the course (null-terminated string).
        times_booked: how many times booked.

    Pre-conditions:
        course_name must not be NULL.

    Post-conditions:
        A new frequentation object is allocated and initialized.

    Returns:
        pointer to the new frequentation.
*/
frequentation_ptr create_frequentation(uint16_t course_id, char *course_name, uint16_t times_booked) {
    frequentation_ptr new_frequentation = malloc(sizeof(struct frequentation));
    CHECK_NULL(new_frequentation);

    new_frequentation->course_id = course_id;

    new_frequentation->course_name = malloc(strlen(course_name) + 1);
    CHECK_NULL(new_frequentation->course_name);
    strcpy(new_frequentation->course_name, course_name);

    new_frequentation->times_booked = times_booked;

    return new_frequentation;
}

/*
    Writes frequentation data to a file in CSV format.

    Parameters:
        file: output file pointer.
        element: void pointer to frequentation.

    Returns:
        None.
*/
void save_frequentation_callback(FILE *file, void *element) {
    frequentation_ptr frequentation = (frequentation_ptr)element;
    fprintf(file, "%d,%s,%d,",
            get_frequentation_id(frequentation),
            get_frequentation_name(frequentation),
            get_frequentation_times_booked(frequentation));
}

/*
    Frees memory allocated for frequentation and its course_name string.

    Parameters:
        element: void pointer to frequentation.

    Returns:
        None.
*/
void delete_frequentation(void* element) {
    if (!element) return;
    frequentation_ptr f = (frequentation_ptr)element;
    free(f->course_name);
    free(f);
}

/*
    Returns the course_id.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        course ID.
*/
uint16_t get_frequentation_id(frequentation_ptr frequentation) {
    return frequentation->course_id;
}

/*
    Returns the course_name.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        course name string.
*/
char* get_frequentation_name(frequentation_ptr frequentation) {
    return frequentation->course_name;
}

/*
    Returns the times_booked.

    Parameters:
        frequentation: pointer to frequentation.

    Returns:
        times booked.
*/
uint16_t get_frequentation_times_booked(frequentation_ptr frequentation) {
    return frequentation->times_booked;
}

/*
    Sets the times_booked to the given value.

    Parameters:
        frequentation: pointer to frequentation.
        value: new times booked count.

    Returns:
        None.
*/
void set_frequentation_times_booked(frequentation_ptr frequentation, int value) {
    frequentation->times_booked = value;
}

/*
    Prints a formatted frequentation entry to a file if entry is valid.

    Parameters:
        file: output file pointer.
        element: void pointer to frequentation.

    Returns:
        None.
*/
void print_frequentation_callback(FILE* file, void* element) {
    frequentation_ptr entry = (frequentation_ptr)element;

    // Check if entry is effectively empty/null
    if (entry == NULL ||
        (entry->course_id == 0 &&
         entry->times_booked == 0 &&
         (entry->course_name == NULL ||
          strcmp(entry->course_name, "") == 0 ||
          strcmp(entry->course_name, "0") == 0 ||
          strcmp(entry->course_name, "\"\"") == 0))) {
        return;
    }

    fprintf(file, "History Entry - ID: %hu, Name: %s, Times Booked: %hu\n",
            entry->course_id, entry->course_name, entry->times_booked);
}