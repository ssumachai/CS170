CC=g++
CFLAGS= -Wall -g

test: main.cpp
	$(CC) -o test.exe main.cpp