// Aleigha Keight Laranja Reyes
/*
 * dt_int.c: Checked integers for Unit 5, Section A.
 *
 * In C, signed integer overflow has undefined behavior.
 * The compiler can assume that signed overflow does not occur.
 * An optimizer can remove a guarded check after the arithmetic.
 *
 *     long long sum = a + b
 *     if (b > 0 && sum < a) return DT_ERR_OVERFLOW // optimizer may remove this branch
 *
 * Check before the operation. Use comparison values that cannot overflow.
 * A positive b overflows when a > LLONG_MAX - b.
 * A negative b produces a result below LLONG_MIN when a < LLONG_MIN - b.
 * These comparison subtractions are safe.
 *
 * Multiplication has more cases. LLONG_MIN multiplied by -1 overflows.
 * LLONG_MIN divided by -1 also has undefined behavior.
 *
 * These stubs report overflow for every input. The normal cases fail until you implement them.
 */

#include "dt.h"

#include <limits.h>

/*
 * dt_int_add computes a + b.
 * It returns DT_ERR_OVERFLOW and does not change *out for an overflow.
 */
dt_status dt_int_add(long long a, long long b, long long *out)
{
    /* TODO: Check for overflow. Then write the sum to *out.
       dt_int_add(2, 3, &out)          -> DT_OK, out = 5
       dt_int_add(LLONG_MAX, 1, &out)  -> DT_ERR_OVERFLOW, out untouched
       cases/normal/int_arithmetic.case, cases/boundary/int_overflow_add.case */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

/*
 * dt_int_sub computes a - b.
 * It returns DT_ERR_OVERFLOW and does not change *out for an overflow.
 */
dt_status dt_int_sub(long long a, long long b, long long *out)
{
    /* TODO: Check subtraction directly.
       The value -LLONG_MIN does not exist in long long.
       Therefore, dt_int_add(a, -b, out) fails when b is LLONG_MIN.
       dt_int_sub(10, 4, &out)                 -> DT_OK, out = 6
       dt_int_sub(LLONG_MIN + 1, 2, &out)      -> DT_ERR_OVERFLOW, out untouched
       cases/normal/int_arithmetic.case, cases/boundary/int_overflow_sub_min.case */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}

/*
 * dt_int_mul computes a * b.
 * It returns DT_ERR_OVERFLOW and does not change *out for an overflow.
 */
dt_status dt_int_mul(long long a, long long b, long long *out)
{
    /* TODO: Handle zero first. Then handle LLONG_MIN with -1.
       Finally, handle the remaining values.
       dt_int_mul(6, 7, &out)            -> DT_OK, out = 42
       dt_int_mul(LLONG_MIN, 0, &out)    -> DT_OK, out = 0
       dt_int_mul(LLONG_MIN, -1, &out)   -> DT_ERR_OVERFLOW, out untouched
       cases/normal/int_arithmetic.case,
       cases/boundary/int_mul_min_by_negative_one.case */
    (void)a;
    (void)b;
    (void)out;
    return DT_ERR_OVERFLOW;
}
