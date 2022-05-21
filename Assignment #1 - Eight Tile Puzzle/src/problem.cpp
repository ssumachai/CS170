#include "../include/problem.h"
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
    direction = " ";
}

problem::problem(std::vector<int> v, int rows, int columns){
    parent = NULL;
    num_rows = rows;
    num_columns = columns;
    boardSize = num_rows * num_columns;
    totalCost = gDistance = 0;
    direction = " ";

    currBoard = v;
    generateSolutionBoard(goalBoard);

}

// Note, the direction of the move corresponds to where the BLANK SPACE is moving!

problem* problem::moveUp(){
    problem* movePiece = new problem(this->currBoard, num_rows, num_columns);
    int blankIndex = findBlankIndex();

    // If the blank piece is in the first row, it can't move "up"
    if(blankIndex < num_columns){
        return NULL;
    }
    else{
        
        // If there is an empty piece in the middle (Index 4), we'd want to move the piece above it
        // down, so index 1.  Therefore, we "swap" the empty piece and the piece above it.  Moving the
        // Empty piece "up"
        std::swap(movePiece->currBoard.at(blankIndex), movePiece->currBoard.at(blankIndex - num_columns));
        movePiece->parent = this;
        movePiece->gDistance = this->gDistance + 1;
        return movePiece;

    }

}

problem* problem::moveLeft(){
    problem* movePiece = new problem(this->currBoard, num_rows, num_columns);
    int blankIndex = findBlankIndex();

    // If the blank piece is on the outermost column, it can't move left!
    // 0, 3, or 6 can't move left!
    if(blankIndex % num_columns == 0){
        return NULL;
    }
    else{

        // If there is an empty space in the middle (Index 4), we'd want to move the piece to the left of 
        // it (Index 3) to the right.  Therefore, we swap the empty piece and the leftmost piece, moving the
        // empty piece "Left"
        std::swap(movePiece->currBoard.at(blankIndex), movePiece->currBoard.at(blankIndex - 1));
        movePiece->parent = this;
        movePiece->gDistance = this->gDistance + 1;
        return movePiece;
    }

}

problem* problem::moveDown(){
    problem* movePiece = new problem(this->currBoard, num_rows, num_columns);
    int blankIndex = findBlankIndex();

    // If the blank piece is in the last row, it can't move "up"
    // num_columns * num_columns - 1 = 3 * (3 - 1) = 6, so if it's index is greater-equal than 6 it's invalid
    if(blankIndex >= (num_columns*(num_columns - 1))){
        return NULL;
    }
    else{
        
        // If there is an empty piece in the middle (Index 4), we'd want to move the piece below it
        // down, so index 7.  Therefore, we "swap" the empty piece and the piece below it.  Moving the
        // Empty piece "down"
        std::swap(movePiece->currBoard.at(blankIndex), movePiece->currBoard.at(blankIndex + num_columns));
        movePiece->parent = this;
        movePiece->gDistance = this->gDistance + 1;
        return movePiece;

    }

}

problem* problem::moveRight(){
    problem* movePiece = new problem(this->currBoard, num_rows, num_columns);
    int blankIndex = findBlankIndex();

    // If the blank piece is on the outermost column, it can't move left!
    // 2, 5, or 8 can't move left!
    // This is the same as saying 3, 6, and 9 can't move...so index + 1!
    if((blankIndex + 1) % num_columns == 0){
        return NULL;
    }
    else{

        // If there is an empty space in the middle (Index 4), we'd want to move the piece to the right of 
        // it (Index 5) to the left.  Therefore, we swap the empty piece and the rightmost piece, moving the
        // empty piece "right"
        std::swap(movePiece->currBoard.at(blankIndex), movePiece->currBoard.at(blankIndex + 1));
        movePiece->parent = this;
        movePiece->gDistance = this->gDistance + 1;
        return movePiece;
    }

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

void problem::print(){
    for(int i = 0; i < boardSize; ++i){
        if(i % num_columns == 0){
            std::cout << std::endl;
        }
        std::cout << currBoard.at(i) << ' ';
    }
    std::cout << std::endl;
}

void problem::determineDirection(int value){
    switch(value){
        case 0:
            this->direction = "Up";
            break;
        case 1:
            this->direction = "Down";
            break;
        case 2:
            this->direction = "Left";
            break;
        case 3:
            this->direction = "Right";
            break;
        default:
            break;
    }
}

std::vector<int> problem::getCurrBoard(){
    return this->currBoard;
}

int problem::findBlankIndex(){
    int index;

    for(int i = 0; i < boardSize; ++i){
        if(currBoard.at(i) == 0){
            index = i;
        }
    }
    return index;
}

bool problem::solutionfound(){
    for(int i=0; i<boardSize; ++i){
        if(currBoard.at(i) != goalBoard.at(i)){
            return false;
        }
    }
    return true;
}





