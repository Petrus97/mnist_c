# Shell
SHELL = /bin/sh
#
# Compiler options (https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html)
#
CC=gcc
CFLAGS=-g -Wall -Werror -Wpedantic
LDLIBS=-lm
LDFLAGS=

#
# Directories
#
SRC_DIR=./src
INC_DIR=./include
OBJ_DIR=./objs
IMG_DIR=./images

#
# Automatic variables for .c and .o files
#
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

BIN = mnist_c


CFLAGS += -DDEBUG=1

#
# Compile the binary
#
all: prebuild $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC_DIR) $(LDLIBS)

$(OBJS): $(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)


#
# Add the operations to do before start the compilation
#
prebuild:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BIN) $(OBJ_DIR)/* $(IMG_DIR)/*

