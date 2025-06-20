#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include "course.h"
#include <stdbool.h>
#include "array.h"

typedef struct linked_list *linked_list_ptr;

/*
    Creates an empty linked list.

    parameters:
        none

    pre-condition:
        none

    post-condition:
        A new, empty linked list is created in memory.

    return:
        linked_list_ptr: pointer to a newly allocated, empty linked list.
*/
linked_list_ptr ll_create();

/*
    Adds a new node containing the given element to the end of the list.

    parameters:
        linked_list: valid (non-NULL) pointer to the list where the new node will be added.
        element: valid (non-NULL) pointer to the element to be stored in the node.

    pre-condition:
        Both parameters must be valid and non-NULL.

    post-condition:
        The list is updated to include the new node.

    return:
        None
*/
void ll_add(linked_list_ptr linked_list, void* element);

/*
    Searches the list for an element using a user-provided comparison function.

    parameters:
        linked_list: valid (non-NULL) pointer to the list to search in.
        element: valid (non-NULL) pointer to the target element.
        compare_function: valid function pointer to compare elements.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        The list remains unmodified.

    return:
        int: Index (starting from 0) of the matching node if found, -1 otherwise.
*/
int ll_search(linked_list_ptr linked_list, void* element, int (*compare_function)(void* element1, void* element2));

/*
    Retrieves a pointer to the element at a specific index in the list.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        index: index of the element to retrieve.

    pre-condition:
        linked_list must be valid and index must be within bounds of the list.

    post-condition:
        The list remains unmodified.

    return:
        void**: pointer to the element at the specified index, or NULL if index is out of bounds.
*/
void** ll_get_at(linked_list_ptr linked_list, uint16_t index);

/*
    Returns the number of elements currently in the list.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.

    pre-condition:
        linked_list must be valid and non-NULL.

    post-condition:
        The list remains unmodified.

    return:
        uint16_t: number of elements in the list.
*/
uint16_t ll_get_element_count(linked_list_ptr linked_list);

/*
    Copies all elements from the linked list to an array.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        array: valid (non-NULL) pointer to the array where elements will be copied.

    pre-condition:
        Both parameters must be valid and non-NULL. Array must be appropriately sized.

    post-condition:
        The array contains a copy of all elements from the list.

    return:
        None
*/
void ll_copy_list_to_array(linked_list_ptr linked_list, array_ptr array);

/*
    Deletes the node at the specified index in the list.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        index: index of the node to delete.
        delete_function: valid function pointer to deallocate the element in the node.

    pre-condition:
        All parameters must be valid and index must be within bounds.

    post-condition:
        The node at the specified index is removed and its memory is released.

    return:
        None
*/
void ll_delete_at(linked_list_ptr linked_list,
    uint16_t index,
    void (*delete_function)(void* element));

/*
    Removes the first node from the list that matches the given element.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        element: valid (non-NULL) pointer to the element to remove.
        compare_function: valid function pointer to determine matching elements.
        delete_function: valid function pointer to deallocate a node.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        If a matching node is found, it is removed and its memory is freed.

    return:
        None
*/
void ll_delete_element(linked_list_ptr linked_list, 
    void* element, 
    bool (*compare_function)(void* element1, void* element2),
    void (*delete_function)(void* element));

/*
    Frees all nodes and their elements from memory.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        delete_function: valid function pointer to deallocate each element.

    pre-condition:
        Both parameters must be valid and non-NULL.

    post-condition:
        All memory used by the list and its elements is released.

    return:
        None
*/
void ll_delete_list(linked_list_ptr linked_list, void (*delete_function)(void* element));

/*
    Prints all elements in the list using the provided print function.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        file: file in which output the print function.
        print_function: valid function pointer to print an element.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        The list remains unmodified; elements are printed to the specified file.

    return:
        None
*/
void ll_print(linked_list_ptr linked_list, FILE* file, void (*print_function)(FILE* file, void* element));

#endif
