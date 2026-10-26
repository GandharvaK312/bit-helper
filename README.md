# bit-helper

A tiny, dependency-free C library for single-bit operations on 32-bit values: set, clear, toggle, and read.

It is plain C99 with no `malloc`, no floating point, and no OS or hardware dependencies, so it works on a PC, on an ESP32, or on any other microcontroller toolchain.

## API

All functions live in [`include/bits.h`](include/bits.h). Bits are numbered from 0, where bit 0 is the least significant (rightmost) bit.

| Function | Returns |
|---|---|
| `uint32_t bit_set(uint32_t value, unsigned n)` | `value` with bit `n` forced to 1 |
| `uint32_t bit_clear(uint32_t value, unsigned n)` | `value` with bit `n` forced to 0 |
| `uint32_t bit_toggle(uint32_t value, unsigned n)` | `value` with bit `n` flipped |
| `bool bit_read(uint32_t value, unsigned n)` | `true` if bit `n` is 1, otherwise `false` |

**Precondition:** `n` must be in the range 0-31. Every function checks this with `assert(n < 32)`. A violation aborts the program with a message showing the file and line. If you compile with `-DNDEBUG`, the check is removed and an out-of-range `n` is undefined behavior, so don't pass it values that come from outside your program without checking them first.

The functions never modify their arguments. They return the new value, so use them like this: `x = bit_set(x, 3);`

## Example

```c
#include <stdio.h>
#include "bits.h"

int main(void)
{
    uint32_t reg = 0x89;               /* 1000 1001 */

    reg = bit_set(reg, 2);             /* 1000 1101 -> 0x8D */
    reg = bit_clear(reg, 7);           /* 0000 1101 -> 0x0D */
    reg = bit_toggle(reg, 0);          /* 0000 1100 -> 0x0C */

    printf("reg = 0x%02X\n", (unsigned)reg);
    printf("bit 2 is %s\n", bit_read(reg, 2) ? "set" : "clear");
    return 0;
}
```

Expected output:

```
reg = 0x0C
bit 2 is set
```

## Getting the code

```bash
git clone https://github.com/gandharvak312/bit-helper.git
cd bit-helper
```

## Building and running the tests

You need `gcc` (or another C compiler) and `make`.

```bash
make test
```

This builds the tests with `-Wall -Wextra` and the address and undefined-behavior sanitizers, runs them, and prints `all tests passed` on success.

Other targets:

| Command | What it does |
|---|---|
| `make lib` | builds a static library at `build/libbits.a` |
| `make clean` | removes the `build/` folder |

To use a different compiler: `make test CC=clang`.

## Using the library in your own project

### Option 1: copy two files (simplest)

Copy `include/bits.h` and `src/bits.c` into your project, add `bits.c` to your build, and include the header:

```c
#include "bits.h"
```

### Option 2: compile it alongside your code

Point the compiler at the header folder and add `bits.c` to the command. Adjust the paths to where you cloned the repository:

```bash
gcc -Wall -Wextra -o main main.c path/to/bit-helper/src/bits.c -I path/to/bit-helper/include
```

Forgetting `bits.c` produces an `undefined reference to 'bit_set'` linker error, because the header only declares the functions.

### Option 3: static library

```bash
make lib
gcc -o main main.c -I path/to/bit-helper/include -L path/to/bit-helper/build -lbits
```

### Option 4: ESP-IDF component

Create a folder `components/bits/` inside your ESP-IDF project and copy `include/` and `src/` into it. Add this `CMakeLists.txt` in `components/bits/`:

```cmake
idf_component_register(SRCS "src/bits.c"
                       INCLUDE_DIRS "include")
```

Then in your code, `#include "bits.h"`. If the build can't find the header from another component, add `bits` to that component's `REQUIRES` list in its `CMakeLists.txt`.

### Using it from C++

The header has `extern "C"` guards, so it works from C++ and Arduino sketches without changes.

## Project layout

```
bit-helper/
├── include/bits.h      public header
├── src/bits.c          implementation
├── tests/test_bits.c   tests (plain assert, no framework)
├── Makefile
├── LICENSE
└── README.md
```

## License

MIT. See [LICENSE](LICENSE).
