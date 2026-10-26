#include "../include/bits.h"
#include <assert.h>


uint32_t bit_set(uint32_t value, unsigned n) {
   assert(n < 32);
   return value | (1u << n);
}

uint32_t bit_clear(uint32_t value, unsigned n) {
   assert(n < 32);
   return value & ~(1u << n);
}

uint32_t bit_toggle(uint32_t value, unsigned n) {
   assert(n < 32);
   return value ^ (1u << n);
}

bool bit_read(uint32_t value, unsigned n) {
   assert(n < 32);
   return value & (1u << n);
}
