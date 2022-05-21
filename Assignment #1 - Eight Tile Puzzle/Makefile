CC=g++
CFLAGS= -Wall -g
SRC_DIR := src

all : clean turnin test-cases


test-cases: $(SRC_DIR)/test-cases.cpp
	$(CC) -o test-cases.exe $(SRC_DIR)/test-cases.cpp $(SRC_DIR)/setup.cpp $(SRC_DIR)/problem.cpp

turnin: $(SRC_DIR)/main.cpp
	$(CC) -o turnin.exe $(SRC_DIR)/main.cpp $(SRC_DIR)/setup.cpp $(SRC_DIR)/problem.cpp

clean:
	-del *.exe