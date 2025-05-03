#ifndef COURSE_H
#define COURSE_H

#include <inttypes.h>

typedef struct course *course_ptr;

course_ptr create_course(
    uint16_t id, 
    const char* name, 
    const char* date, 
    const char* time, 
    uint16_t seats_total,
    uint16_t seats_booked
);

uint16_t get_course_id(course_ptr course);
char* get_course_name(course_ptr course);
char* get_course_date(course_ptr course);
char* get_course_time(course_ptr course);
uint16_t get_course_seats_total(course_ptr course);
uint16_t get_course_seats_booked(course_ptr course);

void print_course(course_ptr course);

void delete_course(course_ptr course);

#endif