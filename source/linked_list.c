#include "linked_list.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

struct node {
    void* element;
    struct node* next;
};

struct linked_list {
    struct node* head;
    uint16_t element_count;
};

/*
    Allocates and initializes memory for a new linked list struct with head set to NULL and element count zero.

    parameters:
        none

    pre-condition:
        none

    post-condition:
        A new, empty linked list is created in memory.

    return:
        linked_list_ptr: pointer to the newly created list.
*/
linked_list_ptr ll_create() {
    struct linked_list* new_booking_list = malloc(sizeof(struct linked_list));
    CHECK_NULL(new_booking_list);

    new_booking_list->head = NULL;
    new_booking_list->element_count = 0;

    return new_booking_list;
}

/*
    Creates a new node, traverses to the end of the list, and appends the node there.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        element: valid (non-NULL) pointer to the element to store.

    pre-condition:
        linked_list and element must be valid and non-NULL.

    post-condition:
        A new node is added to the end of the list.
        element_count is incremented.

    return:
        None
*/
void ll_add(linked_list_ptr linked_list, void* element) {
    struct node* new_booking = malloc(sizeof(struct node));
    CHECK_NULL(new_booking);
    new_booking->element = element;
    new_booking->next = NULL;

    if (linked_list->head == NULL) {
        linked_list->head = new_booking;
    } else {
        struct node* current = linked_list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_booking;
    }

    linked_list->element_count++;
}

/*
    Iterates over the list, comparing each element using compare_function until a match is found.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        element: valid (non-NULL) pointer to the target element.
        compare_function: valid function pointer to compare elements.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        No changes to the list.

    return:
        int: Index (starting from 0) of the first matching node, or -1 if not found.
*/
int ll_search(linked_list_ptr linked_list, void* element, int (*compare_function)(void* element1, void* element2)) {
    int index = 0;
    struct node* current = linked_list->head;

    while (current != NULL) {
        if (compare_function(current->element, element)) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

/*
    Traverses the list up to the given index and returns a pointer to the element.

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
void** ll_get_at(linked_list_ptr linked_list, uint16_t index){
    if(index >= linked_list->element_count) return NULL;
    
    struct node* current = linked_list->head;
    uint16_t i = 0;
    while(current && index != i) {
        i++;
        current = current->next;
    }
    return &current->element;
}

/*
    Returns the current count of elements stored in the list.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.

    pre-condition:
        linked_list must be valid and non-NULL.

    post-condition:
        The list remains unmodified.

    return:
        uint16_t: number of elements in the list.
*/
uint16_t ll_get_element_count(linked_list_ptr linked_list) {
    return linked_list->element_count;
}

/*
    Iterates through the list and adds each element to the provided array using array_add.

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
void ll_copy_list_to_array(linked_list_ptr linked_list, array_ptr array) {
    struct node* current = linked_list->head;
    while(current) {
        array_add(array, current->element);
        current = current->next;
    }
}

/*
    Traverses the list to the given index, unlinks the node, calls delete_function, and frees it.

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
    void (*delete_function)(void* element)) {

    if (index >= linked_list->element_count) {
        return;
    }

    struct node* current = linked_list->head;
    struct node* to_delete = NULL;

    if (index == 0) {
        to_delete = current;
        linked_list->head = current->next;
    } else {
        for (uint16_t i = 0; i < index - 1; i++) {
            current = current->next;
        }
        to_delete = current->next;
        current->next = to_delete->next;
    }

    if (delete_function) {
        delete_function(to_delete->element);
    }
    free(to_delete);
    linked_list->element_count--;
}

/*
    Traverses the list to find the first match using compare_function, removes the node, and frees its memory.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        element: valid (non-NULL) pointer to the element to remove.
        compare_function: valid function pointer to identify matching element.
        delete_function: valid function pointer to deallocate the node.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        If a match is found, the node is removed and memory freed.
        element_count is decremented if deletion occurs.

    return:
        None
*/
void ll_delete_element(linked_list_ptr linked_list, 
    void* element, 
    bool (*compare_function)(void* element1, void* element2),
    void (*delete_function)(void* element)) {
    
    struct node* current = linked_list->head;

    if (current != NULL && compare_function(current->element, element)) {
        linked_list->head = current->next;
        delete_function(current->element);
        free(current);
        linked_list->element_count--;
        return;
    }

    while (current != NULL && current->next != NULL) {
        if (compare_function(current->next->element, element)) {
            struct node* to_delete = current->next;
            current->next = to_delete->next;
            delete_function(to_delete->element);
            free(to_delete);
            linked_list->element_count--;
            return;
        }
        current = current->next;
    }
}

/*
    Iterates through the list, freeing each node's element using delete_function and then the node itself.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        delete_function: valid function pointer to deallocate each node.

    pre-condition:
        Both parameters must be valid and non-NULL.

    post-condition:
        All nodes and their elements are freed from memory.
        The list itself is also deallocated.

    return:
        None
*/
void ll_delete_list(linked_list_ptr linked_list, void (*delete_function)(void* element)) {
    if (!delete_function) {
        free(linked_list);
        return;
    }
    
    struct node* current = linked_list->head;
    
    while (current != NULL) {
        struct node* to_delete = current;
        current = current->next;
        delete_function(to_delete->element);
        free(to_delete);
    }

    free(linked_list);
}

/*
    Walks through each node in the list and uses the provided print function to display the element.

    parameters:
        linked_list: valid (non-NULL) pointer to the list.
        file: file in which output the print function.
        print_function: valid function pointer to print a node's element.

    pre-condition:
        All parameters must be valid and non-NULL.

    post-condition:
        The list is unchanged; output is printed to the specified file.

    return:
        None
*/
void ll_print(linked_list_ptr linked_list,  FILE* file, void (*print_function)(FILE* file, void* element)) {
    struct node* current = linked_list->head;

    while (current != NULL) {
        print_function(file, current->element);
        current = current->next;
    }
}