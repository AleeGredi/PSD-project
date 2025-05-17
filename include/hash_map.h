#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "user.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct item* item_ptr;
typedef struct hash_map* hash_map_ptr;

// Create a new hash map with given capacity
hash_map_ptr new_hash_map(uint16_t size);

// Insert or update the user at key
void insert_user(hash_map_ptr map, uint16_t key, user_ptr value);

// Retrieve user by key, or NULL if not found
user_ptr get_user(hash_map_ptr map, uint16_t key);

// Free the entire map
void free_hash_map(hash_map_ptr map);

#endif