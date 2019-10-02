# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

all: main

unittests: tests

tests: manhattan.o utils.o point.o tests.o
	$(CC) $(CFLAGS) manhattan.o utils.o point.o tests.o -lm -o exe/tests

main: main.o manhattan.o utils.o point.o
	$(CC) $(CFLAGS) main.o manhattan.o utils.o point.o -lm -o exe/main

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

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