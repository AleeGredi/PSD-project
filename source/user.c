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

void save_user_to_file(user_ptr user, FILE* f) {
    fprintf(f, "%u,%s,%s,%s,%s,%u,%s,%s\n",
        user->id,
        user->CF,
        user->first_name,
        user->last_name,
        user->password,
        get_subscription_id(user->subscription),
        get_subscription_start_date(user->subscription),
        get_subscription_end_date(user->subscription)
    );
}

user_ptr load_user_from_file(FILE* f) {
    if (!f) return NULL;

    char line[512];
    if (!fgets(line, sizeof(line), f)) return NULL;

    uint16_t id, sub_id;
    char CF[50], first_name[50], last_name[50], password[50];
    char start_date[11], end_date[11];

    int parsed = sscanf(
        line,
        "%hu,%49[^,],%49[^,],%49[^,],%49[^,],%hu,%10[^,],%10[^,\n]",
        &id,
        CF,
        first_name,
        last_name,
        password,
        &sub_id,
        start_date,
        end_date
    );

    if (parsed != 8) {
        fprintf(stderr, "Errore nel parsing della riga utente.\n");
        return NULL;
    }

    subscription_ptr sub = create_subscription(sub_id, start_date, end_date);
    if (!sub) return NULL;

    return create_user(id, CF, first_name, last_name, password, sub);
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