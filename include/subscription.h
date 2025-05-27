#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "datetime.h"
#include <stdint.h>

typedef struct subscription *subscription_ptr;

/*
    Creates a new subscription with a start and end date.

    Parameters:
        start_date: pointer to a datetime representing the start of the subscription.
        end_date: pointer to a datetime representing the end of the subscription.

    Pre-conditions:
        start_date and end_date must be non-NULL.
        The datetime values must be valid and managed externally.

    Post-conditions:
        A new subscription object is allocated and initialized.

    Returns:
        subscription_ptr: pointer to the newly created subscription.
*/
subscription_ptr create_subscription(
    datetime_ptr start_date,
    datetime_ptr end_date
);

/*
    Retrieves the start date of the subscription.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        None.

    Returns:
        datetime_ptr: pointer to the start date.
*/
datetime_ptr get_subscription_start_date(subscription_ptr subscription);

/*
    Retrieves the end date of the subscription.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        None.

    Returns:
        datetime_ptr: pointer to the end date.
*/
datetime_ptr get_subscription_end_date(subscription_ptr subscription);

/*
    Sets a new start date for the subscription.

    Parameters:
        subscription: pointer to a valid subscription object.
        start_date: pointer to a valid datetime object.

    Pre-conditions:
        Both pointers must not be NULL.

    Post-conditions:
        The subscription's start date is updated.
*/
void set_subscription_start_date(subscription_ptr subscription, datetime_ptr start_date);

/*
    Sets a new end date for the subscription.

    Parameters:
        subscription: pointer to a valid subscription object.
        end_date: pointer to a valid datetime object.

    Pre-conditions:
        Both pointers must not be NULL.

    Post-conditions:
        The subscription's end date is updated.
*/
void set_subscription_end_date(subscription_ptr subscription, datetime_ptr end_date);

/*
    Renews a subscription by setting both start and end dates.

    Parameters:
        subscription: pointer to a valid subscription object.
        start_date: pointer to the new start date.
        end_date: pointer to the new end date.

    Pre-conditions:
        All pointers must not be NULL.

    Post-conditions:
        Both start and end dates are updated in the subscription.
*/
void set_subscription_renew(subscription_ptr subscription, datetime_ptr start_date, datetime_ptr end_date);

/*
    Prints the subscription's start and end dates.

    Parameters:
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        Information is printed to stdout.
*/
void print_subscription(subscription_ptr subscription);

/*
    Deletes a subscription and frees its memory (including datetime fields).

    Parameters:
        subscription: pointer to the subscription to delete.

    Pre-conditions:
        subscription must not be NULL.

    Post-conditions:
        The subscription and its datetime fields are deallocated.
*/
void delete_subscription(subscription_ptr subscription);

#endif