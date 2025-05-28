# Compiler & flags
CC        = gcc
CFLAGS    = -std=c99 -Wall -Wextra -Iinclude -g

# All source files → object files under build/
SRC       = $(wildcard source/*.c)
OBJ_ALL   = $(patsubst source/%.c,build/%.o,$(SRC))

# Library objects = everything except main.o
LIB_OBJ   = $(filter-out build/main.o,$(OBJ_ALL))

# Test sources → object files under build/test/
TEST_SRC  = $(wildcard test/*.c)
TEST_OBJ  = $(patsubst test/%.c,build/test/%.o,$(TEST_SRC))

# Executables
TARGET       = build/MyFitness
TEST_TARGET  = build/test/MyFitness_test

# Default target
all: $(TARGET)

# Link main executable (all objects)
$(TARGET): $(OBJ_ALL)
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

# Link test executable (all library objects + test objects)
.PHONY: test
test: $(LIB_OBJ) $(TEST_OBJ)
	mkdir -p build/test
	$(CC) $(CFLAGS) $^ -o $(TEST_TARGET)

# Compile source/*.c → build/%.o
build/%.o: source/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test/*.c → build/test/%.o
build/test/%.o: test/%.c
	mkdir -p build/test
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
.PHONY: clean
clean:
	rm -rf build