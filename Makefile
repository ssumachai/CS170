CC=g++
CFLAGS= -Wall -g

all : turnin test-cases

test: main.cpp
	$(CC) -o test.exe test.cpp setup.cpp problem.cpp

test-cases: test-cases.cpp
	$(CC) -o test-cases.exe test-cases.cpp setup.cpp problem.cpp

turnin: main.cpp
	$(CC) -o turnin.exe main.cpp setup.cpp problem.cpp