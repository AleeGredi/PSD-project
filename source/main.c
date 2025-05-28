#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_functions.h"

int main(void){
    hash_map_ptr hash_map;
    array_ptr array;
    user_ptr user = NULL;
    linked_list_ptr booked_list = NULL;
    linked_list_ptr history_list = NULL;

    int action = 0;
    printf("Select action:\n");
    printf("1. Register new user\n");
    printf("2. Login\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &action) != 1) {
        fprintf(stderr, "Invalid input. Exiting.\n");
        return 1;
    }
    getchar(); // consume newline

    if (action == 1) {
        registration_user();
        // After registration, proceed to login
    }

    char *username = NULL;
    while (!username) {
        username = login_user();
        if (!username) {
            printf("Login failed. Try again.\n");
        }
    }

    // Load courses and logged user data
    load_courses(COURSE_PATH, &array, &hash_map);

    char user_filepath[192] = {0};
    snprintf(user_filepath, sizeof(user_filepath), "%s%s.txt", USERS_PATH, username);
    user = load_user(user_filepath, &booked_list, &history_list, &hash_map);
    free(username);

    int choice;
    do {
        printf("\n====== MENU ======\n");
        printf("1. Print all available courses\n");
        printf("2. Show my booked courses\n");
        printf("3. Show course history\n");
        printf("4. Book a course\n");
        printf("5. Cancel a booked course\n");
        printf("6. Check if subscription is valid\n");
        printf("7. Show last report\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
        case 1: action_print_all_courses(array);       break;
        case 2: action_show_booked_courses(booked_list);  break;
        case 3: action_show_history(history_list);    break;
        case 4:
            uint16_t course_id;
            printf("Enter course ID to book: ");
            if (scanf("%hu", &course_id) != 1) { getchar(); exit(1); }
            getchar(); 

            action_book_course(course_id, booked_list, history_list, hash_map, user); break;
        case 5: action_cancel_course(booked_list, history_list); break;
        case 6: action_check_subscription(user);      break;
        case 7: action_show_last_report(user);        break;
        case 0: action_exit_and_save(hash_map, array, booked_list, history_list, user); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0); 
    return 0;
}
   