#include "setup.h"

bool checkBoardInput(std::vector<int> gameBoard){    
    std::sort(gameBoard.begin(), gameBoard.end());

    for(int i = 0; i < board_size; i++){
        if(gameBoard.at(i) != i){
            std::cout << "Invalid Board, please enter again!\n";
            return false;
        }
    }

    return true;
}

void generateSolutionBoard(std::vector<int> &solBoard){
    
    //Take size of board.  If a board is 3 x 3, the correct
    //input values will be 1 - 8
    for(int i = 1; i < board_size; i++){
        solBoard.push_back(i);
    }

    //Pushback 0 at end of vector to indicate blank piece
    solBoard.push_back(0);
}

void takeRowInput(std::vector<int> &board){
    int buf;

    do{
        std::cin >> buf;
        board.push_back(buf);
    }
    while(std::cin.peek() == ' ');
}

void generateProblemBoard(int boardChoice, std::vector<int> &problemBoard){
    bool valid_board = false;
    int buf;

    switch(boardChoice){
        case 1:
            problemBoard = {1, 0, 3, 4, 2, 6, 7, 5, 8};
            break;
        case 2:
            while(!valid_board){
                problemBoard = {};      // Re-initializes the board on for input
                
                std::cout << "Enter your puzzle, use a zero to represent the blank\nEnter the first row, use space between numbers: ";
                takeRowInput(problemBoard);
                std::cout << "Enter the second row, use space between numbers: ";
                takeRowInput(problemBoard);
                std::cout << "Enter the third row, use space between numbers: ";
                takeRowInput(problemBoard);

                valid_board = checkBoardInput(problemBoard);
            }
    }
}

int setup(std::vector<int> &sBoard, std::vector<int> &pBoard){
    int boardInput = 0;
    bool board_select, algo_select = false;
    std::string temp_message;



    std::cout << "Welcome to Chai and Nikki's Board Tile solver!\nBoard Preset is: 3 x 3\n";
    std::cout << "1 -- Hardcoded Tile Board\n2 -- Custom Tile Board\n";

    std::cout << "Please enter your selection (1/2): ";
    std::cin >> boardInput;

    while(!board_select){
        switch(boardInput){
            case 1:
                generateProblemBoard(1, pBoard);
                board_select = true;
                break;
            case 2:
                generateProblemBoard(2, pBoard);
                board_select = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> boardInput;
                break;
        }  
    } 

    std::cout << "1 -- Uniform Cost Search\n2 -- A* w/ Misplaced Tile\n3 -- A* w/ Euclidean Distance\n";
    std::cout << "Please enter your selection (1/2/3): ";
    std::cin >> boardInput;

    while(!algo_select){
        switch(boardInput){
            case 1:
                temp_message += "Do Uniform Cost Search\n";
                algo_select = true;
                break;
            case 2:
                temp_message += "Do Misplaced Heuristic\n";
                algo_select = true;
                break;
            case 3:
                temp_message += "Do Euclidean Heuristic\n";
                algo_select = true;
                break;
            default:
                std::cout << "Invalid Input, please try again: ";
                std::cin >> boardInput;
                break;
        }
    }
    std::cout << temp_message;
    
    return boardInput;
}