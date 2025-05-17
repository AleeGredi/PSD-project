#include "user.h"
#include "hash_map.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    uint16_t key;
    user_ptr value;
    bool is_occupied;
};

struct hash_map {
    uint16_t size;
    uint16_t count;
    item_ptr table;
};

static uint16_t hash_function(uint16_t key, uint16_t size) {
    uint32_t x = key;
    x = ((x >> 7) ^ x) * 0x85ebca6b;
    x = ((x >> 11) ^ x) * 0xc2b2ae35;
    x = (x >> 15) ^ x;
    return (uint16_t)(x % size);
}

hash_map_ptr new_hash_map(uint16_t size) {
    hash_map_ptr map = malloc(sizeof(*map));
    CHECK_NULL(map);
    map->size = size;
    map->count = 0;
    map->table = calloc(size, sizeof(*map->table));
    CHECK_NULL(map->table);
    return map;
}

void insert_user(hash_map_ptr map, uint16_t key, user_ptr value) {
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
            slot->value = value;
            return;
        }
    }

    fprintf(stderr, "Hash map probing failed, map may be full.\n");
}

user_ptr get_user(hash_map_ptr map, uint16_t key) {
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

void free_hash_map(hash_map_ptr map) {
    if (!map) return;
    free(map->table);
    free(map);
}