#ifndef USER_H
#define USER_H

#include "subscription.h"
#include <stdio.h>
#include <stdint.h>

typedef struct user *user_ptr;

user_ptr create_user(
    uint16_t id,
    char* CF,
    char* first_name,
    char* last_name,
    char* password,
    subscription_ptr subscription    
);

uint16_t get_user_id(user_ptr user);
const char* get_user_CF(user_ptr user);
const char* get_user_first_name(user_ptr user);
const char* get_user_last_name(user_ptr user);
const char* get_user_password(user_ptr user);
subscription_ptr get_user_subscription(user_ptr user);

void print_user(user_ptr user);
void save_user_to_file(user_ptr user, FILE* f);
user_ptr load_user_from_file(FILE* f);
void delete_user(user_ptr user);

#endif