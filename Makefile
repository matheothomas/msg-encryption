# Matheo Thomas - 2024

# Project settings
debug ?= 0
NAME = main
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
LIB_DIR = lib
TESTS_DIR = tests
BIN_DIR = bin

CC = gcc
CFLAGS = -I$(INC_DIR) -Wall -Wextra -Wno-deprecated
LIBS=-lcrypto

# Linking and compiling

# _DEPS = $(wildcard $(LIB_DIR)/*.h)
# DEPS = $(patsubst %,$(LIB_DIR)/%,$(_DEPS))

_OBJ = $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c)) 
OBJ = $(patsubst %,$(BUILD_DIR)/%,$(patsubst $(SRC_DIR)/%,%, $(_OBJ)))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN_DIR)/$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean dir

dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

clean:
	@rm -f $(BUILD_DIR)/*.o *~ core $(INCDIR)/*~
