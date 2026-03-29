# Red-Black Tree Makefile

# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -O2
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
DEBUG_FLAGS = -g -DDEBUG

# Directories
GTEST_DIR = D:/app/googletest
GTEST_INCLUDE = $(GTEST_DIR)/googletest/include
GTEST_LIB = $(GTEST_DIR)/build/libgtest.a

# Target names
TARGET_GTEST = rbtree_gtest.exe
LIB = rbtree.a

# Source files
SRCS = rbtree.c
OBJS = rbtree.o
GTEST_SRCS = test_rbtree_gtest.cpp
GTEST_OBJS = test_rbtree_gtest.o

# Default target
all: $(TARGET_GTEST)

# Build gtest executable
$(TARGET_GTEST): $(OBJS) $(GTEST_OBJS) $(GTEST_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_GTEST) $(OBJS) $(GTEST_OBJS) $(GTEST_LIB) -lpthread

# Build static library
lib: $(LIB)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

# Compile C source files
rbtree.o: rbtree.c rbtree.h
	$(CC) $(CFLAGS) -c rbtree.c

# Compile C++ source files
test_rbtree_gtest.o: test_rbtree_gtest.cpp rbtree.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -c test_rbtree_gtest.cpp

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Run gtest tests
test: $(TARGET_GTEST)
	./$(TARGET_GTEST)

# Clean build files
clean:
	@echo Cleaning build files...
	-@rm -f rbtree.o 2>nul || true
	-@rm -f test_rbtree_gtest.o 2>nul || true
	-@rm -f $(TARGET_GTEST) 2>nul || true
	-@rm -f $(LIB) 2>nul || true
	@echo Clean complete.

# Clean gtest build (not needed when using external gtest)
clean-gtest:
	@echo Using external gtest library, nothing to clean.

# Install (copy to system directories - Linux/Unix only)
install: $(LIB)
	cp rbtree.h /usr/local/include/
	cp $(LIB) /usr/local/lib/

# Uninstall
uninstall:
	rm -f /usr/local/include/rbtree.h
	rm -f /usr/local/lib/$(LIB)

# Help
help:
	@echo Available targets:
	@echo   all        - Build gtest executable (default)
	@echo   lib        - Build static library
	@echo   debug      - Build with debug flags
	@echo   test       - Build and run gtest tests
	@echo   clean      - Remove build files
	@echo   clean-gtest- Remove gtest build files
	@echo   install    - Install library system-wide (Linux/Unix)
	@echo   uninstall  - Remove installed library
	@echo   help       - Show this help

.PHONY: all lib debug test clean clean-gtest install uninstall help
