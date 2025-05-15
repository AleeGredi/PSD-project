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

uint16_t get_subscription_id(subscription_ptr subscription) {
    return subscription->id;
}

const datetime_ptr get_subscription_start_date(subscription_ptr subscription) {
    return subscription->start_date;
}

const datetime_ptr get_subscription_end_date(subscription_ptr subscription) {
    return subscription->end_date;
}

void print_subscription(subscription_ptr subscription) {
    printf("Subscription ID: %u\n", subscription->id);
    printf("Start Date: %s\n", subscription->start_date);
    printf("End Date: %s\n", subscription->end_date);
}

void delete_subscription(subscription_ptr subscription) {
    free(subscription->start_date);
    free(subscription->end_date);
    free(subscription);
}