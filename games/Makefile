CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
DYN = -lncurses

LIFE = game_of_life.c

PONG_STATIC = pong.c
PONG_INTERACTIVE = pong_interactive.c

SOURCE = src
TARGET = build

all: life_game pong_dynamic pong_static

life_game:
	$(CC) $(CFLAGS) $(SOURCE)/game_in_life/$(LIFE) $(DYN) -o $(TARGET)/life/$(LIFE:.c=.exe)

pong_static:
	$(CC) $(CFLAGS) $(SOURCE)/pong/$(PONG_STATIC) -o $(TARGET)/pong/$(PONG_STATIC:.c=.exe)

pong_interactive:
	$(CC) $(CFLAGS) $(SOURCE)/pong/$(PONG_INTERACTIVE) $(DYN) -o $(TARGET)/pong/$(PONG_INTERACTIVE:.c=.exe)

clean:
	rm $(TARGET)/*/*.exe
