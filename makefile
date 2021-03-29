.PHONY: clean run debug all

CC=gcc
CFLAGS=-O2
DEBUG_FLAGS=-g
FILES=src/*.c
INCLUDE=`pkg-config --cflags gtk+-3.0` -I src/
LIBS=`pkg-config --libs gtk+-3.0`

all: bin/main
	@echo ================
	@echo Wow such makefile

run: bin/main
	./bin/main --class float_please

debug: bin/main-debug
	gdb bin/main-debug

bin/main: $(FILES)
	$(CC) $(INCLUDE) $(LIBS) $(CFLAGS) $(FILES) -o bin/main 

bin/main-debug: $(FILES)
	$(CC) $(INCLUDE) $(LIBS) $(DEBUG_FLAGS) $(FILES) -o bin/main-debug

clean:
	rm -rf bin/main
