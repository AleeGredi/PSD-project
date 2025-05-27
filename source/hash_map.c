#include "hash_map.h"
#include "course.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    uint16_t key;
    course_ptr value;
    bool is_occupied;
};

struct hash_map {
    uint16_t size;
    uint16_t count;
    item_ptr table;
};

/*
    Computes the hash value for a given key using a mixing algorithm.

    Parameters:
        key: the key to hash.
        size: the size of the hash table.

    Pre-conditions:
        size must be > 0.

    Post-conditions:
        None.

    Returns:
        uint16_t: a hash value in the range [0, size - 1].
*/
static uint16_t hash_function(uint16_t key, uint16_t size) {
    uint32_t x = key;
    x = ((x >> 7) ^ x) * 0x85ebca6b;
    x = ((x >> 11) ^ x) * 0xc2b2ae35;
    x = (x >> 15) ^ x;
    return (uint16_t)(x % size);
}

/*
    Creates and initializes a new hash map with a given size.

    Parameters:
        size: the number of buckets in the hash map.

    Pre-conditions:
        size > 0

    Post-conditions:
        Memory is allocated for the hash map and its internal table.

    Returns:
        hash_map_ptr: pointer to the newly created hash map.
*/
hash_map_ptr create_hash_map(uint16_t size) {
    hash_map_ptr map = malloc(sizeof(*map));
    CHECK_NULL(map);
    map->size = size;
    map->count = 0;
    map->table = calloc(size, sizeof(*map->table));
    CHECK_NULL(map->table);
    return map;
}

/*
    Inserts a course into the hash map, or replaces an existing one with the same key.

    Parameters:
        map: pointer to the hash map.
        key: unique identifier for the course.
        value: pointer to the course to insert.

    Pre-conditions:
        map and value must not be NULL.
        map must not be full.

    Post-conditions:
        The course is inserted or replaces an existing entry with the same key.

    Returns:
        None.
*/
void insert_course(hash_map_ptr map, uint16_t key, course_ptr value) {
    CHECK_NULL(map);
    CHECK_NULL(value);
    if (map->count >= map->size) {
        fprintf(stderr, "Hash map full, cannot insert key %u\n", key);
        return;
    }

    uint16_t start = hash_function(key, map->size);
    for (uint16_t i = 0; i < map->size; ++i) {
        uint16_t idx = (start + i) % map->size;
        item_ptr slot = &map->table[idx];

        if (!slot->is_occupied) {
            slot->key = key;
            slot->value = value;
            slot->is_occupied = true;
            map->count++;
            return;
        }

        if (slot->key == key) {
            delete_course(slot->value);
            slot->value = value;
            return;
        }
    }

    fprintf(stderr, "Hash map probing failed, map may be full.\n");
}

/*
    Retrieves a course from the hash map by its key.

    Parameters:
        map: pointer to the hash map.
        key: the course ID to look up.

    Pre-conditions:
        map must not be NULL.

    Post-conditions:
        None.

    Returns:
        course_ptr: pointer to the course if found, otherwise NULL.
*/
course_ptr get_course(hash_map_ptr map, uint16_t key) {
    CHECK_NULL(map);

    uint16_t start = hash_function(key, map->size);
    for (uint16_t i = 0; i < map->size; ++i) {
        uint16_t idx = (start + i) % map->size;
        item_ptr slot = &map->table[idx];

        if (!slot->is_occupied) {
            return NULL;
        }

        if (slot->key == key) {
            return slot->value;
        }
    }

    return NULL;
}

/*
    Deletes the entire hash map and optionally all course objects it contains.

    Parameters:
        map: pointer to the hash map.
        delete_elements: if true, delete each stored course using delete_course.

    Pre-conditions:
        map must not be NULL.

    Post-conditions:
        The hash map's internal table is freed.
        If delete_elements is true, all stored course objects are freed.
        The hash map itself is freed.

    Returns:
        None.
*/
void delete_hash_map(hash_map_ptr map, bool delete_elements) {
    CHECK_NULL(map);

    if (!delete_elements) {
        free(map->table);
        free(map);
        return;
    }

    for (uint16_t i = 0; i < map->size; ++i) {
        if (map->table[i].is_occupied) {
            delete_course(map->table[i].value);
        }
    }

    free(map->table);
    free(map);
}