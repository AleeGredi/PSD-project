#include "subscription.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct subscription {
    uint16_t id;
    datetime_ptr start_date;
    datetime_ptr end_date;
};

/*
    Allocates memory for a new subscription object and initializes its fields.
    The start_date and end_date pointers are stored directly without copying,
    managing their memory and ensuring their validity is done outiside this function.

    parameters:
        id: Unique identifier for the subscription.
        start_date: Pointer to an initialized datetime object representing the start.
        end_date: Pointer to an initialized datetime object representing the end.

    return:
        A pointer to the newly allocated subscription.
*/
subscription_ptr create_subscription(
    uint16_t id,
    datetime_ptr start_date,
    datetime_ptr end_date
) {
    subscription_ptr new_subscription = malloc(sizeof(struct subscription));
    CHECK_NULL(new_subscription);
    new_subscription->id = id;

    // stored a reference to the datetime_ptr datetime parameter
    new_subscription->start_date = start_date;

    // stored a reference to the datetime_ptr datetime parameter
    new_subscription->end_date = end_date;

    return new_subscription;
}

/*
    Returns the ID of the given subscription.

    parameters:
        subscription: A valid pointer to a subscription object.

    return:
        The subscription ID.
*/
uint16_t get_subscription_id(subscription_ptr subscription) {
    return subscription->id;
}

/*
    Returns the start date of the given subscription.

    parameters:
        subscription: A valid pointer to a subscription object.

    return:
        Pointer to the start date datetime object.
*/
const datetime_ptr get_subscription_start_date(subscription_ptr subscription) {
    return subscription->start_date;
}

/*
    Returns the end date of the given subscription.

    parameters:
        subscription: A valid pointer to a subscription object.

    return:
        Pointer to the end date datetime object.
*/
const datetime_ptr get_subscription_end_date(subscription_ptr subscription) {
    return subscription->end_date;
}

/*
    Prints subscription information, including ID, start date, and end date.

    parameters:
        subscription: A valid pointer to a subscription object.
*/
void print_subscription(subscription_ptr subscription) {
    printf("Subscription ID: %u\n", subscription->id);
    printf("Start Date: %s\n", subscription->start_date);
    printf("End Date: %s\n", subscription->end_date);
}

/*
    Frees the memory associated with a subscription object, including its
    referenced start and end datetime objects.

    parameters:
        subscription: A pointer to the subscription to free.
*/
void delete_subscription(subscription_ptr subscription) {
    free(subscription->start_date);
    free(subscription->end_date);
    free(subscription);
}