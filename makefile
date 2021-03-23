.PHONY: clean run

CC=gcc
CFLAGS=-g
INCLUDE=`pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`

all: bin/main
	@echo ================
	@echo Wow such makefile

run: bin/main
	./bin/main --class float_please

bin/main: src/main.c
	$(CC) $(INCLUDE) $(LIBS) $(CFLAGS) src/main.c -o bin/main 

clean:
	rm -rf bin/main
