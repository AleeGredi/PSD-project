#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <stdint.h>

typedef struct subscription *subscription_ptr;

subscription_ptr create_subscription(
    uint16_t id,
    char* start_date,
    char* end_date
);

uint16_t get_subscription_id(subscription_ptr subscription);
const char* get_subscription_start_date(subscription_ptr subscription);
const char* get_subscription_end_date(subscription_ptr subscription);

void print_subscription(subscription_ptr subscription);

void delete_subscription(subscription_ptr subscription);

#endif