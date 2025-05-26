#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "linked_list.h"
#include "hash_map.h"
#include "frequentation.h"
#include "course.h"
#include "user.h"
#include "utils.h"

#define LINE_READ_BUFFER 1024
#define MAX_INPUT_USER 128
#define USERS_PATH "assets/users/"
#define COURSE_PATH "assets/courses.txt"
#define REPORT_PATH "assets/report/"

char *login_user();
void load_courses(const char *filepath, array_ptr *array, hash_map_ptr *hash_map);
user_ptr load_user(const char *filepath, linked_list_ptr *booked_list, linked_list_ptr *history_list, hash_map_ptr *hash_map);
void save_user(linked_list_ptr booked_list, linked_list_ptr history_list, user_ptr user);
void registration_user();
void save_course(array_ptr array);
void report(user_ptr user, linked_list_ptr frequentation_linked_list);

int main(void){
    hash_map_ptr hash_map;
    array_ptr array;
    user_ptr user;
    linked_list_ptr booked_list;
    linked_list_ptr history_list;

    registration_user();
    // Load courses and logged user
    load_courses(COURSE_PATH, &array, &hash_map);

    char *username = login_user();
    CHECK_NULL(username);
    char user_filepath[192] = {0};
    snprintf(user_filepath, sizeof(user_filepath), "%s%s.txt", USERS_PATH, username);
    user = load_user(user_filepath, &booked_list, &history_list, &hash_map);

    int choice;
    do {
        printf("\n====== MENU ======\n");
        printf("1. Print all available courses\n");
        printf("2. Show my booked courses\n");
        printf("3. Show course history\n");
        printf("4. Book a course\n");
        printf("5. Cancel a booked course\n");
        printf("6. Check if subscription is valid\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("\n--- Available Courses ---\n");
                array_print(array, stdout, print_course_callback);
                break;

            case 2:
                printf("\n--- Booked Courses ---\n");
                ll_print(booked_list, stdout, print_course_callback);
                break;

            case 3:
                printf("\n--- Course History ---\n");
                ll_print(history_list, stdout, print_frequentation_callback);
                break;

            case 4: {
                if (compare_datetime(get_datetime(), get_subscription_end_date(get_user_subscription(user))) == 1){
                    printf("Subscription has expired.\n");
                    break;
                }

                uint16_t course_id;
                printf("Enter course ID to book: ");
                scanf("%hu", &course_id);
                getchar();

                course_ptr course = get_course(hash_map, course_id);
                if (!course) {
                    printf("Course ID not found.\n");
                    break;
                }

                course_ptr temp = create_course(course_id, "", NULL, 0, 0);

                if (ll_search(booked_list, temp, compare_course_id) != -1) {
                    printf("You have already booked this course.\n");
                    delete_course(temp);
                    break;
                }
                delete_course(temp);

                if (get_course_seats_booked(course) >= get_course_seats_total(course)) {
                    printf("No available seats for this course.\n");
                    break;
                }

                ll_add(booked_list, course);
                set_course_seats_booked(course, get_course_seats_booked(course) + 1);

                int has_ever_been_booked = ll_search(history_list, course, compare_course_id);
                if (has_ever_been_booked == -1) {
                    frequentation_ptr new_frequentation = create_frequentation(get_course_id(course), get_course_name(course), 1);
                    ll_add(history_list, new_frequentation);
                } else {
                    frequentation_ptr temp_frequentation = ll_get_at(history_list, has_ever_been_booked);
                    set_frequentation_times_booked(temp_frequentation, get_frequentation_times_booked(temp_frequentation) + 1);
                }

                printf("Course booked successfully.\n");
                break;
            }

            case 5: {
                uint16_t course_id;
                printf("Enter course ID to cancel: ");
                scanf("%hu", &course_id);
                getchar();

                // 1) Search if the ID is in the history list (so if booked)
                int booked_idx = ll_search(booked_list, &course_id, compare_course_id);
                if (booked_idx == -1) {
                    printf("You have not booked this course.\n");
                    break;
                }

                // 2) Get pointer and decrements seats_booked
                course_ptr course = *(course_ptr*)ll_get_at(booked_list, booked_idx);
                ll_delete_at(booked_list, booked_idx, NULL);
                // Decremento i posti prenotati
                set_course_seats_booked(course,
                    get_course_seats_booked(course) - 1);

                // 3) Decrements frequentation times_booked
                int history_idx = ll_search(history_list, course, compare_course_id);
                if (history_idx != -1) {
                    frequentation_ptr freq = *(frequentation_ptr*)
                        ll_get_at(history_list, history_idx);
                    int new_times = get_frequentation_times_booked(freq) - 1;
                    set_frequentation_times_booked(freq, new_times);

                    // 4) remove freq if times_booked == 0 
                    if (new_times <= 0) {
                        ll_delete_at(history_list, history_idx, delete_frequentation);
                    }
                }

                printf("Course cancellation successful.\n");
                break;
            }

            case 6:
                if (compare_datetime(get_datetime(), get_subscription_end_date(get_user_subscription(user))) < 1) {
                    printf("Subscription is valid.\n");
                } else {
                    printf("Subscription has expired.\n");
                    char sub_renew;
                    printf("Do you want to renew it? (y or n): ");
                    scanf(" %c", &sub_renew);
                    getchar();

                    if (sub_renew == 'y' || sub_renew == 'Y') {
                        datetime_ptr now = get_datetime();
                        datetime_ptr start_renewal = now;
                        datetime_ptr end_renewal = create_datetime(
                            get_datetime_field(now, "minute"),
                            get_datetime_field(now, "hour"),
                            30,
                            get_datetime_field(now, "month"),
                            get_datetime_field(now, "year")
                        );
                        set_subscription_renew(get_user_subscription(user), start_renewal, end_renewal);
                        printf("Subscription renewed.\n");
                    } else {
                        printf("Subscription will not be renewed.\n");
                    }
                }
                break;

            case 0:
                save_user(booked_list, history_list, user);
                save_course(array);
                printf("Exiting program and saving courses\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

    } while (choice != 0);

    free(username);

    return 0;
}

char *login_user(){
    char *username = NULL, *line = NULL;
    size_t len = 0, line_len = 0;
    char password[MAX_INPUT_USER];
    char stored_password[MAX_INPUT_USER];

    printf("Enter username: ");
    if (getline(&username, &len, stdin) == -1){
        fprintf(stderr, "Failed to read username.\n");
        return NULL;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (!fgets(password, sizeof(password), stdin)){
        fprintf(stderr, "Failed to read password.\n");
        free(username);
        return NULL;
    }
    password[strcspn(password, "\n")] = '\0';

    char filepath[192] = {0};
    snprintf(filepath, sizeof(filepath), "assets/users/%s.txt", username);

    FILE *file = fopen(filepath, "r");
    if (!file){
        fprintf(stderr, "User '%s' not found.\n", username);
        free(username);
        return NULL;
    }

    getline(&line, &line_len, file);
    if (getline(&line, &line_len, file) == -1){
        fprintf(stderr, "Error reading user file.\n");
        fclose(file);
        free(username);
        free(line);
        return NULL;
    }

    int field = 0;
    char *token = strtok(line, ",");
    while (token && field++ < 4)
        token = strtok(NULL, ",");
    if (!token){
        fprintf(stderr, "Error in user file.\n");
        fclose(file);
        free(username);
        free(line);
        return NULL;
    }
    strncpy(stored_password, token, MAX_INPUT_USER - 1);
    stored_password[strcspn(stored_password, "\n")] = '\0';

    fclose(file);
    free(line);

    if (strcmp(password, stored_password) != 0){
        fprintf(stderr, "Incorrect password.\n");
        free(username);
        return NULL;
    }

    return username;
}

void load_courses(const char *filepath, array_ptr *array, hash_map_ptr *hash_map){
    FILE *fp = fopen(filepath, "r");
    CHECK_NULL(fp);

    // Read number of courses
    uint16_t num_of_courses;
    if (fscanf(fp, "%hu\n", &num_of_courses) != 1){
        fprintf(stderr, "Failed to read course count\n");
        fclose(fp);
        exit(1);
    }

    *array = array_create(num_of_courses);
    *hash_map = create_hash_map(num_of_courses);

    char line[LINE_READ_BUFFER];

    for (uint16_t i = 0; i < num_of_courses; i++){
        if (!fgets(line, sizeof line, fp)){
            fprintf(stderr, "Unexpected EOF at line %u\n", i + 2);
            break;
        }

        // Split CSV: id,name,HH:MM DD/MM/YY,seats_total,seats_booked
        char *p = line;
        char *id_str = str_sep(&p, ",");
        char *name_str = str_sep(&p, ",");
        char *dt_str = str_sep(&p, ",");
        char *total_str = str_sep(&p, ",");
        char *booked_str = str_sep(&p, ",;\n");

        // convert fields
        uint16_t id = (uint16_t)atoi(id_str);
        uint16_t seats_total = (uint16_t)atoi(total_str);
        uint16_t seats_booked = (uint16_t)atoi(booked_str);

        datetime_ptr datetime;
        // Parse datetime "HH:MM DD/MM/YYYY"
        int hh, mm, dd, mo, yyyy;
        if (sscanf(dt_str, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy) == 5){
            datetime = create_datetime(mm, hh, dd, mo, yyyy);
        }
        else{
            fprintf(stderr, "Bad datetime format on line: %u\n", i + 2);
            exit(1);
        }

        // Allocate course
        course_ptr course = create_course(
            id,
            str_dup(name_str),
            datetime,
            seats_total,
            seats_booked);
        // add course to array (already sorted in file);
        array_add(*array, course);
        // add course to hash map
        insert_course(*hash_map, get_course_id(course), course);
    }

    fclose(fp);
}

user_ptr load_user(const char *filepath, linked_list_ptr *booked_list, linked_list_ptr *history_list, hash_map_ptr *hash_map){
    FILE *fp = fopen(filepath, "r");
    CHECK_NULL(fp);

    char line[LINE_READ_BUFFER];

    // 1) Read last report date
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read report date\n");
        fclose(fp);
        exit(1);
    }
    int hh, mm, dd, mo, yyyy;
    if (sscanf(line, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy) != 5){
        fprintf(stderr, "Invalid datetime format\n");
        fclose(fp);
        exit(1);
    }
    datetime_ptr last_report_date = create_datetime(mm, hh, dd, mo, yyyy);

    // 2) Read user data
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read user data\n");
        fclose(fp);
        exit(1);
    }
    char *p = line;
    char *cf_str = str_sep(&p, ",");
    char *first_name_str = str_sep(&p, ",");
    char *last_name_str = str_sep(&p, ",");
    char *username_str = str_sep(&p, ",");
    char *password_str = str_sep(&p, ",");
    char *sub_start = str_sep(&p, ",");
    char *sub_end = str_sep(&p, ",;\n");

    sscanf(sub_start, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy);
    datetime_ptr sub_start_date = create_datetime(hh, mm, dd, mo, yyyy);
    sscanf(sub_end, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy);
    datetime_ptr sub_end_date = create_datetime(hh, mm, dd, mo, yyyy);

    subscription_ptr subscription = create_subscription(sub_start_date, sub_end_date);

    // inizializza le liste
    *booked_list = ll_create();
    *history_list = ll_create();

    user_ptr user = create_user(
        str_dup(cf_str),
        str_dup(first_name_str),
        str_dup(last_name_str),
        str_dup(username_str),
        str_dup(password_str),
        subscription,
        last_report_date);

    // 3) Read booked course IDs
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read booked courses\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p){
        char *course_id = str_sep(&p, ",;\n");
        course_ptr course_reference = get_course(*hash_map, (uint16_t)atoi(course_id));

        if (course_reference)
        {
            ll_add(*booked_list, course_reference);
        }
    }

    // 4) Read history as flat CSV: every 3 elementi -> (id, name, times)
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read history\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p){
        char *id_hist = str_sep(&p, ",");
        if (!id_hist || !*id_hist)
            exit(1);
        uint16_t course_id = (uint16_t)atoi(id_hist);

        char *name_hist = str_sep(&p, ",");
        if (!name_hist)
            exit(1);

        // leggo times
        char *times_hist = str_sep(&p, ",;\n");
        if (!times_hist)
            exit(1);
        uint16_t times_booked = (uint16_t)atoi(times_hist);

        frequentation_ptr frequentation = create_frequentation(course_id, str_dup(name_hist), times_booked);

        ll_add(*history_list, frequentation);
    }

    fclose(fp);
    return user;
}

void save_user(linked_list_ptr booked_list, linked_list_ptr history_list, user_ptr user){
    char filepath[192] = {0};
    snprintf(filepath, sizeof(filepath), "assets/users/%s.txt", get_user_username(user));
    FILE *file = fopen(filepath, "w");
    CHECK_NULL(file);

    // 1) Last report date
    print_datetime(file, get_user_last_report_date(user));
    fprintf(file, "\n");

    // 2) User data
    fprintf(file, "%s,%s,%s,%s,%s,",
        get_user_CF(user),
        get_user_first_name(user),
        get_user_last_name(user),
        get_user_username(user),
        get_user_password(user));
    print_datetime(file, get_subscription_start_date(get_user_subscription(user)));
    fprintf(file, ",");
    print_datetime(file, get_subscription_end_date(get_user_subscription(user)));
    fprintf(file, "\n");

    // 3) Booked courses (if the user is being created write 0,)
    if (ll_get_element_count(booked_list) == 0) {
        fprintf(file, "0,");
    } else {
        ll_print(booked_list, file, save_booking_callback);
    }
    fprintf(file, "\n");

    // 4) Booked history (if the user is being created write "0,,0,")
    if (ll_get_element_count(history_list) == 0) {
        fprintf(file, "0,"",0,");
    } else {
        ll_print(history_list, file, save_frequentation_callback);
    }

    fclose(file);
}

void save_course(array_ptr array){    
    FILE *file = fopen(COURSE_PATH, "w");
    CHECK_NULL(file);

    fprintf(file, "%d\n", get_size(array));

    array_print(array, file, print_course_file_callback);

    fclose(file);
}

void registration_user() {
    char cf[MAX_INPUT_USER];
    char first_name[MAX_INPUT_USER];
    char last_name[MAX_INPUT_USER];
    char username[MAX_INPUT_USER];
    char password[MAX_INPUT_USER];
    char filepath[192];
    FILE *file;

    printf("=== New User Registration ===\n");

    // Read CF
    printf("Enter CF: ");
    if (fgets(cf, sizeof(cf), stdin) == NULL) {
        fprintf(stderr, "Failed to read CF.\n");
        return;
    }
    cf[strcspn(cf, "\n")] = '\0';

    // Read first name
    printf("Enter first name: ");
    if (fgets(first_name, sizeof(first_name), stdin) == NULL) {
        fprintf(stderr, "Failed to read first name.\n");
        return;
    }
    first_name[strcspn(first_name, "\n")] = '\0';

    // Read last name
    printf("Enter last name: ");
    if (fgets(last_name, sizeof(last_name), stdin) == NULL) {
        fprintf(stderr, "Failed to read last name.\n");
        return;
    }
    last_name[strcspn(last_name, "\n")] = '\0';

    // Choose username
    printf("Choose a username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Failed to read username.\n");
        return;
    }
    username[strcspn(username, "\n")] = '\0';

    // Check if username already exists
    snprintf(filepath, sizeof(filepath), "%s%s.txt", USERS_PATH, username);
    file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        fprintf(stderr, "Error: Username '%s' already exists.\n", username);
        return;
    }

    // Read password
    printf("Choose a password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Failed to read password.\n");
        return;
    }
    password[strcspn(password, "\n")] = '\0';

    // Prepare subscription dates
    datetime_ptr now = get_datetime();
    datetime_ptr start = now;
    // Set subscription end date to day 30 of current month
        datetime_ptr end = create_datetime(
        get_datetime_field(now, "minute"),
        get_datetime_field(now, "hour"),
        30,
        get_datetime_field(now, "month"),
        get_datetime_field(now, "year")
    );
    subscription_ptr sub = create_subscription(start, end);

    // Create user struct
    user_ptr new_user = create_user(
        str_dup(cf),
        str_dup(first_name),
        str_dup(last_name),
        str_dup(username),
        str_dup(password),
        sub,
        now
    );

    // Initialize empty lists
    linked_list_ptr booked_list = ll_create();
    linked_list_ptr history_list = ll_create();

    // Save to file
    save_user(booked_list, history_list, new_user);

    printf("Registration successful. User '%s' created.\n", username);

    delete_user(new_user);
    ll_delete_list(booked_list, NULL);
    ll_delete_list(history_list, NULL);
}

void report(user_ptr user, linked_list_ptr frequentation_linked_list) {
    datetime_ptr last_report_datetime = get_user_last_report_date(user);
    datetime_ptr current_datetime = get_datetime();
    
    int flag_year = get_datetime_field(last_report_datetime, "year") 
        <= 
        get_datetime_field(current_datetime, "year");
    int flag_month = get_datetime_field(last_report_datetime, "month") 
        <
        get_datetime_field(current_datetime, "month");
    
    if (!flag_year || !flag_month) return;
    
    char filename[256] = {0};
    snprintf(filename, sizeof(filename), "%s%s_report.txt", REPORT_PATH, get_user_username(user));
    // create flag
    FILE* file = fopen(filename, "w");
    CHECK_NULL(file);

    int array_size = ll_get_element_count(frequentation_linked_list);
    array_ptr temp_array = array_create(array_size);
    ll_copy_list_to_array(frequentation_linked_list, temp_array);
    
    for (int i = 0; i < array_size - 1; i++) {
        // After each full pass, the largest element among the first (n-i) is at position n-i-1
        for (int j = 0; j < array_size - i - 1; j++) {
            frequentation_ptr element1 = (frequentation_ptr)get_at(temp_array, j);
            frequentation_ptr element2 = (frequentation_ptr)get_at(temp_array, j + 1);
            if (get_frequentation_times_booked(element1) > get_frequentation_times_booked(element2)) {
                ptr_swap(element1, element2);
            }
        }
    }
    // print datetime for this report
    print_datetime(file, current_datetime);

    int i = 0;
    frequentation_ptr* fr;
    fprintf(file, "Top tree courses followed:\n");
    while(i < array_size && i < 3) {
        fr = (frequentation_ptr*)get_at(temp_array, i);
        print_frequentation_callback(file, *fr);
        i++;
    }
    fprintf(file, "Other courses:");
    while(i < array_size) {
        fr = (frequentation_ptr*)get_at(temp_array, i);
        print_frequentation_callback(file, *fr);
        i++;
    }
    delete_datetime(current_datetime);
    // TODO: delete temp_array
    fclose(file);
}