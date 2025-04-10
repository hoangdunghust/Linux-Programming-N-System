CC = gcc
AR = ar
CFLAGS = -Wall -fPIC
LIB_DIR = lib
BUILD_DIR = build

STATIC_LIB = $(BUILD_DIR)/libmylib.a
SHARED_LIB = $(BUILD_DIR)/libmylib.so

all: prepare $(STATIC_LIB) $(SHARED_LIB) build-main-static build-main-shared

prepare:
	mkdir -p $(BUILD_DIR)

$(STATIC_LIB): $(LIB_DIR)/mylib.c
	$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/mylib.o
	$(AR) rcs $@ $(BUILD_DIR)/mylib.o

$(SHARED_LIB): $(LIB_DIR)/mylib.c
	$(CC) -shared -fPIC -o $@ $<

build-main-static: main.c $(STATIC_LIB)
	$(CC) main.c -I$(LIB_DIR) $(STATIC_LIB) -o $(BUILD_DIR)/main_static

build-main-shared: main.c $(SHARED_LIB)
	$(CC) main.c -I$(LIB_DIR) -L$(BUILD_DIR) -lmylib -o $(BUILD_DIR)/main_shared

run-static:
	./$(BUILD_DIR)/main_static

run-shared:
	LD_LIBRARY_PATH=$(BUILD_DIR) ./$(BUILD_DIR)/main_shared

clean:

	rm -rf $(BUILD_DIR)

.PHONY: all clean run-static run-shared prepare

