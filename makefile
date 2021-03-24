.PHONY: clean run

CC=gcc
CFLAGS=-g
FILES=src/*.c
INCLUDE=`pkg-config --cflags gtk+-3.0` -I src/
LIBS=`pkg-config --libs gtk+-3.0`

all: bin/main
	@echo ================
	@echo Wow such makefile

run: bin/main
	./bin/main --class float_please

bin/main: $(FILES)
	$(CC) $(INCLUDE) $(LIBS) $(CFLAGS) $(FILES) -o bin/main 

clean:
	rm -rf bin/main
