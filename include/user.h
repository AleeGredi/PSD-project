#ifndef USER_H
#define USER_H

#include "subscription.h"
#include "array.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdint.h>

typedef struct user *user_ptr;

/*
    Creates a new user object with the specified parameters.

    Parameters:
        id: unique identifier for the user.
        CF: codice fiscale (tax code), null-terminated string.
        first_name: user's first name, null-terminated string.
        last_name: user's last name, null-terminated string.
        username: user's login username, null-terminated string.
        password: user's login password, null-terminated string.
        subscription: pointer to a valid subscription object.

    Pre-conditions:
        All strings must be valid (not NULL).
        subscription must not be NULL.

    Post-conditions:
        A new user object is allocated and initialized.

    Returns:
        user_ptr: pointer to the newly created user.
*/
user_ptr create_user(
    char* CF,
    char* first_name,
    char* last_name,
    char* username,
    char* password,
    subscription_ptr subscription,
    datetime_ptr last_report_date
);

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
char* get_user_CF(user_ptr user);

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
char* get_user_first_name(user_ptr user);

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
char* get_user_last_name(user_ptr user);

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
char* get_user_username(user_ptr user);

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
char* get_user_password(user_ptr user);

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
subscription_ptr get_user_subscription(user_ptr user);

/*
    Returns the last_report_date associated with the user.

    Parameters:
        user: pointer to a valid user object.

    Pre-conditions:
        user must not be NULL.

    Returns:
        datetime_ptr: pointer to the user's last_report_date.
*/
datetime_ptr get_user_last_report_date(user_ptr user);

/*
    Sets the user's last report date.

    Parameters:
        user: pointer to the user object.
        last_report: pointer to the new datetime.

    Pre-conditions:
        Both user and last_report must not be NULL.

    Post-conditions:
        The previous datetime is freed and replaced by the new one.
*/
void set_user_last_report_date(user_ptr user, datetime_ptr last_report);

/*
    Prints user information to standard output.

    Parameters:
        user: pointer to the user object.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        User information is printed to stdout.
*/
void print_user(user_ptr user);

/*
    Frees all memory associated with the user.

    Parameters:
        user: pointer to the user object to delete.

    Pre-conditions:
        user must not be NULL.

    Post-conditions:
        All allocated memory for the user and its fields is released.
*/
void delete_user(user_ptr user);

#endif