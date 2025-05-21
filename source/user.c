#include "user.h"
#include "subscription.h"
#include "utils.h"

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

    new_user->username = malloc(strlen(username) + 1);
    CHECK_NULL(new_user->username);
    strcpy(new_user->username, username);

    new_user->password = malloc(strlen(password) + 1);
    CHECK_NULL(new_user->password);
    strcpy(new_user->password, password);

    new_user->subscription = subscription;

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
    Saves user data to a file in CSV format.

    Parameters:
        user: pointer to the user object.
        f: pointer to an open file for writing.

    Pre-conditions:
        user and f must not be NULL.
        File must be open in write or append mode.

    Post-conditions:
        User data is written to the file in CSV format.

    Returns:
        None.
*/
void save_user_to_file(user_ptr user, FILE* f) {
    fprintf(f, "%u,%s,%s,%s,%s,%s,%u,\n",
        user->id,
        user->CF,
        user->first_name,
        user->last_name,
        user->username,
        user->password,
        get_subscription_id(user->subscription)
    );
    print_datetime(get_subscription_start_date(user->subscription));
    print_datetime(get_subscription_end_date(user->subscription));
}

/*
    Loads a user from a file containing CSV-formatted data.

    Parameters:
        f: pointer to an open file for reading.

    Pre-conditions:
        f must not be NULL.
        File must contain a valid line of user data.

    Post-conditions:
        A new user object is created and returned.

    Returns:
        user_ptr: pointer to the loaded user object, or NULL on error.

user_ptr load_user_from_file(FILE* f) {
    if (!f) return NULL;

    char line[512];
    if (!fgets(line, sizeof(line), f)) return NULL;

    uint16_t id, sub_id;
    char CF[50], first_name[50], last_name[50], username[50], password[50];
    char start_date[11], end_date[11];

    int parsed = sscanf(
        line,
        "%hu,%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%hu,%10[^,],%10[^,\n]",
        &id,
        CF,
        first_name,
        last_name,
        username,
        password,
        &sub_id,
        start_date,
        end_date
    );

    if (parsed != 9) {
        fprintf(stderr, "Errore nel parsing della riga utente.\n");
        return NULL;
    }

    subscription_ptr sub = create_subscription(sub_id, start_date, end_date);
    if (!sub) return NULL;

    return create_user(id, CF, first_name, last_name, username, password, sub);
}
*/
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