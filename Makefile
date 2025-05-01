JUL = $(BUILD_DIR)/bin/jul

CC := g++

OBJ_DIR := obj
BUILD_DIR := build
SOURCE_FILES := main.cpp compiler_msg.cpp lexer.cpp
OBJS := $(SOURCE_FILES:%.cpp=$(OBJ_DIR)/%.o)

CFLAGS := -Wall -Wpedantic -Wextra -Werror -xc++ -std=c++23 -g
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

$(OBJ_DIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: cleanbuild
cleanbuild: clean jul