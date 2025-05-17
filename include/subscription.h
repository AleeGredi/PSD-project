#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "datetime.h"
#include <stdint.h>

typedef struct subscription *subscription_ptr;

/*
    Function that creates a new subscription.

    parameters:
        id: Unique identifier for the subscription.
        start_date: Pointer to a datetime representing the subscription's start date.
        end_date: Pointer to a datetime representing the subscription's end date.

    pre-condition:
        start_date and end_date must be valid, non-NULL datetime_ptr values.
        end_date must not be earlier than start_date.

    post-condition:
        A new subscription is created and returned.

    return:
        subscription_ptr: A pointer to the newly created subscription.
*/
subscription_ptr create_subscription(
    uint16_t id,
    datetime_ptr start_date,
    datetime_ptr end_date
);

/*
    Function that retrieves the subscription's ID.

    parameters:
        subscription: Pointer to the subscription.

    pre-condition:
        subscription must be initialized and not NULL.

    post-condition:
        No modification to the subscription.

    return:
        uint16_t: The ID of the subscription.
*/
uint16_t get_subscription_id(subscription_ptr subscription);

/*
    Function that retrieves the start date of the subscription.

    parameters:
        subscription: Pointer to the subscription.

    pre-condition:
        subscription must be initialized and not NULL.

    post-condition:
        No modification to the subscription.

    return:
        datetime_ptr: A pointer to the start date.
*/
const datetime_ptr get_subscription_start_date(subscription_ptr subscription);

/*
    Function that retrieves the end date of the subscription.

    parameters:
        subscription: Pointer to the subscription.

    pre-condition:
        subscription must be initialized and not NULL.

    post-condition:
        No modification to the subscription.

    return:
        datetime_ptr: A pointer to the end date.
*/
const datetime_ptr get_subscription_end_date(subscription_ptr subscription);

/*
    Function that prints the subscription's information.

    parameters:
        subscription: Pointer to the subscription to print.

    pre-condition:
        subscription must be initialized and not NULL.

    post-condition:
        No modification to the subscription.

    return:
        Nothing.
*/
void print_subscription(subscription_ptr subscription);

/*
    Function that deletes a subscription and frees its memory.

    parameters:
        subscription: Pointer to the subscription to delete.

    pre-condition:
        subscription must be initialized and not NULL.

    post-condition:
        The subscription and its associated resources are freed from memory.

    return:
        Nothing.
*/
void delete_subscription(subscription_ptr subscription);

#endif