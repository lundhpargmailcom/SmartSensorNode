CC := gcc

SRC_DIR := src

BUILD_DIR := build

CFLAGS := -std=c90 -Isrc -Iinclude -Wall -Wextra -MMD -MP

LDFLAGS := -flto -Wl,--gc-sections

SRC := $(shell find -L $(SRC_DIR) -type f -name '*.c')

OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

DEP := $(OBJ:.o=.d)

BIN := main

all: $(BIN)
	@echo "Build complete."

$(BIN): $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	@rm -rf $(BIN)

.PHONY: all clean run