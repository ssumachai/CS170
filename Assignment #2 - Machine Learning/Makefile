CC=g++
CFLAGS= -Wall -g
SRC_DIR := src

all: clean data-test turnin

turnin: $(SRC_DIR)/turnin.cpp
	$(CC) -o turnin.exe $(SRC_DIR)/turnin.cpp $(SRC_DIR)/setup.cpp $(SRC_DIR)/classifier.cpp $(SRC_DIR)/dataset.cpp $(SRC_DIR)/problem.cpp $(SRC_DIR)/algorithms.cpp $(SRC_DIR)/validator.cpp

test: $(SRC_DIR)/main.cpp
	$(CC) -o test.exe $(SRC_DIR)/main.cpp $(SRC_DIR)/setup.cpp $(SRC_DIR)/algorithms.cpp $(SRC_DIR)/problem.cpp

data-test: $(SRC_DIR)/data_test.cpp
	$(CC) -o data.exe $(SRC_DIR)/data_test.cpp $(SRC_DIR)/dataset.cpp $(SRC_DIR)/classifier.cpp $(SRC_DIR)/validator.cpp

clean:
	-del *.exe