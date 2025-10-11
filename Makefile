CC = gcc
CFLAGS = -Wall -I/opt/homebrew/Cellar/cunit/2.1-3/include
LDFLAGS = -L/opt/homebrew/Cellar/cunit/2.1-3/lib -lcunit

main: 
	$(CC) interpreter.c tokenizer.c -o main

tests: tests.c tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) tests.c tokenizer.c $(LDFLAGS) -o tests

clean:
	rm -f tests

.PHONY: clean