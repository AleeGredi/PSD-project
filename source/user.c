#include "user.h"
#include "subscription.h"
#include "utils.h"
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    uint16_t id;
    char* CF;
    char* first_name;
    char* last_name;
    char* username;
    char* password;
    subscription_ptr subscription;
    datetime_ptr last_report_date;
};



struct frequentation {
    uint16_t course_id;
    char *course_name;
    uint16_t times_booked;
};

frequentation_ptr create_frequentation(uint16_t course_id, char *course_name, uint16_t times_booked){
    struct frequentation* new_frequentation = malloc(sizeof(struct frequentation));

    new_frequentation->course_id = course_id;

    new_frequentation->course_name = malloc(strlen(course_name) + 1);
    CHECK_NULL(new_frequentation->course_name);
    strcpy(new_frequentation->course_name, course_name);

    new_frequentation->times_booked = times_booked;

    return new_frequentation;
}

void print_frequentation_callback(FILE* file, void* element) {
    frequentation_ptr entry = (frequentation_ptr)element;
    printf("History Entry - ID: %hu, Name: %s, Times Booked: %hu\n",
           entry->course_id, entry->course_name, entry->times_booked);
}

uint16_t get_frequentation_id(frequentation_ptr frequentation) {
    return frequentation->course_id;
}

char* get_frequentation_name(frequentation_ptr frequentation) {
    return frequentation->course_name;
}

uint16_t get_frequentation_times_booked(frequentation_ptr frequentation) {
    return frequentation->times_booked;
}

void set_frequentation_times_booked(frequentation_ptr frequentation, int value) {
    frequentation->times_booked = value;
}

/*
    Allocates and initializes a new user object by allocating its strings
    and setting its fields.

    Parameters:
        id: unique user identifier.
        CF: user's codice fiscale (null-terminated string).
        first_name: user's first name (null-terminated string).
        last_name: user's last name (null-terminated string).
        username: user's login username (null-terminated string).
        password: user's login password (null-terminated string).
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        All string parameters and subscription must not be NULL.

    Post-conditions:
        Returns a pointer to a newly allocated user object with deep copies of the strings.

    Returns:
        user_ptr: pointer to the initialized user object.
*/
user_ptr create_user(
    uint16_t id,
    char* CF,
    char* first_name,
    char* last_name,
    char* username,
    char* password,
    subscription_ptr subscription,
    datetime_ptr last_report_date
){
    struct user* new_user = malloc(sizeof(struct user));
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

    new_user->username = malloc(strlen(username) + 1);
    CHECK_NULL(new_user->username);
    strcpy(new_user->username, username);

    new_user->password = malloc(strlen(password) + 1);
    CHECK_NULL(new_user->password);
    strcpy(new_user->password, password);

    new_user->subscription = subscription;
    new_user->last_report_date = last_report_date;

    return new_user;
}

/*
    Returns the ID of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        uint16_t: user ID.
*/
uint16_t get_user_id(user_ptr user) {
    return user->id;
}

/*
    Returns the codice fiscale of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        const char*: pointer to the user's CF string.
*/
const char* get_user_CF(user_ptr user) {
    return user->CF;
}

/*
    Returns the first name of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        const char*: pointer to the user's first name.
*/
const char* get_user_first_name(user_ptr user) {
    return user->first_name;
}

/*
    Returns the last name of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        const char*: pointer to the user's last name.
*/
const char* get_user_last_name(user_ptr user) {
    return user->last_name;
}

/*
    Returns the username of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        const char*: pointer to the user's username.
*/
const char* get_user_username(user_ptr user) {
    return user->username;
}

/*
    Returns the password of the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        const char*: pointer to the user's password.
*/
const char* get_user_password(user_ptr user) {
    return user->password;
}

/*
    Returns the subscription associated with the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        subscription_ptr: pointer to the user's subscription.
*/
subscription_ptr get_user_subscription(user_ptr user) {
    return user->subscription;
}

/*
    Returns the last_report_date associated with the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        datetime_ptr: pointer to the user's last_report_date.
*/
datetime_ptr get_user_last_report_date(user_ptr user) {
    return user->last_report_date;
}

/*
    Prints detailed user information to standard output.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        None.
*/
void print_user(user_ptr user) {
    printf("User ID     : %u\n", user->id);
    printf("CF          : %s\n", user->CF);
    printf("First Name  : %s\n", user->first_name);
    printf("Last Name   : %s\n", user->last_name);
    printf("Username    : %s\n", user->username);
    printf("Password    : %s\n", user->password);
    printf("Subscription:\n");
    print_subscription(user->subscription);
}

/*
    Frees all memory associated with a user object.

    Parameters:
        user: pointer to the user object to delete.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        All memory allocated for the user and its fields is released.

    Returns:
        None.
*/
void delete_user(user_ptr user) {
    free(user->CF);
    free(user->first_name);
    free(user->last_name);
    free(user->username);
    free(user->password);

    delete_subscription(user->subscription);
    free(user);
}