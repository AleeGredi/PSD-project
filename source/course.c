#include "course.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course {
    uint16_t id;
    char* name;
    char* date;
    char* time;
    uint16_t seats_total;
    uint16_t seats_booked;
};

course_ptr create_course(
    uint16_t id, 
    char* name, 
    char* date, 
    char* time, 
    uint16_t seats_total,
    uint16_t seats_booked
) {
    struct course* new_course = malloc(sizeof(struct course));
    CHECK_NULL(new_course);
    new_course->id = id;

    new_course->name = malloc(strlen(name) + 1);
    CHECK_NULL(new_course->name);
    strcpy(new_course->name, name);

    new_course->date = malloc(strlen(date) + 1);
    CHECK_NULL(new_course->date);
    strcpy(new_course->date, date);

    new_course->time = malloc(strlen(time) + 1);
    CHECK_NULL(new_course->time);
    strcpy(new_course->time, time);

    new_course->seats_total = seats_total;
    new_course->seats_booked = seats_booked;

    return new_course;
}


//TODO: check for edge case and errors/unitialized values

uint16_t get_course_id(course_ptr course) {
    return course->id;
}

const char* get_course_name(course_ptr course) {
    return course->name;
}

const char* get_course_date(course_ptr course) {
    return course->date;
}

const char* get_course_time(course_ptr course) {
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