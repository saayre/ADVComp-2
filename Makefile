CC=g++
CFLAGS=-g -Wall

md: md.cpp initialize.o iterate.o
	$(CC) $(CFLAGS) md.cpp initialize.o iterate.o -o md

initialize: initialize.cpp
	$(CC) $(CFLAGS) -c initialize.cpp

iterate: iterate.cpp
	$(CC) $(CFLAGS) -c iterate.cpp

test: test.cpp initialize.o iterate.o
	$(CC) $(CFLAGS) test.cpp initialize.o iterate.o -o test

test2: test2.cpp initialize.o iterate.o
	$(CC) $(CFLAGS) test2.cpp initialize.o iterate.o -o test2

clean:
	rm md test test2 initialize.o iterate.o
