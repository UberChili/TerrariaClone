# Name of the output binary
NAME = terraria

# Source and output dirs
SRC = src/main.c
BIN = bin/$(NAME)

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    PLATFORM = macos
    CFLAGS = -Ilib/macos -Wall -O2
    LDFLAGS = lib/macos/libraylib.a \
              -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
else
    PLATFORM = linux
    CFLAGS = -Wall -O2
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compiler
CC = gcc

# Default target
all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(BIN)

print-platform:
	@echo Detected platform: $(PLATFORM)

.PHONY: all clean print-platform
