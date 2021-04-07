.PHONY: all run try debug check clean

CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -Werror
OPT_FLAGS=$(CFLAGS) -O2
DEBUG_FLAGS=$(CFLAGS) -g
IMG_SIZE=500
FILES=src/*.c
HEADERS=src/*.h
INCLUDE=`pkg-config --cflags gtk+-3.0` -I src/
LIBS=`pkg-config --libs gtk+-3.0` -lm

all: bin/main
	@echo ================
	@echo Wow such makefile

run: bin/main
	env IMG_SIZE=$(IMG_SIZE) ./bin/main --class float_please

try: bin/main
	env IMG_SIZE=$(IMG_SIZE) G_MESSAGES_DEBUG=all ./bin/main --class float_please

debug: bin/main-debug
	env IMG_SIZE=$(IMG_SIZE) gdb bin/main-debug

bin/main: $(FILES) $(HEADERS)
	$(CC) $(INCLUDE) $(LIBS) $(OPT_FLAGS) $(FILES) -o bin/main 

bin/main-debug: $(FILES) $(HEADERS)
	$(CC) $(INCLUDE) $(LIBS) $(DEBUG_FLAGS) $(FILES) -o bin/main-debug

check:
	./check.sh

clean:
	rm -rf bin/main bin/main-debug
