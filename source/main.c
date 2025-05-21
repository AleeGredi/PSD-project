#include <stdio.h>
#include <stdlib.h>
#include <array.h>
#include <hash_map.h>
#include <course.h>
#include <utils.h>

#define LINE_READ_BUFFER 1024
#define USERS_PATH "assets/users/"
#define COURSE_FILENAME "assets/courses.txt"

void load_courses(const char *filename, array_ptr* array, hash_map_ptr* hash_map);
void loading(array_ptr* array, hash_map_ptr* hash_map);

void print_courses(void* element) {
    course_ptr course = (course_ptr)element;
    print_course(course);
}

int main(void) {
    hash_map_ptr hash_map;
    array_ptr array;
    loading(&array, &hash_map);
    print_array(array, print_courses);
    
    
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

    *array = create_array(num_of_courses);
    *hash_map = new_hash_map(num_of_courses);

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
        add_element(*array, course);
        // add course to hash map
        insert_course(*hash_map, get_course_id(course), course);
    }

    fclose(fp);
}


void loading(array_ptr* array, hash_map_ptr* hash_map) {
    // load course;
    load_courses(COURSE_FILENAME, array, hash_map);
}