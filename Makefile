


### 1
# supported platforms ( TARGET_ARCH ): linux64 linux32 aarch64-linux arm-linux win32 win64
TARGET_ARCH = win32


ifeq ($(TARGET_ARCH), win32)
	TARGET_COMPILER = i686-w64-mingw32-gcc
	CFLAGS = -m32 -Iinclude
else ifeq ($(TARGET_ARCH), win64)
	TARGET_COMPILER = x86_64-w64-mingw32-gcc
	CFLAGS = -m64 -Iinclude
else
	TARGET_COMPILER = gcc
	CFLAGS = -Iinclude
endif

	



TARGET_LIB_PATH = -Lplatforms/$(TARGET_ARCH)
TARGET_LIB = -ltornado-$(TARGET_ARCH)
CC = $(TARGET_COMPILER)

LDFLAGS =  $(TARGET_LIB_PATH) $(TARGET_LIB)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(SRC_DIR)/gc_test.c $(SRC_DIR)/gc_heap.c $(SRC_DIR)/gc_test2.c $(SRC_DIR)/defrag_test.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
TARGETS = $(BIN_DIR)/gc_test $(BIN_DIR)/gc_test2 $(BIN_DIR)/gc_heap $(BIN_DIR)/defrag_test

all: $(BIN_DIR) $(TARGETS)

# Rule to create the output directory
$(BIN_DIR):
	mkdir -p $@

# Rule to build each target
$(BIN_DIR)/gc_test: $(OBJ_DIR)/gc_test.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@
	
$(BIN_DIR)/gc_test2: $(OBJ_DIR)/gc_test2.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/gc_heap: $(OBJ_DIR)/gc_heap.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@


$(BIN_DIR)/defrag_test: $(OBJ_DIR)/defrag_test.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $@

clean:
	@echo "[+] Cleaning up ..."
	@rm -rf $(OBJ_DIR) $(TARGETS) $(BIN_DIR)/*
	@echo "[*] Done."

