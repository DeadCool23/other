CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
MATH = -lm
SOURCE_DIR = src
LIBS_DIR = $(SOURCE_DIR)/libs
LIBS = $(wildcard $(LIBS_DIR)/*.c) $(LIBS_DIR)/graph/graph_draw.c $(LIBS_DIR)/polish/polish.c
MAIN = $(SOURCE_DIR)/main.c

SOURCE = $(LIBS) $(MAIN)

TARGET = build/app.exe

.PHONY: run debug build clean

run: $(TARGET)
	./$(TARGET)

debug: $(SOURCE)
	$(CC) $(CFLAGS) -g $(SOURCE) -o $(TARGET) $(MATH)

build: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(MATH)

clean:
	rm -f build/*.exe

