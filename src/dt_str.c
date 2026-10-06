// Jemarco Briz
/*
 * dt_str.c: Length-carrying strings for Unit 5, Section B.
 *
 * A C string is a null-terminated character sequence stored in an array.
 * An array expression usually converts to a pointer to its first character.
 * strlen reads only through the first zero byte.
 * A pointer does not store the array capacity.
 *
 * This type stores the length and capacity with the bytes. dt_str_len reads a
 * field. A zero byte is data. Append operations use the stored capacity.
 *
 * An implementation can store a final zero byte after the data.
 * The public interface requires callers to use dt_str_len.
 */

#include "dt.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct dt_str {
    char  *bytes;
    size_t length;
    size_t capacity;
};

/*
 * dt_str_new copies the first `length` bytes. A zero byte is data. The function
 * returns NULL when allocation or size representation fails.
 */
dt_str *dt_str_new(const char *bytes, size_t length)
{
    if (length == SIZE_MAX) return NULL;
    dt_str *s = malloc(sizeof *s);
    if (s == NULL) return NULL;
    s->bytes = malloc(length + 1);
    if (s->bytes == NULL) {
        free(s);
        return NULL;
    }
    if (length != 0) memcpy(s->bytes, bytes, length);
    s->bytes[length] = '\0';
    s->length = length;
    s->capacity = length + 1;
    return s;
}

/*
 * dt_str_free releases the buffer and handle. It accepts NULL.
 */
void dt_str_free(dt_str *s)
{
    if (s == NULL) return;
    free(s->bytes);
    free(s);
}

/*
 * dt_str_len returns the stored byte count in constant time.
 */
size_t dt_str_len(const dt_str *s)
{
    return s->length;
}

/*
 * dt_str_bytes returns the string bytes. Internal storage can include a final
 * zero byte. Callers must use dt_str_len with this pointer.
 */
const char *dt_str_bytes(const dt_str *s)
{
    return s->bytes;
}

/*
 * dt_str_append adds `length` bytes and grows the buffer when necessary. It
 * returns DT_ERR_CAPACITY when allocation or size representation fails.
 * The function does not change the string after a failure.
 */
dt_status dt_str_append(dt_str *s, const char *bytes, size_t length)
{
    if (length > SIZE_MAX - s->length - 1) return DT_ERR_CAPACITY;
    if (length == 0) return DT_OK;
    size_t needed = s->length + length + 1;
    if (needed > s->capacity) {
        size_t capacity = s->capacity;
        while (capacity < needed) {
            if (capacity > SIZE_MAX / 2) {
                capacity = needed;
                break;
            }
            capacity *= 2;
        }
        /* Copy before freeing so appending the string's own bytes is valid. */
        char *grown = malloc(capacity);
        if (grown == NULL) return DT_ERR_CAPACITY;
        memcpy(grown, s->bytes, s->length);
        memcpy(grown + s->length, bytes, length);
        free(s->bytes);
        s->bytes = grown;
        s->capacity = capacity;
    } else {
        memmove(s->bytes + s->length, bytes, length);
    }
    s->length += length;
    s->bytes[s->length] = '\0';
    return DT_OK;
}

/*
 * dt_str_substr builds a new string from length bytes at start.
 * It returns DT_ERR_RANGE when the requested range exceeds the source.
 * It returns DT_ERR_CAPACITY after an allocation failure.
 * The function does not change the source string.
 */
dt_status dt_str_substr(const dt_str *s, size_t start, size_t length, dt_str **out)
{
    if (start > s->length || length > s->length - start)
        return DT_ERR_RANGE;
    dt_str *part = dt_str_new(s->bytes + start, length);
    if (part == NULL) return DT_ERR_CAPACITY;
    *out = part;
    return DT_OK;
}

/*
 * dt_str_eq reports whether both strings hold the same bytes.
 * The stored lengths let the comparison include embedded zero bytes.
 */
bool dt_str_eq(const dt_str *a, const dt_str *b)
{
    return a->length == b->length &&
           memcmp(a->bytes, b->bytes, a->length) == 0;
}
