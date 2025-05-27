#include "course.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course {
    uint16_t id;
    char* name;
    datetime_ptr datetime;
    uint16_t seats_total;
    uint16_t seats_booked;
};

/*
    Allocates memory for a new course object and initializes its fields.
    Copies the provided name string, stores a reference to the datetime parameter.

    Parameters:
        id: unique identifier for the course.
        name: null-terminated string with the course name.
        datetime: pointer to an initialized datetime object for the course.
        seats_total: total number of seats available.
        seats_booked: number of seats already booked.

    Pre-conditions:
        name must not be NULL.
        datetime must be a valid datetime_ptr.

    Post-conditions:
        A new course object is allocated and initialized.

    Returns:
        A pointer to the newly allocated course.
*/
course_ptr create_course(
    uint16_t id,
    char* name,
    datetime_ptr datetime,
    uint16_t seats_total,
    uint16_t seats_booked
) {
    course_ptr new_course = malloc(sizeof(struct course));
    CHECK_NULL(new_course);

    new_course->id = id;

    new_course->name = malloc(strlen(name) + 1);
    CHECK_NULL(new_course->name);
    strcpy(new_course->name, name);

    new_course->datetime = datetime;
    new_course->seats_total  = seats_total;
    new_course->seats_booked = seats_booked;

    return new_course;
}

/*
    Returns the course's ID.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        The course ID.
*/
uint16_t get_course_id(course_ptr course) {
    return course->id;
}

/*
    Compares two course pointers by ID for equality.

    Parameters:
        a: void pointer to the first course.
        b: void pointer to the second course.

    Pre-conditions:
        Both a and b must be valid pointers to course objects.

    Returns:
        1 if both courses have the same ID, 0 otherwise.
*/
int compare_course_id(void* a, void* b) {
    course_ptr course_a = (course_ptr)a;
    course_ptr course_b = (course_ptr)b;
    return get_course_id(course_a) == get_course_id(course_b);
}

/*
    Returns the course's name.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        Pointer to the null-terminated name string.
*/
char* get_course_name(course_ptr course) {
    return course->name;
}

/*
    Returns the datetime of the course.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        Pointer to the datetime object.
*/
datetime_ptr get_course_datetime(course_ptr course) {
    return course->datetime;
}

/*
    Returns the total number of seats for the course.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        Total seats.
*/
uint16_t get_course_seats_total(course_ptr course) {
    return course->seats_total;
}

/*
    Returns the number of already booked seats.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        Booked seats.
*/
uint16_t get_course_seats_booked(course_ptr course) {
    return course->seats_booked;
}

/*
    Updates the number of seats booked for a course.

    Parameters:
        course: pointer to a course object.
        value:  new number of booked seats.

    Pre-conditions:
        course must be initialized and not NULL.

    Post-conditions:
        course->seats_booked is updated to the new value.

    Returns:
        None.
*/
void set_course_seats_booked(course_ptr course, int value) {
    course->seats_booked = value;
}

/*
    Callback function to print only the course ID to a file.

    Parameters:
        file: output file pointer.
        element: void pointer to a course.

    Pre-conditions:
        file must be a valid FILE pointer.
        element must be a valid pointer to a course object.

    Returns:
        None.
*/
void save_booking_callback(FILE *file, void *element){
    course_ptr course = (course_ptr)element;
    fprintf(file, "%d,", get_course_id(course));
}

/*
    Prints detailed information about the course.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must be initialized and not NULL.

    Returns:
        None.
*/
void print_course(course_ptr course) {
    printf("Course ID: %u\n", course->id);
    printf("Name     : %s\n", course->name);
    printf("Datetime : ");
    print_datetime(stdout, course->datetime);
    printf("\n");
    printf("Seats    : %u total, %u booked\n",
           course->seats_total,
           course->seats_booked);
}

/*
    Callback to print course details to stdout.

    Parameters:
        file: ignored (stdout used instead).
        element: void pointer to a course.

    Pre-conditions:
        element must be a valid pointer to a course object.

    Returns:
        None.
*/
void print_course_callback(FILE *file, void *element){
    (void)file; // Explicitly ignore unused parameter
    course_ptr course = (course_ptr)element;
    print_course(course);
}

/*
    Callback to print course data to a file in CSV format.

    Parameters:
        file: output file pointer.
        element: void pointer to a course.

    Pre-conditions:
        file must be a valid FILE pointer.
        element must be a valid pointer to a course object.

    Returns:
        None.
*/
void print_course_file_callback(FILE *file, void *element){
    course_ptr course = (course_ptr)element;
    fprintf(file, "%u,%s,", get_course_id(course), get_course_name(course));
    print_datetime(file, get_course_datetime(course));
    fprintf(file, ",%u,%u,", get_course_seats_total(course), get_course_seats_booked(course));
    fprintf(file, "\n");
}

/*
    Frees all memory associated with the course:
    name, datetime object, and the course struct itself.

    Parameters:
        course: a pointer to the course to delete.

    Pre-conditions:
        course must be initialized and not NULL.

    Post-conditions:
        The course and all associated memory are freed.

    Returns:
        None.
*/
void delete_course(course_ptr course) {
    free(course->name);
    free(course->datetime);
    free(course);
}
