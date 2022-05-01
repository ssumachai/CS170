#ifndef __SETUP_H__
#define __SETUP_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const int number_rows = 3;
const int number_columns = 3;
const int board_size = number_columns * number_rows;

// Pass vector to ensure that it's a valid input
bool checkBoardInput(std::vector<int> gameBoard);
void generateSolutionBoard(std::vector<int> &solBoard);
void takeRowInput(std::vector<int> &board);
void generateProblemBoard(int boardChoice, std::vector<int> &problemBoard);
int setup(std::vector<int> &sBoard, std::vector<int> &pBoard);

#endif