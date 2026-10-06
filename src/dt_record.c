// Aleighia Keith Reyes
/*
 * dt_record.c: Records for Unit 5, Section F.
 *
 * A record selects fields by name. A compiled language can replace a field
 * access with a fixed offset. That access requires no run-time search.
 *
 * This implementation keeps a field-name array.
 * A lookup searches the array and returns an index.
 *
 * An undeclared field returns DT_ERR_FIELD. Records cannot add fields after
 * construction. An associative array can add keys.
 */

#include "dt.h"

#include <stdlib.h>
#include <string.h>

struct dt_record {
    char    *names[DT_RECORD_MAX_FIELDS];
    dt_value values[DT_RECORD_MAX_FIELDS];
    size_t   count;
};

/*
 * dt_record_new builds a record with the specified fields in declaration order.
 * It sets each field to nil and copies each field name.
 * It returns NULL for too many fields or an allocation failure.
 */
dt_record *dt_record_new(const char **field_names, size_t field_count)
{
    // The arrays are fixed-size, so reject anything that won't fit
    if (field_count > DT_RECORD_MAX_FIELDS) {
        return NULL;
    }

    dt_record *r = malloc(sizeof(struct dt_record));
    if (r == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < field_count; i++) {
        // Copy the name so the record doesn't depend on the caller's strings
        size_t len = strlen(field_names[i]);
        r->names[i] = malloc(len + 1);   // +1 for the '\0' terminator
        if (r->names[i] == NULL) {
            // Roll back: free only the names copied so far (0 .. i-1)
            for (size_t j = 0; j < i; j++) {
                free(r->names[j]);
            }
            free(r);
            return NULL;
        }
        memcpy(r->names[i], field_names[i], len + 1);   // Includes the '\0'
        r->values[i] = dt_value_nil();                  // Every field starts as nil
    }

    // Set count last so it only reflects fully built fields
    r->count = field_count;
    return r;
}

/*
 * dt_record_free releases the copied field names and the record.
 * It accepts NULL. The environment owns the field values.
 */
void dt_record_free(dt_record *r)
{
    // Allow free-on-NULL, like free()
    if (r == NULL) {
        return;
    }

    // Free each copied name; values are not freed because the record doesn't own them
    for (size_t i = 0; i < r->count; i++) {
        free(r->names[i]);
    }

    free(r);   // Free the record itself last
}

/*
 * dt_record_field_count returns the stored field count in constant time.
 */
size_t dt_record_field_count(const dt_record *r)
{
    // Count is stored, so no scanning is needed
    return r->count;
}

/*
 * dt_record_field_name writes the field name at declaration position index to *out.
 * It returns DT_ERR_RANGE and does not change *out for an invalid index.
 * The record prints fields in declaration order.
 */
dt_status dt_record_field_name(const dt_record *r, size_t index, const char **out)
{
    // size_t is unsigned, so only the upper bound needs checking
    if (index >= r->count) {
        return DT_ERR_RANGE;
    }

    *out = r->names[index];   // Points at the record's own copy; caller must not free it
    return DT_OK;
}

/*
 * dt_record_get writes the value of field to *out.
 * It returns DT_ERR_FIELD and does not change *out when the field is absent.
 */
dt_status dt_record_get(const dt_record *r, const char *field, dt_value *out)
{
    // Linear search by name; this is the run-time lookup the header describes
    for (size_t i = 0; i < r->count; i++) {
        if (strcmp(r->names[i], field) == 0) {
            *out = r->values[i];   // Same index as the matching name
            return DT_OK;
        }
    }

    // No name matched: *out is left untouched
    return DT_ERR_FIELD;
}

/*
 * dt_record_set replaces the value of field with v.
 * It returns DT_ERR_FIELD and changes nothing when the field is absent.
 * A record cannot gain fields after construction.
 */
dt_status dt_record_set(dt_record *r, const char *field, dt_value v)
{
    // Same search as dt_record_get, but writes instead of reads
    for (size_t i = 0; i < r->count; i++) {
        if (strcmp(r->names[i], field) == 0) {
            r->values[i] = v;
            return DT_OK;
        }
    }

    // Unknown field: set never creates new fields
    return DT_ERR_FIELD;
}