CC=g++
CFLAGS= -Wall -g

all: test turnin

test: main.cpp
	$(CC) -o test.exe main.cpp setup.cpp problem.cpp

turnin: main.cpp
	$(CC) -o turnin.exe main.cpp setup.cpp problem.cpp