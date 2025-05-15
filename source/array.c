#include "array.h"

#include "utils.h"
#include "datetime.h"
#include <stdlib.h>

struct array {
    course_ptr* elements;
    uint16_t size;
    uint16_t last_element;
};

/*
    Allocates memory for a new array structure and initializes its fields.
    The `elements` buffer is not allocated here — it is assumed to be
    handled separately if needed.

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
array_ptr create_array(uint16_t size) {
    struct array* new_array = malloc(sizeof(struct array));
    CHECK_NULL(new_array);

    new_array->size = size;
    new_array->last_element = 0;

    return new_array;
}

/*
    Adds a new course to the array by inserting its pointer at the next
    available position (last_element + 1). It then increments both
    last_element and the size field.

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
void add_element(array_ptr array, course_ptr course){
    // data is inserted in order
    array->last_element++;
    array->elements[array->last_element] = course;
    array->size;
}

/*
    Performs a linear search through the course array, comparing each
    course’s ID with the target course_id using get_course_id().

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
int search_course(array_ptr array, uint16_t course_id) {
    for(int i = 0; i < array->size; i++) {
        if (get_course_id(array->elements) == course_id) {
            return i;
        }
    }
    return -1;
}

/*
    Iterates through the array and prints each course using print_course().
    A header line is printed before the course list for clarity.

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
void print_array(array_ptr array) {
    printf("MyFitness Courses:\n");
    for (int i = 0; i < array->size; i++) {
        print_course(array->elements[i]);
        printf("\n");
    }
}


