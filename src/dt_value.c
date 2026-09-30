// Aleigha Keight Laranja Reyes
/*
 * dt_value.c: Discriminated union for Unit 5, Section I.
 *
 * The supplied constructors set the tag and payload.
 *
 * Implement the three readers at the end of this file.
 * Each reader must check the tag before it reads the payload.
 * C permits code to read a different union member.
 * The tag lets this interface reject that operation.
 *
 * The stubs reject every read. Therefore, each as command exits with code 70.
 *
 * Check the tag before you return a payload. Without this check, `as str 42`
 * gives the printer an integer as a pointer. That operation has undefined
 * behavior.
 */

#include "dt.h"

/* dt_value_nil returns the supplied empty value. */
dt_value dt_value_nil(void)
{
    dt_value v = { .tag = DT_NIL, .as = { .integer = 0 } };
    return v;
}

/* dt_value_int returns a supplied integer value. */
dt_value dt_value_int(long long n)
{
    dt_value v = { .tag = DT_INT, .as = { .integer = n } };
    return v;
}

/* dt_value_enum returns a supplied enumeration value. */
dt_value dt_value_enum(int ordinal)
{
    dt_value v = { .tag = DT_ENUM, .as = { .ordinal = ordinal } };
    return v;
}

/* dt_value_str returns a supplied string value. */
dt_value dt_value_str(dt_str *s)
{
    dt_value v = { .tag = DT_STR, .as = { .string = s } };
    return v;
}

/* dt_value_array returns a supplied array value. */
dt_value dt_value_array(dt_array *a)
{
    dt_value v = { .tag = DT_ARRAY, .as = { .array = a } };
    return v;
}

/* dt_value_map returns a supplied associative array value. */
dt_value dt_value_map(dt_map *m)
{
    dt_value v = { .tag = DT_MAP, .as = { .map = m } };
    return v;
}

/* dt_value_record returns a supplied record value. */
dt_value dt_value_record(dt_record *r)
{
    dt_value v = { .tag = DT_RECORD, .as = { .record = r } };
    return v;
}

/* dt_value_tuple returns a supplied tuple value. */
dt_value dt_value_tuple(dt_tuple *t)
{
    dt_value v = { .tag = DT_TUPLE, .as = { .tuple = t } };
    return v;
}

/* dt_value_list returns a supplied list value. */
dt_value dt_value_list(dt_list *l)
{
    dt_value v = { .tag = DT_LIST, .as = { .list = l } };
    return v;
}

/* dt_value_ref returns a supplied reference value. */
dt_value dt_value_ref(dt_ref *p)
{
    dt_value v = { .tag = DT_REF, .as = { .ref = p } };
    return v;
}

/* Student functions. */

/*
 * dt_value_as_int writes the integer in v to *out.
 * It returns DT_ERR_TAG and does not change *out for another tag.
 */
dt_status dt_value_as_int(dt_value v, long long *out)
{
    /* TODO: Check v.tag for DT_INT. Write v.as.integer to *out after a match.
       Otherwise, return DT_ERR_TAG and preserve *out.
       dt_value_as_int(dt_value_int(42), &out)  -> DT_OK, out = 42
       dt_value_as_int(dt_value_str(s), &out)   -> DT_ERR_TAG, out untouched
       cases/normal/union_readers.case, cases/tag/as_int_on_string.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

/*
 * dt_value_as_enum validates DT_ENUM and writes its ordinal to *out.
 */
dt_status dt_value_as_enum(dt_value v, int *out)
{
    /* TODO: Check DT_ENUM and write v.as.ordinal to *out.
       dt_value_as_enum(dt_value_enum(2), &out)  -> DT_OK, out = 2 for BLUE
       dt_value_as_enum(dt_value_nil(), &out)    -> DT_ERR_TAG, out untouched
       cases/normal/union_readers.case, cases/tag/as_enum_on_nil.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}

/*
 * dt_value_as_str validates DT_STR and writes its pointer to *out.
 */
dt_status dt_value_as_str(dt_value v, dt_str **out)
{
    /* TODO: Check DT_STR and write v.as.string to *out.
       dt_value_as_str(dt_value_str(s), &out)  -> DT_OK, *out is s
       dt_value_as_str(dt_value_int(42), &out) -> DT_ERR_TAG, *out untouched
       the tag check prevents the printer from reading 42 as an address
       cases/normal/union_readers.case, cases/tag/as_str_on_int.case */
    (void)v;
    (void)out;
    return DT_ERR_TAG;
}
