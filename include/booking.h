#ifndef BOOKING_H
#define BOOKING_H

#include <stdint.h>

typedef struct booking_list *booking_list_ptr;

/*
    Function that creates an empty booking list.

    return:
        booking_list_ptr: a pointer to the newly created booking list.
*/
booking_list_ptr create_booking_list();

/*
    Function that creates and adds a booking to the booking list.

    parameters:
        booking_list: pointer to the booking list where the booking
                      should be added.
        user_id: ID of the user making the booking.

    pre-condition:
        booking_list must be initialized and not NULL.
        user_id must be a valid uint16_t.

    post-condition:
        The original booking_list will be modified (a new booking is added).

    return:
        Nothing.
*/
void add_booking(booking_list_ptr booking_list, uint16_t user_id);

/*
    Function that searches for a booking in the list.

    parameters:
        booking_list: pointer to the booking list where the booking
                      should be searched.
        user_id: the ID of the booking to search for.

    pre-condition:
        booking_list must be initialized and not NULL.
        user_id must be a valid uint16_t.

    post-condition:
        No modification to the list.

    return:
        -1 if the booking is not found,
        otherwise the position (starting from 0) of the booking in the list.
*/
int search_booking(booking_list_ptr booking_list, uint16_t user_id);

/*
    Function that deletes a booking from the list.

    parameters:
        booking_list: pointer to the booking list where the booking
                      should be deleted.
        user_id: the ID of the booking to delete. If not found, no error occurs.

    pre-condition:
        booking_list must be initialized and not NULL.
        user_id must be a valid uint16_t.

    post-condition:
        The booking (if found) is removed from the list.
        The booking count is updated.

    return:
        Nothing.
*/
void delete_booking(booking_list_ptr booking_list, uint16_t user_id);

/*
    Function that deletes the booking list and all its elements.

    parameters:
        booking_list: pointer to the booking list to delete.

    pre-condition:
        booking_list must be initialized and not NULL.

    post-condition:
        The booking list and all its bookings are freed from memory.

    return:
        Nothing.
*/
void delete_booking_list(booking_list_ptr booking_list);

/*
    Function that prints the booking list and all its elements.

    parameters:
        booking_list: pointer to the booking list to print.

    pre-condition:
        booking_list must be initialized and not NULL.

    post-condition:
        Nothing.

    return:
        Nothing.
*/
void print_booking_list(booking_list_ptr booking_list);

#endif
