#include "subscription.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct subscription {
    datetime_ptr start_date;
    datetime_ptr end_date;
};

/*
    Creates a new subscription object with specified start and end dates.

    Parameters:
        start_date: pointer to an initialized datetime object.
        end_date: pointer to an initialized datetime object.

    Pre-conditions:
        start_date and end_date must not be NULL.
        The datetime objects are managed externally (no internal copying).

    Post-conditions:
        A new subscription object is allocated and initialized.

    Returns:
        subscription_ptr: pointer to the newly created subscription object.
*/
subscription_ptr create_subscription(
    datetime_ptr start_date,
    datetime_ptr end_date
) {
    CHECK_NULL(start_date);
    CHECK_NULL(end_date);

    subscription_ptr new_subscription = malloc(sizeof(struct subscription));
    CHECK_NULL(new_subscription);

    new_subscription->start_date = start_date;
    new_subscription->end_date = end_date;

    return new_subscription;
}

/*
    Returns the start date of a subscription.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        None.

    Returns:
        datetime_ptr: pointer to the start date.
*/
datetime_ptr get_subscription_start_date(subscription_ptr subscription) {
    CHECK_NULL(subscription);
    return subscription->start_date;
}

/*
    Returns the end date of a subscription.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        None.

    Returns:
        datetime_ptr: pointer to the end date.
*/
datetime_ptr get_subscription_end_date(subscription_ptr subscription) {
    CHECK_NULL(subscription);
    return subscription->end_date;
}

/*
    Sets the start date of a subscription.

    Parameters:
        subscription: pointer to a valid subscription object.
        start_date: pointer to a valid datetime object.

    Pre-conditions:
        subscription and start_date must not be NULL.

    Post-conditions:
        The subscription's start date is updated.
*/
void set_subscription_start_date(subscription_ptr subscription, datetime_ptr start_date) {
    CHECK_NULL(subscription);
    CHECK_NULL(start_date);
    subscription->start_date = start_date;
}

/*
    Sets the end date of a subscription.

    Parameters:
        subscription: pointer to a valid subscription object.
        end_date: pointer to a valid datetime object.

    Pre-conditions:
        subscription and end_date must not be NULL.

    Post-conditions:
        The subscription's end date is updated.
*/
void set_subscription_end_date(subscription_ptr subscription, datetime_ptr end_date) {
    CHECK_NULL(subscription);
    CHECK_NULL(end_date);
    subscription->end_date = end_date;
}

/*
    Updates both start and end dates of the subscription.

    Parameters:
        subscription: pointer to a valid subscription object.
        start_date: pointer to the new start date.
        end_date: pointer to the new end date.

    Pre-conditions:
        All parameters must be non-NULL.

    Post-conditions:
        The subscription's start and end dates are updated.
*/
void set_subscription_renew(subscription_ptr subscription, datetime_ptr start_date, datetime_ptr end_date) {
    set_subscription_start_date(subscription, start_date);
    set_subscription_end_date(subscription, end_date);
}

/*
    Prints the subscription's start and end dates.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        Information is printed to stdout.
*/
void print_subscription(subscription_ptr subscription) {
    CHECK_NULL(subscription);

    printf("Start Date: ");
    print_datetime(stdout, subscription->start_date);
    printf("\n");

    printf("End Date: ");
    print_datetime(stdout, subscription->end_date);
    printf("\n");
}

/*
    Frees the memory allocated for a subscription, including its datetime objects.

    Parameters:
        subscription: pointer to the subscription to free.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        Memory for the subscription and its datetime fields is deallocated.
*/
void delete_subscription(subscription_ptr subscription) {
    CHECK_NULL(subscription);

    free(subscription->start_date);
    free(subscription->end_date);
    free(subscription);
}