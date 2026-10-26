CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -g
INC      = -Iinclude
BUILD    = build

LIB_SRC  = src/bits.c
TEST_SRC = tests/test_bits.c
HEADERS  = include/bits.h

.PHONY: all lib test clean

all: lib

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/bits.o: $(LIB_SRC) $(HEADERS) | $(BUILD)
	$(CC) $(CFLAGS) $(INC) -c $(LIB_SRC) -o $@

$(BUILD)/libbits.a: $(BUILD)/bits.o
	ar rcs $@ $<

lib: $(BUILD)/libbits.a

$(BUILD)/test_bits: $(TEST_SRC) $(LIB_SRC) $(HEADERS) | $(BUILD)
	$(CC) $(CFLAGS) -fsanitize=address,undefined $(INC) $(TEST_SRC) $(LIB_SRC) -o $@

test: $(BUILD)/test_bits
	./$(BUILD)/test_bits

clean:
	rm -rf $(BUILD)
