#include "course.h"
#include "utils.h"
#include "booking.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course {
    uint16_t id;
    char* name;
    datetime_ptr datetime;
    uint16_t seats_total;
    uint16_t seats_booked;
    booking_list_ptr booking_list;
};

course_ptr create_course(
    uint16_t id, 
    char* name, 
    datetime_ptr datetime,  
    uint16_t seats_total,
    uint16_t seats_booked
) {
    struct course* new_course = malloc(sizeof(struct course));
    CHECK_NULL(new_course);
    new_course->id = id;

    new_course->name = malloc(strlen(name) + 1);
    CHECK_NULL(new_course->name);
    strcpy(new_course->name, name);
    // stored a reference to the datetime_ptr datetime parameter
    new_course->datetime = datetime;

    new_course->seats_total = seats_total;
    new_course->seats_booked = seats_booked;

    new_course->booking_list = create_booking_list();

    return new_course;
}


uint16_t get_course_id(course_ptr course) {
    return course->id;
}

const char* get_course_name(course_ptr course) {
    return course->name;
}

datetime_ptr get_course_datetime(course_ptr course) {
    return course->datetime;
}

uint16_t get_course_seats_total(course_ptr course) {
    return course->seats_total;
}

uint16_t get_course_seats_booked(course_ptr course) {
    return course->seats_booked;
}

void print_course_booking_list(course_ptr course) {
    print_booking_list(course->booking_list);
}

void print_course(course_ptr course) {
    printf("Course ID: %u\n", course->id);
    printf("Name     : %s\n", course->name);
    printf("Datetime :");
    print_datetime(course->datetime);
    printf("Seats    : %u total, %u booked\n", course->seats_total, course->seats_booked);
}

void delete_course(course_ptr course) {
    free(course->name);
    free(course->datetime);
    delete_booking_list(course->booking_list);
    free(course);
}