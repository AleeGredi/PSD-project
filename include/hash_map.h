#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "course.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct item* item_ptr;
typedef struct hash_map* hash_map_ptr;

// Create a new hash map with given capacity
hash_map_ptr create_hash_map(uint16_t size);

// Insert or update the course at key
void insert_course(hash_map_ptr map, uint16_t key, course_ptr value);

// Retrieve course by key, or NULL if not found
course_ptr get_course(hash_map_ptr map, uint16_t key);

// Free the entire map
void delete_hash_map(hash_map_ptr map);

#endif