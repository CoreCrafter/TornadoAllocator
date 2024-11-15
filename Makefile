
CC = gcc
CFLAGS = -O2 -Iinclude


COMMON_SRCS = src/utils/handle_err.c src/helpers/allocator.c src/helpers/memory_met.c src/tmalloc.c   
MAIN_SRC = src/defrag_test.c
GC_SRC = src/gc_test.c


OBJDIR = obj
COMMON_OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(COMMON_SRCS))
MAIN_OBJS = $(OBJDIR)/defrag_test.o $(COMMON_OBJS)
GC_OBJS = $(OBJDIR)/gc_test.o $(COMMON_OBJS)


OUTPUT_DIR = bin
TARGET = $(OUTPUT_DIR)/defrag_test
TARGET2 = $(OUTPUT_DIR)/gc_test


all: $(OUTPUT_DIR) $(TARGET) $(TARGET2)


$(OUTPUT_DIR): 
	mkdir -p $@


$(TARGET): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -o $@


$(TARGET2): $(GC_OBJS)
	$(CC) $(GC_OBJS) -o $@


$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	mkdir -p $(dir $@)  
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJDIR):
	mkdir -p $@


clean:
	@echo "Cleaning up..."
	@find . -name '*.o' -delete  
	@rm -rf $(OBJDIR) $(OUTPUT_DIR)
	@echo "Done"