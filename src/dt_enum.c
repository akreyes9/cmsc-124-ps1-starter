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
    if (dt_enum_is_valid(ordinal)) {
        *out = COLOR_NAMES[ordinal];
        return DT_OK;
    }

    return DT_ERR_RANGE;
}

/*
 * dt_enum_from_name searches the enumerator text and writes its ordinal to
 * *out. It returns DT_ERR_RANGE when the text has no match.
 */
dt_status dt_enum_from_name(const char *name, int *out)
{
    for (int i = 0; i < DT_COLOR_COUNT; i++) {
        if (strcmp(name, COLOR_NAMES[i]) == 0) {
            *out = i;
            return DT_OK;
        }
    }

    return DT_ERR_RANGE;
}