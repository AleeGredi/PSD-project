#ifndef ARRAY_H
#define ARRAY_H

#include "course.h"
#include <stdint.h>

typedef struct array *array_ptr;

/*
    Function that creates a new array capable of holding up to `size` elements.

    parameters:
        size: the intended capacity of the array (uint16_t).

    pre-condition:
        size must be greater than zero.

    post-condition:
        A new array structure is created with the given size, and
        last_element is initialized to 0.

    return:
        A pointer to the newly allocated array structure,
        or exit if memory allocation fails.
*/
array_ptr create_array(uint16_t size);

/*
    Function that adds a reference of `course` into `array`.

    parameters:
        array: pointer to the array where the course should be added.
        course: pointer to the course to insert.

    pre-condition:
        array must be non-NULL and have enough capacity to insert a new course.
        course must be a valid, non-NULL course_ptr.

    post-condition:
        The course is added to the array at the next available index.
        last_element and size fields are incremented.

    return:
        Nothing.
*/
void add_element(array_ptr array, course_ptr course);

/*
    Function that searches for a course by its ID within the array.

    parameters:
        array: pointer to the initialized array of courses to search.
        course_id: the course ID to find (uint16_t).

    pre-condition:
        array must be non-NULL and properly initialized.
        array->elements must contain valid course_ptr entries.

    post-condition:
        The array remains unchanged.

    return:
        The zero-based index of the course if a match is found;
        otherwise, returns -1.
*/
int search_course(array_ptr array, uint16_t course_id);

/*
    Function that prints all courses stored in the array in their current order.

    parameters:
        array: pointer to the array containing courses to print.

    pre-condition:
        array must be non-NULL and properly initialized.
        array->elements must point to valid course_ptr entries.

    post-condition:
        All courses in the array are printed to stdout in the order stored.
        The array contents are not modified.

    return:
        Nothing.
*/
void print_array(array_ptr array);


#endif 
