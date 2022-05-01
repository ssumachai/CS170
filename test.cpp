#include "problem.h"
#include "solutionalgorithms.h"

int main(){
    std::vector<int> problemB = {};
    std::vector<int> solution = {};
    std::vector<problem*> repeats = {};
    
    setup(solution, problemB);
    problem* tileBoard = new problem(problemB, number_rows, number_columns);
    repeats.push_back(tileBoard);

    char menu_input = ' ';
    while(menu_input != 'q'){
        std::cout << " -- Menu --\n[W] - Move Blank Up\n[A] - Move Left\n[S] - Move Down\n[D] - Move Right\n";
        std::cout << "[R] - Print Previous Board\n[P] - Print Current Board\n[Q] - Quit\n";
        std::cin >> menu_input;
        switch(menu_input){
            case 'w':
                if(tileBoard->moveUp() == NULL){
                    tileBoard = tileBoard;
                }
                else{
                    if(!searchRepeats(tileBoard->moveUp(), repeats)){
                        tileBoard = tileBoard->moveUp();
                        repeats.push_back(tileBoard);
                    }
                    else{
                        std::cout << "Duplicate Found, no move made\n";
                        tileBoard = tileBoard;
                    }
                }
                tileBoard->print();
                break;
            case 'a':
                if(tileBoard->moveLeft() == NULL){
                    tileBoard = tileBoard;
                }
                else{
                    if(!searchRepeats(tileBoard->moveLeft(), repeats)){
                        tileBoard = tileBoard->moveLeft();
                        repeats.push_back(tileBoard);
                    }
                    else{
                        std::cout << "Duplicate found, no move made\n";
                        tileBoard = tileBoard;
                    }
                }
                tileBoard->print();
                break;
            case 's':
                if(tileBoard->moveDown() == NULL){
                    tileBoard = tileBoard;
                }
                else{
                    if(!searchRepeats(tileBoard->moveDown(), repeats)){
                        tileBoard = tileBoard->moveDown();
                        repeats.push_back(tileBoard);
                    }
                    else{
                        std::cout << "Duplicate found, no move made\n";
                        tileBoard = tileBoard;
                    }
                }
                tileBoard->print();
                break;
            case 'd':
                if(tileBoard->moveRight() == NULL){
                    tileBoard = tileBoard;
                }
                else{
                    if(!searchRepeats(tileBoard->moveRight(), repeats)){
                        tileBoard = tileBoard->moveRight();
                        repeats.push_back(tileBoard);
                    }
                    else{
                        std::cout << "Duplicate found, no move made\n";
                        tileBoard = tileBoard;
                    }
                }
                tileBoard->print();
                break;
            case 'r':
                std::cout << "-- PREVIOUS BOARD -- \n";
                if(tileBoard->parent != NULL)
                    tileBoard->parent->print();
                else{
                    std::cout << "No Previous Board\n";
                }
                break;
            case 'p':
                std::cout << " -- CURRENT BOARD --\n";
                tileBoard->print();
                std::cout << std::endl;
                break;
            case 'q':
                break;
            default:
                std::cout << "Invalid Input, try again!\n";
                break;
        }
    }
}