JUL = $(BUILD_DIR)/bin/jul

CC := g++

OBJ_DIR := obj
BUILD_DIR := build
SOURCE_FILES := main.cpp lexer.cpp parser.cpp

FMTLIB_INC := -Ithirdparty/fmt/include

OBJS := $(SOURCE_FILES:%.cpp=$(OBJ_DIR)/%.o)

CFLAGS := -Ithirdparty $(FMTLIB_INC) -Wall -Wpedantic -Wextra -Werror -xc++ -std=c++23

.PHONY: jul
jul: CFLAGS += -g
jul: $(OBJ_DIR) $(BUILD_DIR) $(JUL)

.PHONY: release
release: $(OBJ_DIR) $(BUILD_DIR) $(JUL)
	

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
	rm -rf $(OBJ_DIR) $(BUILD_DIR) .cache

# .PHONY: cleanbuild
# cleanbuild: clean jul