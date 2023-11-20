CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion

INC_DIR = inc
INC= -I $(INC_DIR)

SRC = $(wildcard src/*.c)
HEADERS = $(wildcard $(INC_DIR)/*.h)

BUILD_DIR = .
OBJDIR = $(BUILD_DIR)/out
OBJ = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))

TARGET = $(BUILD_DIR)/my_cat

.PHONY: build
build: $(TARGET)

.PHONY: release
release: CFLAGS += -O3
release: $(TARGET)

.PHONY: debug
debug: CFLAGS += -g
debug: CFLAGS += -O0
debug: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET) -r $(OBJDIR)

$(TARGET): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR): $(BUILD_DIR)
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
