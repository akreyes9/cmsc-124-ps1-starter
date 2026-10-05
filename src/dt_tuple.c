// Jemarco Briz
/*
 * dt_tuple.c: Tuples for Unit 5, Section G.
 *
 * A tuple is a record with numbered parts.
 * A field selector can show meaning, but a numeric position does not.
 * Tuples suit small temporary groups, such as two function results.
 *
 * A tuple needs no declaration. You build it from its parts and read by position.
 *
 * There is no dt_tuple_set. Construction fixes the arity and contents.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_tuple {
    dt_value values[DT_TUPLE_MAX_ARITY];
    size_t   arity;
};

/*
 * dt_tuple_new builds a tuple from the first count values in order.
 * A zero count creates a valid empty tuple.
 * It returns NULL for excessive arity or an allocation failure.
 */
dt_tuple *dt_tuple_new(const dt_value *values, size_t count)
{
    if (count > DT_TUPLE_MAX_ARITY) return NULL;
    dt_tuple *t = malloc(sizeof *t);
    if (t == NULL) return NULL;
    t->arity = count;
    for (size_t i = 0; i < count; i++) t->values[i] = values[i];
    return t;
}

/*
 * dt_tuple_free releases the tuple. It accepts NULL.
 * The environment owns the values.
 */
void dt_tuple_free(dt_tuple *t)
{
    free(t);
}

/*
 * dt_tuple_arity returns the stored part count in constant time.
 */
size_t dt_tuple_arity(const dt_tuple *t)
{
    return t->arity;
}

/*
 * dt_tuple_at writes the value at zero-based position index to *out.
 * It returns DT_ERR_RANGE and does not change *out for an invalid index.
 */
dt_status dt_tuple_at(const dt_tuple *t, size_t index, dt_value *out)
{
    if (index >= t->arity) return DT_ERR_RANGE;
    *out = t->values[index];
    return DT_OK;
}
