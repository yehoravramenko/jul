JUL = $(BUILD_DIR)/bin/jul

CC := gcc

OBJ_DIR := obj
BUILD_DIR := build
SOURCE_FILES := main.c compiler_msg.c
SRCS := $(SOURCE_FILES:%.c=src/%.c)
OBJS := $(SOURCE_FILES:%.c=$(OBJ_DIR)/%.o)

CFLAGS := -Wall -Wextra -xc -std=c23
# LFLAGS :=

.PHONY: jul
jul: $(OBJ_DIR) $(BUILD_DIR) $(JUL)

$(OBJ_DIR):
	mkdir -p obj

$(BUILD_DIR):
	mkdir -p build
	mkdir -p build/bin

$(JUL): $(OBJS)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: src/%.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)