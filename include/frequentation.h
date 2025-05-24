#ifndef FREQUENTATION_H
#define FREQUENTATION_H

#include <stdio.h>
#include <stdint.h>

typedef struct frequentation *frequentation_ptr;

frequentation_ptr create_frequentation(uint16_t course_id, char *course_name, uint16_t times_booked);

void save_frequentation_callback(FILE *file, void *element);

void print_frequentation_callback(FILE* file, void* element);

uint16_t get_frequentation_id(frequentation_ptr frequentation);

char* get_frequentation_name(frequentation_ptr frequentation);

uint16_t get_frequentation_times_booked(frequentation_ptr frequentation);

void set_frequentation_times_booked(frequentation_ptr frequentation, int value);

#endif