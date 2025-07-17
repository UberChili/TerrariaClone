# Name of the output binary
NAME = terraria

# Source and output dirs
SRC = src/main.c
BIN = bin/$(NAME)

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    PLATFORM = macos
    LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
else
    PLATFORM = linux
    LIBS = -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compiler and flags
CC = gcc
CFLAGS = -Ilib/$(PLATFORM) -Wall -O2

# Default target
all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) lib/$(PLATFORM)/libraylib.a $(LIBS)

clean:
	rm -f $(BIN)

.PHONY: all clean
