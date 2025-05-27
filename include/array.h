#ifndef ARRAY_H
#define ARRAY_H

#include "course.h"
#include <stdio.h>
#include <stdint.h>

typedef struct array *array_ptr;

/*
    Function that creates a new array capable of holding up to `size` elements.
    It allocates internal storage and initializes control fields.

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
array_ptr array_create(uint16_t size);

/*
    Adds a new element to the array by inserting its reference at the next
    available position.

    parameters:
        array:   pointer to the array 
        element: the void* to insert 

    pre-condition:
        array must be valid
        element must be valid
        array->last_element < array->size

    post-condition:
        - element inserted at the last available position
        - last_element is incremented by 1

    return:
        None; exits the program if capacity would be exceeded.
*/
void array_add(array_ptr array, void* element);

/*
    Returns the total capacity (size) of the array.

    parameters:
        array: pointer to the array (must be valid)

    pre-condition:
        array must be valid

    post-condition:
        No changes to the array

    return:
        The capacity of the array
*/
uint16_t get_size(array_ptr array);

/*
    Retrieves a pointer to the element at the specified index.

    parameters:
        array: pointer to the array (must be valid)
        index: zero-based index to retrieve from

    pre-condition:
        array must be valid
        index < array->size

    post-condition:
        No changes to the array

    return:
        Pointer to the element at the given index, or NULL if out of bounds
*/
void** get_at(array_ptr array, uint16_t index);

/*
    Replaces the element at the specified index with a new element.

    parameters:
        array:   pointer to the array (must be valid)
        index:   zero-based index to replace
        element: new element to set at the given index

    pre-condition:
        array must be valid
        index < array->size

    post-condition:
        The element at the specified index is replaced

    return:
        None
*/
void set_at(array_ptr array, uint16_t index, void* element);

/*
    Function that searches for an element by its ID within the array.

    parameters:
        array: pointer to the initialized array of courses to search.
        course_id: the element ID to find (uint16_t).

    pre-condition:
        array must be non-NULL and properly initialized.
        array->elements must contain valid course_ptr entries.

    post-condition:
        The array remains unchanged.

    return:
        The zero-based index of the element if a match is found;
        otherwise, returns -1.

int search_course(array_ptr array, uint16_t course_id);
*/

/*
    Iterates over the array and prints each element using a user-provided function.

    parameters:
        array:          pointer to the array (must be valid)
        file:           file in which output the print function
        print_function: function to print one element (must be valid)

    pre-condition:
        array must be valid
        file must be valid
        print_function must be valid

    post-condition:
        All elements have been passed to print_function in insertion order;
        the array remains unchanged.

    return:
        None.
*/
void array_print(array_ptr array,  FILE* file, void (*print_function)(FILE* file, void* element));

/*
    Frees memory for all elements in the array using a provided delete_function,
    then frees the array structure itself.

    parameters:
        array:           pointer to the array (must be valid)
        delete_function: function to deallocate each element (may be NULL)

    pre-condition:
        array must be valid

    post-condition:
        All element memory is deallocated if delete_function is provided,
        then the array and its internal storage are freed

    return:
        None
*/
void array_delete(array_ptr array, void (*delete_function)(void* element));

#endif
