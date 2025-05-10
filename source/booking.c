#include "booking.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

struct booking {
    uint16_t id;
    struct booking* next;
};

struct booking_list {
    struct booking* head;
    uint16_t booking_count;
};

booking_list_ptr create_booking_list() {
    struct booking_list* new_booking_list = malloc(sizeof(struct booking_list));
    CHECK_NULL(new_booking_list);

    new_booking_list->head = NULL;
    new_booking_list->booking_count = 0;

    return new_booking_list;
}

void add_booking(booking_list_ptr booking_list, uint16_t user_id) {
    struct booking* new_booking = malloc(sizeof(struct booking));
    CHECK_NULL(new_booking);
    new_booking->id = user_id;
    new_booking->next = NULL;

    struct booking* current = booking_list->head;
    
    if (booking_list->head == NULL) {
        booking_list->head = new_booking;
    } else {
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = new_booking;
    }
    
    booking_list->booking_count++;
}

int search_booking(booking_list_ptr booking_list, uint16_t user_id) {
    int return_value = 0;
    struct booking* current = booking_list->head;

    /*
        if it find that the element to search is the last,
        it will exit the loop before return_value is incremented
    */
    while(current != NULL) {
        if (current->id == user_id) {
            return return_value;
        }
        current = current->next;
        return_value++;
    }

    return -1;
}

void delete_booking(booking_list_ptr booking_list, uint16_t user_id) {
    struct booking* current = booking_list->head;
    // head case
    if (current->id == user_id) {
        struct booking* next = current->next;
        free(current);
        booking_list->head = next;
        booking_list->booking_count--;
    } else {
        while(current != NULL) {
            if(current->next->id == user_id) {
                struct booking* to_delete = current->next;
                current->next = to_delete->next;
                free(to_delete);
                booking_list->booking_count--;
                break;
            }
            current = current->next;
        }
    }
}

void delete_booking_list(booking_list_ptr booking_list) {
    struct booking* current = booking_list->head;

    while(current != NULL) {
        struct booking* to_delete = current;
        current = current->next;
        free(to_delete);
    }

    free(booking_list);
}

void print_booking_list(booking_list_ptr booking_list) {
    printf("Total bookings: %u\n", booking_list->booking_count);

    struct booking* current = booking_list->head;
    if (current == NULL) {
        printf("No bookings to display.\n");
        return;
    }

    while (current != NULL) {
        printf(" - Booking ID: %u\n", current->id);
        current = current->next;
    }
}
