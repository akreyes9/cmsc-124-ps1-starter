// Aleighia Keith Reyes
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
    // Valid ordinals are 0 .. DT_COLOR_COUNT - 1; anything else is out of range
    if (ordinal >= DT_COLOR_COUNT || ordinal < 0) {
        return false;
    }

    return true;
}

/*
 * dt_enum_name writes the enumerator text to *out. It returns DT_ERR_RANGE for
 * an invalid ordinal. A failure preserves *out.
 */
dt_status dt_enum_name(int ordinal, const char **out)
{
    // Validate first so we never index outside COLOR_NAMES
    if (dt_enum_is_valid(ordinal)) {
        *out = COLOR_NAMES[ordinal];   // Ordinal doubles as the array index
        return DT_OK;
    }

    // Invalid ordinal: *out is left untouched, as the spec requires
    return DT_ERR_RANGE;
}

/*
 * dt_enum_from_name searches the enumerator text and writes its ordinal to
 * *out. It returns DT_ERR_RANGE when the text has no match.
 */
dt_status dt_enum_from_name(const char *name, int *out)
{
    // Linear search over every declared color
    for (int i = 0; i < DT_COLOR_COUNT; i++) {
        // strcmp returns 0 on an exact, case-sensitive match
        if (strcmp(name, COLOR_NAMES[i]) == 0) {
            *out = i;          // The matching index is the ordinal
            return DT_OK;
        }
    }

    // No name matched: *out is left untouched
    return DT_ERR_RANGE;
}