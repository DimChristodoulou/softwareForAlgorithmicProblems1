main: main.o manhattan.o
    g++ -g -o main main.o manhattan.o -pthread

main.o: main.cpp
    g++ -g  -c -pthread main.cpp

manhattan.o: manhattan.h manhattan.cpp
    g++ -g -c -pthread manhattan.cpp