# Compiler vars
CC       ?= clang
CFLAGS   ?= -Wall -Isrc -Iheader $(shell pkg-config --cflags libsystemd)
LDLIBS   := $(shell pkg-config --libs libsystemd)

# Main bin vars
TARGET   := waybar-module-lrc
SRC      := src/main.c src/parser.c
OBJ      := $(patsubst src/%.c, build/%.o, $(SRC))

# Test vars
TESTS        := $(wildcard test/*.c)
TEST_OBJECTS := $(patsubst test/%.c, test/%.o, $(TESTS))
TEST_BIN     := $(patsubst test/%.c, test/%, $(TESTS))

ARGS         := lrc/circle.lrc

# Main bin
all: build/$(TARGET)

build/$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(OBJ) -o $@ $(LDLIBS)

# Objects
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

test/%.o: test/%.c
	@mkdir -p test
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test
test: $(TEST_BIN)

test/%: test/%.o build/parser.o
	$(CC) $^ -o $@ $(LDLIBS)

# Run test
run_tests: test
	@for t in $(TEST_BIN); do \
		echo "Running $$t..."; \
		./$$t; \
	done

# Run main
run_main: build/$(TARGET)
	./build/$(TARGET) $(ARGS)

# Run
run: run_tests run_main

# Clean
clean:
	rm -rf build test/*.o $(TEST_BIN)

.PHONY: all clean run tests run_tests run_main
