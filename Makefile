# Compiler & flags
CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Iinclude -g

# Sources → objects
SRC     = $(wildcard source/*.c)
OBJ     = $(patsubst source/%.c,build/%.o,$(SRC))

# Final executable
TARGET  = build/MyFitness

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

# Compile
build/%.o: source/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf build