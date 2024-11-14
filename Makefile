CC = gcc
CFLAGS = -O2 -Iinclude

# Source files
COMMON_SRCS = src/tmalloc.c src/helpers/allocator.c src/helpers/memory_met.c src/utils/handle_err.c
MAIN_SRC = src/main.c
GC_SRC = src/gc_test.c

# Object files
COMMON_OBJS = $(COMMON_SRCS:.c=.o)
MAIN_OBJS = obj/main.o $(COMMON_OBJS)
GC_OBJS = obj/gc_test.o $(COMMON_OBJS)

# Output directory and executables
OUTPUT_DIR = bin
TARGET = $(OUTPUT_DIR)/main
TARGET2 = $(OUTPUT_DIR)/gc_test

# Default target - compile both programs
all: $(OUTPUT_DIR) $(TARGET) $(TARGET2)

# Create the output directory if it doesn't exist
$(OUTPUT_DIR): 
	mkdir -p $@

# Rule to compile the main program
$(TARGET): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -o $(TARGET)

# Rule to compile the gc_test program
$(TARGET2): $(GC_OBJS)
	$(CC) $(GC_OBJS) -o $(TARGET2)

# Rule to compile .c files into .o files in the obj/ directory
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf obj $(OUTPUT_DIR) $(COMMON_OBJS)

