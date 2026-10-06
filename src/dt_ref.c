// Jemarco Briz
/*
 * dt_ref.c: Owned references for Unit 5, Section J.
 *
 * This module detects three ownership failures.
 *
 * A dangling reference retains an address after release.
 * Reading that address has undefined behavior. It can return old data or terminate.
 *
 * A double release gives the same allocation to free twice.
 * This operation has undefined behavior. The visible failure can occur later.
 *
 * An unreleased allocation still has an owner at the final check. The driver
 * reports DT_ERR_LEAK before cleanup.
 *
 * A released flag lets this small interface report the first two mistakes as
 * DT_ERR_RELEASED. The driver's final check reports the third as DT_ERR_LEAK.
 * These checks model this assignment's ownership contract only.
 *
 * Ownership stops at the cell. dt_ref_new copies the value into an owned cell.
 * The environment still owns a string that the copied value references.
 */

#include "dt.h"

#include <stdlib.h>

struct dt_ref {
    dt_value *cell;
    bool      released;
};

/*
 * dt_ref_new builds a reference to a copy of v.
 * The reference owns this cell. It returns NULL after an allocation failure.
 */
dt_ref *dt_ref_new(dt_value v)
{
    dt_ref *p = malloc(sizeof *p);
    if (p == NULL) return NULL;
    p->cell = malloc(sizeof *p->cell);
    if (p->cell == NULL) {
        free(p);
        return NULL;
    }
    *p->cell = v;
    p->released = false;
    return p;
}

/*
 * dt_ref_borrow writes a copy of the cell value to *out.
 * It returns DT_ERR_RELEASED and does not change *out after release.
 * Check the release flag before you access the cell pointer.
 */
dt_status dt_ref_borrow(const dt_ref *p, dt_value *out)
{
    if (p->released) return DT_ERR_RELEASED;
    *out = *p->cell;
    return DT_OK;
}

/*
 * dt_ref_release releases the cell and sets the release state.
 * It returns DT_ERR_RELEASED and changes nothing after an earlier release.
 */
dt_status dt_ref_release(dt_ref *p)
{
    if (p->released) return DT_ERR_RELEASED;
    free(p->cell);
    p->cell = NULL;
    p->released = true;
    return DT_OK;
}

/*
 * dt_ref_is_released reports the release state.
 * The driver uses this state to identify leaked cells.
 */
bool dt_ref_is_released(const dt_ref *p)
{
    return p->released;
}

/*
 * dt_ref_destroy releases a remaining cell and then releases the handle.
 * The driver reports leaks before it calls this function.
 * This function accepts NULL and does not report leaks.
 */
void dt_ref_destroy(dt_ref *p)
{
    if (p == NULL) return;
    free(p->cell);
    free(p);
}
