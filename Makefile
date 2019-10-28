# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++11 -Wall

all: lsh cube

curves: curve_grid_lsh

unittests: tests

tests: manhattan.o utils.o point.o tests.o curve.o
	$(CC) $(CFLAGS) manhattan.o utils.o point.o tests.o curve.o -lm -o exe/tests

lsh: lsh.o manhattan.o utils.o point.o curve.o
	$(CC) $(CFLAGS) lsh.o manhattan.o utils.o point.o curve.o -lm -o exe/lsh

cube: cube.o manhattan.o utils.o point.o curve.o
	$(CC) $(CFLAGS) cube.o manhattan.o utils.o point.o curve.o -lm -o exe/cube

curve_grid_lsh: curve_grid_lsh.o manhattan.o utils.o point.o curve.o
	$(CC) $(CFLAGS) curve_grid_lsh.o manhattan.o utils.o point.o curve.o -lm -o exe/curve_grid_lsh

lsh.o: src/lsh.cpp
	$(CC) $(CFLAGS) -c src/lsh.cpp

cube.o: src/cube.cpp
	$(CC) $(CFLAGS) -c src/cube.cpp

curve_grid_lsh.o: src/curve_grid_lsh.cpp
	$(CC) $(CFLAGS) -c src/curve_grid_lsh.cpp

manhattan.o: src/manhattan.cpp
	$(CC) $(CFLAGS) -c src/manhattan.cpp

utils.o: src/utils.cpp
	$(CC) $(CFLAGS) -c src/utils.cpp

point.o: src/point.cpp
	$(CC) $(CFLAGS) -c src/point.cpp

curve.o: src/curve.cpp
	$(CC) $(CFLAGS) -c src/curve.cpp

tests.o: tests/tests.cpp
	$(CC) $(CFLAGS) -c tests/tests.cpp

clean:
	rm -fv *.o exe/*
	rm -f tmp/*

cunit:
	sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev