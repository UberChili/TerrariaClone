# Name of the output binary
NAME = terraria

CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Iinclude
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    PLATFORM = macos
    CFLAGS = -Ilib/macos -Wall -O2
    LDFLAGS = lib/macos/libraylib.a \
              -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
else
    PLATFORM = linux
    CFLAGS = -Wall -O2 -Werror -Wextra
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Object files (all go to build directory)
# This example was taken from filter, leaving for reference in case I forget
# OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/helpers.o $(BUILDDIR)/png.o $(BUILDDIR)/chunk.o
OBJS = $(BUILDDIR)/main.o

# Main target
$(BINDIR)/terraria: $(OBJS) | $(BINDIR)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

# Compile main.c
# This example was compiling with filter.h
# $(BUILDDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/filter.h | $(BUILDDIR)
$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile png.c
# This example was taken from filter, we don't need it, keeping it for future reference
# $(BUILDDIR)/png.o: $(SRCDIR)/png.c $(INCDIR)/filter.h | $(BUILDDIR)

# Create directories if they don't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean build artifacts
clean:
	rm -f $(BUILDDIR) $(BINDIR)

print-platform:
	@echo Detected platform: $(PLATFORM)

.PHONY: all clean print-platform
