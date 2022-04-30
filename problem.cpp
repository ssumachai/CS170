#include "problem.h"
#include <stdlib.h>
#include <math.h>

problem::problem(){
    parent = NULL;
    num_rows = number_rows;
    num_columns = number_columns;
    boardSize = board_size;

    generateSolutionBoard(currBoard);
    generateSolutionBoard(goalBoard);

    totalCost = heuristic = gDistance = 0;
}

problem::problem(std::vector<int> v, int rows, int columns){
    num_rows = rows;
    num_columns = columns;
    boardSize = num_rows * num_columns;
    totalCost = gDistance = 0;

    currBoard = v;
    generateSolutionBoard(goalBoard);

}

int problem::misplacedCost(){
    int count = 0;

    for(int i = 0; i < boardSize - 1; i++){
        if(currBoard.at(i) != goalBoard.at(i)){
            count++;
        }
    }
    return count;
}

int problem::euclideanCost(){
    // Manhattan Distance Formula given by: sqrt((a1 - b1)^2 + (a2-b2)^2)

    int count = 0;
    int currX, currY;
    int trueX, trueY;
    int distX, distY;
    int manhattan;
    bool cYDone, tYDone = false;

    for(int i = 0; i < boardSize; i++){
        if(currBoard.at(i) == 0){
            continue;
        }
        else if(currBoard.at(i) != goalBoard.at(i)){
            currX = ((i+1) % num_columns == 0) ? num_columns : (i + 1) % num_columns;
            trueX = (currBoard.at(i) % num_columns == 0) ? num_columns : currBoard.at(i) % num_columns;

            cYDone = tYDone = false;

            for(int j = 1; j < num_rows + 1; j++){
                if((i < j * num_columns) && !cYDone){
                    currY = j;
                    cYDone = true;
                }
                if((currBoard.at(i) < j * num_columns) && !tYDone){
                    trueY = j;
                    tYDone = true;
                }
            }

            distX = currX - trueX;
            distY = currY - trueY;

            distX = abs(distX);
            distY = abs(distY);

            manhattan = sqrt(pow(distX, 2) + pow(distY, 2));

            count += manhattan;
        }
    }

    return count;
}