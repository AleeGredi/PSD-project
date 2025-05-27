#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "course.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct item* item_ptr;
typedef struct hash_map* hash_map_ptr;

/*
    Creates and initializes a new hash map with a given size.

    Parameters:
        size: number of slots in the hash map.

    Pre-conditions:
        size > 0

    Post-conditions:
        Memory is allocated for the hash map and its table.

    Returns:
        hash_map_ptr: pointer to the newly created hash map.
*/
hash_map_ptr create_hash_map(uint16_t size);

/*
    Inserts a course into the hash map using the given key.
    If the key already exists, the existing course is deleted and replaced.

    Parameters:
        map: pointer to the hash map.
        key: unique identifier for the course.
        value: pointer to the course to insert.

    Pre-conditions:
        map and value must not be NULL.
        The map must have available space.

    Post-conditions:
        The course is inserted or updated in the map.

    Returns:
        None.
*/
void insert_course(hash_map_ptr map, uint16_t key, course_ptr value);

/*
    Retrieves a course from the hash map using the given key.

    Parameters:
        map: pointer to the hash map.
        key: the key to look up.

    Pre-conditions:
        map must not be NULL.

    Post-conditions:
        None.

    Returns:
        course_ptr: pointer to the course if found, otherwise NULL.
*/
course_ptr get_course(hash_map_ptr map, uint16_t key);

/*
    Frees all memory used by the hash map and optionally its course elements.

    Parameters:
        map: pointer to the hash map.
        delete_elements: if true, all stored course objects are also freed.

    Pre-conditions:
        map must not be NULL.

    Post-conditions:
        The hash map's internal table is freed.
        If delete_elements is true, all stored course objects are freed.
        The hash map itself is freed.

    Returns:
        None.
*/
void delete_hash_map(hash_map_ptr map, bool delete_elements);

#endif
