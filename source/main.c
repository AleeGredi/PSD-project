#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <linked_list.h>
#include <hash_map.h>
#include <course.h>
#include <user.h>
#include <utils.h>

#define LINE_READ_BUFFER 1024
#define USERS_PATH "assets/users/"
#define COURSE_FILENAME "assets/courses.txt"

void load_courses(const char *filename, array_ptr* array, hash_map_ptr* hash_map);
user_ptr load_user(const char *filename, linked_list_ptr* booked_list, linked_list_ptr* history_list, hash_map_ptr* hash_map);
void print_courses(void* element);

void print_course_callback(void* element) {
    uint16_t* course_id = (uint16_t*)element;
    printf("Course ID: %hu\n", *course_id);
}

int main(void) {
    hash_map_ptr hash_map;
    array_ptr array;
    user_ptr user;
    linked_list_ptr booked_list;
    linked_list_ptr history_list;
    
    // Load courses and logged user
    load_courses(COURSE_FILENAME, &array, &hash_map);
    user = load_user("assets/users/marior.txt", &booked_list, &history_list, &hash_map);

    array_print(array, print_courses);
    print_user(user);

    printf("\n--- Booked Courses ---\n");
    ll_print(booked_list, print_course_callback);

    printf("\n--- Course History ---\n");
    ll_print(history_list, print_frequentation_callback);
    
    return 0;
}



void load_courses(const char *filename, array_ptr* array, hash_map_ptr* hash_map) {
    FILE *fp = fopen(filename, "r");
    CHECK_NULL(fp);

    // Read number of courses
    uint16_t num_of_courses;
    if (fscanf(fp, "%hu\n", &num_of_courses) != 1) {
        fprintf(stderr, "Failed to read course count\n");
        fclose(fp);
        exit(1);
    }

    *array = array_create(num_of_courses);
    *hash_map = create_hash_map(num_of_courses);

    char line[LINE_READ_BUFFER];

    for (uint16_t i = 0; i < num_of_courses; i++) {
        if (!fgets(line, sizeof line, fp)) {
            fprintf(stderr, "Unexpected EOF at line %u\n", i + 2);
            break;
        }

        // Split CSV: id,name,HH:MM DD/MM/YY,seats_total,seats_booked
        char *p          = line;
        char *id_str     = str_sep(&p, ",");
        char *name_str   = str_sep(&p, ",");
        char *dt_str     = str_sep(&p, ",");
        char *total_str  = str_sep(&p, ",");
        char *booked_str = str_sep(&p, ",;\n");

        // convert fields
        uint16_t id           = (uint16_t)atoi(id_str);
        uint16_t seats_total  = (uint16_t)atoi(total_str);
        uint16_t seats_booked = (uint16_t)atoi(booked_str);

        datetime_ptr datetime;
        // Parse datetime "HH:MM DD/MM/YYYY"
        int hh, mm, dd, mo, yyyy;
        if (sscanf(dt_str, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy) == 5) {
            datetime = create_datetime(mm, hh, dd, mo, yyyy);
        } else {
            fprintf(stderr, "Bad datetime format on line: %u\n", i + 2);
            exit(1);
        }

        // Allocate course
        course_ptr course = create_course(
            id, 
            str_dup(name_str), 
            datetime, 
            seats_total, 
            seats_booked
        );
        // add course to array (already sorted in file);
        array_add(*array, course);
        // add course to hash map
        insert_course(*hash_map, get_course_id(course), course);
    }

    fclose(fp);
}

user_ptr load_user(const char *filename, linked_list_ptr* booked_list, linked_list_ptr* history_list, hash_map_ptr* hash_map) {
    FILE *fp = fopen(filename, "r");
    CHECK_NULL(fp);

    char line[LINE_READ_BUFFER];

    // 1) Read last report date
    if (!fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Failed to read report date\n");
        fclose(fp);
        exit(1);
    }
    int hh, mm, dd, mo, yyyy;
    if (sscanf(line, "%2d:%2d %2d/%2d/%4d",
               &hh, &mm, &dd, &mo, &yyyy) != 5) {
        fprintf(stderr, "Invalid datetime format\n");
        fclose(fp);
        exit(1);
    }
    datetime_ptr last_report_date = create_datetime(mm, hh, dd, mo, yyyy);

    // 2) Read user data
    if (!fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Failed to read user data\n");
        fclose(fp);
        exit(1);
    }
    char *p = line;
    char *id_str         = str_sep(&p, ",");
    char *cf_str         = str_sep(&p, ",");
    char *first_name_str = str_sep(&p, ",");
    char *last_name_str  = str_sep(&p, ",");
    char *username_str   = str_sep(&p, ",");
    char *password_str   = str_sep(&p, ",");
    char *sub_start      = str_sep(&p, ",");
    char *sub_end        = str_sep(&p, ",;\n");

    uint16_t id = (uint16_t)atoi(id_str);
    int sdd, smo, syyyy, edd, emo, eyyyy;
    sscanf(sub_start, "%2d/%2d/%4d", &sdd, &smo, &syyyy);
    sscanf(sub_end,   "%2d/%2d/%4d", &edd, &emo, &eyyyy);
    datetime_ptr sub_start_date = create_datetime(0, 0, sdd, smo, syyyy);
    datetime_ptr sub_end_date   = create_datetime(0, 0, edd, emo, eyyyy);

    subscription_ptr subscription = create_subscription(id, sub_start_date, sub_end_date);

    // inizializza le liste
    *booked_list  = ll_create();
    *history_list = ll_create();

    user_ptr user = create_user(
        id,
        str_dup(cf_str),
        str_dup(first_name_str),
        str_dup(last_name_str),
        str_dup(username_str),
        str_dup(password_str),
        subscription,
        last_report_date
    );

    // 3) Read booked course IDs
    if (!fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Failed to read booked courses\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p) {
        char *course_id = str_sep(&p, ",;\n");
        course_ptr course_reference = get_course(*hash_map, (uint16_t)atoi(course_id));

        if (course_reference) {
            ll_add(*booked_list, course_reference);
        }
    }

    // 4) Read history as flat CSV: every 3 elementi -> (id, name, times)
    if (!fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Failed to read history\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p) {
        char *id_hist = str_sep(&p, ",");
        if (!id_hist || !*id_hist) exit(1);
        uint16_t course_id = (uint16_t)atoi(id_hist);

        char *name_hist = str_sep(&p, ",");
        if (!name_hist) exit(1);

        // leggo times
        char *times_hist = str_sep(&p, ",;\n");
        if (!times_hist) exit(1);
        uint16_t times_booked = (uint16_t)atoi(times_hist);

        frequentation_ptr frequentation = create_frequentation(course_id, str_dup(name_hist), times_booked);

        ll_add(*history_list, frequentation);
    }

    fclose(fp);
    return user;
}

void print_courses(void* element) {
    course_ptr course = (course_ptr)element;
    print_course(course);
}