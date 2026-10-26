#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "../include/bits.h"

void print_bin8(uint8_t value) {

   int bin[8] = {0}, temp = value, x = 7;
   while(temp > 0) {
      bin[x] = temp % 2;
      temp /= 2;
      x --;
   }
   for(int i = 0; i < 8; ++ i) { printf("%d ", bin[i]); }
   printf("\n");

}

static void test_set(void)
{
    assert(bit_set(0x05, 3) == 0x0D);        /* 0101 -> 1101 */
    assert(bit_set(0x0D, 3) == 0x0D);        /* already set: no change */
    assert(bit_set(0x00, 0) == 0x01);
    assert(bit_set(0xF0, 0) == 0xF1);        /* other bits untouched */
    assert(bit_set(0x00, 31) == 0x80000000u);
    for (unsigned n = 0; n < 32; n++) {
        assert(bit_set(0, n) == (UINT32_C(1) << n));
    }
}

static void test_clear(void)
{
    assert(bit_clear(0x0D, 3) == 0x05);      /* 1101 -> 0101 */
    assert(bit_clear(0x05, 3) == 0x05);      /* already clear: no change */
    assert(bit_clear(0xFF, 0) == 0xFE);
    assert(bit_clear(0xFFFFFFFFu, 31) == 0x7FFFFFFFu);
    for (unsigned n = 0; n < 32; n++) {
        assert(bit_clear(0xFFFFFFFFu, n) == ~(UINT32_C(1) << n));
    }
}

static void test_toggle(void)
{
    assert(bit_toggle(0x05, 3) == 0x0D);
    assert(bit_toggle(0x0D, 3) == 0x05);
    for (unsigned n = 0; n < 32; n++) {      /* toggling twice = original */
        assert(bit_toggle(bit_toggle(0xA5A5A5A5u, n), n) == 0xA5A5A5A5u);
    }
}

static void test_read(void)
{
    /* 0x0D = 0b1101 */
    assert(bit_read(0x0D, 0));
    assert(!bit_read(0x0D, 1));
    assert(bit_read(0x0D, 2));
    assert(bit_read(0x0D, 3));
    assert(!bit_read(0x0D, 4));
    assert(bit_read(0x80000000u, 31));
    assert(!bit_read(0, 31));
    assert(bit_read(0x0D, 3) == 1);          /* exactly 1, not 8 */
}

// static void test_out_of_range(void)
// {
//     /* only valid if your policy is "return value unchanged" */
//     assert(bit_set(0x05, 32) == 0x05);
//     assert(bit_clear(0x05, 100) == 0x05);
//     assert(bit_toggle(0x05, 32) == 0x05);
//     assert(!bit_read(0x05, 32));
// }

int main(void)
{
    test_set();
    test_clear();
    test_toggle();
    test_read();
    // test_out_of_range();
    printf("all tests passed\n");
    return 0;
}
