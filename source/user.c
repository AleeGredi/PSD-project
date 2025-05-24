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

bool compare_course_id(void* a, void* b) {
    course_ptr course_a = (course_ptr)a;
    course_ptr course_b = (course_ptr)b;
    return get_course_id(course_a) == get_course_id(course_b);
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