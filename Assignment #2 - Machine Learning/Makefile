CC=g++
CFLAGS= -Wall -g

all: test data-test

test: main.cpp
	$(CC) -o test.exe main.cpp setup.cpp algorithms.cpp problem.cpp

data-test: data_test.cpp
	$(CC) -o data.exe data_test.cpp dataset.cpp classifier.cpp