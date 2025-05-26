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

    // Copy course name
    new_course->name = malloc(strlen(name) + 1);
    CHECK_NULL(new_course->name);
    strcpy(new_course->name, name);

    // Store reference to provided datetime
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
        course must not be NULL.

    Post-conditions:
        None.

    Returns:
        The course ID.
*/
uint16_t get_course_id(course_ptr course) {
    return course->id;
}

int compare_course_id(void* a, void* b) {
    course_ptr course_a = (course_ptr)a;
    course_ptr course_b = (course_ptr)b;
    if (get_course_id(course_a) == get_course_id(course_b)){
        return 1;
    }    
    return 0;
}

/*
    Returns the course's name.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must not be NULL.

    Post-conditions:
        None.

    Returns:
        Pointer to the null-terminated name string.
*/
const char* get_course_name(course_ptr course) {
    return course->name;
}

/*
    Returns the datetime of the course.

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must not be NULL.

    Post-conditions:
        None.

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
        course must not be NULL.

    Post-conditions:
        None.

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
        course must not be NULL.

    Post-conditions:
        None.

    Returns:
        Booked seats.
*/
uint16_t get_course_seats_booked(course_ptr course) {
    return course->seats_booked;
}

void set_course_seats_booked(course_ptr course, int value) {
    course->seats_booked = value;
}

void save_booking_callback(FILE *file, void *element){
    course_ptr course = (course_ptr)element;
    fprintf(file, "%d,", get_course_id(course));
}

/*
    Prints detailed information about the course, including:
    ID, name, datetime (using print_datetime), seat counts (total and booked)

    Parameters:
        course: a valid pointer to a course object.

    Pre-conditions:
        course must not be NULL.

    Post-conditions:
        None.

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

void print_course_callback(FILE *file, void *element){
    course_ptr course = (course_ptr)element;
    print_course(course);
}

void print_course_file_callback(FILE *file, void *element){
    course_ptr course = (course_ptr)element;
    fprintf(file, "%u,%s,", get_course_id(course), get_course_name(course));
    print_datetime(file, get_course_datetime(course));
    fprintf(file, ",%u,%u,",get_course_seats_total(course), get_course_seats_booked(course));
    fprintf(file, "\n");
}

/*
    Frees all memory (name, datetime object and the course struct itself)
    associated with the course:

    Parameters:
        course: a pointer to the course to delete.

    Pre-conditions:
        course must not be NULL.

    Post-conditions:
        All memory allocated for the course and its components is freed.

    Returns:
        None.
*/
void delete_course(course_ptr course) {
    free(course->name);
    free(course->datetime);
    free(course);
}