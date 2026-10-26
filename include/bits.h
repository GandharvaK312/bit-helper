#ifndef BITS_H
#define BITS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Bit helpers. Bits are numbered from 0, where bit 0 is the least
 * significant (rightmost) bit. For all functions, n must be in 0..31;
 * otherwise the function asserts.
 */

/* Returns value with bit n forced to 1. */
uint32_t bit_set(uint32_t value, unsigned n);

/* Returns value with bit n forced to 0. */
uint32_t bit_clear(uint32_t value, unsigned n);

/* Returns value with bit n flipped. */
uint32_t bit_toggle(uint32_t value, unsigned n);

/* Returns true if bit n of value is 1, false if it is 0. */
bool bit_read(uint32_t value, unsigned n);

#ifdef __cplusplus
}
#endif

#endif /* BITS_H */
