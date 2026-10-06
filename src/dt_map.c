// Jemarco Briz
/*
 * dt_map.c: Associative arrays for Unit 5, Section E.
 *
 * An array does not store its indices. This map stores its keys.
 * An array calculates a position with one subtraction.
 * The map calculates a hash and then compares keys in one bucket.
 *
 * Hashing turns the key into a bucket number. Compare all keys in that bucket
 * because two keys can select it. Use a linked list for each bucket. Start the
 * unsigned accumulator at 14695981039346656037ULL. For each unsigned byte,
 * exclusive-or the byte into it and multiply by 1099511628211ULL.
 *
 * A separate list stores insertion order for stable output. dt_map_key_at
 * reads this list. Updating a key preserves its position. Removing and
 * reinserting a key moves it to the end.
 */

#include "dt.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAP_BUCKET_COUNT 64

typedef struct map_entry {
    char *key;
    dt_value value;
    struct map_entry *next;
} map_entry;

struct dt_map {
    map_entry *buckets[MAP_BUCKET_COUNT];
    map_entry **order;
    size_t count;
    size_t capacity;
};

static size_t map_bucket(const char *key)
{
    uint64_t hash = UINT64_C(14695981039346656037);
    for (const unsigned char *p = (const unsigned char *)key; *p != '\0'; p++) {
        hash ^= *p;
        hash *= UINT64_C(1099511628211);
    }
    return (size_t)(hash % MAP_BUCKET_COUNT);
}

static map_entry *map_find(const dt_map *m, const char *key, size_t bucket)
{
    for (map_entry *entry = m->buckets[bucket]; entry != NULL; entry = entry->next)
        if (strcmp(entry->key, key) == 0) return entry;
    return NULL;
}

/*
 * dt_map_new builds an empty map. It returns NULL after an allocation failure.
 */
dt_map *dt_map_new(void)
{
    dt_map *m = malloc(sizeof *m);
    if (m == NULL) return NULL;
    for (size_t i = 0; i < MAP_BUCKET_COUNT; i++) m->buckets[i] = NULL;
    m->order = NULL;
    m->count = 0;
    m->capacity = 0;
    return m;
}

/*
 * dt_map_free releases each entry, copied key, order array, and map.
 * It accepts NULL. The environment owns the values.
 */
void dt_map_free(dt_map *m)
{
    if (m == NULL) return;
    for (size_t i = 0; i < m->count; i++) {
        free(m->order[i]->key);
        free(m->order[i]);
    }
    free(m->order);
    free(m);
}

/*
 * dt_map_len returns the number of keys in constant time.
 */
size_t dt_map_len(const dt_map *m)
{
    return m->count;
}

/*
 * dt_map_put binds v to key.
 * An existing key keeps its insertion position. A new key becomes the last key.
 * Copy each new key because the caller owns the source buffer.
 * Return DT_ERR_CAPACITY after an allocation failure.
 */
dt_status dt_map_put(dt_map *m, const char *key, dt_value v)
{
    size_t bucket = map_bucket(key);
    map_entry *entry = map_find(m, key, bucket);
    if (entry != NULL) {
        entry->value = v;
        return DT_OK;
    }
    size_t key_length = strlen(key);
    if (key_length == SIZE_MAX) return DT_ERR_CAPACITY;
    entry = malloc(sizeof *entry);
    if (entry == NULL) return DT_ERR_CAPACITY;
    entry->key = malloc(key_length + 1);
    if (entry->key == NULL) {
        free(entry);
        return DT_ERR_CAPACITY;
    }
    memcpy(entry->key, key, key_length + 1);
    if (m->count == m->capacity) {
        size_t limit = SIZE_MAX / sizeof *m->order;
        if (m->capacity == limit) {
            free(entry->key);
            free(entry);
            return DT_ERR_CAPACITY;
        }
        size_t capacity = m->capacity == 0 ? 8 :
                          (m->capacity > limit / 2 ? limit : m->capacity * 2);
        map_entry **order = realloc(m->order, capacity * sizeof *order);
        if (order == NULL) {
            free(entry->key);
            free(entry);
            return DT_ERR_CAPACITY;
        }
        m->order = order;
        m->capacity = capacity;
    }
    entry->value = v;
    entry->next = m->buckets[bucket];
    m->buckets[bucket] = entry;
    m->order[m->count++] = entry;
    return DT_OK;
}

/*
 * dt_map_get writes the value for key to *out.
 * It returns DT_ERR_KEY and does not change *out when the key is absent.
 * An absent key differs from a nil value.
 */
dt_status dt_map_get(const dt_map *m, const char *key, dt_value *out)
{
    map_entry *entry = map_find(m, key, map_bucket(key));
    if (entry == NULL) return DT_ERR_KEY;
    *out = entry->value;
    return DT_OK;
}

/*
 * dt_map_remove removes key from its bucket and insertion position.
 * It releases the copied key. It returns DT_ERR_KEY when the key is absent.
 */
dt_status dt_map_remove(dt_map *m, const char *key)
{
    size_t bucket = map_bucket(key);
    map_entry **link = &m->buckets[bucket];
    while (*link != NULL && strcmp((*link)->key, key) != 0)
        link = &(*link)->next;
    if (*link == NULL) return DT_ERR_KEY;
    map_entry *entry = *link;
    *link = entry->next;
    size_t index = 0;
    while (m->order[index] != entry) index++;
    for (size_t i = index + 1; i < m->count; i++)
        m->order[i - 1] = m->order[i];
    m->count--;
    free(entry->key);
    free(entry);
    return DT_OK;
}

/*
 * dt_map_key_at writes the key at insertion position index to *out.
 * It returns DT_ERR_RANGE and does not change *out for an invalid index.
 */
dt_status dt_map_key_at(const dt_map *m, size_t index, const char **out)
{
    if (index >= m->count) return DT_ERR_RANGE;
    *out = m->order[index]->key;
    return DT_OK;
}
