# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++11 -Wall

all: lsh

unittests: tests

tests: manhattan.o utils.o point.o tests.o
	$(CC) $(CFLAGS) manhattan.o utils.o point.o tests.o -lm -o exe/tests

lsh: lsh.o manhattan.o utils.o point.o
	$(CC) $(CFLAGS) lsh.o manhattan.o utils.o point.o -lm -o exe/lsh

lsh.o: src/lsh.cpp
	$(CC) $(CFLAGS) -c src/lsh.cpp

manhattan.o: src/manhattan.cpp
	$(CC) $(CFLAGS) -c src/manhattan.cpp

utils.o: src/utils.cpp
	$(CC) $(CFLAGS) -c src/utils.cpp

point.o: src/point.cpp
	$(CC) $(CFLAGS) -c src/point.cpp

tests.o: tests/tests.cpp
	$(CC) $(CFLAGS) -c tests/tests.cpp

clean:
	rm -fv *.o exe/*
	rm -f tmp/*

cunit:
	sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev