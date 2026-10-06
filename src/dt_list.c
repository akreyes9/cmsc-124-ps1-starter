// Aleighia Keith Reyes
/*
 * dt_list.c: Lists for Unit 5, Section H.
 *
 * A cell holds a value and a pointer to the list tail.
 * CAR reads the value. CDR reads the tail. CONS creates a new first cell.
 *
 * CONS creates one cell and shares the supplied tail. After these commands:
 *
 *     list nil e
 *     list cons b 2 e
 *     list cons a 1 b
 *
 * List a is (1 2). List b is (2). Both lists reference the cell that holds 2.
 * CONS takes constant time and allocates one cell.
 *
 * dt_list_free releases one cell. Following the tail would release cells that
 * list b still uses.
 *
 * A null pointer represents the empty list.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_list {
    dt_value head;
    dt_list *tail;
};

/*
 * dt_list_nil returns the null pointer that represents the empty list.
 */
dt_list *dt_list_nil(void)
{
    return NULL;
}

/*
 * dt_list_cons builds a new cell that holds head and references tail.
 * The new cell shares the supplied tail.
 * The function returns NULL after an allocation failure.
 */
dt_list *dt_list_cons(dt_value head, dt_list *tail)
{
    // Allocate exactly one cell; sizeof *cell stays correct if the type changes
    dt_list *cell = malloc(sizeof *cell);
    if (cell == NULL) {
        return NULL;   // Allocation failed; nothing to clean up
    }

    cell->head = head;
    cell->tail = tail;   // Share the tail by pointer, no copying

    return cell;
}

/*
 * dt_list_free releases one cell and preserves its tail.
 * Another list can still reference the tail. The function accepts NULL.
 */
void dt_list_free(dt_list *l)
{
    // Free only this cell; the tail may still be used by another list.
    free(l);
}

/*
 * dt_list_len counts the cells. It visits each cell once.
 */
size_t dt_list_len(const dt_list *l)
{
    size_t count = 0;

    // Walk until the NULL terminator, counting each cell
    while (l != NULL) {
        count++;
        l = l->tail;   // Advance to the next cell
    }
    return count;
}

/*
 * dt_list_car writes the first cell value to *out.
 * It returns DT_ERR_EMPTY and does not change *out for an empty list.
 * A nil value differs from an absent value.
 */
dt_status dt_list_car(const dt_list *l, dt_value *out)
{
    // An empty list has no first cell to read
    if (l == NULL) {
        return DT_ERR_EMPTY;
    }

    *out = l->head;   // Copy the first value out
    return DT_OK;
}

/*
 * dt_list_cdr writes the tail to *out. It returns DT_ERR_EMPTY for an empty
 * list. A one-element list has an empty tail and returns DT_OK.
 */
dt_status dt_list_cdr(const dt_list *l, dt_list **out)
{
    // An empty list has no tail; this differs from a tail that is empty
    if (l == NULL) {
        return DT_ERR_EMPTY;
    }

    *out = l->tail;   // May be NULL for a one-element list, which is valid
    return DT_OK;
}