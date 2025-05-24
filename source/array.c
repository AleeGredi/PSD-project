#include "array.h"

#include "utils.h"
#include "datetime.h"
#include <stdlib.h>

struct array {
    void** elements;
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
array_ptr array_create(uint16_t size) {
    struct array* new_array = malloc(sizeof(struct array));
    CHECK_NULL(new_array);

    new_array->elements = malloc(sizeof(void*) * size);
    new_array->size = size;
    new_array->last_element = 0;

    return new_array;
}

/*
    Adds a new element to the array by inserting its pointer at the next
    available position (last_element + 1). It then increments
    last_element.

    parameters:
        array:   pointer to the array (must be valid)
        element: the void* to insert (must be valid)

    pre-condition:
        array must be valid
        element must be valid
        array->last_element < array->size

    post-condition:
        - `elements[old last_element] == element`
        - `last_element` is incremented by 1

    return:
        None; exits the program if capacity would be exceeded.

*/
void array_add(array_ptr array, void* element){
    // data is inserted in order
    if (array->last_element > array->size) {
        perror("Array size surpassed");
        exit(1);
    }
    array->elements[array->last_element] = element;
    array->last_element++;
}

void* get_at(array_ptr array, uint16_t index) {
    if (index >= array->size) return NULL;
    return array->elements[index];
}

void set_at(array_ptr array, uint16_t index, void* element) {
    if (index >= array->size) return NULL;
    array->elements[index] = element;
}


/*
    Performs a linear search through the element array, comparing each
    element’s ID with the target course_id using get_course_id().

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

int search_course(array_ptr array, uint16_t course_id) {
    for(int i = 0; i < array->size; i++) {
        if (get_course_id(array->elements) == course_id) {
            return i;
        }
    }
    return -1;
}
*/

/*
    Iterates over the array and calls a user-provided print function on each element.

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
void array_print(array_ptr array,  FILE* file, void (*print_function)(FILE* file, void* element)) {
    CHECK_NULL(array);
    CHECK_NULL(print_function);
    for (int i = 0; i < array->size; i++) {
        print_function(file, array->elements[i]);
    }
}