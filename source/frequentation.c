#include "frequentation.h"
#include "utils.h"
#include <string.h>

struct frequentation {
    uint16_t course_id;
    char *course_name;
    uint16_t times_booked;
};

frequentation_ptr create_frequentation(uint16_t course_id, char *course_name, uint16_t times_booked){
    struct frequentation* new_frequentation = malloc(sizeof(struct frequentation));

    new_frequentation->course_id = course_id;

    new_frequentation->course_name = malloc(strlen(course_name) + 1);
    CHECK_NULL(new_frequentation->course_name);
    strcpy(new_frequentation->course_name, course_name);

    new_frequentation->times_booked = times_booked;

    return new_frequentation;
}

void save_frequentation_callback(FILE *file, void *element){
    frequentation_ptr frequentation = (frequentation_ptr)element;
    fprintf(file, "%d,%s,%d,",
            get_frequentation_id(frequentation),
            get_frequentation_name(frequentation),
            get_frequentation_times_booked(frequentation));
}

void print_frequentation_callback(FILE* file, void* element) {
    frequentation_ptr entry = (frequentation_ptr)element;
    fprintf(file, "History Entry - ID: %hu, Name: %s, Times Booked: %hu\n",
           entry->course_id, entry->course_name, entry->times_booked);
}

uint16_t get_frequentation_id(frequentation_ptr frequentation) {
    return frequentation->course_id;
}

char* get_frequentation_name(frequentation_ptr frequentation) {
    return frequentation->course_name;
}

uint16_t get_frequentation_times_booked(frequentation_ptr frequentation) {
    return frequentation->times_booked;
}

void set_frequentation_times_booked(frequentation_ptr frequentation, int value) {
    frequentation->times_booked = value;
}