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
    The elements buffer is also allocated to hold pointers up to the given size.

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
    available position (last_element). It then increments last_element.

    parameters:
        array:   pointer to the array (must be valid)
        element: the void* to insert (must be valid)

    pre-condition:
        array must be valid
        element must be valid
        array->last_element < array->size

    post-condition:
        - elements[old last_element] == element
        - last_element is incremented by 1

    return:
        None; exits the program if capacity would be exceeded.
*/
void array_add(array_ptr array, void* element){
    if (array->last_element > array->size) {
        perror("Array size surpassed");
        exit(1);
    }
    array->elements[array->last_element] = element;
    array->last_element++;
}

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
uint16_t get_size(array_ptr array){
    return array->size;
}

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
void** get_at(array_ptr array, uint16_t index) {
    if (index >= array->size) return NULL;
    return &array->elements[index];
}

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
void set_at(array_ptr array, uint16_t index, void* element) {
    if (index >= array->size) return;
    array->elements[index] = element;
}

/*
    Iterates over the array and calls a user-provided print function on each element.

    parameters:
        array:          pointer to the array (must be valid)
        file:           file in which to output the print function
        print_function: function to print one element (must be valid)

    pre-condition:
        array must be valid
        file must be valid
        print_function must be valid

    post-condition:
        All elements have been passed to print_function in insertion order;
        the array remains unchanged.

    return:
        None
*/
void array_print(array_ptr array,  FILE* file, void (*print_function)(FILE* file, void* element)) {
    CHECK_NULL(array);
    CHECK_NULL(print_function);
    for (int i = 0; i < array->size; i++) {
        print_function(file, array->elements[i]);
    }
}

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
void array_delete(array_ptr array, void (*delete_function)(void* element)) {
    if (!delete_function) {
        free(array->elements);
        free(array);
        return;
    }

    for(int i = 0; i < array->size; i++) {
        delete_function(array->elements[i]);
    }

    free(array->elements);
    free(array);
}