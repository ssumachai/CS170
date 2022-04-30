#include "problem.h"

int main(){
    std::vector<int> problemB = {};
    std::vector<int> solution = {};
    
    setup(solution, problemB);
    problem* tileBoard = new problem(problemB, number_rows, number_columns);

    std::cout << "Misplaced Tiles: " << tileBoard->misplacedCost() << std::endl;   
    std::cout << "Manhattan Distance: " << tileBoard->euclideanCost() << std::endl;

    char menu_input = ' ';
    while(menu_input != 'q'){
        std::cout << " -- Menu --\n[W] - Move Blank Up\n[A] - Move Left\n[S] - Move Down\n[D] - Move Right\n[P] - Print Current Board\n[Q] - Quit\n";
        std::cin >> menu_input;
        switch(menu_input){
            case 'w':
                tileBoard = (tileBoard->moveUp() == NULL) ? tileBoard : tileBoard->moveUp();
                tileBoard->print();
                break;
            case 'a':
                tileBoard = (tileBoard->moveLeft() == NULL) ? tileBoard : tileBoard->moveLeft();
                tileBoard->print();
                break;
            case 's':
                tileBoard = (tileBoard->moveDown() == NULL) ? tileBoard : tileBoard->moveDown();
                tileBoard->print();
                break;
            case 'd':
                tileBoard = (tileBoard->moveRight() == NULL) ? tileBoard : tileBoard->moveRight();
                tileBoard->print();
                break;
            case 'p':
                std::cout << " -- CURRENT BOARD --\n";
                tileBoard->print();
                std::cout << std::endl;
                break;
            case 'q':
                break;
            default:
                break;
        }
    }
}