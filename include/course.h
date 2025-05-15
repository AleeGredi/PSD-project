#ifndef COURSE_H
#define COURSE_H

#include "datetime.h"
#include <stdint.h>

typedef struct course *course_ptr;

course_ptr create_course(
    uint16_t id,
    char* name, 
    datetime_ptr datetime, 
    uint16_t seats_total,
    uint16_t seats_booked
);

uint16_t get_course_id(course_ptr course);
const char* get_course_name(course_ptr course);
datetime_ptr get_course_datetime(course_ptr course);
uint16_t get_course_seats_total(course_ptr course);
uint16_t get_course_seats_booked(course_ptr course);
void print_course_booking_list(course_ptr course);

void print_course(course_ptr course);

void delete_course(course_ptr course);

#endif