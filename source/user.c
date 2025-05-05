#include "user.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    uint16_t id;
    char* CF;
    char* first_name;
    char* last_name;
    char* password;
    subscription_ptr subscription;
};

user_ptr create_user(
    uint16_t id,
    char* CF,
    char* first_name,
    char* last_name,
    char* password,
    subscription_ptr subscription    
){
    user_ptr new_user = malloc(sizeof(struct user));
    CHECK_NULL(new_user);
    new_user->id = id;

    new_user->CF = malloc(strlen(CF) + 1);
    CHECK_NULL(new_user->CF);
    strcpy(new_user->CF, CF);

    new_user->first_name = malloc(strlen(first_name) + 1);
    CHECK_NULL(new_user->first_name);
    strcpy(new_user->first_name, first_name);

    new_user->last_name = malloc(strlen(last_name) + 1);
    CHECK_NULL(new_user->last_name);
    strcpy(new_user->last_name, last_name);

    new_user->password = malloc(strlen(password) + 1);
    CHECK_NULL(new_user->password);
    strcpy(new_user->password, password);

    new_user->subscription = subscription;

    return new_user;
}

uint16_t get_user_id(user_ptr user) {
    return user->id;
}

const char* get_user_CF(user_ptr user) {
    return user->CF;
}

const char* get_user_first_name(user_ptr user) {
    return user->first_name;
}

const char* get_user_last_name(user_ptr user) {
    return user->last_name;
}

const char* get_user_password(user_ptr user) {
    return user->password;
}

subscription_ptr get_user_subscription(user_ptr user) {
    return user->subscription;
}

void print_user(user_ptr user) {
    printf("User ID     : %u\n", user->id);
    printf("CF          : %s\n", user->CF);
    printf("First Name  : %s\n", user->first_name);
    printf("Last Name   : %s\n", user->last_name);
    printf("Password    : %s\n", user->password);
    printf("Subscription:\n");
    print_subscription(user->subscription);
}

void delete_user(user_ptr user) {
    free(user->CF);
    free(user->first_name);
    free(user->last_name);
    free(user->password);

    delete_subscription(user->subscription);
    free(user);
}