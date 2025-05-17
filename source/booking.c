#include "booking.h"
#include "utils.h"
#include "course.h"

#include <stdio.h>
#include <stdlib.h>

struct booking {
    course_ptr course;
    struct booking* next;
};

struct booking_list {
    struct booking* head;
    uint16_t booking_count;
};

/*
    Allocates memory for a new booking list, initializes head to NULL
    and booking_count to 0. Returns a pointer to the newly created list.

    return:
        booking_list_ptr: a pointer to the newly created booking list.
*/
booking_list_ptr create_booking_list() {
    struct booking_list* new_booking_list = malloc(sizeof(struct booking_list));
    CHECK_NULL(new_booking_list);

    new_booking_list->head = NULL;
    new_booking_list->booking_count = 0;

    return new_booking_list;
}

/*
    Allocates a new booking node with the given course pointer.
    If the list is empty, the new booking becomes the head.
    Otherwise, it is appended to the end of the list.
    Increments booking_count after every successful insertion.

    parameters:
        booking_list: pointer to the booking list where the booking should be added.
        course: pointer to the course being booked.

    pre-condition:
        booking_list and course must be non-NULL and properly initialized.

    post-condition:
        The booking list is modified by adding a new booking.

    return:
        Nothing.
*/
void add_booking(booking_list_ptr booking_list, course_ptr course) {
    struct booking* new_booking = malloc(sizeof(struct booking));
    CHECK_NULL(new_booking);
    new_booking->course = course;
    new_booking->next = NULL;

    struct booking* current = booking_list->head;

    if (current == NULL) {
        booking_list->head = new_booking;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_booking;
    }

    booking_list->booking_count++;
}

/*
    Iterates through the list, comparing each booking's course pointer.
    Returns the index of the first match or -1 if not found.

    parameters:
        booking_list: pointer to the booking list to search.
        course: pointer to the course to search for.

    pre-condition:
        booking_list and course must be non-NULL.

    post-condition:
        No modification to the list.

    return:
        -1 if no matching booking is found;
         otherwise, the position (starting from 0) of the booking.
*/
int search_booking(booking_list_ptr booking_list, course_ptr course) {
    int index = 0;
    struct booking* current = booking_list->head;

    while (current != NULL) {
        if (current->course == course) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

/*
    Deletes the first booking that matches the given course pointer.

    parameters:
        booking_list: pointer to the booking list to modify.
        course: pointer to the course to remove.

    pre-condition:
        booking_list and course must be non-NULL.

    post-condition:
        If a booking is found, it is removed and memory is freed.

    return:
        Nothing.
*/
void delete_booking(booking_list_ptr booking_list, course_ptr course) {
    struct booking* current = booking_list->head;

    // Head case
    if (current != NULL && current->course == course) {
        booking_list->head = current->next;
        free(current);
        booking_list->booking_count--;
        return;
    }

    // Middle or end
    while (current != NULL && current->next != NULL) {
        if (current->next->course == course) {
            struct booking* to_delete = current->next;
            current->next = to_delete->next;
            free(to_delete);
            booking_list->booking_count--;
            return;
        }
        current = current->next;
    }
}

/*
    Frees all memory used by the booking list and its bookings.

    parameters:
        booking_list: pointer to the booking list to delete.

    pre-condition:
        booking_list must be non-NULL.

    post-condition:
        All memory for the list and its bookings is freed.

    return:
        Nothing.
*/
void delete_booking_list(booking_list_ptr booking_list) {
    struct booking* current = booking_list->head;

    while (current != NULL) {
        struct booking* to_delete = current;
        current = current->next;
        free(to_delete);
    }

    free(booking_list);
}

/*
    Prints the list of bookings and their associated course IDs.

    parameters:
        booking_list: pointer to the booking list to print.

    pre-condition:
        booking_list must be non-NULL.

    post-condition:
        Nothing.

    return:
        Nothing.
*/
void print_booking_list(booking_list_ptr booking_list) {
    printf("Total bookings: %u\n", booking_list->booking_count);

    struct booking* current = booking_list->head;
    if (current == NULL) {
        printf("No bookings to display.\n");
        return;
    }

    while (current != NULL) {
        printf(" - Course ID: %u\n", get_course_id(current->course));
        current = current->next;
    }
}