#include "course.h"

#include "stdlib.h"
#include "string.h"

struct course {
    uint16_t id;
    const char* name;
    const char* date;
    const char* time;
    uint16_t seats_total;
    uint16_t seats_booked;
};

course_ptr create_course(
    uint16_t id, 
    const char* name, 
    const char* date, 
    const char* time, 
    uint16_t seats_total,
    uint16_t seats_booked
) {
    struct course* new_course = malloc(sizeof(struct course));
    new_course->id = id;
    new_course->name = strdup(name);
    new_course->date = strdup(date);
    new_course->time = strdup(time);
    new_course->seats_total = seats_total;
    new_course->seats_booked = seats_booked;

    return new_course;
}

uint16_t get_course_id(course_ptr course) {
    return course->id;
}
char* get_course_name(course_ptr course) {
    return course->name;
}
char* get_course_date(course_ptr course) {
    return course->date;
}
char* get_course_time(course_ptr course) {
    return course->time;
}
uint16_t get_course_seats_total(course_ptr course) {
    return course->seats_total;
}

uint16_t get_course_seats_booked(course_ptr course) {
    return course->seats_booked;
}

void print_course(course_ptr course) {
    printf("Course ID: %u\n", course->id);
    printf("Name     : %s\n", course->name);
    printf("Date     : %s\n", course->date);
    printf("Time     : %s\n", course->time);
    printf("Seats    : %u total, %u booked\n", course->seats_total, course->seats_booked);
}

void delete_course(course_ptr course) {
    free(course->name);
    free(course->date);
    free(course->time);
    free(course);
}

