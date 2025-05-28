#include "user.h"
#include "subscription.h"
#include "utils.h"
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char* CF;
    char* first_name;
    char* last_name;
    char* username;
    char* password;
    subscription_ptr subscription;
    datetime_ptr last_report_date;
};

/*
    Allocates and initializes a new user object with deep-copied strings.

    Parameters:
        CF: user's codice fiscale (null-terminated string).
        first_name: user's first name.
        last_name: user's last name.
        username: user's login username.
        password: user's login password.
        subscription: pointer to an existing subscription object.
        last_report_date: pointer to a datetime object.

    Pre-conditions:
        All string parameters and pointers must not be NULL.

    Post-conditions:
        A new user is returned with duplicated strings; subscription and last_report_date are referenced.

    Returns:
        Pointer to the newly created user object.
*/
user_ptr create_user(
    char* CF,
    char* first_name,
    char* last_name,
    char* username,
    char* password,
    subscription_ptr subscription,
    datetime_ptr last_report_date
){
    CHECK_NULL(CF);
    CHECK_NULL(first_name);
    CHECK_NULL(last_name);
    CHECK_NULL(username);
    CHECK_NULL(password);
    CHECK_NULL(subscription);
    CHECK_NULL(last_report_date);

    user_ptr new_user = malloc(sizeof(struct user));
    CHECK_NULL(new_user);

    new_user->CF = str_dup(CF);
    CHECK_NULL(new_user->CF);

    new_user->first_name = str_dup(first_name);
    CHECK_NULL(new_user->first_name);

    new_user->last_name = str_dup(last_name);
    CHECK_NULL(new_user->last_name);

    new_user->username = str_dup(username);
    CHECK_NULL(new_user->username);

    new_user->password = str_dup(password);
    CHECK_NULL(new_user->password);

    new_user->subscription = subscription;
    new_user->last_report_date = last_report_date;

    return new_user;
}

/*
    Returns the user's codice fiscale (CF).

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        char*: pointer to the CF string.
*/
char* get_user_CF(user_ptr user) {
    CHECK_NULL(user);
    return user->CF;
}

/*
    Returns the user's first name.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        char*: pointer to the first name string.
*/
char* get_user_first_name(user_ptr user) {
    CHECK_NULL(user);
    return user->first_name;
}

/*
    Returns the user's last name.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        char*: pointer to the last name string.
*/
char* get_user_last_name(user_ptr user) {
    CHECK_NULL(user);
    return user->last_name;
}

/*
    Returns the user's username.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        char*: pointer to the username string.
*/
char* get_user_username(user_ptr user) {
    CHECK_NULL(user);
    return user->username;
}

/*
    Returns the user's password.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        char*: pointer to the password string.
*/
char* get_user_password(user_ptr user) {
    CHECK_NULL(user);
    return user->password;
}

/*
    Returns the user's subscription.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        None.

    Returns:
        subscription_ptr: pointer to the user's subscription.
*/
subscription_ptr get_user_subscription(user_ptr user) {
    CHECK_NULL(user);
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
    CHECK_NULL(user);
    return user->last_report_date;
}

/*
    Updates the user's last report date, replacing the previous datetime.

    Parameters:
        user: pointer to a valid user object.
        last_report: new datetime to assign.

    Pre-conditions:
        user and last_report must not be NULL.

    Post-conditions:
        Replaces the old datetime (freed) with the new one.
*/
void set_user_last_report_date(user_ptr user, datetime_ptr last_report) {
    CHECK_NULL(user);
    CHECK_NULL(last_report);

    if (user->last_report_date != last_report) {
        free(user->last_report_date);
    }
    user->last_report_date = last_report;
}

/*
    Prints all user information.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        Outputs user data to stdout.
*/
void print_user(user_ptr user) {
    CHECK_NULL(user);
    printf("CF          : %s\n", user->CF);
    printf("First Name  : %s\n", user->first_name);
    printf("Last Name   : %s\n", user->last_name);
    printf("Username    : %s\n", user->username);
    printf("Password    : %s\n", user->password);
    printf("Subscription:\n");
    print_subscription(user->subscription);
    printf("Last Report : ");
    print_datetime(stdout, user->last_report_date);
    printf("\n");
}

/*
    Frees all memory associated with the user.

    Parameters:
        user: pointer to the user to delete.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        All associated memory is freed.
*/
void delete_user(user_ptr user) {
    CHECK_NULL(user);

    free(user->CF);
    free(user->first_name);
    free(user->last_name);
    free(user->username);
    free(user->password);

    delete_subscription(user->subscription);
    delete_datetime(user->last_report_date);
    free(user);
}