// Aleigha Keight Laranja Reyes
/*
 * dt_enum.c: Enumerations for Unit 5, Section C.
 *
 * A C enumeration type is compatible with an integer type and uses named
 * enumerators. A dt_color can still hold 47. This module instead accepts only
 * the three declared color ordinals. Other languages place different
 * restrictions on creating enumeration values from arbitrary integers.
 *
 * These three functions validate each enumeration operation in one location.
 */

#include "dt.h"

#include <string.h>

static const char *const COLOR_NAMES[] = { "RED", "GREEN", "BLUE" };

/*
 * dt_enum_is_valid returns true for a declared ordinal. C permits any integer
 * in an enumeration object. This function validates the declared range.
 */
bool dt_enum_is_valid(int ordinal)
{
    /* TODO: Return true for an ordinal from zero through DT_COLOR_COUNT - 1.
       dt_enum_is_valid(0)   -> true, RED
       dt_enum_is_valid(2)   -> true, BLUE
       dt_enum_is_valid(3)   -> false, one past the set
       dt_enum_is_valid(-1)  -> false, below the lower bound */
    (void)ordinal;
    (void)COLOR_NAMES; /* Delete this line after you use COLOR_NAMES. */
    return false;
}

/*
 * dt_enum_name writes the enumerator text to *out. It returns DT_ERR_RANGE for
 * an invalid ordinal. A failure preserves *out.
 */
dt_status dt_enum_name(int ordinal, const char **out)
{
    /* TODO: Return DT_ERR_RANGE when the ordinal is outside the set.
       Otherwise, write the corresponding text to *out.
       Validate the ordinal before you index COLOR_NAMES.
       dt_enum_name(0, &out)  -> DT_OK, *out = "RED"
       dt_enum_name(2, &out)  -> DT_OK, *out = "BLUE"
       dt_enum_name(3, &out)  -> DT_ERR_RANGE, *out untouched
       cases/normal/enum_names.case */
    (void)ordinal;
    (void)out;
    return DT_ERR_RANGE;
}

/*
 * dt_enum_from_name searches the enumerator text and writes its ordinal to
 * *out. It returns DT_ERR_RANGE when the text has no match.
 */
dt_status dt_enum_from_name(const char *name, int *out)
{
    /* TODO: Search COLOR_NAMES. Return DT_ERR_RANGE when no text matches.
       dt_enum_from_name("GREEN", &out)   -> DT_OK, out = 1
       dt_enum_from_name("PURPLE", &out)  -> DT_ERR_RANGE, out untouched
       dt_enum_from_name("1", &out)       -> DT_ERR_RANGE because no text matches
       cases/normal/enum_names.case */
    (void)name;
    (void)out;
    return DT_ERR_RANGE;
}
